#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <game/defines.h>

#define GAME_FPS_TARGET 60

typedef struct GameState_s {
	bool shouldQuit;
	bool isPaused;
	int32 tickCount;
} GameState_s;

GameState_s GameState_new ();
void GameState_init (GameState_s* state);
void GameState_free (GameState_s* state);

#endif