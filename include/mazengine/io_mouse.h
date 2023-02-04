#ifndef MAZENGINE_IO_MOUSE_H_
#define MAZENGINE_IO_MOUSE_H_

#include "mazengine.h"
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

namespace mazengine {
	/**
	 * The IOMouse class is an IO that only parses mouse inputs.
	 * */
	class IOMouse : public IO {
	public:
		IOMouse() { YAML::Node mz = YAML::LoadFile("Mazzycat"); };
		int ReadSettings();
		int Parse(SDL_Event *event);
	};
} // namespace mazengine

#endif // IO_MOUSE_H_
