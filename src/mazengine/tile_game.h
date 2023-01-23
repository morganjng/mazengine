#ifndef TILE_GAME_H_
#define TILE_GAME_H_

#include "mazengine.h"
#include "tile_entity.h"
#include "tile_map.h"
#include "tile_player.h"
#include "tile_renderer.h"
#include <string>
#include <yaml-cpp/yaml.h>

namespace mazengine {
	/**
	 * TileGame object. Needs reconfiguring.
	 * */
	class TileGame : public Game {
	private:
		String data_path;	   /**< Path for data files. */
		String img_path;	   /**< Path for image files. */
		String audio_path;	   /**< Path for audio files. */
		String map_key;		   /**< Current map key. */
		String following_key;  /**< Key for entity being followed. */
		TileEntity *following; /**< Entity being followed. */
		TileRenderer *tiles;   /**< TileRenderer object. */
		TileMap *current_map;  /**< Current map object. */
		YAML::Node map_yaml;   /**< YAML data. */
		int tile_size;		   /**< ? */
		int tile_width;		   /**< Tile width. */
		int tile_height;	   /**< Tile height. */
		TilePlayer *player;	   /**< Player object. */

	public:
		/**
		 * Constructor for TileGame.
		 * */
		TileGame(int tile_sz, int tile_w, int tile_h, String _name,
				 Game *_parent)
			: Game(_name, _parent) {
			auto paths = Mazzycat::GetPaths();
			data_path = paths["data"];
			img_path = paths["img"];
			audio_path = paths["audio"];
			YAML::Node data = YAML::LoadFile(data_path + _name + ".yaml");
			following = nullptr;
			current_map = nullptr;
			tiles = nullptr;
			tile_size = data["tile_size"].as<int>();
			tile_width = data["tile_width"].as<int>();
			tile_height = data["tile_height"].as<int>();
			internal_width = tile_width * tile_size;
			internal_height = tile_height * tile_size;
		}
		int Tick(int status); /**< Tick game. */
		int Draw();			  /**< Draw game. */
		int Present();		  /**< To be deprecated. */
		int React(int idx);	  /**< To be deprecated. */
	};

}; // namespace mazengine

#endif
