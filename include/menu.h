#ifndef MENU_H_
#define MENU_H_

#include "mazengine.h"
#include <iostream>
#include <vector>

namespace mazengine {

	class menu_widget {
	protected:
		SDL_Rect rect;
		std::vector<SDL_Surface *> textures;
		std::string function;

	public:
		std::string name;
		menu_widget(std::string _name, int x, int y, int _width, int _height,
					std::vector<SDL_Surface *> _textures) {
			rect = *new SDL_Rect();
			name = _name;
			rect.w = _width;
			rect.h = _height;
			// std::cout << _width << _height << std::endl;
			rect.x = x;
			rect.y = y;
			std::cout << name << ": " << rect.x << ", " << rect.y << ", "
					  << rect.w << "," << rect.h << std::endl;
			textures = _textures;
			texture_idx = 0;
		};
		int texture_idx;
		SDL_Rect *get_rect();
		SDL_Surface *get_texture();
	};

	class menu : public game {
	protected:
		std::vector<menu_widget *> widgets;
		SDL_Surface *internal_surface;

	public:
		menu() {
			renderer = nullptr;
			name = "UNSET";
		};
		int initial_tick();
		int tick(int status);
		int draw();
		int present();
		int reaction(int index);
	};

}; // namespace mazengine

#endif // MENU_H_
