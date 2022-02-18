INCLUDE = -I/Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_mixer/2.0.4_3/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include
LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_mixer/2.0.4_3/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib
SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

all :
	gcc main.c -o sound_effects $(INCLUDE) $(LIB) $(SDL)
