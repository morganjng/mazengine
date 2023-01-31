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
		 * Parent of this Game instance -- mostly important for children of
		 * UGame.
		 * */
		Game *parent;
		/**
		 * Name of game, which corresponds to yaml file which stores information
		 * about the Game.
		 * */
		std::string name;

		/**
		 * Constructor of Game. Loads simple data for children.
		 * @param _name name of this Game instance.
		 * @param _parent parent of this Game instance.
		 * */
		Game(std::string _name, Game *_parent) {
			parent = _parent;
			name = _name;
			YAML::Node temp = YAML::LoadFile("Mazzycat");
			std::string data_pth = "data/";
			if (temp["data_path"]) {
				data_pth = temp["data_path"].as<std::string>();
			}
			YAML::Node data = YAML::LoadFile(data_pth + _name + ".yaml");
			internal_width = data["width"].as<int>();
			internal_height = data["height"].as<int>();
		}

		/**
		 * Take command and parse it to modify state of this Game. Should
		 * usually be used by child.
		 * @param command Vector of String commands to be parsed by this
		 * function.
		 * @param offset How far into vector to start parsing the command at.
		 *  */
		virtual int Command(std::vector<std::string> *command,
							size_t offset) = 0;
		/**
		 * Update state of this Game based on current status.
		 * @param status Current status of Engine/parent/etc.
		 *  */
		virtual int Tick() = 0;
		virtual int Draw() = 0; /**< Draw current state to Engine renderer. */
	};
} // namespace mazengine

#endif
