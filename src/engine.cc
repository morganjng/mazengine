#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <iostream>
#include <mazengine.h>
#include <thread>
#include <vector>

using namespace mazengine;

int Engine::SetIO(IO *io) {
	_io = io;
	return 1;
}

int Engine::SetGame(Game *game) {
	_game = game;
	return 1;
}

int Engine::Start() {
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

	if (_io->ReadSettings() == UNSET_VALUE_ERROR) {
		std::cout << "Failed to read settings" << std::endl;
		return UNSET_VALUE_ERROR;
	}

	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Event event;

	double cursor_x = 0;
	double cursor_y = 0;
	ButtonVector presses;
	ButtonVector releases;

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
	std::chrono::system_clock::time_point parse_time =
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point tick_time =
		std::chrono::system_clock::now();
	std::chrono::milliseconds none(0);
	std::chrono::milliseconds tick_rate(20);

	_game->renderer = renderer;

	_game->PassPointers(&presses, &releases, &cursor_x, &cursor_y);
	_io->PassPointers(&presses, &releases, &cursor_x, &cursor_y);
	_io->window_width = &window_width;
	_io->window_height = &window_height;

	tick_val = _game->InitialTick();

	if (tick_val != STATUS_OK) {
		std::cout << "Something failed in _game->InitialTick" << std::endl;
		return tick_val;
	}

	std::cout << "Starting " << name << " engine loop" << std::endl;

	while (running == 1) {
		start_time = std::chrono::system_clock::now();

		SDL_RenderClear(renderer);

		presses.clear();
		releases.clear();

		while (SDL_PollEvent(&event)) {
			_io->Parse(&event);
		}

		parse_time = std::chrono::system_clock::now();

		tick_val = _game->Tick(STATUS_OK);

		tick_time = std::chrono::system_clock::now();

		_game->Draw();

		end_time = std::chrono::system_clock::now();

		if (tick_rate - (end_time - start_time) > none) {
			std::this_thread::sleep_for(tick_rate - (end_time - start_time));
		} else {
			std::cout << "Lagging behind on tick " << frame_count << " by "
					  << ((tick_rate) - (end_time - start_time)).count()
					  << std::endl;
		}

		_game->Present();

		if (tick_val == ENGINE_KILL) {
			running = 0;
		}

		/*
		if (tick_val % 100 == 0) {
			std::cout << "Start time: "
					  << std::chrono::system_clock::to_time_t(start_time)
					  << " Parse time: "
					  << std::chrono::system_clock::to_time_t(parse_time)
					  << " Tick time: "
					  << std::chrono::system_clock::to_time_t(tick_time)
					  << " End time: "
					  << std::chrono::system_clock::to_time_t(end_time)
					  << std::endl;
		}
		*/

		frame_count++;
	}

	// tick returning 1 means that we recieved an exit code
	if (tick_val == 1) {
		return 0;
	}

	return tick_val;
}

void Game::PassPointers(ButtonVector *presses, ButtonVector *releases,
						double *cursor_x, double *cursor_y) {
	this->presses = presses;
	this->releases = releases;
	this->cursor_x = cursor_x;
	this->cursor_y = cursor_y;
}

void IO::PassPointers(ButtonVector *presses, ButtonVector *releases,
					  double *cursor_x, double *cursor_y) {
	this->presses = presses;
	this->releases = releases;
	this->cursor_x = cursor_x;
	this->cursor_y = cursor_y;
}
