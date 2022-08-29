#include <SDL_keycode.h>
#include <io_2d_no_mouse.h>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

void io_2d_no_mouse::set_settings_path(std::string path) {
  settings_path = path;
}

void io_2d_no_mouse::set_controls_map(
    std::map<SDL_Keycode, mazengine::button> *contr) {
  controls = contr;
}

int io_2d_no_mouse::read_settings() {
  if (settings_path == "UNSET") {
    return -1;
  }
  YAML::Node input = YAML::LoadFile(settings_path);
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["up"].as<std::string>().c_str()),
      mazengine::UP));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["down"].as<std::string>().c_str()),
      mazengine::DOWN));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["left"].as<std::string>().c_str()),
      mazengine::LEFT));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["right"].as<std::string>().c_str()),
      mazengine::RIGHT));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["A"].as<std::string>().c_str()), mazengine::A));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["B"].as<std::string>().c_str()), mazengine::B));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["start"].as<std::string>().c_str()),
      mazengine::START));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["select"].as<std::string>().c_str()),
      mazengine::SELECT));
  controls->insert(std::pair<SDL_Keycode, mazengine::button>(
      SDL_GetKeyFromName(input["kill"].as<std::string>().c_str()),
      mazengine::KILL));
  return 0;
}

int io_2d_no_mouse::parse(SDL_Event *event,
                          std::vector<mazengine::button> *presses,
                          std::vector<mazengine::button> *releases) {
  if (event->type == SDL_QUIT) {
    presses->push_back(mazengine::KILL);
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
