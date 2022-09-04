#include <SDL_image.h>
#include <iostream>

#include <menu.h>
#include <yaml-cpp/node/parse.h>

using namespace mazengine;

SDL_Rect *menu_widget::get_rect() { return &rect; }

SDL_Texture *menu_widget::get_texture() { return texture; }

int menu::initial_tick() {
	if (name == "UNSET") {
		return UNSET_VALUE_ERROR;
	}

	YAML::Node mz = YAML::LoadFile("mazzycat");

	YAML::Node data_yaml =
		YAML::LoadFile(mz["data_path"].as<std::string>() + name + ".yaml");

	internal_width = data_yaml["width"].as<int>();
	internal_height = data_yaml["height"].as<int>();

	widgets = *new std::vector<menu_widget *>();

	std::cout << data_yaml << std::endl;

	for (std::string widget_name :
		 data_yaml["widget_names"].as<std::vector<std::string>>()) {
		YAML::Node widget = data_yaml["widgets"][widget_name];
		widgets.push_back(
			new menu_widget(widget["x"].as<double>() * internal_width,
							widget["y"].as<double>() * internal_height,
							widget["width"].as<double>() * internal_width,
							widget["height"].as<double>() * internal_height,
							widget["function"].as<std::string>(),
							IMG_LoadTexture(renderer,
											(mz["img_path"].as<std::string>() +
											 widget["path"].as<std::string>())
												.c_str())));
	}

	return STATUS_OK;
}

int menu::tick(int status) { return STATUS_OK; }

int menu::draw() { return STATUS_OK; }

int menu::present() { return STATUS_OK; }

int menu::reaction(int index) { return STATUS_OK; }
