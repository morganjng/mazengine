#include "mazengine/mazengine.h"

namespace mazengine {
	std::vector<Future *> Engine::futures = *new std::vector<Future *>;

	void Future::Load() {
		this->texture = IMG_LoadTexture(Engine::renderer, this->path.c_str());
		if (this->texture == NULL) {
			std::cout << "Loading Future " << this->path
					  << " failed, SDL error " << SDL_GetError() << std::endl;
		}
	}
} // namespace mazengine
