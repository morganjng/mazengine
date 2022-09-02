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
		return -1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Initializing SDL failed" << std::endl;
		return 1;
	}

	if (_io->read_settings() == -1) {
		std::cout << "Failed to read settings" << std::endl;
		return 2;
	}

	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Event event;
	std::vector<button> presses;
	std::vector<button> releases;

	// TODO set up a settings thing here

	window = SDL_CreateWindow("Dry Springs", SDL_WINDOWPOS_CENTERED,
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

	tick_val = _game->initial_tick();

	if (tick_val != 0) {
		std::cout << "Something failed in _game->initial_tick" << std::endl;
		return tick_val;
	}

	while (running == 1) {
		start_time = std::chrono::system_clock::now();

		end_time = std::chrono::system_clock::now();

		presses.clear();
		releases.clear();

		while (SDL_PollEvent(&event)) {
			_io->parse(&event, &presses, &releases);
		}
		tick_val = _game->tick(&presses, &releases);
		_game->draw();

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
