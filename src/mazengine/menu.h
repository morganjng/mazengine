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
		SDL_Rect rect; /**< Location on screen. */
		std::vector<SDL_Surface *>
			textures;	 /**< Vector of textures to display. */
		String function; /**< Function from yaml. */

	public:
		String name;  /**< Name of widget. */
		int on_click; /**< Function for click. */
		int on_hover; /**< Function for hover. */
		int no_click; /**< Function for not-clicking. */
		int no_hover; /**< Function for not-hovering. */
		/**
		 * Widget constructor. Sets all necessary values.
		 * */
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
		int texture_idx;		/**< Current index of texture. */
		SDL_Rect *Rect();		/**< Getter for location. */
		SDL_Surface *Texture(); /**< Getter for texture. */
	};

	class Menu : public Game {
	protected:
		std::vector<MenuWidget *> widgets; /**< All widgets. */
		SDL_Surface *internal_surface;	   /**< Surface to draw to. */
		FuncVector reactions; /**< Vector of lambdas for interactions. */
		Func *Parse(String str,
					int iv); /**< Parse command to lambda function. */

	public:
		/**
		 * Menu constructor. Loads list of widgets from .yaml file and populates
		 * all variables.
		 * */
		Menu(String _name, Game *_parent) : Game(_name, _parent) {
			YAML::Node mz = YAML::LoadFile("Mazzycat");

			YAML::Node data_yaml =
				YAML::LoadFile(mz["data_path"].as<String>() + name + ".yaml");

			internal_width = data_yaml["width"].as<int>();
			internal_height = data_yaml["height"].as<int>();

			internal_surface = SDL_CreateRGBSurface(
				0, internal_width, internal_height, 32, 0, 0, 0, 0);

			widgets = *new std::vector<MenuWidget *>();
			reactions = *new FuncVector();

			String img_prefix = mz["img_path"].as<String>();

			MenuWidget *w_temp = nullptr;

			int func_index = 0;

			for (String widget_name :
				 data_yaml["widget_names"].as<StringVector>()) {
				std::vector<SDL_Surface *> *textures =
					new std::vector<SDL_Surface *>();
				YAML::Node widget = data_yaml["widgets"][widget_name];

				for (String img_path :
					 widget["texture_paths"].as<std::vector<String>>()) {
					// std::cout << img_prefix << img_path << std::endl;
					textures->push_back(
						IMG_Load((img_prefix + img_path).c_str()));
				}

				w_temp = new MenuWidget(
					widget_name, widget["x"].as<double>() * internal_width,
					widget["y"].as<double>() * internal_height,
					widget["width"].as<double>() * internal_width,
					widget["height"].as<double>() * internal_height, *textures);

				String func_string = "none";

				func_string = widget["on_click"].as<String>();
				if (func_string != "none") {
					reactions.push_back(Parse(func_string, func_index));
					w_temp->on_click = func_index;
					func_index++;
				}

				func_string = widget["on_hover"].as<String>();
				if (func_string != "none") {
					reactions.push_back(Parse(func_string, func_index));
					w_temp->on_hover = func_index;
					func_index++;
				}

				func_string = widget["no_click"].as<String>();
				if (func_string != "none") {
					reactions.push_back(Parse(func_string, func_index));
					w_temp->no_click = func_index;
					func_index++;
				}

				func_string = widget["no_hover"].as<String>();
				if (func_string != "none") {
					reactions.push_back(Parse(func_string, func_index));

					w_temp->no_hover = func_index;
					func_index++;
				}

				widgets.push_back(w_temp);
			}
		};
		int Tick(int status); /**< Update state. */
		int Draw();			  /**< Draw state. */
		int Present();		  /**< Present textures. */
		int React(int index); /**< React to states. */
	};

}; // namespace mazengine

#endif // MENU_H_
