#ifndef ECS_H_
#define ECS_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t ECS_Entity;

typedef struct Component {
	ECS_Entity entity;
	char type[32];
	int size;
	void* data;
} Component;

typedef struct ComponentType {
	char name[32];
	int size;
} ComponentType;

typedef struct ComponentStorage {
	char type[32];
	Component* components;
	int count;
} ComponentStorage;

typedef struct ECS_Entities {
	int count;
	ECS_Entity* entities;
} ECS_Entities;

extern int ECS_ENTITY_MAX_SIZE;
extern int ECS_componentCount;
extern ComponentType ECS_componentTypes[32];
extern ComponentStorage ECS_componentStorage[32];
extern Component* ECS_components;
extern int ECS_entityCount;

void ECS_Init();

ECS_Entity ECS_Create();

void ECS_AddComponent(char* name, int size);

ECS_Entities ECS_QueryEntities(int count, ...);

void ECS_QueryMatchingEntities(int count, ECS_Entities* entities, ECS_Entities* entitiesList);

bool ECS_HasComponent(ECS_Entity entity, char* name);

int ECS_ComponentsCount(char* name);

ComponentType ECS_ComponentFromName(char* name);

int ECS_ComponentStorageName(char* name);

void ECS_SetComponent(ECS_Entity entity, char* name, void* component);

void* ECS_GetComponent(ECS_Entity entity, char* name);

void* ECS_GetComponentIndex(char* name, int index);

#endif