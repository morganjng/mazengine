#include <tile_entity.h>

using namespace mazengine;

int tile_entity::push_press_hook(void func(button, int *)) {
	press_hooks.push_back(func);
	return STATUS_OK;
}

int tile_entity::push_release_hook(void func(button, int *)) {
	release_hooks.push_back(func);
	return STATUS_OK;
}

std::vector<void (*)(button, int *)> *tile_entity::get_press_hooks() {
	return &press_hooks;
}

std::vector<void (*)(button, int *)> *tile_entity::get_release_hooks() {
	return &release_hooks;
}
