#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <game/defines.h>

#define GAME_FPS_TARGET 60

typedef struct GameState {
	bool shouldQuit;
	bool isPaused;
	int32 tickCount;
} GameState;

GameState GameState_new ();
void GameState_init (GameState* state);
void GameState_free (GameState* state);

#endif