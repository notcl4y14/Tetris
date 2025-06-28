#include <game/state.h>

#include <game/defines.h>

GameState_s GameState_new () {
	GameState_s state;
	GameState_init(&state);
	return state;
}

void GameState_init (GameState_s* state) {
	state->shouldQuit = false;
	state->isPaused = false;
	state->tickCount = 0;
}

void GameState_free (GameState_s* state) {
	state->shouldQuit = false;
	state->isPaused = false;
	state->tickCount = 0;
}