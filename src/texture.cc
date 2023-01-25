#include <geometry.h>
#include <iostream>
#include <mazengine.h>
#include <texture.h>

namespace mazengine {
	std::vector<Texture *> Texture::registry = *new std::vector<Texture *>;

	void Texture::Load() {
		this->texture = IMG_LoadTexture(Engine::renderer, this->path.c_str());
		if (this->texture == NULL) {
			std::cout << "Loading Texture " << this->path
					  << " failed, SDL error " << SDL_GetError() << std::endl;
		}
	}

	void Texture::Draw(Rect *src, Rect *dest) {
		if (texture == nullptr) {
			Load();
		}
		SDL_Rect a, b;
		SDL_Rect *_src = &a;
		SDL_Rect *_dest = &b;
		if (src == NULL) {
			_src = NULL;
		} else {
			_src->x = src->x;
			_src->y = src->y;
			_src->w = src->w;
			_src->h = src->h;
		}
		if (dest == NULL) {
			_dest = NULL;
		} else {
			_dest->x = dest->x;
			_dest->y = dest->y;
			_dest->w = dest->w;
			_dest->h = dest->h;
		}
		int rv = SDL_RenderCopy(Engine::renderer, texture, _src, _dest);
		if (rv != 0) {
			std::cout << "Rendering texture " << path << " failed with value "
					  << rv << " SDL error " << SDL_GetError() << std::endl;
		}
	}

} // namespace mazengine
