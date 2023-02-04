#ifndef MAZENGINE_IO_2D_MOUSE_H_
#define MAZENGINE_IO_2D_MOUSE_H_

#include "mazengine.h"
#include <yaml-cpp/yaml.h>

namespace mazengine {
	/**
	 * The IO2dMouse class is an IO class that parses keyboard and mouse inputs.
	 * */
	class IO2dMouse : public IO {
	private:
		std::string settings_path;
		std::map<SDL_Keycode, Button> *controls;
		std::map<SDL_Keycode, Button>::iterator iter;

	public:
		IO2dMouse() {
			YAML::Node mzy = YAML::LoadFile("Mazzycat");
			settings_path = mzy["settings_path"].as<std::string>();
			controls = new std::map<SDL_Keycode, Button>;
		};
		int ReadSettings();
		int Parse(SDL_Event *event);
	};
}; // namespace mazengine

#endif
