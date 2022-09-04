#ifndef MENU_H_
#define MENU_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class menu_widget {
	protected:
		SDL_Rect rect;
		SDL_Texture *texture;
		std::string function;

	public:
		menu_widget(int _width, int _height, int x, int y,
					std::string _function, SDL_Texture *texture) {
			rect.w = _width;
			rect.h = _height;
			rect.x = x;
			rect.y = y;
			function = _function;
			this->texture = texture;
		};
		SDL_Rect *get_rect();
		SDL_Texture *get_texture();
	};

	class menu : public game {
	protected:
		std::vector<menu_widget *> widgets;

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
