#ifndef MAZENGINE_H_
#define MAZENGINE_H_

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#define STATUS_OK 0
#define ENGINE_KILL -1
#define UNSET_VALUE_ERROR -2

namespace mazengine {

	enum button {
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

	class engine;
	class io;
	class game;

	class engine {
	protected:
		io *_io;
		game *_game;
		int window_width;
		int window_height;
		std::string name;

	public:
		engine(int width, int height, std::string name) {
			window_width = width;
			window_height = height;
			this->name = name;
			_io = nullptr;
			_game = nullptr;
		};
		int set_io(io *io);
		int set_game(game *game);
		int start();
	};

	class io {
	protected:
		std::vector<button> *presses;
		std::vector<button> *releases;

	public:
		io(){};
		virtual int read_settings() = 0;
		void pass_vectors(std::vector<button> *presses,
						  std::vector<button> *releases);
		virtual int parse(SDL_Event *event) = 0;
	};

	class game {
	protected:
		std::vector<button> *presses;
		std::vector<button> *releases;
		int internal_width;
		int internal_height;

	public:
		std::string name;
		SDL_Renderer *renderer;
		game() {
			renderer = nullptr;
			name = "UNSET";
		};
		void pass_vectors(std::vector<button> *presses,
						  std::vector<button> *releases);
		virtual int initial_tick() = 0;
		virtual int tick(int status) = 0;
		virtual int draw() = 0;
		virtual int present() = 0;
		virtual int reaction(int) = 0;
	};

} // namespace mazengine
#endif
