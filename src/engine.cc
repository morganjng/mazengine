#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>
#include <chrono>
#include <iostream>
#include <mazengine.h>
#include <thread>
#include <vector>
#include <yaml-cpp/yaml.h>

#include <texture.h>

namespace mazengine {
	auto data = YAML::LoadFile("Mazzycat");
	SDL_Renderer *Engine::renderer = nullptr;
	std::vector<Button> *IO::presses = nullptr;
	std::vector<Button> *IO::releases = nullptr;
	double *IO::cursor_x = nullptr;
	double *IO::cursor_y = nullptr;
	int Engine::window_width =
		data["window_width"] ? data["window_width"].as<int>() : -1;
	int Engine::window_height =
		data["window_height"] ? data["window_height"].as<int>() : -1;
	int Engine::framerate = data["framerate"] ? data["framerate"].as<int>() : 1;
	std::string Engine::name = "Mazengine Game";
	std::string Engine::data_path = "data/";
	std::string Engine::img_path = "img/";
	std::string Engine::audio_path = "audio/";
	Engine *Engine::engine = nullptr;

	void Engine::LoadTextures() {
		for (auto texture : Texture::registry) {
			if (texture != nullptr && texture->texture == nullptr) {
				texture->Load();
			}
		}
	}

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

		IO::presses = new std::vector<Button>;
		IO::releases = new std::vector<Button>;
		IO::cursor_x = new double;
		IO::cursor_y = new double;

		// TODO set up a settings thing here

		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED, window_width,
								  window_height, SDL_WINDOW_OPENGL);
		Engine::renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

		int img_rv = IMG_Init(IMG_INIT_PNG);
		int ttf_rv = TTF_Init();
		int mix_rv = Mix_Init(MIX_INIT_MP3);

		if (img_rv == 0) {
			std::cout << "Initializing SDL_IMG failed." << std::endl;
			return img_rv;
		}
		if (mix_rv == 0) {
			std::cout << "Initializing SDL_mixer failed." << std::endl;
			return img_rv;
		}
		if (ttf_rv != 0) {
			std::cout << "Initializing SDL_TTF failed." << std::endl;
			return ttf_rv;
		}
		if (window == NULL) {
			std::cout << "Window creation failed." << std::endl;
			return 2;
		}
		if (Engine::renderer == NULL) {
			std::cout << "Renderer creation failed." << std::endl;
			return ENGINE_KILL;
		}

		// add loading screen here soon

		this->running = 1;
		int tick_val = 0;
		int frame_count = 0;

		std::cout << "Initializing chronology." << std::endl;

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

		LoadTextures();
		size_t textures_cursor = Texture::registry.size();

		std::cout << "Starting " << name << " engine loop." << std::endl;

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

			while (textures_cursor < Texture::registry.size() &&
				   tick_rate - (std::chrono::system_clock::now() - start_time) >
					   none) {
				if (Texture::registry[textures_cursor] != nullptr) {
					Texture::registry[textures_cursor]->Load();
				}
				textures_cursor++;
			}

			if (tick_rate - (end_time - start_time) > none) {
				std::this_thread::sleep_for(tick_rate -
											(end_time - start_time));
			} else {
				std::cout << "Lagging behind on tick " << frame_count << " by "
						  << ((tick_rate) - (end_time - start_time)).count()
						  << std::endl;
			}

			SDL_RenderPresent(Engine::renderer);

			if (tick_val == ENGINE_KILL) {
				running = 0;
			}

			frame_count++;
		}

		IMG_Quit();
		TTF_Quit();
		Mix_Quit();

		return tick_val;
	}

	IO *Engine::GetIO() { return this->_io; }

	Game *Engine::GetGame() { return this->_game; }

} // namespace mazengine
