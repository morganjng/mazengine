#include <entity.h>

using namespace mazengine;

int entity::push_press_hook(void func(button, int *)) {
	press_hooks.push_back(func);
	return 0;
}

int entity::push_release_hook(void func(button, int *)) {
	release_hooks.push_back(func);
	return 0;
}

std::vector<void (*)(button, int *)> *entity::get_press_hooks() {
	return &press_hooks;
}

std::vector<void (*)(button, int *)> *entity::get_release_hooks() {
	return &release_hooks;
}
