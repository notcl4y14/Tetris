#ifndef GAME_TETRIS_SHAPE_H
#define GAME_TETRIS_SHAPE_H

#define TETRIS_SHAPE_BLOCK_AMOUNT 4

#define TETRIS_SHAPE_TYPE_I 0
#define TETRIS_SHAPE_TYPE_O 1
#define TETRIS_SHAPE_TYPE_S 2
#define TETRIS_SHAPE_TYPE_Z 3
#define TETRIS_SHAPE_TYPE_L 4
#define TETRIS_SHAPE_TYPE_J 5
#define TETRIS_SHAPE_TYPE_T 6

#include <game/tetris/block.h>
#include <game/tetris/grid.h>

typedef struct TetrisShapeBlock_s {
	int x, y;
} TetrisShapeBlock_s;

typedef struct TetrisShape_s {
	TetrisShapeBlock_s* blocks;
	int x, y;
	char type;
	char color;
} TetrisShape_s;

TetrisShape_s TetrisShape_new ();
void TetrisShape_init (TetrisShape_s* shape);
void TetrisShape_free (TetrisShape_s* shape);
void TetrisShape_rotateCW (TetrisShape_s* shape);
void TetrisShape_rotateCCW (TetrisShape_s* shape);
char TetrisShape_collides (TetrisShape_s* shape, TetrisGrid_s* grid, int offsetX, int offsetY);
void TetrisShape_applyToGrid (TetrisShape_s* shape, TetrisGrid_s* grid);
void TetrisShape_render (TetrisShape_s* shape);

#endif