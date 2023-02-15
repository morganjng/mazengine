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
							Engine::Execute(widget->on_hover);
						} else {
							Engine::Execute(widget->no_hover);
						}
						break;
					case MOUSE_CLICK:
						if (in_rect) {
							Engine::Execute(widget->on_click);
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
							Engine::Execute(widget->no_click);
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

	void Menu::SetWidgetValue(std::string value, size_t widget_idx,
							  size_t new_value) {
		(void)value;
		if (widgets.size() > widget_idx) {
			widgets[widget_idx]->texture_idx = new_value;
		}
	}

	void MenuWrapper::SetWidget(std::string u, size_t v, size_t w) {
		menu->SetWidgetValue(u, v, w);
	}

} // namespace mazengine
