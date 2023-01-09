/*
 * Definitions for all necessary classes for the engine to operate.
 */

#ifndef MAZENGINE_H_
#define MAZENGINE_H_

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <functional>
#include <string>
#include <vector>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#define STATUS_OK 0
#define ENGINE_KILL -1
#define UNSET_VALUE_ERROR -2

namespace mazengine {

	/* Enum for input types */
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

	/* Typedefs for long, frequently used types */
	typedef std::string String;
	typedef std::vector<Button> ButtonVector;
	typedef std::vector<std::function<int(int)> *> FuncVector;
	typedef std::function<int(int)> Func;
	typedef std::vector<String> StringVector;
	typedef std::pair<int, int> IntPair;
	typedef std::map<String, String> StringMap;

	/* Forward declarations of each class so they can reference eachother */
	class Engine;
	class IO;
	class Game;

	class Mazzycat {
	public:
		static std::vector<YAML::Node> data;
		static void Init();
		static String GetName();
		static IntPair GetWindowSize();
		static int GetFramerate();
		static StringMap GetPaths();
	};

	/* The engine class represents a wrapper for the game - controls how it
	 * ticks, when it ticks, and when it draws */
	class Engine {
	protected:
		IO *_io;
		Game *_game;
		int window_width;
		int window_height;
		int framerate;
		String name;

	public:
		Engine() {
			_io = nullptr;
			_game = nullptr;
			name = Mazzycat::GetName();
			IntPair dims = Mazzycat::GetWindowSize();
			window_width = dims.first;
			window_height = dims.second;
			framerate = Mazzycat::GetFramerate();
		};
		int SetIO(IO *io);
		int SetGame(Game *game);
		int Start();
	};

	/* IO class represents how the program should read in inputs, and how it
	 * should parse those into output buttons */
	class IO {
	protected:
		ButtonVector *presses;
		ButtonVector *releases;
		double *cursor_x;
		double *cursor_y;

	public:
		int *window_width;
		int *window_height;

		IO(){};
		virtual int ReadSettings() = 0;
		void PassPointers(ButtonVector *presses, ButtonVector *releases,
						  double *cursor_x, double *cursor_y);
		virtual int Parse(SDL_Event *event) = 0;
	};

	/* Game class encompasses the rest of the game -- entities, how to draw, etc
	 */
	class Game {
	protected:
		int internal_width;
		int internal_height;
		Game *parent;

	public:
		ButtonVector *presses;
		ButtonVector *releases;
		double *cursor_x;
		double *cursor_y;
		String name;
		SDL_Renderer *renderer;
		Game(String _name) {
			renderer = nullptr;
			parent = nullptr;
			name = _name;
		};
		void PassPointers(ButtonVector *presses, ButtonVector *releases,
						  double *cursor_x, double *cursor_y);
		virtual int InitialTick() = 0;
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0;
		virtual int Present() = 0;
		virtual int React(int) = 0;
	};

} // namespace mazengine
#endif
