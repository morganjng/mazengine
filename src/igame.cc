#include "igame.h"

namespace mazengine {
	int IGame::Tick() {
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Tick();
			}
		}
		return 0;
	}

	int IGame::Draw() {
		if (background_idx != -1) {
			backgrounds[background_idx]->Draw(NULL, NULL);
		}
		for (Element *elem : elements) {
			if (elem != nullptr) {
				elem->Draw();
			}
		}
		return 0;
	}

	void IGame::AddElement(Element *element) { elements.push_back(element); }
} // namespace mazengine
