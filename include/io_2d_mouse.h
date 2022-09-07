#ifndef IO_2D_MOUSE_H_
#define IO_2D_MOUSE_H_

#include "mazengine.h"

namespace mazengine {
	class io_2d_mouse : public io {
	private:
		std::string settings_path;
		std::map<SDL_Keycode, button> *controls;
		std::map<SDL_Keycode, button>::iterator iter;

	public:
		io_2d_mouse() {
			settings_path = "UNSET";
			controls = nullptr;
		};
		void set_controls_map(std::map<SDL_Keycode, button> *contr);
		void set_settings_path(std::string path);
		int read_settings();
		int parse(SDL_Event *event);
	};
}; // namespace mazengine

#endif
