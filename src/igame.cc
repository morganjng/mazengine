#include "mazengine/igame.h"

namespace mazengine {
	int IGame::Tick(int status) {
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Tick(status);
			}
		}
		return 0;
	}

	int IGame::Draw() {
		if (background_idx != -1) {
			Engine::Draw(backgrounds[background_idx], NULL, NULL);
		}
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Draw();
			}
		}
		return 0;
	}

} // namespace mazengine
