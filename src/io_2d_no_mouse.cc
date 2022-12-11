#include "mazengine/io_2d_no_mouse.h"
#include "mazengine/mazengine.h"
#include <SDL_keycode.h>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

void IO2dNoMouse::set_settings_path(std::string path) { settings_path = path; }

void IO2dNoMouse::set_controls_map(std::map<SDL_Keycode, Button> *contr) {
	controls = contr;
}

int IO2dNoMouse::ReadSettings() {
	if (settings_path == "UNSET") {
		return UNSET_VALUE_ERROR;
	}
	YAML::Node input = YAML::LoadFile(settings_path);
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["up"].as<std::string>().c_str()), UP));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["down"].as<std::string>().c_str()), DOWN));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["left"].as<std::string>().c_str()), LEFT));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["right"].as<std::string>().c_str()), RIGHT));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["A"].as<std::string>().c_str()), A));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["B"].as<std::string>().c_str()), B));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["start"].as<std::string>().c_str()), START));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["select"].as<std::string>().c_str()), SELECT));
	controls->insert(std::pair<SDL_Keycode, Button>(
		SDL_GetKeyFromName(input["kill"].as<std::string>().c_str()), KILL));
	return STATUS_OK;
}

int IO2dNoMouse::Parse(SDL_Event *event) {
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
	return STATUS_OK;
}
