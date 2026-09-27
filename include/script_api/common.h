/// EVT scripting API functions available at all times.

// Command for reading all declarations in a source file:
// $ cat src/evt/*.c | grep "ApiStatus [^{]*" -o | sed "s/ $/;/"

#ifndef _SCRIPT_API_COMMON_H_
#define _SCRIPT_API_COMMON_H_

#include "../common.h"
#include "macros.h"

// battle.cpp is pulling windows.h and conflicting with PlaySound
#ifdef _WIN32
#undef PlaySound
#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/// @{
/// @name Map

/// Translates the given model's position.
/// @evtapi
/// @param modelID
/// @param x
/// @param y
/// @param z
API_CALLABLE(TranslateModel);

/// Rotates the model the given amount on the selected axis. `x`, `y`, and `z` are booleans
/// selecting which axes to rotate on.
/// @evtapi
/// @param modelID
/// @param angle
/// @param x
/// @param y
/// @param z
API_CALLABLE(RotateModel);

/// @evtapi
/// @param modelID
/// @param x
/// @param y
/// @param z
API_CALLABLE(ScaleModel);

/// Returns the given model's index.
/// @evtapi
/// @param modelID
/// @param outIndex
API_CALLABLE(GetModelIndex);

/// @evtapi
/// @param modelID
API_CALLABLE(InvalidateModelTransform);

/// Clones the given model.
/// @evtapi
/// @param modelID
/// @param newModelID
API_CALLABLE(CloneModel);

/// Returns the center of the given model.
/// @evtapi
/// @param modelID
/// @evtout LVar0 posX
/// @evtout LVar1 posY
/// @evtout LVar2 posZ
API_CALLABLE(GetModelCenter);

/// Sets a model's pannerID and sets the texture pan flag
/// @evtapi
/// @param modelID
/// @param panID
API_CALLABLE(SetTexPanner);

/// @evtapi
/// @param modelID
/// @param bool
API_CALLABLE(SetCustomGfxEnabled);

/// Either parameter can be -1 for no change.
/// @evtapi
/// @param modelID
/// @param customGfxIndex
/// @param fogType
API_CALLABLE(SetModelCustomGfx);

/// @evtapi
/// @param modelID
/// @param variation
API_CALLABLE(SetModelTexVariant);

/// Enables or disables texture panning on the given model.
/// @evtapi
/// @param modelID
/// @param bool
API_CALLABLE(EnableTexPanning);

/// Enables or disables the given model.
/// @evtapi
/// @param modelID
/// @param bool
API_CALLABLE(EnableModel);

/// Enables or disables the given group. `mode` can be 0 (disabled), 1 (enabled),
/// 2 (all others disabled), or 3 (all others enabled).
/// @evtapi
/// @param modelID
/// @param mode
API_CALLABLE(SetGroupVisibility);

/// Sets offsets for texture panners. `tile` is 0 for main or 1 for aux.
/// @evtapi
/// @param panID
/// @param tile
/// @param offsetU
/// @param offsetV
API_CALLABLE(SetTexPanOffset);

/// @evtapi
/// @param index
/// @param preDisplayList
/// @param postDisplayList
API_CALLABLE(SetCustomGfx);

/// @evtapi
/// @param index
/// @param preFunc
/// @param postFunc
API_CALLABLE(SetCustomGfxBuilders);

/// Sets flags for models. `bool` is 1 to set or 0 to clear.
/// @evtapi
/// @param modelID
/// @param flagbits
/// @param bool
API_CALLABLE(SetModelFlags);

/// @evtapi
/// @param modelID
API_CALLABLE(MakeTransformGroup);

/// @evtapi
/// @param modelID
/// @param bool
API_CALLABLE(SetTransformGroupEnabled);

/// Translates the given group's position.
/// @evtapi
/// @param modelID
/// @param x
/// @param y
/// @param z
API_CALLABLE(TranslateGroup);

/// Rotates the given group's position. `x`, `y`, and `z` are booleans selecting which axes
/// to rotate on.
/// @evtapi
/// @param modelID
/// @param angle
/// @param x
/// @param y
/// @param z
API_CALLABLE(RotateGroup);

/// @evtapi
/// @param modelID
/// @param x
/// @param y
/// @param z
API_CALLABLE(ScaleGroup);

/// @evtapi
/// @param modelID
/// @param outGroupID
API_CALLABLE(GetTransformGroup);

/// Enables or disables the given group.
/// @evtapi
/// @param modelID
/// @param bool
API_CALLABLE(EnableGroup);

/// @evtapi
/// @param copyIndex
/// @param modelID
/// @param bool
API_CALLABLE(MakeLocalVertexCopy);

/// Set flags for collider + siblings + children. `mode` is 0 to set bits, 1 to clear bits,
/// 2 to replace, or 3 to replace lowest 16 bits.
/// @evtapi
/// @param mode
/// @param colliderID
/// @param flags
API_CALLABLE(ModifyColliderFlags);

/// @evtapi
/// @param LavaResetList
API_CALLABLE(ResetFromLava);

/// Returns the center of the given collider.
/// @evtapi
/// @param colliderID
/// @evtout LVar0 posX
/// @evtout LVar1 posY
/// @evtout LVar2 posZ
API_CALLABLE(GetColliderCenter);

/// Associates a model with a collider and applies the model's transformation.
/// @evtapi
/// @param colliderID
/// @param modelID
API_CALLABLE(ParentColliderToModel);

/// Applies transformation from parent model.
/// @evtapi
/// @param colliderID
API_CALLABLE(UpdateColliderTransform);

/// Enables or disables the given zone.
/// @evtapi
/// @param zoneID
/// @param bool
API_CALLABLE(SetZoneEnabled);

/// Makes the player go to the given map and at the given entrance.
/// @evtapi
/// @param mapName
/// @param entryID
API_CALLABLE(GotoMap);

/// Makes the player go to the given map and at the given entrance with a unique fadeout effect.
/// @evtapi
/// @param mapName
/// @param entryID
/// @param transitionType
/// See [`ScreenTransitions`].
API_CALLABLE(GotoMapSpecial);

/// @evtapi
/// @param areaID
/// @param mapID
/// @param entryID
API_CALLABLE(GotoMapByID);

/// Returns the entryID of the Entry that the player entered the map from.
/// @evtapi
/// @param outEntryID
API_CALLABLE(GetEntryID);

/// Returns the mapID of the map the player is currently on.
/// @evtapi
/// @param outMapID
API_CALLABLE(GetMapID);

/// Returns the way the player loaded into the map, commonly used to put the player in the correct position for save blocks.
/// @evtapi
/// @param outLoadType
API_CALLABLE(GetLoadType);

/// @evtapi
/// @param modelID
/// @param renderMode
API_CALLABLE(SetRenderMode);

/// Plays the given sound at the given model.
/// @evtapi
/// @param modelID
/// @param soundID
/// @param SoundSpatializationFlags
API_CALLABLE(PlaySoundAtModel);

/// Plays the given sound at the given collider.
/// @evtapi
/// @param colliderID
/// @param soundID
/// @param SoundSpatializationFlags
API_CALLABLE(PlaySoundAtCollider);

/// @}

/// @{
/// @name Animated Model

/// @evtapi
API_CALLABLE(InitAnimatedModels);

/// @evtapi
/// @param animModelIndex
/// @param AnimatedModelTree
API_CALLABLE(LoadAnimatedModel);

/// @evtapi
/// @param animModelIndex
/// @param AnimatedModelTree
API_CALLABLE(LoadAnimatedMesh);

/// @evtapi
/// @param animModelIndex
/// @param ModelAnimation
API_CALLABLE(PlayModelAnimation);

/// @evtapi
/// @param animModelIndex
/// @param ModelAnimation
/// @param startTime
API_CALLABLE(PlayModelAnimationStartingFrom);

/// @evtapi
/// @param animModelIndex
/// @param ModelAnimation
API_CALLABLE(ChangeModelAnimation);

/// @evtapi
/// @param animModelIndex
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetAnimatedModelRootPosition);

/// @evtapi
/// @param animModelIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetAnimatedModelRootPosition);

/// @evtapi
/// @param animModelIndex
/// @param Dx
/// @param Dy
/// @param Dz
API_CALLABLE(AddAnimatedModelRootPosition);

/// @evtapi
/// @param animModelIndex
/// @param Rx
/// @param Ry
/// @param Rz
API_CALLABLE(SetAnimatedModelRootRotation);

/// @evtapi
/// @param animModelIndex
/// @param Sx
/// @param Sy
/// @param Sz
API_CALLABLE(SetAnimatedModelRootScale);

/// @evtapi
/// @param animModelIndex
/// @param renderMode
API_CALLABLE(SetAnimatedModelRenderMode);

/// @evtapi
/// @param animModelIndex
API_CALLABLE(DeleteAnimatedModel);

/// @evtapi
/// @param animModelIndex
/// @param bits
/// @param mode
API_CALLABLE(SetAnimatorFlags);

/// @evtapi
/// @param animatorIndex
/// @param nodeIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetAnimatedNodePosition);

/// @evtapi
/// @param animatorIndex
/// @param nodeIndex
/// @param outRotX
/// @param outRotY
/// @param outRotZ
API_CALLABLE(GetAnimatedNodeRotation);

/// @evtapi
/// @param animatorIndex
/// @param treeIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetAnimatedPositionByTreeIndex);

/// @evtapi
/// @param animatorIndex
/// @param treeIndex
/// @param outRotX
/// @param outRotY
/// @param outRotZ
API_CALLABLE(GetAnimatedRotationByTreeIndex);

/// @evtapi
/// @param animatorIndex
/// @param nodeID
/// @param bits
/// @param mode
API_CALLABLE(SetAnimatedNodeFlags);

/// @}

/// @{
/// @name Camera

/// @evtapi
/// @param camID
/// @param enabled
API_CALLABLE(SetCamEnabled);

/// @evtapi
/// @param camID
/// @param enabled
API_CALLABLE(SetCamNoDraw);

/// @evtapi
/// @param camID
/// @param type
/// @param vfov
/// @param nearClip
/// @param farClip
API_CALLABLE(SetCamPerspective);

/// @evtapi
/// @param camID
/// @param mode
API_CALLABLE(SetCamUpdateMode);

/// @evtapi
/// @param camID
/// @param outPitch
/// @param outYaw
/// @param outDist
/// @param outOffsetY
API_CALLABLE(GrabCamera);

/// @evtapi
/// @param camID
/// @param outDist
API_CALLABLE(GetInterpCamDist);

/// @evtapi
/// @param camID
/// @param outOffsetY
API_CALLABLE(GetInterpCamOffsetY);

/// @evtapi
/// @param camID
/// @param dist
API_CALLABLE(SetInterpCamDist);

/// @evtapi
/// @param camID
/// @param offsetY
API_CALLABLE(SetInterpCamOffsetY);

/// @evtapi
/// @param camID
/// @param pitch
/// @param yaw
/// @param dist
/// @param offsetY
API_CALLABLE(SetInterpCamParams);

/// @evtapi
/// @param camID
/// @param skipRecalc
/// @param dist
/// @param fovScale
/// @param pitch
API_CALLABLE(SetNoInterpCamParams);

/// @evtapi
/// @param camID
/// @param startX
/// @param startY
/// @param width
/// @param height
API_CALLABLE(SetCamViewport);

/// @evtapi
/// @param camID
/// @param R
/// @param G
/// @param B
API_CALLABLE(SetCamBGColor);

/// @evtapi
/// @param camID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetCamLookTarget);

/// @evtapi
/// @param camID
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(SetCamTarget);

/// @evtapi
/// @param camID
/// @param useTarget
/// @param posX
/// @param posY
/// @param posZ
/// @param time
API_CALLABLE(InterpCamTargetPos);

/// @evtapi
/// @param camID
/// @param mode
/// @param duration
/// @param magnitude
API_CALLABLE(ShakeCam);

/// @evtapi
/// @param camID
/// @param enabled
API_CALLABLE(SetCamLeadPlayer);

/// @evtapi
API_CALLABLE(EnableCameraFollowPlayerY);

/// @evtapi
API_CALLABLE(DisableCameraFollowPlayerY);

/// @evtapi
API_CALLABLE(EnableCameraLeadingPlayer);

/// @evtapi
API_CALLABLE(DisableCameraLeadingPlayer);

/// @evtapi
/// @param camID
/// @param scale
API_CALLABLE(SetCamLeadScale);

/// @evtapi
/// @param camID
/// @param easingPhase
/// @param targetType
API_CALLABLE(PanToTarget);

/// @evtapi
/// @param camID
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(UseSettingsFrom);

/// @evtapi
/// @param camID
/// @param CamSettings
API_CALLABLE(LoadSettings);

/// @evtapi
/// @param camID
/// @param controlType
/// @param bool
API_CALLABLE(SetCamType);

/// @evtapi
/// @param camID
/// @param boomPitch
/// @param viewPitch
API_CALLABLE(SetCamPitch);

/// @evtapi
/// @param camID
/// @param boomLength
API_CALLABLE(SetCamDistance);

/// @evtapi
/// @param camID
/// @param x
/// @param y
API_CALLABLE(SetCamPosA);

/// @evtapi
/// @param camID
/// @param x
/// @param y
API_CALLABLE(SetCamPosB);

/// @evtapi
/// @param camID
/// @param x
/// @param y
API_CALLABLE(SetCamPosC);

/// @evtapi
/// @param camID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPanTarget);

/// @evtapi
/// @param camID
/// @param speed
API_CALLABLE(SetCamSpeed);

/// @evtapi
/// @param camID
/// @param outType
/// @param outBool
API_CALLABLE(GetCamType);

/// @evtapi
/// @param camID
/// @param outBoomPitch
/// @param outViewPitch
API_CALLABLE(GetCamPitch);

/// @evtapi
/// @param camID
/// @param outBoomLength
API_CALLABLE(GetCamDistance);

/// @evtapi
/// @param camID
/// @param outX
/// @param outZ
API_CALLABLE(GetCamPosA);

/// @evtapi
/// @param camID
/// @param outX
/// @param outZ
API_CALLABLE(GetCamPosB);

/// @evtapi
/// @param camID
/// @param outX
/// @param outZ
API_CALLABLE(GetCamPosC);

/// @evtapi
/// @param camID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetCamPosition);

/// @evtapi
/// @param camID
/// @param endInterpValue
API_CALLABLE(WaitForCam);

/// @evtapi
/// @param camID
/// @param moveSpeed
/// @param x
/// @param y
/// @param z
/// @param boomLength
/// @param boomPitch
/// @param viewPitch
API_CALLABLE(SetCamProperties);

/// @evtapi
/// @param camID
/// @param moveSpeed
/// @param offsetX
/// @param boomLength
/// @param boomPitch
/// @param viewPitch
API_CALLABLE(AdjustCam);

/// @evtapi
/// @param camID
/// @param moveSpeed
API_CALLABLE(ResetCam);

/// @}

/// @{
/// @name NPC

/// @evtapi
/// @param npcID
/// @param initialAnim
API_CALLABLE(CreateNpc);

/// @evtapi
/// @param npcID
API_CALLABLE(DeleteNpc);

/// @evtapi
/// @param npcID
/// @param outPointer
API_CALLABLE(GetNpcPointer);

/// @evtapi
/// @param npcID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetNpcPos);

/// @evtapi
/// @param npcID
/// @param rX
/// @param rY
/// @param rZ
API_CALLABLE(SetNpcRotation);

/// @evtapi
/// @param npcID
/// @param pivotY
API_CALLABLE(SetNpcRotationPivot);

/// @evtapi
/// @param npcID
/// @param sX
/// @param sY
/// @param sZ
API_CALLABLE(SetNpcScale);

/// @evtapi
/// @param npcID
/// @param height
/// @param radius
API_CALLABLE(SetNpcCollisionSize);

/// @evtapi
/// @param npcID
/// @param speed
API_CALLABLE(SetNpcSpeed);

/// @evtapi
/// @param npcID
/// @param jumpScale
API_CALLABLE(SetNpcJumpscale);

/// @evtapi
/// @param npcID
/// @param animation
API_CALLABLE(SetNpcAnimation);

/// @evtapi
/// @param npcID
/// @param outAnimation
API_CALLABLE(GetNpcAnimation);

/// @evtapi
/// @param npcID
/// @param animationSpeed
API_CALLABLE(SetNpcAnimationSpeed);

/// @evtapi
/// @param npcID
/// @param goalX
/// @param goalZ
/// @param time
API_CALLABLE(NpcMoveTo);

/// @evtapi
/// @param npcID
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param duration
API_CALLABLE(NpcJump0);

/// @evtapi
/// @param npcID
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param duration
API_CALLABLE(NpcJump1);

/// @evtapi
/// @param npcID
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param duration
/// @param arcAmplitude
/// @param easing
API_CALLABLE(NpcFlyTo);

/// @evtapi
/// @param npcID
/// @param outYaw
API_CALLABLE(GetNpcYaw);

/// @evtapi
/// @param npcID
/// @param angle
API_CALLABLE(SetNpcYaw);

/// @evtapi
/// @param npcID
/// @param goalAngle
/// @param time
API_CALLABLE(InterpNpcYaw);

/// @evtapi
/// @param npcID
/// @param duration
API_CALLABLE(NpcFacePlayer);

/// @evtapi
/// @param turningNpcID
/// @param targetNpcID
/// @param duration
API_CALLABLE(NpcFaceNpc);

/// @evtapi
/// @param npcID
/// @param flags
/// @param mode
API_CALLABLE(SetNpcFlagBits);

/// @evtapi
/// @param npcID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetNpcPos);

/// @evtapi
/// @param npcID
/// @param channel
API_CALLABLE(SetNpcCollisionChannel);

/// @evtapi
/// @param npcID
/// @param animID
API_CALLABLE(SetNpcSprite);

/// @evtapi
/// @param npcID
/// @param enabled
API_CALLABLE(EnableNpcShadow);

/// @evtapi
/// @param npcID
/// @param enabled
API_CALLABLE(EnableNpcBlur);

/// @evtapi
/// @param npcID
API_CALLABLE(ClearPartnerMoveHistory);

/// @evtapi
/// @param npcID
API_CALLABLE(NpcSetHomePosToCurrent);

/// @evtapi
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartnerPos);

/// @evtapi
/// @param mode
API_CALLABLE(DisablePartnerAI);

/// @evtapi
API_CALLABLE(EnablePartnerAI);

/// @evtapi
API_CALLABLE(func_802CF54C);

/// @evtapi
/// @param value
API_CALLABLE(func_802CF56C);

/// @evtapi
/// @param partnerID
API_CALLABLE(BringPartnerOut);

/// @evtapi
API_CALLABLE(PutPartnerAway);

/// @evtapi
/// @param outPartnerID
API_CALLABLE(GetCurrentPartnerID);

/// @evtapi
/// @param outCanUse
API_CALLABLE(PartnerCanUseAbility);

/// @evtapi
/// @param outIsFlying
API_CALLABLE(PartnerIsFlying);

/// @evtapi
/// @param npcID
/// @param imgfxType
/// @param param2
/// @param param3
/// @param param4
/// @param param5
API_CALLABLE(SetNpcImgFXParams);

/// @evtapi
/// @param npcID
/// @param flags
API_CALLABLE(SetNpcImgFXFlags);

/// @evtapi
/// @param npcID
/// @param paletteSwapMode
API_CALLABLE(SetNpcPaletteSwapMode);

/// @evtapi
/// @param npcID
/// @param palIndexA
/// @param palIndexB
/// @param timeHoldA
/// @param timeAB
API_CALLABLE(SetNpcPaletteSwapLower);

/// @evtapi
/// @param npcID
/// @param palIndexA
/// @param palIndexB
/// @param timeHoldA
/// @param timeAB
/// @param timeHoldB
/// @param timeBA
/// @param palIndexC
/// @param palIndexD
API_CALLABLE(SetNpcPaletteSwapping);

/// @evtapi
/// @param npcID
/// @param index
/// @param npcDecoration
API_CALLABLE(SetNpcDecoration);

/// @evtapi
/// @param npcID
/// @param soundID
/// @param flags
API_CALLABLE(PlaySoundAtNpc);

/// @evtapi
/// @param npcID
/// @param renderMode
API_CALLABLE(SetNpcRenderMode);

/// @}

/// @{
/// @name Encounter

/// @evtapi
/// @param flags
/// @param mode
API_CALLABLE(SetEncounterStatusFlags);

/// @evtapi
/// @param outResult
API_CALLABLE(IsStartingConversation);

/// @evtapi
/// @param demoBattleIndex
API_CALLABLE(LoadDemoBattle);

/// @evtapi
API_CALLABLE(func_80044290);

/// @evtapi
/// @param createMode
/// @param npcGroupList
API_CALLABLE(MakeNpcs);

/// @evtapi
/// @param npcID
API_CALLABLE(RemoveNpc);

/// @evtapi
/// @param npcID
API_CALLABLE(RemoveEncounter);

/// @evtapi
/// @param outBattleOutcome
API_CALLABLE(GetBattleOutcome);

/// @evtapi
/// @param outValue
API_CALLABLE(func_800445A8);

/// @evtapi
/// @param outValue
API_CALLABLE(func_800445D4);

/// @evtapi
/// @param outTrigger
API_CALLABLE(GetOwnerEncounterTrigger);

/// @evtapi
API_CALLABLE(DoNpcDefeat);

/// @evtapi
API_CALLABLE(StartBattle);

/// @evtapi
/// @param songID
API_CALLABLE(StartBattleWith);

/// @evtapi
/// @param songID
API_CALLABLE(StartBossBattle);

/// @evtapi
/// @param songID
API_CALLABLE(SetBattleMusic);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcAI);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcIdle);

/// @evtapi
/// @param npcID
API_CALLABLE(RestartNpcAI);

/// @evtapi
/// @param npcID
/// @param enabled
API_CALLABLE(EnableNpcAI);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(SetNpcAux);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcAux);

/// @evtapi
/// @param npcID
API_CALLABLE(RestartNpcAux);

/// @evtapi
/// @param npcID
/// @param enabled
API_CALLABLE(EnableNpcAux);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcInteract);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcHit);

/// @evtapi
/// @param npcID
/// @param script
API_CALLABLE(BindNpcDefeat);

/// @evtapi
/// @param index
/// @param value
API_CALLABLE(SetSelfVar);

/// @evtapi
/// @param index
/// @param outValue
API_CALLABLE(GetSelfVar);

/// @evtapi
/// @param npcID
/// @param index
/// @param value
API_CALLABLE(SetNpcVar);

/// @evtapi
/// @param npcID
/// @param index
/// @param outValue
API_CALLABLE(GetNpcVar);

/// @evtapi
/// @param rotX
/// @param rotY
/// @param rotZ
API_CALLABLE(SetSelfRotation);

/// @evtapi
/// @param flags
API_CALLABLE(SetSelfEnemyFlags);

/// @evtapi
/// @param flags
/// @param mode
API_CALLABLE(SetSelfEnemyFlagBits);

/// @evtapi
/// @param hitboxIsActive
API_CALLABLE(SelfEnemyOverrideSyncPos);

/// @evtapi
/// @param outNpcID
API_CALLABLE(GetSelfNpcID);

/// @evtapi
API_CALLABLE(ClearDefeatedEnemies);

/// @evtapi
/// @param npcID
/// @param flags
/// @param mode
API_CALLABLE(SetEnemyFlagBits);

/// @evtapi
API_CALLABLE(func_8004572C);

/// @evtapi
/// @param index
/// @param outAnimation
API_CALLABLE(GetSelfAnimationFromTable);

/// @evtapi
/// @param value
API_CALLABLE(func_80045798);

/// @evtapi
/// @param instigatorValue
API_CALLABLE(SetOwnerInstigatorValue);

/// @evtapi
API_CALLABLE(SetBattleAsScripted);

/// @evtapi
/// @param outHitTier
API_CALLABLE(GetEncounterTriggerHitTier);

/// @evtapi
/// @param npcID
/// @param soundID
/// @param flags
API_CALLABLE(func_80045838);

/// @evtapi
/// @param outResult
API_CALLABLE(func_800458CC);

/// @evtapi
/// @param skipReaction
API_CALLABLE(OnPlayerFled);

/// @evtapi
/// @param npcID
/// @param tattleMsg
API_CALLABLE(SetTattleMessage);

/// @evtapi
API_CALLABLE(ShowMerleeCoinMessage);

/// @evtapi
API_CALLABLE(ShowMerleeRanOutMessage);

/// @evtapi
API_CALLABLE(FadeInMerlee);

/// @evtapi
API_CALLABLE(FadeOutMerlee);

/// @evtapi
API_CALLABLE(MerleeUpdateFX);

/// @evtapi
API_CALLABLE(MerleeStopFX);

/// @evtapi
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(PlayMerleeGatherFX);

/// @evtapi
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(PlayMerleeOrbFX);

/// @evtapi
API_CALLABLE(FadeBackgroundDarken);

/// @evtapi
API_CALLABLE(FadeBackgroundLighten);

/// @evtapi
/// @evtout LVar0 x
/// @evtout LVar1 y
/// @evtout LVar2 z
API_CALLABLE(GetCamLookAtObjVector);

/// @evtapi
/// @evtout LVar0 result
API_CALLABLE(HasMerleeCasts);

/// @evtapi
API_CALLABLE(OnDefeatEnemy);

/// @evtapi
API_CALLABLE(OnFleeBattleDrops);

/// @}

/// @{
/// @name Message

/// @evtapi
/// @param npcID
/// @param talkAnim
/// @param idleAnim
/// @param flags
/// @param messageID
API_CALLABLE(SpeakToPlayer);

/// @evtapi
/// @param npcID
/// @param talkAnim
/// @param idleAnim
/// @param flags
API_CALLABLE(EndSpeech);

/// @evtapi
/// @param npcID
/// @param talkAnim
/// @param idleAnim
/// @param flags
/// @param messageID
API_CALLABLE(ContinueSpeech);

/// @evtapi
/// @param npcID
/// @param talkAnim
/// @param idleAnim
/// @param flags
/// @param targetNpcID
/// @param messageID
API_CALLABLE(SpeakToNpc);

/// @evtapi
/// @param stringID
/// @param screenPosX
/// @param screenPosY
API_CALLABLE(ShowMessageAtScreenPos);

/// @evtapi
/// @param stringID
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(ShowMessageAtWorldPos);

/// @evtapi
/// @evtout LVar0 result
API_CALLABLE(CloseMessage);

/// @evtapi
/// @param stringID
API_CALLABLE(SwitchMessage);

/// @evtapi
/// @param options
/// @evtout LVar0 selectedIndex
API_CALLABLE(ShowChoice);

/// @evtapi
API_CALLABLE(CloseChoice);

/// @evtapi
API_CALLABLE(CancelMessage);

/// @evtapi
/// @param messageImageList
API_CALLABLE(SetMessageImages);

/// @evtapi
/// @param value
API_CALLABLE(func_802D0C94);

/// @evtapi
/// @param stringID
/// @param messageVarIndex
API_CALLABLE(SetMessageText);

/// @evtapi
/// @param value
/// @param messageVarIndex
API_CALLABLE(SetMessageValue);

/// @}

/// @{
/// @name Player

/// Hides the player's shadow if `hide` is `true`, shows it if `false`.
/// @evtapi
/// @param hide
/// See [`disable_player_shadow`], [`enable_player_shadow`].
API_CALLABLE(HidePlayerShadow);

/// Disables player physics if `disable` is `true`, enables it if `false`.
/// @evtapi
/// @param disable
/// See [`disable_player_static_collisions`], [`enable_player_static_collisions`].
API_CALLABLE(DisablePlayerPhysics);

/// Disables player and partner input, and disables the status menu.
/// @evtapi
/// @param disable
API_CALLABLE(DisablePlayerInput);

/// Disables player and partner input during a loading zone walk, but only when
/// the "DX: Prevent Loading Zone Storage" enhancement is enabled. Takes no arguments.
/// @evtapi
API_CALLABLE(DisableLoadingZoneInput);

/// Sets the player position. A `y` of `-1000` is used for hiding the player.
/// @evtapi
/// @param x
/// @param y
/// @param z
/// See [`GetPlayerPos`].
API_CALLABLE(SetPlayerPos);

/// Overrides the player collision size.
/// @evtapi
/// @param height
/// @param diameter
API_CALLABLE(SetPlayerCollisionSize);

/// Sets the move speed of the player for subequent [`PlayerMoveTo`] calls.
/// @evtapi
/// @param speed
/// See [`SetNpcSpeed`].
API_CALLABLE(SetPlayerSpeed);

/// @evtapi
/// @param jumpScale
API_CALLABLE(SetPlayerJumpscale);

/// @evtapi
/// @param playerAnim
API_CALLABLE(SetPlayerAnimation);

/// @evtapi
/// @param actionState
API_CALLABLE(SetPlayerActionState);

/// @evtapi
/// @param animationSpeed
API_CALLABLE(SetPlayerAnimationSpeed);

/// @evtapi
/// @param goalX
/// @param goalZ
/// @param time
API_CALLABLE(PlayerMoveTo);

/// @evtapi
/// @param targetX
/// @param targetZ
/// @param speed
API_CALLABLE(func_802D1270);

/// @evtapi
/// @param targetX
/// @param targetZ
/// @param duration
API_CALLABLE(func_802D1380);

/// @evtapi
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param arcHeight
API_CALLABLE(PlayerJump);

/// @evtapi
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param arcHeight
API_CALLABLE(PlayerJump1);

/// @evtapi
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param arcHeight
API_CALLABLE(PlayerJump2);

/// @evtapi
/// @param targetAngle
/// @param time
API_CALLABLE(InterpPlayerYaw);

/// @evtapi
/// @param facingTarget
/// @param targets
/// @param fixed
API_CALLABLE(PlayerFaceNpc);

/// @evtapi
/// @param outYaw
API_CALLABLE(GetPlayerTargetYaw);

/// @evtapi
/// @param bits
/// @param mode
API_CALLABLE(SetPlayerFlagBits);

/// @evtapi
/// @param outActionState
API_CALLABLE(GetPlayerActionState);

/// @evtapi
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPlayerPos);

/// @evtapi
/// @param outAnimation
API_CALLABLE(GetPlayerAnimation);

/// @evtapi
API_CALLABLE(FullyRestoreHPandFP);

/// @evtapi
API_CALLABLE(FullyRestoreSP);

/// Enables switching to the given partner.
/// @evtapi
/// @param partnerID
/// See [`DisablePartner`].
API_CALLABLE(EnablePartner);

/// Disables switching to the given partner.
/// @evtapi
/// @param partnerID
/// See [`EnablePartner`].
API_CALLABLE(DisablePartner);

/// @evtapi
/// @param moveDist
/// @param time
/// @evtout LVar1 goalPosX
/// @evtout LVar2 goalPosY
/// @evtout LVar3 goalPosZ
/// @evtout LVar5 offsetStep
API_CALLABLE(UseEntryHeading);

/// @evtapi
API_CALLABLE(func_802D2148);

/// @evtapi
/// @param moveDist
/// @param entryID
/// @evtout LVar1 goalPosX
/// @evtout LVar2 goalPosY
/// @evtout LVar3 goalPosZ
API_CALLABLE(UseExitHeading);

/// @evtapi
API_CALLABLE(WaitForPlayerTouchingFloor);

/// @evtapi
API_CALLABLE(func_802D2484);

/// @evtapi
/// @param outResult
API_CALLABLE(IsPlayerOnValidFloor);

/// @evtapi
API_CALLABLE(WaitForPlayerMoveToComplete);

/// @evtapi
API_CALLABLE(WaitForPlayerInputEnabled);

/// @evtapi
/// @param animPart
/// @param imgfxType
/// @param ...
API_CALLABLE(UpdatePlayerImgFX);

/// @evtapi
/// @param flags
API_CALLABLE(SetPlayerImgFXFlags);

/// @evtapi
/// @param targetX
/// @param targetZ
/// @param duration
API_CALLABLE(FacePlayerTowardPoint);

/// @evtapi
/// @param disabled
API_CALLABLE(DisablePulseStone);

/// @evtapi
/// @param outPartnerID
API_CALLABLE(GetPartnerInUse);

/// @evtapi
API_CALLABLE(ForceUsePartner);

/// @evtapi
API_CALLABLE(InterruptUsePartner);

/// Enables and disables the 8-bit Mario easter egg.
///
/// @evtapi
/// @param disable
///
/// Whilst active, the player uses a retro sprite, and the following actions are disabled:
/// - Spin dash
/// - Hammer
/// - Spin jump and tornado jump
/// - Menus
/// - Partner usage and partner switching
///
/// See [`PA_FLAG_8BIT_MARIO`].
API_CALLABLE(Disable8bitMario);

/// @evtapi
/// @param value
API_CALLABLE(func_802D2C14);

/// @evtapi
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPlayerPushVelocity);

/// @evtapi
/// @param soundID
/// @param flags
API_CALLABLE(PlaySoundAtPlayer);

/// @}

/// @{
/// @name Math

/// @evtapi
/// @param start
/// @param end
/// @param duration
/// @param easing
API_CALLABLE(MakeLerp);

/// @evtapi
/// @evtout LVar0 currentValue
/// @evtout LVar1 done
API_CALLABLE(UpdateLerp);

/// @evtapi
/// @param max
/// @param outValue
API_CALLABLE(RandInt);

/// @evtapi
/// @param npcID_A
/// @param npcID_B
/// @param outAngle
API_CALLABLE(GetAngleBetweenNPCs);

/// @evtapi
/// @param npcID
/// @param outAngle
API_CALLABLE(GetAngleToNPC);

/// @evtapi
/// @param npcID
/// @param outAngle
API_CALLABLE(GetAngleToPlayer);

/// @evtapi
/// @param X
/// @param Z
/// @param radius
API_CALLABLE(AwaitPlayerApproach);

/// @evtapi
/// @param X
/// @param Z
/// @param radius
/// @param outIsWithin
API_CALLABLE(IsPlayerWithin);

/// @evtapi
/// @param X
/// @param Z
/// @param radius
API_CALLABLE(AwaitPlayerLeave);

/// @evtapi
/// @param outX
/// @param outZ
/// @param radius
/// @param angle
API_CALLABLE(AddVectorPolar);

/// @evtapi
API_CALLABLE(func_802D4BDC);

/// @evtapi
API_CALLABLE(func_802D4C4C);

/// @evtapi
/// @param value
API_CALLABLE(func_802D4CC4);

/// @evtapi
/// @param value
API_CALLABLE(func_802D4D14);

/// @evtapi
API_CALLABLE(func_802D4D88);

/// @evtapi
/// @param time
/// @param VectorList
/// @param numVectors
/// @param easing
/// See [`GetNextPathPos`].
API_CALLABLE(LoadPath);

/// @evtapi
/// @param none
/// @evtout LVar0 done
/// @evtout LVar1 posX
/// @evtout LVar2 posY
/// @evtout LVar3 posZ
/// See [`LoadPath`].
API_CALLABLE(GetNextPathPos);

/// @evtapi
/// @param outDist
/// @param X1
/// @param Y1
/// @param X2
/// @param Y2
API_CALLABLE(GetDist2D);

/// @evtapi
/// @param timeFreezeMode
API_CALLABLE(SetTimeFreezeMode);

/// @evtapi
/// @param mode
/// @param bits
API_CALLABLE(ModifyGlobalOverrideFlags);

/// @evtapi
/// @param dest
/// @param src
API_CALLABLE(SetValueByRef);

/// @evtapi
/// @param src
/// @param outDest
API_CALLABLE(GetValueByRef);

/// @evtapi
/// @param gameMode
API_CALLABLE(SetGameMode);

/// @evtapi
/// @param angle
API_CALLABLE(ClampAngleInt);

/// @evtapi
/// @param angle
API_CALLABLE(ClampAngleFloat);

#ifdef VERSION_PAL
/// @evtapi
/// @param outLanguage
API_CALLABLE(GetLanguage);
#endif

/// Get current [`GameContext`] from [`GameStatus`].
/// Use this to tell whether the script is executing in world or battle.
/// @evtapi
/// @param outGameContext
API_CALLABLE(GetGameContext);

/// @}

/// @{
/// @name UI

/// @evtapi
/// @param enabled
API_CALLABLE(EnableWorldStatusBar);

/// @evtapi
/// @param show
API_CALLABLE(ShowWorldStatusBar);

/// @evtapi
/// @param show
API_CALLABLE(ShowCoinCounter);

/// @}

/// @{
/// @name Audio

/// @evtapi
API_CALLABLE(PollMusicEvents);

/// @evtapi
/// @param musicEventList
API_CALLABLE(RegisterMusicEvents);

/// @evtapi
/// @param musicPlayer
/// @param fadeTime
API_CALLABLE(FadeOutMusic);

/// @evtapi
/// @param musicPlayer
/// @param songID
/// @param variation
/// @param volume
API_CALLABLE(SetMusic);

/// @evtapi
/// @param musicPlayer
/// @param songID
/// @param variation
/// @param fadeTime
/// @param fadeStartVolume
/// @param fadeEndVolume
API_CALLABLE(FadeInMusic);

/// @evtapi
/// @param playerIndex
API_CALLABLE(EnableMusicProximityMix);

/// @evtapi
/// @param playerIndex
/// @param mix
/// @param state
API_CALLABLE(AdjustMusicProximityMix);

/// @evtapi
/// @param trackVolSet
API_CALLABLE(SetTrackVolumes);

/// @evtapi
API_CALLABLE(PopSong);

/// @evtapi
/// @param songID
/// @param variation
API_CALLABLE(PushSong);

/// @evtapi
API_CALLABLE(PopBattleSong);

/// @evtapi
API_CALLABLE(PushBattleSong);

/// @evtapi
/// @param songID
/// @param variation
API_CALLABLE(SetBattleSong);

/// @evtapi
/// @param time
API_CALLABLE(ClearAmbientSounds);

/// @evtapi
/// @param soundID
API_CALLABLE(PlayAmbientSounds);

/// @evtapi
/// @param soundID
API_CALLABLE(PlaySound);

/// @evtapi
/// @param soundID
/// @param volume
API_CALLABLE(PlaySoundWithVolume);

/// @evtapi
/// @param soundID
/// @param flags
/// @param x
/// @param y
/// @param z
API_CALLABLE(PlaySoundAt);

/// @evtapi
/// @param soundID
API_CALLABLE(StopSound);

/// @evtapi
/// @param soundID
API_CALLABLE(StopTrackingSoundPos);

/// @evtapi
/// @param doorSounds
API_CALLABLE(UseDoorSounds);

/// @evtapi
/// @param roomDoorSounds
API_CALLABLE(UseRoomDoorSounds);

/// @evtapi
/// @param soundID
/// @param spatializationFlags
/// @param x
/// @param y
/// @param z
API_CALLABLE(PlaySoundAtF);

/// @}

/// @{
/// @name Virtual Entity

/// @evtapi
API_CALLABLE(InitVirtualEntityList);

/// @evtapi
/// @param index
/// @param EntityModelScript
API_CALLABLE(CreateVirtualEntityAt);

/// @evtapi
/// @param outIndex
/// @param EntityModelScript
API_CALLABLE(CreateVirtualEntity);

/// @evtapi
/// @param outIndex
/// @param EntityModelScript
API_CALLABLE(CreateVirtualEntity_ALT);

/// @evtapi
/// @param index
API_CALLABLE(DeleteVirtualEntity);

/// @evtapi
/// @param index
/// @param EntityModelScript
API_CALLABLE(SetVirtualEntityRenderCommands);

/// @evtapi
/// @param index
/// @param posX
/// @param posY
/// @param posZ
API_CALLABLE(SetVirtualEntityPosition);

/// @evtapi
/// @param index
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetVirtualEntityPosition);

/// @evtapi
/// @param index
/// @param rotX
/// @param rotY
/// @param rotZ
API_CALLABLE(SetVirtualEntityRotation);

/// @evtapi
/// @param index
/// @param sx
/// @param sy
/// @param sz
API_CALLABLE(SetVirtualEntityScale);

/// @evtapi
/// @param index
/// @param speed
API_CALLABLE(SetVirtualEntityMoveSpeed);

/// @evtapi
/// @param index
/// @param gravity
API_CALLABLE(SetVirtualEntityJumpGravity);

/// @evtapi
/// @param index
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param time
API_CALLABLE(VirtualEntityMoveTo);

/// @evtapi
/// @param index
/// @param goalX
/// @param goalY
/// @param goalZ
/// @param time
API_CALLABLE(VirtualEntityJumpTo);

/// @evtapi
/// @param index
API_CALLABLE(VirtualEntityLandJump);

/// @evtapi
/// @param index
/// @param bits
API_CALLABLE(SetVirtualEntityFlags);

/// @evtapi
/// @param index
/// @param bits
/// @param mode
API_CALLABLE(SetVirtualEntityFlagBits);

/// @evtapi
/// @param index
/// @param mode
API_CALLABLE(SetVirtualEntityRenderMode);

/// @}

/// @{
/// @name Item

/// @evtapi
/// @evtout LVar0 choiceStatus
/// @evtout LVar1 selectedKeyItemSlot
API_CALLABLE(ShowKeyChoicePopup);

/// @evtapi
/// @evtout LVar0 choiceStatus
/// @evtout LVar1 selectedKeyItemSlot
API_CALLABLE(ShowConsumableChoicePopup);

/// @evtapi
/// @param keyItemSlot
API_CALLABLE(RemoveKeyItemAt);

/// @evtapi
/// @param itemSlot
API_CALLABLE(RemoveItemAt);

/// @evtapi
API_CALLABLE(CloseChoicePopup);

/// @evtapi
/// @param itemID
/// @param outHasItem
API_CALLABLE(HasItem);

/// @evtapi
/// @param itemID
/// @param outItemSlot
API_CALLABLE(FindItem);

/// @evtapi
/// @param itemID
/// @param outItemSlot
API_CALLABLE(AddItem);

/// @evtapi
/// @param itemID
/// @param outItemSlot
API_CALLABLE(RemoveItem);

/// @evtapi
/// @param itemID
/// @param spawnX
/// @param spawnY
/// @param spawnZ
/// @param itemSpawnMode
/// @param GameFlag
/// @param none
/// @evtout LVar0 itemEntityIndex
API_CALLABLE(MakeItemEntity);

/// @evtapi
/// @param itemID
/// @param spawnX
/// @param spawnY
/// @param spawnZ
/// @param itemSpawnMode
/// @param GameFlag
/// @param none
/// @evtout LVar0 itemEntityIndex
API_CALLABLE(DropItemEntity);

/// @evtapi
/// @param itemID
/// @param spawnX
/// @param spawnY
/// @param spawnZ
/// @param itemSpawnMode
/// @param GameFlag
/// @param none
/// @evtout LVar0 itemEntityIndex
API_CALLABLE(DropResizableItemEntity);

/// @evtapi
/// @param itemEntityIndex
API_CALLABLE(RemoveItemEntity);

/// @evtapi
/// @param itemEntityIndex
/// @param X
/// @param Y
/// @param Z
API_CALLABLE(SetItemPos);

/// @evtapi
/// @param itemEntityIndex
/// @param flags
/// @param mode
API_CALLABLE(SetItemFlags);

/// @evtapi
/// @param itemEntityIndex
/// @param alpha
API_CALLABLE(SetItemAlpha);

/// @evtapi
/// @param deltaCoins
/// @evtout LVar0 numCoins
API_CALLABLE(AddCoin);

/// @evtapi
/// @param deltaStarPoints
/// @evtout LVar0 numStarPoints
API_CALLABLE(AddStarPoints);

/// @evtapi
/// @param deltaStarPieces
/// @evtout LVar0 numStarPieces
API_CALLABLE(AddStarPieces);

/// @evtapi
/// @param itemID
/// @param bonusHP
/// @param bonusFP
API_CALLABLE(GetItemPower);

/// @evtapi
/// @param itemID
/// @param showInBattle
/// @param messageBoxFlags
API_CALLABLE(ShowGotItem);

/// @}

/// @{
/// @name Effect

/// @evtapi
/// @param x
/// @param y
/// @param z
/// @param amount
API_CALLABLE(ShowStartRecoveryShimmer);

/// @evtapi
/// @param x
/// @param y
/// @param z
/// @param amount
API_CALLABLE(ShowRecoveryShimmer);

/// @evtapi
/// @param posX
/// @param posY
/// @param posZ
/// @param angle
/// @param magnitude
/// @param duration
API_CALLABLE(func_802D7690);

/// @evtapi
/// @param npcID
/// @param emote
/// @param up
/// @param left
/// @param duration
/// @param useNpcPosAndSize
/// @param dX
/// @param dY
/// @param dZ
/// @param radius
API_CALLABLE(ShowEmote);

/// @evtapi
/// @param effectPtr
API_CALLABLE(RemoveEffect);

/// @evtapi
/// @param effectPtr
API_CALLABLE(DismissEffect);

/// @evtapi
/// @param effectPtr
API_CALLABLE(DismissItemOutline);

/// @evtapi
/// @param effectPtr
API_CALLABLE(func_802D7B74);

/// @evtapi
API_CALLABLE(InterpMotionBlurParams);

/// @evtapi
/// @param type
/// @param centerX0
/// @param centerY0
/// @param centerX1
/// @param centerY1
/// @param amount
/// @param duration
API_CALLABLE(SetMotionBlurParams);

/// @evtapi
/// @param npcID
/// @param type
/// @param pitch
/// @param emoterType
/// @param posX
/// @param posY
/// @param posZ
/// @param radius
/// @param duration
API_CALLABLE(ShowSweat);

/// @evtapi
/// @param npcID
/// @param type
/// @param pitch
/// @param emoterType
/// @param posX
/// @param posY
/// @param posZ
/// @param radius
/// @param outEffectPtr
API_CALLABLE(ShowSleepBubble);

/// @evtapi
/// @param effectPtr
/// @param timeLeft
API_CALLABLE(SetSleepBubbleTimeLeft);

// Undocumented because [PlayEffect] should be used instead
API_CALLABLE(PlayEffect_impl);

/// @}

/// @{
/// @name Entity

/// Creates an entity.
///
/// Takes a variable number of arguments depending on the entity blueprint.
/// @evtapi
/// @param blueprint
/// @param x
/// @param y
/// @param z
/// @param flags
/// @param ...
/// @param MAKE_ENTITY_END
/// @evtout LVar0 entityID
API_CALLABLE(MakeEntity);

/// @evtapi
/// @param cullMode
API_CALLABLE(SetEntityCullMode);

/// @evtapi
/// @param bool
API_CALLABLE(UseDynamicShadow);

/// @evtapi
/// @param Script
API_CALLABLE(AssignScript);

/// @evtapi
/// @param flagVar
API_CALLABLE(AssignSwitchFlag);

/// @evtapi
/// @param flagVar
API_CALLABLE(AssignBlockFlag);

/// @evtapi
/// @param flagVar
API_CALLABLE(AssignChestFlag);

/// @evtapi
/// @param flagVar
API_CALLABLE(AssignPanelFlag);

/// @evtapi
/// @param flagVar
API_CALLABLE(AssignCrateFlag);

/// Removes a trigger previously bound with [`BindTrigger`].
/// @evtapi
/// @param triggerPtr
API_CALLABLE(DeleteTrigger);

/// @}

/// @{
/// @name Sprite shading

/// @evtapi
/// @param preset
API_CALLABLE(SetSpriteShading);

/// @evtapi
/// @param enable
API_CALLABLE(EnableSpriteShading);

/// @}

/// @{
/// @name Demo

/// @evtapi
/// @param outState
API_CALLABLE(GetDemoState);

/// @evtapi
/// @param buttons
API_CALLABLE(DemoPressButton);

/// @evtapi
/// @param buttons
API_CALLABLE(DemoReleaseButton);

/// @evtapi
/// @param buttons
API_CALLABLE(DemoSetButtons);

/// @evtapi
/// @param radius
/// @param angle
API_CALLABLE(DemoJoystickRadial);

/// @evtapi
/// @param leftRight
/// @param upDown
API_CALLABLE(DemoJoystickXY);

/// @}

extern EvtScript EnemyNpcHit;
extern EvtScript EnemyNpcDefeat;

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
