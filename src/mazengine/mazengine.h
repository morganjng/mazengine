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

#define STATUS_OK 0
#define ENGINE_KILL -1
#define UNSET_VALUE_ERROR -2

#define MZ mazengine::Engine

namespace mazengine {

	/**
	 * Enumeration of input-types. Should be expanded or redefined as need be.
	 * */
	enum Button {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		A,
		B,
		START,
		SELECT,
		KILL,
		MOUSE_CLICK,
		MOUSE_MOTION
	};

	/**
	 * Typedefs for long, frequently used types.
	 * */
	typedef std::string String;
	typedef std::vector<Button> ButtonVector;
	typedef std::vector<std::function<int(int)> *> FuncVector;
	typedef std::function<int(int)> Func;
	typedef std::vector<String> StringVector;
	typedef std::pair<int, int> IntPair;
	typedef std::map<String, String> StringMap;

	/**
	 * The Point class is an abstraction away from the SDL point. To be used in
	 * polygons.
	 * */
	class Point {
	public:
		int x; /**< X-pos of the point. */
		int y; /**< Y-pos of the point. */
		/**
		 * Point contsructor. Direct analogue to initialization of SDL_Point.
		 * */
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
	};

	/**
	 * Polygon class. To be done. Will eventually lead into a mesh for 3d
	 * objects.
	 * */
	class Polygon {};

	/**
	 * Abstraction of a rectangle away from the SDL implementation, so that the
	 * user will not have to interface with any SDL functionality directly.
	 * */
	class Rect : public Polygon {
	public:
		int x; /**< X-pos of the rectangle. */
		int y; /**< Y-pos of the rectangle. */
		int w; /**< Width of the rectangle.*/
		int h; /**< Height of the rectangle. */
		/**
		 * Rectangle contructor. Direct analogue to initialization of SDL_Rect.
		 * */
		Rect(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	/* Forward declarations of each class so they can reference eachother */
	class Engine;
	class IO;
	class Game;
	class Texture;

	/**
	 * Mazzycat provides information about the engine and its settings to
	 * members -- soon will be deprecated for Engine static functions and
	 * variables.
	 *  */
	class Mazzycat {
	public:
		static std::vector<YAML::Node> data; /**< Loaded Mazzycat file. */
		static void Init();					 /**< Load Mazzycat file. */
		static String GetName();			 /**< Name of game. */
		static IntPair GetWindowSize();		 /**< Window width/height. */
		static int GetFramerate();			 /**< Framerate of engine. */
		static StringMap GetPaths();		 /**< Paths map from Mazzycat. */
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
		static String name; /**< Name of this Game. From Mazzycat. */
		static std::vector<Texture *>
			textures;			  /**< Registry of Textures. @see Texture */
		static String data_path;  /**< Path to data files. */
		static String img_path;	  /**< Path to image files. */
		static String audio_path; /**< Path to audio files. */
		/**
		 * Engine constructor. Sets everything to their default values.
		 * */
		Engine() {
			auto data = YAML::LoadFile("Mazzycat");

			_io = nullptr;
			renderer = nullptr;
			_game = nullptr;
			textures.clear();

			if (data["name"]) {
				name = data["name"].as<String>();
			}

			window_width = data["window_width"].as<int>();
			window_height = data["window_height"].as<int>();

			if (data["framerate"]) {
				framerate = data["framerate"].as<int>();
			}

			if (data["data_path"]) {
				data_path = data["data_path"].as<String>();
			}
			if (data["img_path"]) {
				img_path = data["img_path"].as<String>();
			}
			if (data["audio_path"]) {
				audio_path = data["audio_path"].as<String>();
			}
		};
		int SetIO(IO *io);			/**< Sets the IO instance. */
		int SetGame(Game *game);	/**< Sets the Game instance. */
		int Start();				/**< Starts the engine. */
		static void LoadTextures(); /**< Load all textures that need loading. */
	};

	/**
	 * IO class represents how the program should read in inputs, and how it
	 * should parse those into output buttons. Users should use provided
	 * implementations or write their own.
	 * */
	class IO {
	public:
		static ButtonVector *presses;  /**< Button presses this tick. */
		static ButtonVector *releases; /**< Button releases this tick. */
		static double
			*cursor_x; /**< X position of cursor as % of window width. */
		static double
			*cursor_y;		/**< Y position of cursor as % of window height. */
		int *window_width;	/**< Pixel width of window. */
		int *window_height; /**< Pixel height of window. */

		IO(){}; /**< Constructor. Doesn't do anything right now. */
		virtual int ReadSettings() = 0; /**< Load settings based on file
										   provided in Mazzycat. */
		/**
		 * Parses a single SDL_Event and puts the corresponding press/release
		 * into presses/releases.
		 * @param event SDL_Event * from Engine instance.
		 * */
		virtual int Parse(SDL_Event *event) = 0;
	};

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
		String name;

		/**
		 * Constructor of Game. Loads simple data for children.
		 * @param _name name of this Game instance.
		 * @param _parent parent of this Game instance.
		 * */
		Game(String _name, Game *_parent) {
			parent = _parent;
			name = _name;
			YAML::Node data =
				YAML::LoadFile(Mazzycat::GetPaths()["data"] + _name + ".yaml");
			internal_width = data["width"].as<int>();
			internal_height = data["height"].as<int>();
		}

		/**
		 * Take command and parse it to modify state of this Game. Should
		 * usually be used by child.
		 * @param command Vector of String commands to be parsed by this
		 * function.
		 *  */
		virtual int Command(StringVector *command, size_t offset) = 0;
		/**
		 * Update state of this Game based on current status.
		 * @param status Current status of Engine/parent/etc.
		 *  */
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0; /**< Draw current state to Engine renderer. */
	};

	/**
	 * Abstraction of SDL_Texture so that the engine has control over loading,
	 * making sure that it is loaded when the Game wants it to be drawn and
	 * whatnot. Users should only use raw SDL_Textures or interface with SDL
	 * directly if they are entirely comfortable with the uncertainties of it.
	 * */
	class Texture {
	public:
		SDL_Texture
			*texture; /**< May be null, but will never be null when drawn. */
		String path;  /**< Path of the texture intended to be loaded. */
		/**
		 * Texture constructor. Stores the path and loads texture when there is
		 * offtime or when a LoadTextures() is called.
		 * @param path Path of texture relative to images folder.
		 * */
		Texture(std::string path) {
			this->path = path;
			texture = nullptr;
			Engine::textures.push_back(this);
		}
		void Load(); /**< Load the texture if it isn't already loaded. */
		/**
		 * Draws Texture from src to dest.
		 * @param src Rectangle indicating where on texture is being copied.
		 * @param dest Rectangle indicating where on Engine::renderer the
		 * texture should be drawn.
		 * */
		void Draw(Rect *src, Rect *dest);
		bool IsLoaded();
	};

	/**
	 * Abstraction of SDL_mixer so that the engine can deal with the
	 * particulars. TODO.
	 * */
	class Audio {};

	/**
	 * Abstraction of SDL_ttf functions so that the engine can deal with the
	 * particulars. TODO.
	 * */
	class Font {};

} // namespace mazengine
#endif
