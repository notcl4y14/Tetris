#ifndef GAME_TETRIS_STATE_H
#define GAME_TETRIS_STATE_H

#include <game/tetris/block.h>
#include <game/tetris/grid.h>
#include <game/tetris/shape.h>

typedef struct TetrisState_s {
	TetrisGrid_s grid;
	TetrisShape_s shape;
	char isPlaying;
	char isOver;
	int score;
	int highScore;
} TetrisState_s;

TetrisState_s TetrisState_new ();
void TetrisState_init (TetrisState_s* state);
void TetrisState_free (TetrisState_s* state);
void TetrisState_start (TetrisState_s* state);
void TetrisState_stop (TetrisState_s* state);
void TetrisState_moveLeft (TetrisState_s* state);
void TetrisState_moveRight (TetrisState_s* state);
void TetrisState_rotate (TetrisState_s* state);
void TetrisState_changeShape (TetrisState_s* state, char shapeType);
void TetrisState_update (TetrisState_s* state);
void TetrisState_render (TetrisState_s* state);

#endif