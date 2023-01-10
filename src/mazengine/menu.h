/*
 * Menu class: A simple class for semi-static menus
 */

#ifndef MENU_H_
#define MENU_H_

#include "mazengine.h"
#include <iostream>
#include <vector>

namespace mazengine {

	class MenuWidget {
	protected:
		SDL_Rect rect;
		std::vector<SDL_Surface *> textures;
		String function;

	public:
		String name;
		int on_click;
		int on_hover;
		int no_click;
		int no_hover;
		MenuWidget(String _name, int x, int y, int _width, int _height,
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
			no_click = -1;
			no_click = -1;
		};
		int texture_idx;
		SDL_Rect *Rect();
		SDL_Surface *Texture();
	};

	class Menu : public Game {
	protected:
		std::vector<MenuWidget *> widgets;
		SDL_Surface *internal_surface;
		FuncVector reactions;
		Func *Parse(String str, int iv);

	public:
		Menu(String _name, Game *_parent) : Game(_name, _parent){};
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int index);
	};

}; // namespace mazengine

#endif // MENU_H_
