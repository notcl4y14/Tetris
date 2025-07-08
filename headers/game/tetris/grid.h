#ifndef GAME_TETRIS_GRID_H
#define GAME_TETRIS_GRID_H

#define TETRIS_GRID_WIDTH 8
#define TETRIS_GRID_HEIGHT 16

#define TETRIS_RENDER_GRID_X 10
#define TETRIS_RENDER_GRID_Y 10
#define TETRIS_RENDER_GRID_SCALE 24
#define TETRIS_RENDER_GRID_SPACE 4

#include <game/tetris/block.h>

typedef struct TetrisGrid {
	TetrisBlock* blocks;
	int width;
	int height;
} TetrisGrid;

TetrisGrid TetrisGrid_new (int w, int h);
void TetrisGrid_init (TetrisGrid* grid, int w, int h);
void TetrisGrid_free (TetrisGrid* grid);
TetrisBlock TetrisGrid_get (TetrisGrid* grid, int x, int y);
void TetrisGrid_set (TetrisGrid* grid, int x, int y, TetrisBlock block);
void TetrisGrid_clear (TetrisGrid* grid);
void TetrisGrid_processLines (TetrisGrid* grid, int* score);
void TetrisGrid_fallLines (TetrisGrid* grid);
void TetrisGrid_emptyLines (TetrisGrid* grid, int* score);
void TetrisGrid_render (TetrisGrid* grid);

#endif