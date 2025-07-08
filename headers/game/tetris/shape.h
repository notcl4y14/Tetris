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

typedef struct TetrisShapeBlock {
	int x, y;
} TetrisShapeBlock;

typedef struct TetrisShape {
	TetrisShapeBlock* blocks;
	int x, y;
	char type;
	char color;
} TetrisShape;

TetrisShape TetrisShape_new ();
void TetrisShape_init (TetrisShape* shape);
void TetrisShape_free (TetrisShape* shape);
void TetrisShape_rotateCW (TetrisShape* shape);
void TetrisShape_rotateCCW (TetrisShape* shape);
char TetrisShape_collides (TetrisShape* shape, TetrisGrid* grid, int offsetX, int offsetY);
void TetrisShape_applyToGrid (TetrisShape* shape, TetrisGrid* grid);
void TetrisShape_render (TetrisShape* shape);

#endif