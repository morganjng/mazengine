#ifndef MAZENGINE_H_
#define MAZENGINE_H_

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <functional>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#define STATUS_OK 0
#define ENGINE_KILL -1
#define UNSET_VALUE_ERROR -2

typedef std::vector<std::function<int(int)> *> FuncVector;
typedef std::function<int(int)> Func;
typedef std::vector<std::string> StringVector;

namespace mazengine {

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

	typedef std::vector<Button> ButtonVector;

	class Engine;
	class IO;
	class Game;

	class Engine {
	protected:
		IO *_io;
		Game *_game;
		int window_width;
		int window_height;
		std::string name;

	public:
		Engine(int width, int height, std::string name) {
			window_width = width;
			window_height = height;
			this->name = name;
			_io = nullptr;
			_game = nullptr;
		};
		int set_io(IO *io);
		int set_game(Game *game);
		int Start();
	};

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
		void pass_pointers(ButtonVector *presses, ButtonVector *releases,
						   double *cursor_x, double *cursor_y);
		virtual int Parse(SDL_Event *event) = 0;
	};

	class Game {
	protected:
		ButtonVector *presses;
		ButtonVector *releases;
		double *cursor_x;
		double *cursor_y;
		int internal_width;
		int internal_height;

	public:
		std::string name;
		SDL_Renderer *renderer;
		Game() {
			renderer = nullptr;
			name = "UNSET";
		};
		void pass_pointers(ButtonVector *presses, ButtonVector *releases,
						   double *cursor_x, double *cursor_y);
		virtual int InitialTick() = 0;
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0;
		virtual int Present() = 0;
		virtual int React(int) = 0;
	};

} // namespace mazengine
#endif
