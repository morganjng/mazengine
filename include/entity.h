#ifndef ENTITY_H_
#define ENTITY_H_

#include "mazengine.h"
#include <vector>

using namespace mazengine;

class entity {
private:
	std::vector<void (*)(button, int *)> press_hooks;
	std::vector<void (*)(button, int *)> release_hooks;

public:
	entity() {
		press_hooks = *new std::vector<void (*)(button, int *)>();
		release_hooks = *new std::vector<void (*)(button, int *)>();
		type = "UNSET";
		id = -1;
		x = -1;
		y = -1;
	};

	entity(std::string type, std::string key, int id, int x, int y) {
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

#endif // ENTITY_H_
