#ifndef IO_2D_MOUSE_H_
#define IO_2D_MOUSE_H_

#include "mazengine.h"
#include <yaml-cpp/yaml.h>

namespace mazengine {
	class IO2dMouse : public IO {
	private:
		String settings_path;
		std::map<SDL_Keycode, Button> *controls;
		std::map<SDL_Keycode, Button>::iterator iter;

	public:
		IO2dMouse() {
			YAML::Node mzy = YAML::LoadFile("Mazzycat");
			settings_path = mzy["settings_path"].as<String>();
			controls = new std::map<SDL_Keycode, Button>;
		};
		int ReadSettings();
		int Parse(SDL_Event *event);
	};
}; // namespace mazengine

#endif
