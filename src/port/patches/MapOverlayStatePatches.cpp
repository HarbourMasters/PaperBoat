#include <cstdint>
#include <cstring>

#include "port/hooks/Events.h"
#include "port/ShipInit.hpp"

extern "C" {

extern float hos_04_TargetBoomLengthPre;
extern uint16_t* hos_04_ColorBufferPtr;
extern int32_t hos_04_TargetBoomLengthPost;
extern int32_t hos_04_TargetViewPitch;
extern uint32_t hos_04_IntroMessageState;
extern int32_t hos_04_IntroMessageAlpha;
extern void* hos_04_CurMessageList;

extern int32_t hos_05_D_802495DC_A3381C;
extern int32_t hos_05_D_802495E0_A33820;
extern float hos_05_StoryCameraAngle;
extern uint16_t* hos_05_ColorBufPtr;
extern int32_t hos_05_D_802498F8_A33B38;
extern int32_t hos_05_D_802498FC_A33B3C;
extern int32_t hos_05_StoryCameraShake1Angle;
extern float hos_05_StoryCameraShake1Scale;
extern int32_t hos_05_StoryCameraShake2Angle;
extern float hos_05_StoryCameraShake2Scale;
extern int32_t hos_05_UnusedBowserLeapTime;
extern int32_t hos_05_BowserHoverTime;
extern float hos_05_UnusedStoryCameraZoomAmt;
extern int32_t hos_05_UnusedKammyMoveTime;
extern int32_t hos_05_KammyHoverTime;
extern float hos_05_BoomLengthInhale;
extern int32_t hos_05_CamMoveInhaleTime;
extern float hos_05_BoomLengthExhale;
extern int32_t hos_05_CamMoveExhaleTime;
extern int32_t hos_05_FlyToStarRodTime;
extern int32_t hos_05_HoldStarRodTime;
extern float hos_05_PanAcrossRoomCamX;
extern float hos_05_PanAcrossRoomCamZ;
extern float hos_05_PanAcrossRoomAngle;
extern int32_t hos_05_PanAcrossRoomTime;
extern float hos_05_OrbitKammyFov;
extern float hos_05_OrbitKammyBoomLength;
extern float hos_05_OrbitKammyCamY;
extern float hos_05_OrbitKammyAngle;
extern int32_t hos_05_OrbitKammyTime;
extern float hos_05_FinalCamMoveBoomLength;
extern int32_t hos_05_FlyToBowserTime;
extern int32_t hos_05_StoryPageState;
extern int32_t hos_05_CurrentStoryPageIdx;
extern int32_t hos_05_CurrentStoryPageTime;
extern uint32_t hos_05_BowserSilhouetteTime;
extern int32_t hos_05_FadeAwayTapeTime;
extern int32_t hos_05_D_8024ACBC_A34EFC;
extern float hos_05_AnimBowser_FlyOff_Time;
extern float hos_05_AnimKammy_FlyOff_Time;
extern uint32_t hos_05_IntroMessageState;
extern int32_t hos_05_IntroMessageAlpha;
extern void* hos_05_CurMessageList;

extern float IntroCamStateA_BoomLength;
extern float IntroCamStateA_BoomPitch;
extern float IntroCamStateA_ViewPitch;
extern float IntroCamStateA_Vfov;
extern float IntroCamStateB_BoomLength;
extern float IntroCamStateB_BoomPitch;
extern float IntroCamStateB_ViewPitch;
extern float IntroCamStateB_Vfov;

} // extern "C"

static void ResetHos04State() {
    hos_04_TargetBoomLengthPre = 700.0f;
    hos_04_ColorBufferPtr = nullptr;
    hos_04_TargetBoomLengthPost = 0;
    hos_04_TargetViewPitch = 0;

    hos_04_IntroMessageState = 0;
    hos_04_IntroMessageAlpha = 0;
    hos_04_CurMessageList = nullptr;
}

static void ResetHos05State() {
    hos_05_D_802495DC_A3381C = 0;
    hos_05_D_802495E0_A33820 = 0;
    hos_05_StoryCameraAngle = 240.0f;
    hos_05_ColorBufPtr = nullptr;

    IntroCamStateA_BoomLength = 130.4f;
    IntroCamStateA_BoomPitch = 12.4f;
    IntroCamStateA_ViewPitch = -16.8f;
    IntroCamStateA_Vfov = 62.0f;
    IntroCamStateB_BoomLength = 130.4f;
    IntroCamStateB_BoomPitch = 12.4f;
    IntroCamStateB_ViewPitch = -16.8f;
    IntroCamStateB_Vfov = 62.0f;

    hos_05_D_802498F8_A33B38 = 0;
    hos_05_D_802498FC_A33B3C = 0;
    hos_05_StoryCameraShake1Angle = 0;
    hos_05_StoryCameraShake1Scale = 1.0f;
    hos_05_StoryCameraShake2Angle = 0;
    hos_05_StoryCameraShake2Scale = 12.0f;
    hos_05_UnusedBowserLeapTime = 0;
    hos_05_BowserHoverTime = 0;
    hos_05_UnusedStoryCameraZoomAmt = 30.0f;
    hos_05_UnusedKammyMoveTime = 0;
    hos_05_KammyHoverTime = 0;
    hos_05_BoomLengthInhale = 121.6f;
    hos_05_CamMoveInhaleTime = 0;
    hos_05_BoomLengthExhale = 90.0f;
    hos_05_CamMoveExhaleTime = 0;
    hos_05_FlyToStarRodTime = 0;
    hos_05_HoldStarRodTime = 0;
    hos_05_PanAcrossRoomCamX = 40.0f;
    hos_05_PanAcrossRoomCamZ = -40.0f;
    hos_05_PanAcrossRoomAngle = 45.0f;
    hos_05_PanAcrossRoomTime = 0;
    hos_05_OrbitKammyFov = 50.0f;
    hos_05_OrbitKammyBoomLength = 246.1f;
    hos_05_OrbitKammyCamY = 200.0f;
    hos_05_OrbitKammyAngle = 25.0f;
    hos_05_OrbitKammyTime = 0;
    hos_05_FinalCamMoveBoomLength = 130.0f;
    hos_05_FlyToBowserTime = 0;

    hos_05_StoryPageState = 0; // STORY_PAGE_STATE_BEGIN
    hos_05_CurrentStoryPageIdx = 0;
    hos_05_CurrentStoryPageTime = 0;
    hos_05_BowserSilhouetteTime = 0;
    hos_05_FadeAwayTapeTime = 30;
    hos_05_D_8024ACBC_A34EFC = 0x00010019;
    hos_05_AnimBowser_FlyOff_Time = 0.0f;
    hos_05_AnimKammy_FlyOff_Time = 0.0f;

    hos_05_IntroMessageState = 0;
    hos_05_IntroMessageAlpha = 0;
    hos_05_CurMessageList = nullptr;
}

static void RegisterMapOverlayStatePatches_Init() {
    REGISTER_LISTENER(OnMapLoad, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        const char* mapName = ((OnMapLoad*)event)->mapName;

        if (mapName == nullptr) {
            return;
        }
        if (strcmp(mapName, "hos_04") == 0) {
            ResetHos04State();
        } else if (strcmp(mapName, "hos_05") == 0) {
            ResetHos05State();
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterMapOverlayStatePatches_Init);
