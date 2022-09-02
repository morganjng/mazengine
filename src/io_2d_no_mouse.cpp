#include <SDL_keycode.h>
#include <io_2d_no_mouse.h>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

void io_2d_no_mouse::set_settings_path(std::string path) {
    settings_path = path;
}

void io_2d_no_mouse::set_controls_map(std::map<SDL_Keycode, button> *contr) {
    controls = contr;
}

int io_2d_no_mouse::read_settings() {
    if (settings_path == "UNSET") {
	return -1;
    }
    YAML::Node input = YAML::LoadFile(settings_path);
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["up"].as<std::string>().c_str()), UP));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["down"].as<std::string>().c_str()), DOWN));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["left"].as<std::string>().c_str()), LEFT));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["right"].as<std::string>().c_str()),
	    RIGHT));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["A"].as<std::string>().c_str()), A));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["B"].as<std::string>().c_str()), B));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["start"].as<std::string>().c_str()),
	    START));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["select"].as<std::string>().c_str()),
	    SELECT));
    controls->insert(std::pair<SDL_Keycode, button>(
	    SDL_GetKeyFromName(input["kill"].as<std::string>().c_str()), KILL));
    return 0;
}

int io_2d_no_mouse::parse(SDL_Event *event, std::vector<button> *presses,
			  std::vector<button> *releases) {
    if (event->type == SDL_QUIT) {
	presses->push_back(KILL);
	return -1;
    }
    if (event->type == SDL_KEYDOWN) {
	iter = controls->find(event->key.keysym.sym);
	if (iter != controls->end()) {
	    presses->push_back(controls->at(event->key.keysym.sym));
	}
	return 0;
    }
    if (event->type == SDL_KEYUP) {
	iter = controls->find(event->key.keysym.sym);
	if (iter != controls->end()) {
	    releases->push_back(controls->at(event->key.keysym.sym));
	}
	return 0;
    }
    return 0;
}
