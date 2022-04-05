#ifndef HUD_H_
#define HUD_H_

#include "../ecs/entity.h"

extern bool toggleUnitSelect;
extern UnitUI selectedUnit;

void PlaceUnit(Unit* worldUnits);

void SelectHUDItem(UnitUI unit);

void DrawHUDUnit(UnitUI unit, int index);

void DrawHUDUnits(UnitUI* units, int c);

void DrawHUDStats(int playerCurrency, int energyStorage);

void DrawHUDTooltip(int x, int y);

void DrawHUDMessage(char* title, char* str);

void DrawHUDInfo(int x, int y, int parent, int level);

void DrawHUDHealth(int x, int y, int maxHealth, int health);

void DrawHUD();

#endif