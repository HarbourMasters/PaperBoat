#ifndef BUILD_H
#define BUILD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// Paperboat Version information
extern char gBuildVersion[];
extern uint16_t gBuildVersionMajor;
extern uint16_t gBuildVersionMinor;
extern uint16_t gBuildVersionPatch;

extern char gGitBranch[];
extern char gGitCommitHash[];
extern char gGitCommitTag[];
extern char gBuildTeam[];
extern char gBuildDate[];
extern char gBuildMakeOption[];
#ifdef __cplusplus
}
#endif

#endif
