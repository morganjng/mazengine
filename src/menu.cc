#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <mazengine.h>
#include <yaml-cpp/node/parse.h>

namespace mazengine {

	SDL_Rect *MenuWidget::Rect() { return &rect; }

	SDL_Surface *MenuWidget::Texture() { return textures[texture_idx]; }

	int Menu::Tick() {
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
							rv = Command(&widget->on_hover, 0);
						} else {
							rv = Command(&widget->no_hover, 0);
						}
						break;
					case MOUSE_CLICK:
						if (in_rect) {
							rv = Command(&widget->on_click, 0);
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
							rv = Command(&widget->no_click, 0);
						}
						break;
					default:
						break;
				}
			}
		}
		return rv;
	}

	int Menu::Command(std::vector<std::string> *command, size_t offset) {
		if (command->size() <= 0 || command->size() <= offset) {
			return STATUS_OK;
		}
		if (command->at(offset) == "up") {
			return parent->Command(command, offset + 1);
		}
		if (command->size() >= 5 + offset && (*command)[offset] == "set") {
			if ((*command)[offset + 1] == "widget") {
				if ((*command)[offset + 3] == "texture") {
					widgets[std::stoi(command->at(offset + 2))]->texture_idx =
						std::stoi(command->at(offset + 4));
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
