#include "mazengine/menu.h"
#include "mazengine/mazengine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <yaml-cpp/node/parse.h>

using namespace mazengine;

SDL_Rect *MenuWidget::Rect() { return &rect; }

SDL_Surface *MenuWidget::Texture() { return textures[texture_idx]; }

int Menu::InitialTick() {
	if (name == "UNSET") {
		return UNSET_VALUE_ERROR;
	}
	if (renderer == nullptr) {
		return UNSET_VALUE_ERROR;
	}

	YAML::Node mz = YAML::LoadFile("Mazzycat");

	YAML::Node data_yaml =
		YAML::LoadFile(mz["data_path"].as<String>() + name + ".yaml");

	internal_width = data_yaml["width"].as<int>();
	internal_height = data_yaml["height"].as<int>();

	// std::cout << "W: " << internal_width << ", "
	// 		  << "H: " << internal_height << std::endl;

	internal_surface = SDL_CreateRGBSurface(0, internal_width, internal_height,
											32, 0, 0, 0, 0);

	widgets = *new std::vector<MenuWidget *>();
	reactions = *new FuncVector();

	String img_prefix = mz["img_path"].as<String>();

	// std::cout << data_yaml << std::endl;

	MenuWidget *w_temp = nullptr;

	int func_index = 0;
	// int widget_index = 0;

	for (String widget_name : data_yaml["widget_names"].as<StringVector>()) {
		std::vector<SDL_Surface *> *textures = new std::vector<SDL_Surface *>();
		YAML::Node widget = data_yaml["widgets"][widget_name];

		for (String img_path :
			 widget["texture_paths"].as<std::vector<String>>()) {
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

	std::cout << "Finished loading widgets for " << name << widgets.size()
			  << std::endl;

	return STATUS_OK;
}

int Menu::Tick(int status) {
	SDL_Point mouse_location;
	mouse_location.x = int(*cursor_x * internal_width);
	mouse_location.y = int(*cursor_y * internal_height);
	int rv = STATUS_OK;
	// std::cout << "starting for" << std::endl;
	for (MenuWidget *widget : widgets) {
		// std::cout << "ticking widg " << widget->name << std::endl;
		bool in_rect = SDL_PointInRect(&mouse_location, widget->Rect());
		for (Button press : *presses) {
			switch (press) {
				case MOUSE_MOTION:
					if (in_rect && widget->on_hover != -1) {
						rv = React(widget->on_hover);
					} else if (!in_rect && widget->on_hover != -1) {
						rv = React(widget->no_hover);
					}
					break;
				case MOUSE_CLICK:
					if (in_rect && widget->on_click != -1) {
						rv = React(widget->on_click);
					}
					break;
				default:
					break;
			}
		}
		for (Button release : *releases) {
			switch (release) {
				case MOUSE_CLICK:
					if (in_rect && widget->no_click != -1) {
						rv = React(widget->no_click);
					}
					break;
				default:
					break;
			}
		}
	}
	return rv;
}

int Menu::Draw() {
	// std::cout << "Starting " << name << " Draw function" << std::endl;
	SDL_FillRect(internal_surface, NULL, 0);
	for (MenuWidget *widget : widgets) {
		if (widget->Texture() == NULL || widget->Texture() == nullptr) {
			std::cout << widget->name << " nullptr" << std::endl;
		}
		SDL_BlitScaled(widget->Texture(), NULL, internal_surface,
					   widget->Rect());
	}
	// std::cout << SDL_GetError() << std::endl;
	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(renderer, internal_surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	return STATUS_OK;
}

int Menu::Present() {
	SDL_RenderPresent(renderer);
	return STATUS_OK;
}

int Menu::React(int index) {
	if (size_t(index) >= reactions.size()) {
		std::cout << index << " OUT OF RANGE" << std::endl;
		return STATUS_OK;
	}
	auto func = *reactions[index];
	return func(STATUS_OK);
}

Func *Menu::Parse(String str, int iv) {
	StringVector temp_v = *new StringVector();
	size_t length = str.length();
	String temp;
	for (size_t i = 0; i < length; i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		} else if (str[i] == ' ') {
			temp_v.push_back(String(temp));
			temp.erase(0, str.length());
		}
	}
	temp_v.push_back(temp);
	if (temp_v[0] == "set") {
		if (temp_v[1] == "widget") {
			if (temp_v[3] == "texture") {
				return new Func{[this, temp_v](int s) -> int {
					this->widgets[std::stoi(temp_v[2])]->texture_idx =
						std::stoi(temp_v[4]);
					return STATUS_OK;
				}};
			}
		}
	}
	if (temp_v[0] == "up") {
		return new Func(
			[temp_v](int s) -> int { return std::stoi(temp_v[1]); });
	}

	return nullptr;
}
