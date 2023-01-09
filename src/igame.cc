#include "mazengine/igame.h"

namespace mazengine {
	int IGame::InitialTick() {
		return 0; // TODO
	}

	int IGame::Tick(int status) {
		for (Object *obj : objects) {
			obj->Tick(status);
		}
		return 0;
	}

	int IGame::Draw() {
		for (Object *obj : objects) {
			obj->Draw();
		}
		return 0;
	}

	int IGame::Present() {
		SDL_RenderPresent(renderer);
		return 0;
	}

	int IGame::React(int val) { return 0; }

} // namespace mazengine
