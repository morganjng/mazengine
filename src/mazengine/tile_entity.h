#ifndef TILE_ENTITY_H_
#define TILE_ENTITY_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class TileEntity {
	private:
		std::vector<void (*)(Button, int *)> press_hooks;
		std::vector<void (*)(Button, int *)> release_hooks;

	public:
		TileEntity() {
			press_hooks = *new std::vector<void (*)(Button, int *)>();
			release_hooks = *new std::vector<void (*)(Button, int *)>();
			type = "UNSET";
			id = -1;
			x = -1;
			y = -1;
		};

		TileEntity(String type, String key, int id, int x, int y) {
			press_hooks = *new std::vector<void (*)(Button, int *)>();
			release_hooks = *new std::vector<void (*)(Button, int *)>();
			this->type = type;
			this->key = key;
			this->id = id;
			this->x = x;
			this->y = y;
		};
		String type;
		String key;
		int id;
		int x;
		int y;
		int push_press_hook(void func(Button press, int *rv));
		int push_release_hook(void func(Button release, int *rv));
		std::vector<void (*)(Button, int *)> *get_press_hooks();
		std::vector<void (*)(Button, int *)> *get_release_hooks();
	};
}; // namespace mazengine

#endif // ENTITY_H_
