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
		int on_click;
		int on_hover;
		menu_widget(std::string _name, int x, int y, int _width, int _height,
					std::vector<SDL_Surface *> _textures) {
			name = _name;
			rect.w = _width;
			rect.h = _height;
			rect.x = x;
			rect.y = y;
			textures = _textures;
			texture_idx = 0;
			on_click = -1;
			on_hover = -1;
		};
		int texture_idx;
		SDL_Rect *get_rect();
		SDL_Surface *get_texture();
	};

	class menu : public game {
	protected:
		std::vector<menu_widget *> widgets;
		SDL_Surface *internal_surface;
		vec_func reactions;
		func_t *parse(std::string str, int iv);

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
