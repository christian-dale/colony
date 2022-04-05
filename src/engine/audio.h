#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL2/SDL_mixer.h>

typedef struct SoundData {
	Mix_Chunk* mixChunk;
	Mix_Music* mixMusic;
} SoundData;

typedef struct Sound {
	char name[32];
	SoundData soundData;
} Sound;

typedef enum SoundType {
	SoundType_WAV, SoundType_MP3, SoundType_OGG
} SoundType;

extern Sound* sounds;
extern int soundsCount;

void Audio_Init();

void Audio_AddSound(char* name, char* path, SoundType soundType);

void AudioPlay(char* name, int loop);

#endif