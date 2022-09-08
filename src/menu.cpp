#include "mazengine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <menu.h>
#include <yaml-cpp/node/parse.h>

using namespace mazengine;

SDL_Rect *menu_widget::get_rect() { return &rect; }

SDL_Surface *menu_widget::get_texture() { return textures[texture_idx]; }

int menu::initial_tick() {
	if (name == "UNSET") {
		return UNSET_VALUE_ERROR;
	}
	if (renderer == nullptr) {
		return UNSET_VALUE_ERROR;
	}

	YAML::Node mz = YAML::LoadFile("mazzycat");

	YAML::Node data_yaml =
		YAML::LoadFile(mz["data_path"].as<std::string>() + name + ".yaml");

	internal_width = data_yaml["width"].as<int>();
	internal_height = data_yaml["height"].as<int>();

	// std::cout << "W: " << internal_width << ", "
	// 		  << "H: " << internal_height << std::endl;

	internal_surface = SDL_CreateRGBSurface(0, internal_width, internal_height,
											32, 0, 0, 0, 0);

	widgets = *new std::vector<menu_widget *>();
	reactions = *new vec_func();

	std::string img_prefix = mz["img_path"].as<std::string>();

	// std::cout << data_yaml << std::endl;

	menu_widget *w_temp = nullptr;

	int func_index = 0;
	// int widget_index = 0;

	for (std::string widget_name : data_yaml["widget_names"].as<vec_string>()) {
		std::vector<SDL_Surface *> *textures = new std::vector<SDL_Surface *>();
		YAML::Node widget = data_yaml["widgets"][widget_name];

		for (std::string img_path :
			 widget["texture_paths"].as<std::vector<std::string>>()) {
			std::cout << img_prefix << img_path << std::endl;
			textures->push_back(IMG_Load((img_prefix + img_path).c_str()));
		}

		/*
				std::cout << widget_name << ", "
						  << widget["x"].as<double>() * internal_width << ", "
						  << widget["y"].as<double>() * internal_height << ", "
						  << widget["width"].as<double>() * internal_width << ",
		   "
						  << widget["height"].as<double>() * internal_height
						  << std::endl;
						  */

		w_temp = new menu_widget(
			widget_name, widget["x"].as<double>() * internal_width,
			widget["y"].as<double>() * internal_height,
			widget["width"].as<double>() * internal_width,
			widget["height"].as<double>() * internal_height, *textures);

		std::string func_string = "none";

		func_string = widget["on_click"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, func_index));
			w_temp->on_click = func_index;
			func_index++;
		}

		func_string = widget["on_hover"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, func_index));
			w_temp->on_hover = func_index;
			func_index++;
		}

		func_string = widget["no_click"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, func_index));
			w_temp->no_click = func_index;
			func_index++;
		}

		func_string = widget["no_hover"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, func_index));
			w_temp->no_hover = func_index;
			func_index++;
		}

		widgets.push_back(w_temp);
	}

	std::cout << "Finished loading widgets for " << name << widgets.size()
			  << std::endl;

	return STATUS_OK;
}

int menu::tick(int status) {
	// std::cout << "Presses size: " << presses->size()
	// 		  << " Releases size: " << releases->size() << std::endl;
	SDL_Point mouse_location;
	mouse_location.x = int(*cursor_x * internal_width);
	mouse_location.y = int(*cursor_y * internal_height);
	int rv = STATUS_OK;
	for (menu_widget *widget : widgets) {
		bool in_rect = SDL_PointInRect(&mouse_location, widget->get_rect());
		for (button press : *presses) {
			switch (press) {
				case MOUSE_MOTION:
					if (in_rect && widget->on_hover != -1) {
						rv = reaction(widget->on_hover);
					} else if (!in_rect && widget->on_hover != -1) {
						rv = reaction(widget->no_hover);
					}
					break;
				case MOUSE_CLICK:
					if (in_rect && widget->on_click != -1) {
						rv = reaction(widget->on_click);
					}
					break;
				default:
					break;
			}
		}
		for (button release : *releases) {
			switch (release) {
				case MOUSE_CLICK:
					if (in_rect && widget->no_click != -1) {
						rv = reaction(widget->no_click);
					}
					break;
				default:
					break;
			}
		}
	}
	return rv;
}

int menu::draw() {
	// std::cout << "Starting " << name << " draw function" << std::endl;
	SDL_FillRect(internal_surface, NULL, 0);
	for (menu_widget *widget : widgets) {
		if (widget->get_texture() == NULL || widget->get_texture() == nullptr) {
			std::cout << widget->name << " nullptr" << std::endl;
		}
		SDL_BlitScaled(widget->get_texture(), NULL, internal_surface,
					   widget->get_rect());
	}
	// std::cout << SDL_GetError() << std::endl;
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(renderer, internal_surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	return STATUS_OK;
}

int menu::present() {
	SDL_RenderPresent(renderer);
	return STATUS_OK;
}

int menu::reaction(int index) {
	// std::cout << index << " REACTION " << reactions.size() << std::endl;

	auto func = *reactions[index];
	return func(STATUS_OK);
}

func_t *menu::parse(std::string str, int iv) {
	vec_string temp_v = *new vec_string();
	size_t length = str.length();
	std::string temp;
	for (size_t i = 0; i < length; i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		} else if (str[i] == ' ') {
			temp_v.push_back(std::string(temp));
			temp.erase(0, str.length());
		}
	}
	temp_v.push_back(temp);
	/*
	std::cout << iv << ": ";
	for (std::string s : temp_v) {
		std::cout << "[\"" << s << "\"]";
	}
	std::cout << std::endl;
	*/
	if (temp_v[0] == "set") {
		if (temp_v[1] == "widget") {
			if (temp_v[3] == "texture") {
				return new func_t{[this, temp_v](int s) -> int {
					this->widgets[std::stoi(temp_v[2])]->texture_idx =
						std::stoi(temp_v[4]);
					return STATUS_OK;
				}};
			}
		}
	}
	if (temp_v[0] == "up") {
		return new func_t(
			[temp_v](int s) -> int { return std::stoi(temp_v[1]); });
	}

	return nullptr;
}
