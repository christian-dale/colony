SOURCE = $(wildcard src/*.c src/ecs/* src/engine/* src/obj/* src/ui/*)
CFLAGS = -Wall -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lSDL2_Mixer -lSDL2_ttf

compile: $(SOURCE)
	gcc $^ $(CFLAGS) -o colony