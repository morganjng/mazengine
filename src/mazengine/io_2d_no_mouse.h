#ifndef TWODXPUT_NO_MOUSE_H_
#define TWODXPUT_NO_MOUSE_H_

#include "SDL_keycode.h"
#include "mazengine.h"
#include <map>
#include <string>
#include <vector>

namespace mazengine {

	class IO2dNoMouse : public IO {
	private:
		String settings_path;
		std::map<SDL_Keycode, Button> *controls;
		std::map<SDL_Keycode, Button>::iterator iter;

	public:
		IO2dNoMouse() {
			YAML::Node mzy = YAML::LoadFile("Mazzycat");
			settings_path = mzy["settings_path"].as<String>();
			controls = new std::map<SDL_Keycode, Button>;
		};
		int ReadSettings();
		int Parse(SDL_Event *event);
	};

}; // namespace mazengine

#endif // TWODXPUT_NO_MOUSE_H_
