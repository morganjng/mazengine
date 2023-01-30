/*
 * Definitions for all necessary classes for the engine to operate.
 */

#ifndef MAZENGINE_H_
#define MAZENGINE_H_

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include "game.h"
#include "geometry.h"
#include "io.h"
#include "texture.h"

#define STATUS_OK 0
#define ENGINE_KILL -1
#define UNSET_VALUE_ERROR -2

#define MZ mazengine::Engine

namespace mazengine {
	/**
	 * Mazzycat provides information about the engine and its settings to
	 * members -- soon will be deprecated for Engine static functions and
	 * variables.
	 *  */
	class Mazzycat {
	public:
		static std::vector<YAML::Node> data; /**< Loaded Mazzycat file. */
		static void Init();					 /**< Load Mazzycat file. */
		static std::string GetName();		 /**< Name of game. */
		static std::pair<int, int> GetWindowSize(); /**< Window width/height. */
		static int GetFramerate();					/**< Framerate of engine. */
		static std::map<std::string, std::string>
			GetPaths(); /**< Paths map from Mazzycat. */
	};

	/**
	 * The engine class represents a wrapper for the game - controls how it
	 * ticks, when it ticks, and when it draws. Should not be extended.
	 * */
	class Engine {
	protected:
		IO *_io;	 /**< IO instance for this Engine. */
		Game *_game; /**< Game instance for this Engine. */

	public:
		static SDL_Renderer
			*renderer; /**< Renderer for this instance. Will be deprecated. */
		static int window_width;  /**< Pixel width of window. */
		static int window_height; /**< Pixel height of window. */
		static int
			framerate; /**< Frames per second of this engine. From Mazzycat. */
		static std::string name;	   /**< Name of this Game. From Mazzycat. */
		static std::string data_path;  /**< Path to data files. */
		static std::string img_path;   /**< Path to image files. */
		static std::string audio_path; /**< Path to audio files. */
		/**
		 * Engine constructor. Sets everything to their default values.
		 * */
		Engine() {
			auto data = YAML::LoadFile("Mazzycat");

			_io = nullptr;
			renderer = nullptr;
			_game = nullptr;

			if (data["name"]) {
				name = data["name"].as<std::string>();
			}

			window_width = data["window_width"].as<int>();
			window_height = data["window_height"].as<int>();

			if (data["framerate"]) {
				framerate = data["framerate"].as<int>();
			}

			if (data["data_path"]) {
				data_path = data["data_path"].as<std::string>();
			}
			if (data["img_path"]) {
				img_path = data["img_path"].as<std::string>();
			}
			if (data["audio_path"]) {
				audio_path = data["audio_path"].as<std::string>();
			}
		}
		int SetIO(IO *io);			/**< Sets the IO instance. */
		int SetGame(Game *game);	/**< Sets the Game instance. */
		int Start();				/**< Starts the engine. */
		static void LoadTextures(); /**< Load all textures that need loading. */
	};
} // namespace mazengine
#endif
