#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <iostream>
#include <mazengine.h>
#include <thread>
#include <vector>

using namespace mazengine;

int engine::set_io(io *io) {
	_io = io;
	return 1;
}

int engine::set_game(game *game) {
	_game = game;
	return 1;
}

int engine::start() {
	if (_io == nullptr || _game == nullptr) {
		std::cout
			<< "null game or xput. please initialize this before starting "
			   "the engine"
			<< std::endl;
		return ENGINE_KILL;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Initializing SDL failed" << std::endl;
		return ENGINE_KILL;
	}

	if (_io->read_settings() == UNSET_VALUE_ERROR) {
		std::cout << "Failed to read settings" << std::endl;
		return UNSET_VALUE_ERROR;
	}

	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Event event;

	int cursor_x = 0;
	int cursor_y = 0;
	vec_button presses;
	vec_button releases;

	// TODO set up a settings thing here

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, window_width,
							  window_height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	if (window == NULL) {
		std::cout << "Window creation failed" << std::endl;
		return 2;
	}
	if (renderer == NULL) {
		std::cout << "Renderer creation failed" << std::endl;
	}

	int running = 1;
	int tick_val = 0;
	int frame_count = 0;

	std::chrono::system_clock::time_point start_time =
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end_time =
		std::chrono::system_clock::now();
	std::chrono::milliseconds none(0);
	std::chrono::milliseconds tick_rate(20);

	_game->renderer = renderer;

	_game->pass_pointers(&presses, &releases, &cursor_x, &cursor_y);
	_io->pass_pointers(&presses, &releases, &cursor_x, &cursor_y);

	tick_val = _game->initial_tick();

	if (tick_val != STATUS_OK) {
		std::cout << "Something failed in _game->initial_tick" << std::endl;
		return tick_val;
	}

	std::cout << "Starting " << name << " engine loop" << std::endl;

	while (running == 1) {
		start_time = std::chrono::system_clock::now();

		SDL_RenderClear(renderer);

		presses.clear();
		releases.clear();

		while (SDL_PollEvent(&event)) {
			_io->parse(&event);
		}

		tick_val = _game->tick(STATUS_OK);

		_game->draw();

		end_time = std::chrono::system_clock::now();

		if (tick_rate - (end_time - start_time) > none) {
			std::this_thread::sleep_for(tick_rate - (end_time - start_time));
		} else {
			std::cout << "Lagging behind on tick " << frame_count << std::endl;
		}

		_game->present();

		if (tick_val == ENGINE_KILL) {
			running = 0;
		}

		frame_count++;
	}

	// tick returning 1 means that we recieved an exit code
	if (tick_val == 1) {
		return 0;
	}

	return tick_val;
}

void game::pass_pointers(vec_button *presses, vec_button *releases,
						 int *cursor_x, int *cursor_y) {
	this->presses = presses;
	this->releases = releases;
}

void io::pass_pointers(vec_button *presses, vec_button *releases, int *cursor_x,
					   int *cursor_y) {
	this->presses = presses;
	this->releases = releases;
	this->cursor_x = cursor_x;
	this->cursor_y = cursor_y;
}
