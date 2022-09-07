#include "SDL_events.h"
#include "mazengine.h"
#include <SDL_keycode.h>
#include <io_2d_mouse.h>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

void io_2d_mouse::set_settings_path(std::string path) { settings_path = path; }

void io_2d_mouse::set_controls_map(std::map<SDL_Keycode, button> *contr) {
	controls = contr;
}

int io_2d_mouse::read_settings() {
	if (settings_path == "UNSET") {
		return UNSET_VALUE_ERROR;
	}
	YAML::Node input = YAML::LoadFile(settings_path);
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["up"].as<std::string>().c_str()), UP));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["down"].as<std::string>().c_str()), DOWN));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["left"].as<std::string>().c_str()), LEFT));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["right"].as<std::string>().c_str()), RIGHT));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["A"].as<std::string>().c_str()), A));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["B"].as<std::string>().c_str()), B));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["start"].as<std::string>().c_str()), START));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["select"].as<std::string>().c_str()), SELECT));
	controls->insert(std::pair<SDL_Keycode, button>(
		SDL_GetKeyFromName(input["kill"].as<std::string>().c_str()), KILL));
	return STATUS_OK;
}

int io_2d_mouse::parse(SDL_Event *event) {
	if (event->type == SDL_QUIT) {
		presses->push_back(KILL);
		return ENGINE_KILL;
	}
	if (event->type == SDL_KEYDOWN) {
		iter = controls->find(event->key.keysym.sym);
		if (iter != controls->end()) {
			presses->push_back(controls->at(event->key.keysym.sym));
		}
		return STATUS_OK;
	}
	if (event->type == SDL_KEYUP) {
		iter = controls->find(event->key.keysym.sym);
		if (iter != controls->end()) {
			releases->push_back(controls->at(event->key.keysym.sym));
		}
		return STATUS_OK;
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		presses->push_back(MOUSE_CLICK);
	}
	if (event->type == SDL_MOUSEMOTION) {
		presses->push_back(MOUSE_MOTION);
		*cursor_x = double(event->motion.x) / double(*window_width);
		*cursor_y = double(event->motion.y) / double(*window_height);
	}
	if (event->type == SDL_MOUSEBUTTONUP) {
		releases->push_back(MOUSE_CLICK);
	}
	return STATUS_OK;
}
