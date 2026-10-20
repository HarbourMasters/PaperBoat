#pragma once

#include <stdint.h>

#include "api.h"

// Mod messages take section 0x80, past the game's own sections (0x00 to 0x2E). Their IDs work anywhere the game
// takes a message ID: item and move names, EVT dialogue such as SpeakToPlayer, and tattles.
#define C_MSG_FIRST 0x00800000
#define C_MSG_LAST  0x0080FFFF

// Text is UTF-8. A new line is "\n", and these tags insert the game's control codes:
//   <<NEXT>>          wait for the player, then start a new page
//   <<WAIT>>          wait for the player
//   <<PAUSE n>>       pause for n frames
//   <<COLOR n>>       text colour, a MSG_PAL_* value
//   <<STYLE n>>       window style, a MSG_STYLE_* value without arguments, e.g. 1 for MSG_STYLE_RIGHT
//   <<A>> <<B>> <<L>> <<R>> <<Z>> <<START>> <<C-UP>> <<C-DOWN>> <<C-LEFT>> <<C-RIGHT>>   button icons
//   <<HEART>> <<STAR>> <<NOTE>>
//   <<RAW xx xx ...>> bytes in hex, for any other control code
// Characters the game's font lacks show as "?".

// Registers a message from ModInit. Returns its message ID, or 0 when it can't. A mod registering the same id
// again gets the same message ID with the new text.
PB_API int32_t C_RegisterMessage(const char* id, const char* text);
// Unregisters a message. The game shows it as empty until it is registered again.
PB_API void C_UnregisterMessage(int32_t msgID);
// Message ID of the registered message with this id, or 0.
PB_API int32_t C_FindMessage(const char* id);

// Replaces the text of one of the game's messages, e.g. MESSAGE_ID(0x26, 0x009), the name of the Mushroom. The newest
// override wins, and a mod's overrides end when it unloads. Returns 1 when the message was replaced.
PB_API int C_OverrideMessage(int32_t msgID, const char* text);
// Removes this mod's override of a message.
PB_API void C_RemoveMessageOverride(int32_t msgID);

// Encodes text into the game's character set, followed by the end code. Writes at most capacity bytes to out and
// returns the size of the whole encoding, so a call with a NULL out measures it.
PB_API uint32_t C_EncodeText(const char* text, uint8_t* out, uint32_t capacity);
