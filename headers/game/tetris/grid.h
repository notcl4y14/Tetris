#ifndef GAME_TETRIS_GRID_H
#define GAME_TETRIS_GRID_H

#define TETRIS_GRID_WIDTH 8
#define TETRIS_GRID_HEIGHT 16

#define TETRIS_RENDER_GRID_X 10
#define TETRIS_RENDER_GRID_Y 10
#define TETRIS_RENDER_GRID_SCALE 24
#define TETRIS_RENDER_GRID_SPACE 4

#include <game/tetris/block.h>

typedef struct TetrisGrid_s {
	TetrisBlock_s* blocks;
	int width;
	int height;
} TetrisGrid_s;

TetrisGrid_s TetrisGrid_new (int w, int h);
void TetrisGrid_init (TetrisGrid_s* grid, int w, int h);
void TetrisGrid_free (TetrisGrid_s* grid);
TetrisBlock_s TetrisGrid_get (TetrisGrid_s* grid, int x, int y);
void TetrisGrid_set (TetrisGrid_s* grid, int x, int y, TetrisBlock_s block);
void TetrisGrid_clear (TetrisGrid_s* grid);
void TetrisGrid_processLines (TetrisGrid_s* grid, int* score);
void TetrisGrid_fallLines (TetrisGrid_s* grid);
void TetrisGrid_emptyLines (TetrisGrid_s* grid, int* score);
void TetrisGrid_render (TetrisGrid_s* grid);

#endif