#ifndef IGAME_H_
#define IGAME_H_

#include "SDL_render.h"
#include "element.h"
#include "elements.h"
#include "mazengine.h"

#include <iostream>

namespace mazengine {
	class IGame : public Game {
	protected:
		std::vector<Element *> elements;
		std::vector<Future *> backgrounds;

	public:
		int background_idx = -1;
		IGame(String _name, Game *_parent) : Game(_name, _parent) {
			YAML::Node data =
				YAML::LoadFile(Mazzycat::GetPaths()["data"] + name + ".yaml");
			for (String val : data["elements"].as<StringVector>()) {
				elements.push_back(Elements::Get(val, this));
			}
			for (String val : data["backgrounds"].as<StringVector>()) {
				backgrounds.push_back(new Future(val));
			}
		}
		int Tick(int status);
		int Draw();
		int Present();
		int React(int val);
	};
} // namespace mazengine

#endif // IGAME_H_
