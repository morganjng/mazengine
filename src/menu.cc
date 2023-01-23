#include "mazengine/menu.h"
#include "mazengine/mazengine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <yaml-cpp/node/parse.h>

namespace mazengine {

	SDL_Rect *MenuWidget::Rect() { return &rect; }

	SDL_Surface *MenuWidget::Texture() { return textures[texture_idx]; }

	int Menu::Tick(int status) {
		SDL_Point mouse_location;
		mouse_location.x = int(*IO::cursor_x * internal_width);
		mouse_location.y = int(*IO::cursor_y * internal_height);
		int rv = STATUS_OK;
		for (MenuWidget *widget : widgets) {
			bool in_rect = SDL_PointInRect(&mouse_location, widget->Rect());
			for (Button press : *IO::presses) {
				switch (press) {
					case MOUSE_MOTION:
						if (in_rect) {
							rv = Command(&widget->on_hover);
						} else {
							rv = Command(&widget->no_hover);
						}
						break;
					case MOUSE_CLICK:
						if (in_rect) {
							rv = Command(&widget->on_click);
						}
						break;
					default:
						break;
				}
			}
			for (Button release : *IO::releases) {
				switch (release) {
					case MOUSE_CLICK:
						if (in_rect) {
							rv = Command(&widget->no_click);
						}
						break;
					default:
						break;
				}
			}
		}
		return rv;
	}

	int Menu::Command(StringVector *command) {
		if (command->size() <= 0) {
			return STATUS_OK;
		}
		if (command->at(0) == "up") {
			for (unsigned int i = 0; i < command->size() - 1; i++) {
				(*command)[i] = (*command)[i + 1];
			}
			command->pop_back();
			// std::cout << "Calling ";
			// for (unsigned int i = 0; i < command->size(); i++) {
			// 	std::cout << command->at(i) << ", ";
			// }
			// std::cout << " for " << parent->name << std::endl;
			return parent->Command(command);
		}
		if (command->size() >= 5 && (*command)[0] == "set") {
			if ((*command)[1] == "widget") {
				if ((*command)[3] == "texture") {
					widgets[std::stoi(command->at(2))]->texture_idx =
						std::stoi(command->at(4));
				}
			}
		}

		return 0;
	}

	int Menu::Draw() {
		SDL_FillRect(internal_surface, NULL, 0);
		for (MenuWidget *widget : widgets) {
			if (widget->Texture() == NULL || widget->Texture() == nullptr) {
				std::cout << widget->name << " nullptr" << std::endl;
			}
			SDL_BlitScaled(widget->Texture(), NULL, internal_surface,
						   widget->Rect());
		}
		SDL_Texture *texture =
			SDL_CreateTextureFromSurface(Engine::renderer, internal_surface);
		SDL_RenderCopy(Engine::renderer, texture, NULL, NULL);
		SDL_DestroyTexture(texture);
		return STATUS_OK;
	}

} // namespace mazengine
