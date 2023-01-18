#include "mazengine/igame.h"

namespace mazengine {
	// int IGame::InitialTick() {
	// 	YAML::Node data =
	// 		YAML::LoadFile(Mazzycat::GetPaths()["data"] + name + ".yaml");
	// 	for (String val : data["elements"].as<StringVector>()) {
	// 		elements.push_back(Elements::Get(val, this));
	// 	}
	// 	for (String val : data["backgrounds"].as<StringVector>()) {
	// 		backgrounds.push_back(IMG_LoadTexture(
	// 			Engine::renderer, (Mazzycat::GetPaths()["img"] + val).c_str()));
	// 	}
	// 	return 0;
	// }

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

	int IGame::Present() {
		SDL_RenderPresent(Engine::renderer);
		return 0;
	}

	int IGame::React(int val) { return 0; }

} // namespace mazengine
