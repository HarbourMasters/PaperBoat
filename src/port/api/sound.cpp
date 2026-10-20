#ifdef ENABLE_SCRIPTING

#include "port/api/sound.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/audio/ModSound.h"
#include "port/hooks/Events.h"

#include "common.h"
#undef Add // an EVT macro, clashes with ModSound::Add

#include <ship/Context.h>
#include <ship/resource/File.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <spdlog/spdlog.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace {

constexpr u16 kMusicPlaying = 0x01; // MUSIC_FLAG_PLAYING

struct Replacement {
    int sound;
    int32_t loopStart;
    std::string owner;
};

std::unordered_map<int, std::string> sSounds;
std::unordered_map<int32_t, Replacement> sReplacements;
// Song whose replacement plays, -1 while none does.
int32_t sReplacing = -1;
// While music started with C_PlayMusic plays, replacements wait.
bool sExplicitMusic = false;

int Register(const uint8_t* data, size_t size, const char* what) {
    std::vector<int16_t> samples;
    if (!ModSound::Decode(data, size, samples)) {
        SPDLOG_ERROR("Sound: {} is not a WAV, MP3 or FLAC file", what);
        return -1;
    }
    const int sound = ModSound::Add(std::move(samples));
    sSounds[sound] = ModOwner::Current();
    return sound;
}

// Follows the main music player: the game's song decides which replacement, if any, plays.
void FollowSong(const MusicControlData* music) {
    if (music != &gMusicControlData[0]) {
        return;
    }
    if (sExplicitMusic) {
        if (ModSound::MusicActive()) {
            return;
        }
        sExplicitMusic = false;
    }
    const bool playing = (music->flags & kMusicPlaying) != 0;
    auto it = playing ? sReplacements.find(music->requestedSongID) : sReplacements.end();
    const int32_t wanted = it != sReplacements.end() ? music->requestedSongID : -1;
    if (wanted == sReplacing) {
        return;
    }
    if (wanted >= 0) {
        ModSound::PlayMusic(it->second.sound, it->second.loopStart);
    } else {
        ModSound::StopMusic();
    }
    sReplacing = wanted;
}

void InitSoundApi() {
    REGISTER_LISTENER(MusicControlPostUpdate, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        FollowSong(reinterpret_cast<MusicControlPostUpdate*>(event)->musicControl);
    });
    ModOwner::AddReleaser([](const std::string& mod) {
        std::vector<int> sounds;
        for (const auto& [sound, owner] : sSounds) {
            if (owner == mod) {
                sounds.push_back(sound);
            }
        }
        for (int sound : sounds) {
            C_UnregisterSound(sound);
        }
        std::erase_if(sReplacements, [&](const auto& entry) { return entry.second.owner == mod; });
    });
}

RegisterShipInitFunc sInitSoundApi(InitSoundApi);

} // namespace

extern "C" int C_RegisterSound(const char* path) {
    if (path == nullptr) {
        return -1;
    }
    auto archives = Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager();
    const auto file = archives->LoadFile(path);
    if (file == nullptr || !file->IsLoaded || file->Buffer == nullptr) {
        SPDLOG_ERROR("Sound: could not read {}", path);
        return -1;
    }
    return Register((const uint8_t*) file->Buffer->data(), file->Buffer->size(), path);
}

extern "C" int C_RegisterSoundData(const uint8_t* data, uint32_t size) {
    return Register(data, size, "the data");
}

extern "C" void C_UnregisterSound(int sound) {
    if (sSounds.erase(sound) == 0) {
        return;
    }
    for (auto it = sReplacements.begin(); it != sReplacements.end();) {
        if (it->second.sound == sound) {
            if (sReplacing == it->first) {
                sReplacing = -1;
            }
            it = sReplacements.erase(it);
        } else {
            ++it;
        }
    }
    ModSound::Remove(sound);
}

extern "C" uint32_t C_SoundLength(int sound) {
    return (uint32_t) ModSound::Length(sound);
}

extern "C" int C_PlaySound(int sound, float volume, float pan) {
    return ModSound::Play(sound, volume, pan);
}

extern "C" void C_StopSound(int voice) {
    ModSound::Stop(voice);
}

extern "C" int C_IsSoundPlaying(int voice) {
    return ModSound::Playing(voice);
}

extern "C" void C_PlayMusic(int sound, int32_t loop_start) {
    sReplacing = -1;
    sExplicitMusic = true;
    ModSound::PlayMusic(sound, loop_start);
}

extern "C" void C_StopMusic(void) {
    sReplacing = -1;
    sExplicitMusic = false;
    ModSound::StopMusic();
}

extern "C" void C_ReplaceSong(int32_t song, int sound, int32_t loop_start) {
    if (sound < 0 || !sSounds.contains(sound)) {
        sReplacements.erase(song);
        return;
    }
    sReplacements[song] = { sound, loop_start, ModOwner::Current() };
    // Takes effect on the next music update, also for the song playing now.
    sReplacing = sReplacing == song ? -1 : sReplacing;
}

#endif
