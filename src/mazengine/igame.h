#ifndef IGAME_H_
#define IGAME_H_

#include "SDL_render.h"
#include "element.h"
#include "mazengine.h"

#include <iostream>

namespace mazengine {
	/**
	 * An IGame is a Game consisting of elements that are drawn and ticked.
	 * */
	class IGame : public Game {
	protected:
		/** Vector of elements. Drawn in order. */
		std::vector<Element *> elements;
		/** Vector of backgrounds. Only
		 * backgrounds[background_idx] is drawn, and only if
		 * background_idx != -1. */
		std::vector<Texture *> backgrounds;

	public:
		/**
		 * Current index of background texture. If background_idx == -1, then
		 * don't draw any background on the screen.
		 * */
		int background_idx = -1;
		/**
		 * IGame constructor. Loads backgrounds from file.
		 * */
		IGame(String _name, Game *_parent) : Game(_name, _parent) {
			YAML::Node data =
				YAML::LoadFile(Mazzycat::GetPaths()["data"] + name + ".yaml");
			for (String val : data["backgrounds"].as<StringVector>()) {
				backgrounds.push_back(new Texture(val));
			}
		}
		int Tick(int status); /**< Update state of elements and this. */
		int Draw();			  /**< Draw current state of elements in order. */
	};
} // namespace mazengine

#endif // IGAME_H_
