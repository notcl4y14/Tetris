#ifndef GAME_TETRIS_STATE_H
#define GAME_TETRIS_STATE_H

#include <game/tetris/block.h>
#include <game/tetris/grid.h>
#include <game/tetris/shape.h>

typedef struct TetrisState {
	TetrisGrid grid;
	TetrisShape currentShape;
	char isPlaying;
	char isOver;
	int score;
	int highScore;
} TetrisState;

TetrisState TetrisState_new ();
void TetrisState_init (TetrisState* state);
void TetrisState_free (TetrisState* state);
void TetrisState_start (TetrisState* state);
void TetrisState_stop (TetrisState* state);
void TetrisState_moveLeft (TetrisState* state);
void TetrisState_moveRight (TetrisState* state);
void TetrisState_rotate (TetrisState* state);
void TetrisState_changeShape (TetrisState* state, char shapeType);
void TetrisState_update (TetrisState* state);
void TetrisState_render (TetrisState* state);

#endif