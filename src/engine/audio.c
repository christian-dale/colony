#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_Mixer.h>
#include "audio.h"

Sound* sounds;
int soundsCount = 0;

void Audio_Init() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	sounds = malloc(sizeof(Sound) * 32);
}

void Audio_AddSound(char* name, char* path, SoundType soundType) {
	Sound sound;
	memcpy(sound.name, name, 32);

	sound.soundData.mixChunk = NULL;
	sound.soundData.mixMusic = NULL;

	switch (soundType) {
		case SoundType_WAV:
			sound.soundData.mixChunk = Mix_LoadWAV(path);
			break;
		case SoundType_OGG:
			sound.soundData.mixMusic = Mix_LoadMUS(path);
			break;
		case SoundType_MP3:
			sound.soundData.mixMusic = Mix_LoadMUS(path);
			break;
	}

	sounds[soundsCount] = sound;
	soundsCount++;
}

void AudioPlay(char* name, int loop) {
	for (int i = 0; i < 32; i++) {
		if (strcmp(sounds[i].name, name) == 0) {
			if (sounds[i].soundData.mixChunk != NULL) {
				Mix_PlayChannel(-1, sounds[i].soundData.mixChunk, loop);
			} else {
				Mix_PlayMusic(sounds[i].soundData.mixMusic, loop);
			}
		}
	}
}