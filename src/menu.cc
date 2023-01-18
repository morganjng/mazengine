#include "mazengine/menu.h"
#include "mazengine/mazengine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <yaml-cpp/node/parse.h>

using namespace mazengine;

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
					if (in_rect && widget->on_hover != -1) {
						rv = React(widget->on_hover);
					} else if (!in_rect && widget->on_hover != -1) {
						rv = React(widget->no_hover);
					}
					break;
				case MOUSE_CLICK:
					if (in_rect && widget->on_click != -1) {
						rv = React(widget->on_click);
					}
					break;
				default:
					break;
			}
		}
		for (Button release : *IO::releases) {
			switch (release) {
				case MOUSE_CLICK:
					if (in_rect && widget->no_click != -1) {
						rv = React(widget->no_click);
					}
					break;
				default:
					break;
			}
		}
	}
	return rv;
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

int Menu::Present() {
	SDL_RenderPresent(Engine::renderer);
	return STATUS_OK;
}

int Menu::React(int index) {
	if (size_t(index) >= reactions.size()) {
		std::cout << index << " OUT OF RANGE" << std::endl;
		return STATUS_OK;
	}
	auto func = *reactions[index];
	return func(STATUS_OK);
}

Func *Menu::Parse(String str, int iv) {
	StringVector temp_v = *new StringVector();
	size_t length = str.length();
	String temp;
	for (size_t i = 0; i < length; i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		} else if (str[i] == ' ') {
			temp_v.push_back(String(temp));
			temp.erase(0, str.length());
		}
	}
	temp_v.push_back(temp);
	if (temp_v[0] == "set") {
		if (temp_v[1] == "widget") {
			if (temp_v[3] == "texture") {
				return new Func{[this, temp_v](int s) -> int {
					this->widgets[std::stoi(temp_v[2])]->texture_idx =
						std::stoi(temp_v[4]);
					return STATUS_OK;
				}};
			}
		}
	}
	if (temp_v[0] == "up") {
		return new Func(
			[temp_v](int s) -> int { return std::stoi(temp_v[1]); });
	}

	return nullptr;
}
