#ifndef MAZENGINE_GAME_H_
#define MAZENGINE_GAME_H_

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace mazengine {
	/**
	 * Game class encompasses the rest of the game -- entities, how to draw, etc
	 * */
	class Game {
	public:
		/**
		 * Width of canvas that the game is rendering --
		 * may be different than Engine width.
		 * */
		int internal_width;
		/**
		 * Height of canvas that the game is rendering --
		 * may be different than Engine height.
		 * */
		int internal_height;
		/**
		 * Name of game, which corresponds to yaml file which stores information
		 * about the Game.
		 * */
		std::string name;
		/**
		 * Python code to be run before first tick.
		 * */
		std::string init_py = "";

		/**
		 * Constructor of Game. Loads simple data for children.
		 * @param _name name of this Game instance.
		 * */
		Game(std::string _name) {
			name = _name;
			YAML::Node temp = YAML::LoadFile("Mazzycat");
			std::string data_pth = "data/";
			if (temp["data_path"]) {
				data_pth = temp["data_path"].as<std::string>();
			}
			YAML::Node data = YAML::LoadFile(data_pth + _name + ".yaml");
			if (data["init"]) {
				init_py = data["init"].as<std::string>();
			}
			internal_width = data["width"].as<int>();
			internal_height = data["height"].as<int>();
		}

		/**
		 * Update state of this Game based on current status.
		 *  */
		virtual int Tick() = 0;
		virtual int Draw() = 0; /**< Draw current state to Engine renderer. */
	};
} // namespace mazengine

#endif
