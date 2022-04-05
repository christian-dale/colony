#include "../ui/tutorial.h"
#include "../engine/engine.h"
#include "../ui/hud.h"

void Tutorial_Update() {
	switch (engine.options.tutorialState) {
		case TutorialState_01:
			DrawHUDMessage("SHIELD", "RESTORE THE SHIELDS");
			break;
	}
}
