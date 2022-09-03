#ifndef TILE_ENTITY_H_
#define TILE_ENTITY_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class tile_entity {
	private:
		std::vector<void (*)(button, int *)> press_hooks;
		std::vector<void (*)(button, int *)> release_hooks;

	public:
		tile_entity() {
			press_hooks = *new std::vector<void (*)(button, int *)>();
			release_hooks = *new std::vector<void (*)(button, int *)>();
			type = "UNSET";
			id = -1;
			x = -1;
			y = -1;
		};

		tile_entity(std::string type, std::string key, int id, int x, int y) {
			press_hooks = *new std::vector<void (*)(button, int *)>();
			release_hooks = *new std::vector<void (*)(button, int *)>();
			this->type = type;
			this->key = key;
			this->id = id;
			this->x = x;
			this->y = y;
		};
		std::string type;
		std::string key;
		int id;
		int x;
		int y;
		int push_press_hook(void func(button press, int *rv));
		int push_release_hook(void func(button release, int *rv));
		std::vector<void (*)(button, int *)> *get_press_hooks();
		std::vector<void (*)(button, int *)> *get_release_hooks();
	};
}; // namespace mazengine

#endif // ENTITY_H_
