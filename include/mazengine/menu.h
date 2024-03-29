/*
 * Menu class: A simple class for semi-static menus
 */

#ifndef MAZENGINE_MENU_H_
#define MAZENGINE_MENU_H_

#include "mazengine.h"
#include <iostream>
#include <vector>

namespace mazengine {

	/**
	 * A MenuWidget is an element of the Menu screen.
	 * */
	class MenuWidget {
	protected:
		SDL_Rect rect; /**< Location on screen. */
		std::vector<SDL_Surface *>
			textures;		  /**< Vector of textures to display. */
		std::string function; /**< Function from yaml. */

	public:
		std::string name;	  /**< Name of widget. */
		std::string on_click; /**< Function for click. */
		std::string on_hover; /**< Function for hover. */
		std::string no_click; /**< Function for not-clicking. */
		std::string no_hover; /**< Function for not-hovering. */
		/**
		 * Widget constructor. Sets all necessary values.
		 * */
		MenuWidget(std::string _name, int x, int y, int _width, int _height,
				   std::vector<SDL_Surface *> _textures, std::string on_click,
				   std::string on_hover, std::string no_click,
				   std::string no_hover) {
			name = _name;
			rect.w = _width;
			rect.h = _height;
			rect.x = x;
			rect.y = y;
			textures = _textures;
			texture_idx = 0;
			this->on_click = on_click;
			this->on_hover = on_hover;
			this->no_click = no_click;
			this->no_hover = no_hover;
		};
		int texture_idx;		/**< Current index of texture. */
		SDL_Rect *Rect();		/**< Getter for location. */
		SDL_Surface *Texture(); /**< Getter for texture. */
	};

	/**
	 * The Menu class represents simple, interactable menus.
	 * */
	class Menu : public Game {
	protected:
		SDL_Surface *internal_surface; /**< Surface to draw to. */

	public:
		std::vector<MenuWidget *> widgets; /**< All widgets. */
		/**
		 * Menu constructor. Loads list of widgets from .yaml file and populates
		 * all variables.
		 * */
		Menu(std::string _name) : Game(_name) {
			YAML::Node mz = YAML::LoadFile("Mazzycat");

			YAML::Node data_yaml = YAML::LoadFile(
				mz["data_path"].as<std::string>() + name + ".yaml");

			internal_width = data_yaml["width"].as<int>();
			internal_height = data_yaml["height"].as<int>();

			internal_surface = SDL_CreateRGBSurface(
				0, internal_width, internal_height, 32, 0, 0, 0, 0);

			widgets = *new std::vector<MenuWidget *>();

			std::string img_prefix = mz["img_path"].as<std::string>();

			MenuWidget *w_temp = nullptr;

			for (std::string widget_name :
				 data_yaml["widget_names"].as<std::vector<std::string>>()) {
				std::vector<SDL_Surface *> *textures =
					new std::vector<SDL_Surface *>();
				YAML::Node widget = data_yaml["widgets"][widget_name];

				for (std::string img_path :
					 widget["texture_paths"].as<std::vector<std::string>>()) {
					// std::cout << img_prefix << img_path << std::endl;
					textures->push_back(
						IMG_Load((img_prefix + img_path).c_str()));
				}

				w_temp = new MenuWidget(
					widget_name, widget["x"].as<double>() * internal_width,
					widget["y"].as<double>() * internal_height,
					widget["width"].as<double>() * internal_width,
					widget["height"].as<double>() * internal_height, *textures,
					widget["on_click"].as<std::string>(),
					widget["on_hover"].as<std::string>(),
					widget["no_click"].as<std::string>(),
					widget["no_hover"].as<std::string>());

				widgets.push_back(w_temp);
			}
		};
		int Tick(); /**< Update state. */
		int Draw(); /**< Draw state. */
		/**
		 * Set the specified value of the specified widget to the provided
		 * value.
		 * */
		void SetWidgetValue(std::string value, size_t widget_idx,
							size_t new_value);
	};
	/**
	 * Wrapper for Menu class so Python can interact with it.
	 * */
	class MenuWrapper {
	public:
		MenuWrapper() { menu = (mazengine::Menu *)MZ::engine->GetGame(); }
		mazengine::Menu *menu; /**< Pointer to the menu being wrapped. */
		/**
		 * Interface to menu->SetWidgetValue function for Python.
		 * */
		void SetWidget(std::string u, size_t v, size_t w);
	};

}; // namespace mazengine

#endif // MENU_H_
