#include <stdio.h>
#include "options.h"
#include "engine/config.h"
#include "engine/engine.h"
#include "engine/audio.h"
#include "engine/gameloop.h"
#include "player.h"

int main(int argc, char* args[]) {
	Engine_Init();

	Engine_SetTitle("Colony");

	printf("Colony\n");

	AudioPlay("Ambience01", -1);

	playerCurrency = 10e4;

	while (!config.quit) {
		GameLoop();
	}

	Engine_Quit();

	return 0;
}