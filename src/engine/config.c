#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "../jsmn.h"
#include "../engine/config.h"
#include "../options.h"
#include "../misc.h"

Config config = { 0, 0 };

const char* Config_JSON_Retrieve_Token(const char* config, const int tokenStart, const int tokenEnd) {
	char* jsonKey = calloc(sizeof(char), 128);
	memcpy(jsonKey, &config[tokenStart], tokenEnd - tokenStart);
	jsonKey[tokenEnd - tokenStart] = '\0';
	return jsonKey;
}

const char* Config_JSON_Retrieve(const char* config, const char* name) {
	jsmn_parser parser;
	jsmntok_t token[128];

	jsmn_init(&parser);
	jsmn_parse(&parser, config, strlen(config), token, 128);

	// Search for the JSON value.
	for (int i = 0; i < COUNT(token); i++) {
		const char* jsonKey = Config_JSON_Retrieve_Token(config, token[i].start, token[i].end);

		if (strcmp(jsonKey, name) == 0) {
			// Receive the next token, the value.
			return Config_JSON_Retrieve_Token(config, token[i + 1].start, token[i + 1].end);
		}
	}

	return '\0';
}

void Config_Load() {
	FILE* fp = fopen("config.json", "r");

	char config[128];
	const int length = fread(config, sizeof(char), 128, fp);
	config[length] = '\0';
	fclose(fp);

	SCREEN_WIDTH = atoi(Config_JSON_Retrieve(config, "screenWidth"));
	SCREEN_HEIGHT = atoi(Config_JSON_Retrieve(config, "screenHeight"));
}