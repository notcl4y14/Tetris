#include <game/state.h>

#include <game/defines.h>

GameState GameState_new () {
	GameState state;
	GameState_init(&state);
	return state;
}

void GameState_init (GameState* state) {
	state->shouldQuit = false;
	state->isPaused = false;
	state->tickCount = 0;
}

void GameState_free (GameState* state) {
	state->shouldQuit = false;
	state->isPaused = false;
	state->tickCount = 0;
}