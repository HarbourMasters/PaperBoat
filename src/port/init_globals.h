#ifndef INIT_GLOBALS_H
#define INIT_GLOBALS_H

/**
 * Initialize all game globals to zero.
 *
 * BSS section globals are not automatically zero-initialized on the PC port,
 * which can cause crashes when garbage values are read. This function must be
 * called before the game loop starts.
 */
void init_game_globals(void);

#endif // INIT_GLOBALS_H
