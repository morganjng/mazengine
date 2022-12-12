#ifndef IO_2D_MOUSE_H_
#define IO_2D_MOUSE_H_

#include "mazengine.h"

namespace mazengine {
	class IO2dMouse : public IO {
	private:
		String settings_path;
		std::map<SDL_Keycode, Button> *controls;
		std::map<SDL_Keycode, Button>::iterator iter;

	public:
		IO2dMouse() {
			settings_path = "UNSET";
			controls = nullptr;
		};
		void set_controls_map(std::map<SDL_Keycode, Button> *contr);
		void set_settings_path(String path);
		int ReadSettings();
		int Parse(SDL_Event *event);
	};
}; // namespace mazengine

#endif
