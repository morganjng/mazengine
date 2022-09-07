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
	int widget_index = 0;

	for (std::string widget_name : data_yaml["widget_names"].as<vec_string>()) {
		std::vector<SDL_Surface *> *textures = new std::vector<SDL_Surface *>();
		YAML::Node widget = data_yaml["widgets"][widget_name];

		for (std::string img_path :
			 widget["texture_paths"].as<std::vector<std::string>>()) {
			std::cout << img_prefix << img_path << std::endl;
			textures->push_back(IMG_Load((img_prefix + img_path).c_str()));
		}

		std::cout << widget_name << ", "
				  << widget["x"].as<double>() * internal_width << ", "
				  << widget["y"].as<double>() * internal_height << ", "
				  << widget["width"].as<double>() * internal_width << ", "
				  << widget["height"].as<double>() * internal_height
				  << std::endl;

		w_temp = new menu_widget(
			widget_name, widget["x"].as<double>() * internal_width,
			widget["y"].as<double>() * internal_height,
			widget["width"].as<double>() * internal_width,
			widget["height"].as<double>() * internal_height, *textures);

		std::string func_string = "none";

		func_string = widget["on_click"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, widget_index));
			w_temp->on_click = func_index;
			func_index++;
		}

		func_string = widget["on_hover"].as<std::string>();
		if (func_string != "none") {
			reactions.push_back(parse(func_string, widget_index));
			w_temp->on_hover = func_index;
			func_index++;
		}

		widgets.push_back(w_temp);
	}

	std::cout << "Finished loading widgets for " << name << widgets.size()
			  << std::endl;

	return STATUS_OK;
}

int menu::tick(int status) {
	/*
	for (button press : *presses) {
	}
	for (button release : *releases) {
	}
	*/
	return STATUS_OK;
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

int menu::reaction(int index) { return STATUS_OK; }

func_t *menu::parse(std::string str, int iv) {
	vec_string temp_v;
	size_t start = 0;
	size_t end;
	while (true) {
		end = str.find(" ", start);
		temp_v.push_back(str.substr(start, end));
		start = end + 1;
		end = str.length();
		if (start >= end) {
			break;
		}
	}
	if (temp_v[0] == "set") {
		if (temp_v[1] == "widget") {
			return nullptr; // TODO
		}
	}
	if (temp_v[0] == "up") {
		return new func_t(
			[temp_v](int s) -> int { return std::stoi(temp_v[1]); });
	}

	return nullptr;
}
