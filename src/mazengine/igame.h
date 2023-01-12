#ifndef IGAME_H_
#define IGAME_H_

#include "SDL_render.h"
#include "element.h"
#include "elements.h"
#include "mazengine.h"

namespace mazengine {
	class IGame : public Game {
	protected:
		std::vector<Element *> elements;
		std::vector<SDL_Texture *> backgrounds;
		YAML::Node data;
		int background_idx = -1;

	public:
		IGame(String _name, Game *_parent) : Game(_name, _parent) {
			data =
				YAML::LoadFile(Mazzycat::GetPaths()["data"] + _name + ".yaml");
			for (String val : data["elements"].as<StringVector>()) {
				elements.push_back(Elements::Get(val, this));
			}
			for (String val : data["backgrounds"].as<StringVector>()) {
				backgrounds.push_back(IMG_LoadTexture(
					Engine::renderer,
					(Mazzycat::GetPaths()["img"] + val).c_str()));
			}
		}
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int val);
	};
} // namespace mazengine

#endif // IGAME_H_
