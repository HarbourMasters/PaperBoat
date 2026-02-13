#ifndef PM_PC_EFFECT_ALIASES_H
#define PM_PC_EFFECT_ALIASES_H

// Forward declarations for effect *_main functions.
// Without these, -Wno-implicit-function-declaration lets the compiler assume int return,
// which truncates 64-bit EffectInstance* pointers on the port.

// Returns struct EffectInstance*
struct EffectInstance* attack_result_text_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 appearVel, s32 duration);
struct EffectInstance* balloon_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* bombette_breaking_main(s32 type, s32 modelID, s32 treeIndex, f32 arg3, s32 arg4, s32 time);
struct EffectInstance* breaking_junk_main(s32 arg0, f32 x, f32 y, f32 z, f32 scale, s32 time);
struct EffectInstance* butterflies_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
struct EffectInstance* chapter_change_main(s32 arg0, f32 posX, f32 posY, f32 arg3, f32 arg4, s32 duration);
struct EffectInstance* chomp_drop_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, f32 arg6, s32 arg7, f32 arg8, s32 arg9);
struct EffectInstance* cold_breath_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, s32 duration);
struct EffectInstance* confetti_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* debuff_main(s32 type, f32 x, f32 y, f32 z);
struct EffectInstance* disable_x_main(s32 type, f32 x, f32 y, f32 z, s32 arg4);
struct EffectInstance* dust_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
struct EffectInstance* effect_46_main(s32 type, struct PlayerStatus* player, f32 scale, s32 duration);
struct EffectInstance* effect_63_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9);
struct EffectInstance* effect_65_main(s32 variation, f32 posX, f32 posY, f32 posZ, f32 scale, s32 duration);
struct EffectInstance* effect_75_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 scale, s32 arg5);
struct EffectInstance* effect_86_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* embers_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8, f32 arg9, f32 argA);
struct EffectInstance* energy_in_out_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* energy_orb_wave_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* fire_breath_main(s32 type, f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, s32 numExtra, s32 spawnDelay, s32 duration);
struct EffectInstance* fire_flower_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
struct EffectInstance* firework_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* firework_rocket_main(s32 variation, f32 centerX, f32 centerY, f32 centerZ, f32 velX, f32 velY, f32 velZ, f32 radius, s32 duration);
struct EffectInstance* flashing_box_shockwave_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 sizeX, f32 sizeY);
struct EffectInstance* floating_cloud_puff_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* floating_rock_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 floorY, f32 fallVelocity, f32 fallAccel, f32 scale, s32 duration);
struct EffectInstance* fright_jar_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* gather_magic_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* green_impact_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
struct EffectInstance* hieroglyphs_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 timeLeft);
struct EffectInstance* huff_puff_breath_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 angle, f32 speed, f32 scale, s32 timeLeft);
struct EffectInstance* ice_pillar_main(s32 arg0, f32 x, f32 y, f32 z, f32 scale, s32 arg5);
struct EffectInstance* ice_shard_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, s32 duration);
struct EffectInstance* lightning_bolt_main(s32 type, f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 scale, s32 duration);
struct EffectInstance* lightning_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
struct EffectInstance* lil_oink_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* merlin_house_stars_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
struct EffectInstance* misc_particles_main(s32 variation, f32 posX, f32 posY, f32 posZ, f32 scaleX, f32 scaleY, f32 arg6, s32 numParticles, s32 duration);
struct EffectInstance* motion_blur_flame_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* moving_cloud_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
struct EffectInstance* partner_buff_main(s32 useRandomValues, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 duration);
struct EffectInstance* peach_star_beam_main(s32 type, f32 x, f32 y, f32 z, f32 arg4, s32 duration);
struct EffectInstance* pink_sparkles_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
struct EffectInstance* purple_ring_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
struct EffectInstance* quizmo_answer_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
struct EffectInstance* quizmo_assistant_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* quizmo_audience_main(s32 arg0, f32 posX, f32 posY, f32 posZ);
struct EffectInstance* quizmo_stage_main(s32 arg0, f32 posX, f32 posY, f32 posZ);
struct EffectInstance* radial_shimmer_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* radiating_energy_orb_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* recover_main(s32 type, f32 posX, f32 posY, f32 posZ, s32 duration);
struct EffectInstance* red_impact_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* shape_spell_main(s32 isChild, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
struct EffectInstance* shimmer_burst_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* shimmer_wave_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7);
struct EffectInstance* shiny_flare_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* snaking_static_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, s32 timeLeft);
struct EffectInstance* snowfall_main(s32 arg0, s32 arg1);
struct EffectInstance* snowman_doll_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* something_rotating_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* spirit_card_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* squirt_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8);
struct EffectInstance* star_main(s32 type, f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 speed);
struct EffectInstance* star_outline_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 arg5);
struct EffectInstance* star_spirits_energy_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* stat_change_main(s32 arg0, f32 x, f32 y, f32 z, f32 scale, s32 time);
struct EffectInstance* static_status_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 numBolts, s32 duration);
struct EffectInstance* stop_watch_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* sun_main(s32 shineFromRight, f32 offsetX, f32 offsetY, f32 offsetZ, f32 arg4, s32 duration);
struct EffectInstance* tattle_window_main(s32 type, f32 x, f32 y, f32 z, f32 arg4, s32 duration);
struct EffectInstance* throw_spiny_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 time);
struct EffectInstance* thunderbolt_ring_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 lifeTime);
struct EffectInstance* tubba_heart_attack_main(s32 type, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 duration);
struct EffectInstance* underwater_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* water_block_main(s32 type, f32 x, f32 y, f32 z, f32 arg4, s32 duration);
struct EffectInstance* water_fountain_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 arg5);
struct EffectInstance* water_splash_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* waterfall_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
struct EffectInstance* whirlwind_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

// Returns void
void aura_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, struct EffectInstance** outEffect);
void big_smoke_puff_main(f32 x, f32 y, f32 z);
void big_snowflakes_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void blast_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void bulb_glow_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, struct EffectInstance** outEffect);
void cloud_puff_main(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void cloud_trail_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void damage_indicator_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 starsRadius, f32 starsAngle, s32 damageAmt, struct EffectInstance** effectOut);
void damage_stars_main(s32 type, f32 x, f32 y, f32 z, f32 rotAxisX, f32 rotAxisY, f32 rotAxisZ, s32 number);
void drop_leaves_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
void effect_3D_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, struct EffectInstance** outEffect);
void emote_main(s32 arg0, struct Npc* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, struct EffectInstance** arg8);
void ending_decals_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 arg4, struct EffectInstance** outEffect);
void energy_shockwave_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void explosion_main(s32 type, f32 x, f32 y, f32 z);
void falling_leaves_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void flame_main(s32 type, f32 arg1, f32 arg2, f32 arg3, f32 arg4, struct EffectInstance** outEffect);
void floating_flower_main(s32 type, f32 posX, f32 posY, f32 posZ, s32 duration);
void flower_splash_main(f32 posX, f32 posY, f32 posZ, f32 angle);
void flower_trail_main(s32 triggeredByNpc, f32 posX, f32 posY, f32 posZ, f32 angle, f32 direction);
void footprint_main(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void gather_energy_pink_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, s32 duration);
void got_item_outline_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 arg4, struct EffectInstance** outEffect);
void landing_dust_main(s32 type, f32 x, f32 y, f32 z, f32 arg4);
void lens_flare_main(s32 type, f32 posX, f32 posY, f32 posZ, s32 duration);
void light_rays_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, struct EffectInstance** outEffect);
void music_note_main(s32 type, f32 posX, f32 posY, f32 posZ);
void ring_blast_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 arg5);
void rising_bubble_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4);
void shattering_stones_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void shockwave_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void sleep_bubble_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, struct EffectInstance** arg6);
void smoke_burst_main(s32 arg0, f32 posX, f32 posY, f32 posZ, f32 arg4, s32 timeLeft);
void smoke_impact_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, f32 arg6, s32 arg7);
void smoke_ring_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void snowflake_main(f32 x, f32 y, f32 z, s32 arg3);
void sparkles_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void spiky_white_aura_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
void stars_burst_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);
void stars_orbiting_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 radius, s32 numStars, struct EffectInstance** outEffect);
void stars_shimmer_main(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, s32 numParts, s32 arg7);
void stars_spread_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void steam_burst_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void sweat_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 timeLeft);
void walking_dust_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void windy_leaves_main(s32 type, f32 arg1, f32 arg2, f32 arg3);

// Wrapper with different signature (not an alias)
void* fx_small_gold_sparkle(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

// Map fx_* names to *_main implementations for PC build.
#define fx_big_smoke_puff big_smoke_puff_main
#define fx_landing_dust landing_dust_main
#define fx_walking_dust walking_dust_main
#define fx_flower_splash flower_splash_main
#define fx_flower_trail flower_trail_main
#define fx_cloud_puff cloud_puff_main
#define fx_cloud_trail cloud_trail_main
#define fx_footprint footprint_main
#define fx_floating_flower floating_flower_main
#define fx_snowflake snowflake_main
#define fx_star star_main
#define fx_emote emote_main
#define fx_sparkles sparkles_main
#define fx_shape_spell shape_spell_main
#define fx_gather_energy_pink gather_energy_pink_main
#define fx_drop_leaves drop_leaves_main
#define fx_dust dust_main
#define fx_shattering_stones shattering_stones_main
#define fx_smoke_ring smoke_ring_main
#define fx_damage_stars damage_stars_main
#define fx_explosion explosion_main
#define fx_lens_flare lens_flare_main
#define fx_got_item_outline got_item_outline_main
#define fx_spiky_white_aura spiky_white_aura_main
#define fx_smoke_impact smoke_impact_main
#define fx_damage_indicator damage_indicator_main
#define fx_purple_ring purple_ring_main
#define fx_flame flame_main
#define fx_stars_burst stars_burst_main
#define fx_stars_shimmer stars_shimmer_main
#define fx_rising_bubble rising_bubble_main
#define fx_ring_blast ring_blast_main
#define fx_shockwave shockwave_main
#define fx_music_note music_note_main
#define fx_smoke_burst smoke_burst_main
#define fx_sweat sweat_main
#define fx_sleep_bubble sleep_bubble_main
#define fx_windy_leaves windy_leaves_main
#define fx_falling_leaves falling_leaves_main
#define fx_stars_spread stars_spread_main
#define fx_steam_burst steam_burst_main
#define fx_stars_orbiting stars_orbiting_main
#define fx_big_snowflakes big_snowflakes_main
#define fx_debuff debuff_main
#define fx_green_impact green_impact_main
#define fx_radial_shimmer radial_shimmer_main
#define fx_ending_decals ending_decals_main
#define fx_light_rays light_rays_main
#define fx_lightning lightning_main
#define fx_fire_breath fire_breath_main
#define fx_shimmer_burst shimmer_burst_main
#define fx_energy_shockwave energy_shockwave_main
#define fx_shimmer_wave shimmer_wave_main
#define fx_aura aura_main
#define fx_bulb_glow bulb_glow_main
#define fx_effect_3D effect_3D_main
#define fx_blast blast_main
#define fx_fire_flower fire_flower_main
#define fx_recover recover_main
#define fx_disable_x disable_x_main
#define fx_bombette_breaking bombette_breaking_main
#define fx_firework firework_main
#define fx_confetti confetti_main
#define fx_snowfall snowfall_main
#define fx_effect_46 effect_46_main
#define fx_gather_magic gather_magic_main
#define fx_attack_result_text attack_result_text_main
#define fx_flashing_box_shockwave flashing_box_shockwave_main
#define fx_balloon balloon_main
#define fx_floating_rock floating_rock_main
#define fx_chomp_drop chomp_drop_main
#define fx_quizmo_stage quizmo_stage_main
#define fx_radiating_energy_orb radiating_energy_orb_main
#define fx_quizmo_answer quizmo_answer_main
#define fx_motion_blur_flame motion_blur_flame_main
#define fx_energy_orb_wave energy_orb_wave_main
#define fx_merlin_house_stars merlin_house_stars_main
#define fx_quizmo_audience quizmo_audience_main
#define fx_butterflies butterflies_main
#define fx_stat_change stat_change_main
#define fx_snaking_static snaking_static_main
#define fx_thunderbolt_ring thunderbolt_ring_main
#define fx_squirt squirt_main
#define fx_water_block water_block_main
#define fx_waterfall waterfall_main
#define fx_water_fountain water_fountain_main
#define fx_underwater underwater_main
#define fx_lightning_bolt lightning_bolt_main
#define fx_water_splash water_splash_main
#define fx_snowman_doll snowman_doll_main
#define fx_fright_jar fright_jar_main
#define fx_stop_watch stop_watch_main
#define fx_effect_63 effect_63_main
#define fx_throw_spiny throw_spiny_main
#define fx_effect_65 effect_65_main
#define fx_tubba_heart_attack tubba_heart_attack_main
#define fx_whirlwind whirlwind_main
#define fx_red_impact red_impact_main
#define fx_floating_cloud_puff floating_cloud_puff_main
#define fx_energy_in_out energy_in_out_main
#define fx_tattle_window tattle_window_main
#define fx_shiny_flare shiny_flare_main
#define fx_huff_puff_breath huff_puff_breath_main
#define fx_cold_breath cold_breath_main
#define fx_embers embers_main
#define fx_hieroglyphs hieroglyphs_main
#define fx_misc_particles misc_particles_main
#define fx_static_status static_status_main
#define fx_moving_cloud moving_cloud_main
#define fx_effect_75 effect_75_main
#define fx_firework_rocket firework_rocket_main
#define fx_peach_star_beam peach_star_beam_main
#define fx_chapter_change chapter_change_main
#define fx_ice_shard ice_shard_main
#define fx_spirit_card spirit_card_main
#define fx_lil_oink lil_oink_main
#define fx_something_rotating something_rotating_main
#define fx_breaking_junk breaking_junk_main
#define fx_partner_buff partner_buff_main
#define fx_quizmo_assistant quizmo_assistant_main
#define fx_ice_pillar ice_pillar_main
#define fx_sun sun_main
#define fx_star_spirits_energy star_spirits_energy_main
#define fx_pink_sparkles pink_sparkles_main
#define fx_star_outline star_outline_main
#define fx_effect_86 effect_86_main
// fx_small_gold_sparkle handled separately due to signature mismatch
#endif
