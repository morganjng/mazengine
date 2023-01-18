#include "SDL_render.h"
#include "mazengine/mazengine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace mazengine;

SDL_Renderer *Engine::renderer = nullptr;
ButtonVector *IO::presses = nullptr;
ButtonVector *IO::releases = nullptr;
double *IO::cursor_x = nullptr;
double *IO::cursor_y = nullptr;
int Engine::window_width = -1;
int Engine::window_height = -1;
int Engine::framerate = 1;
String Engine::name = "Mazengine Game";
std::vector<Future *> Engine::futures = *new std::vector<Future *>;

void Future::Load() {
	this->texture = IMG_LoadTexture(Engine::renderer, this->path.c_str());
	if (this->texture == NULL) {
		std::cout << "Loading Future " << this->path << " failed, SDL error "
				  << SDL_GetError() << std::endl;
	}
}

void Engine::LoadFutures() {
	for (auto future : futures) {
		if (future != nullptr && future->texture == nullptr) {
			future->Load();
		}
	}
}

void Engine::Draw(Future *future, SDL_Rect *src, SDL_Rect *dest) {
	if (future->texture == nullptr) {
		future->Load();
	}
	int rv = SDL_RenderCopy(Engine::renderer, future->texture, src, dest);
	if (rv != 0) {
		std::cout << "Rendering texture " << future->path
				  << " failed with value " << rv << " SDL error "
				  << SDL_GetError() << std::endl;
	}
}

int Game::Command(StringVector command) { return 0; }

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

	SDL_Window *window = NULL;
	SDL_Event event;

	IO::presses = new ButtonVector;
	IO::releases = new ButtonVector;
	IO::cursor_x = new double;
	IO::cursor_y = new double;

	// TODO set up a settings thing here

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, window_width,
							  window_height, SDL_WINDOW_OPENGL);
	Engine::renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	if (window == NULL) {
		std::cout << "Window creation failed" << std::endl;
		return 2;
	}
	if (Engine::renderer == NULL) {
		std::cout << "Renderer creation failed" << std::endl;
	}

	// add loading screen here soon

	int running = 1;
	int tick_val = 0;
	int frame_count = 0;

	std::cout << "Initializing chronology" << std::endl;

	std::chrono::system_clock::time_point start_time =
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end_time =
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point parse_time =
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point tick_time =
		std::chrono::system_clock::now();
	std::chrono::milliseconds none(0);
	std::chrono::milliseconds tick_rate(1000 / this->framerate);

	_io->window_width = &window_width;
	_io->window_height = &window_height;

	LoadFutures();

	// if (tick_val != STATUS_OK) {
	// 	std::cout << "Something failed in _game->InitialTick" << std::endl;
	// 	return tick_val;
	// }

	std::cout << "Starting " << name << " engine loop" << std::endl;

	while (running == 1) {
		start_time = std::chrono::system_clock::now();

		SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 0);
		SDL_RenderClear(Engine::renderer);

		IO::presses->clear();
		IO::releases->clear();

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

// void Game::PassPointers(ButtonVector *presses, ButtonVector *releases,
// 						double *cursor_x, double *cursor_y) {
// 	this->presses = presses;
// 	this->releases = releases;
// 	this->cursor_x = cursor_x;
// 	this->cursor_y = cursor_y;
// }

// void IO::PassPointers(ButtonVector *presses, ButtonVector *releases,
// 					  double *cursor_x, double *cursor_y) {
// 	this->presses = presses;
// 	this->releases = releases;
// 	this->cursor_x = cursor_x;
// 	this->cursor_y = cursor_y;
// }
