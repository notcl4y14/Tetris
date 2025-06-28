compile:
	gcc $(wildcard source/*.c \
	               source/tetris/*.c) \
	    -Iheaders \
	    -Lexternal/bin \
	    -lSDL3 \
		-lSDL3_ttf \
	    -Iexternal/include -g