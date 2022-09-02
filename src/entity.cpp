#include <entity.h>

using namespace mazengine;

int entity::push_press_hook(void func(button press)) {
	press_hooks.push_back(func);
	return 0;
}

int entity::push_release_hook(void func(button release)) {
	release_hooks.push_back(func);
	return 0;
}

std::vector<void (*)(button)> *entity::get_press_hooks() {
	return &press_hooks;
}

std::vector<void (*)(button)> *entity::get_release_hooks() {
	return &release_hooks;
}
