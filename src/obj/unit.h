#ifndef UNIT_H_
#define UNIT_H_

#include "../ecs/entity.h"
#include "../engine/color.h"
#include "../engine/vector.h"

enum UnitType { Unit_Empty, Unit_Lab, Unit_Hangar, Unit_Area, Unit_Gardens };

extern bool toggleUnitOptions;
extern Unit unitSelectedOptions;
extern Component_Transform transformSelectedOptions;

bool UnitAdjacent(Vec2 pos, int owner);

Component_Transform* UnitsAdjacent(Component_Transform unit);

void PlaceGrid(Component_Transform* unit, int x, int y);

void UnitToggle(Unit* worldUnits, int c);

void CreateColony(int enemy, Unit* units, int c);

void OnOptionsClose();

void OnOptionsCreateShip();

void DrawUnitOptions();

void UpdateUnit(Unit* unit, Component_Transform* transform);

Color UnitColorFromOwner(int owner);

void UnitDrawShield(Vec2 pos, Color color);

void DrawUnitTerritory(Unit* units, Component_Transform* transforms);

void DrawUnit(Unit* unit, Component_Transform* transform);

#endif