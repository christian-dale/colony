#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "ecs.h"

int ECS_ENTITY_MAX_SIZE = 10000;
int ECS_componentCount = 0;
ComponentType ECS_componentTypes[32];
ComponentStorage ECS_componentStorage[32];
Component* ECS_components;
ECS_Entities entitiesStorage;
int ECS_entityCount = 1;

void ECS_Init() {
	ECS_components = calloc(sizeof(Component), ECS_ENTITY_MAX_SIZE);
}

ECS_Entity ECS_Create() {
	return ECS_entityCount++;
}

void ECS_AddComponent(char* name, int size) {
	ComponentType componentType = { 0 };
	componentType.size = size;
	memcpy(componentType.name, name, sizeof(componentType.name));
	ECS_componentTypes[ECS_componentCount] = componentType;
	memcpy(ECS_componentStorage[ECS_componentCount].type, name, 32);
	ECS_componentStorage[ECS_componentCount].components = calloc(sizeof(Component), 1000);
	ECS_componentStorage[ECS_componentCount].count = 0;
	ECS_componentCount++;
}


ECS_Entities ECS_QueryEntities(int count, ...) {
	va_list valist;
	va_start(valist, count);

	ECS_Entities* entitiesList = malloc(sizeof(ECS_Entities) * count);
	int componentIndex[8];

	// Loop over each function argument.
	for (int i = 0; i < count; i++) {
		char* component = va_arg(valist, char*);
		componentIndex[i] = ECS_ComponentStorageName(component);

		entitiesList[i].count = ECS_componentStorage[componentIndex[i]].count;
		entitiesList[i].entities = malloc(sizeof(ECS_Entity) * entitiesList[i].count);

		for (int j = 0; j < ECS_componentStorage[componentIndex[i]].count; j++) {
			entitiesList[i].entities[j] = ECS_componentStorage[componentIndex[i]].components[j].entity;
		}
	}

	free(entitiesStorage.entities);

	entitiesStorage.count = 32;
	entitiesStorage.entities = malloc(sizeof(ECS_Entity) * 32);

	ECS_QueryMatchingEntities(count, &entitiesStorage, entitiesList);

	va_end(valist);

	return entitiesStorage;
}

void ECS_QueryMatchingEntities(int count, ECS_Entities* entities, ECS_Entities* entitiesList) {
	int match = 0;
	int index = 0;
	ECS_Entity entity = 0;

	for (int i = 0; i < entitiesList[0].count; i++) {
		match = 0;
		entity = entitiesList[0].entities[i];

		for (int j = 1; j < count; j++) {
			for (int k = 0; k < entitiesList[j].count; k++) {
				if (entity == entitiesList[j].entities[k]) {
					match++;
				}
			}
		}

		if (match == count - 1) {
			entities->entities[index] = entity;
			index++;

			if (index >= entities->count - 1) {
				entities->entities = realloc(entities->entities, sizeof(ECS_Entity) * (entities->count * 2));
				entities->count = entities->count * 2;
			}
		}
	}

	entities->count = index;

	for (int i = 0; i < count; i++) {
		free(entitiesList[i].entities);
	}

	free(entitiesList);
}

bool ECS_HasComponent(ECS_Entity entity, char* name) {
	for (int i = 0; i < ECS_entityCount; i++) {
		if (strcmp(ECS_components[i].type, name) == 0 && ECS_components[i].entity == entity) {
			return true;
		}
	}

	return false;
}

int ECS_ComponentsCount(char* name) {
	return ECS_componentStorage[ECS_ComponentStorageName(name)].count;
}

ComponentType ECS_ComponentFromName(char* name) {
	ComponentType componentType = { 0 };

	for (int i = 0; i < ECS_componentCount; i++) {
		if (strcmp(ECS_componentTypes[i].name, name) == 0) {
			componentType = ECS_componentTypes[i];
		}
	}

	return componentType;
}

int ECS_ComponentStorageName(char* name) {
	for (int i = 0; i < ECS_componentCount; i++) {
		if (strcmp(ECS_componentStorage[i].type, name) == 0) {
			return i;
		}
	}

	return -1;
}

void ECS_SetComponent(ECS_Entity entity, char* name, void* component) {
	ComponentType componentType = ECS_ComponentFromName(name);
	void* ptrComponent = malloc(componentType.size);
	memcpy(ptrComponent, component, componentType.size);

	Component componentItem = { .entity = entity, .size = componentType.size, .data = ptrComponent };
	memcpy(componentItem.type, name, 32);

	int index = ECS_ComponentStorageName(name);
	ECS_componentStorage[index].components[ECS_componentStorage[index].count] = componentItem;
	ECS_componentStorage[index].count++;
}

void* ECS_GetComponent(ECS_Entity entity, char* name) {
	int index = ECS_ComponentStorageName(name);

	for (int i = 0; i < ECS_componentStorage[index].count; i++) {
		if (ECS_componentStorage[index].components[i].entity == entity) {
			return ECS_componentStorage[index].components[i].data;
		}
	}

	return NULL;
}

void* ECS_GetComponentIndex(char* name, int index) {
	return ECS_componentStorage[ECS_ComponentStorageName(name)].components[index].data;
}
