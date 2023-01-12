#include "mazengine/igame.h"

namespace mazengine {
	int IGame::InitialTick() { return 0; }

	int IGame::Tick(int status) {
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Tick(status);
			}
		}
		return 0;
	}

	int IGame::Draw() {
		for (SDL_Texture *background : backgrounds) {
			SDL_RenderCopy(Engine::renderer, background, NULL, NULL);
		}
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Draw();
			}
		}
		return 0;
	}

	int IGame::Present() {
		SDL_RenderPresent(Engine::renderer);
		return 0;
	}

	int IGame::React(int val) { return 0; }

} // namespace mazengine
