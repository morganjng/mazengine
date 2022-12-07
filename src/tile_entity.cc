#include <tile_entity.h>

using namespace mazengine;

int TileEntity::push_press_hook(void func(Button, int *)) {
	press_hooks.push_back(func);
	return STATUS_OK;
}

int TileEntity::push_release_hook(void func(Button, int *)) {
	release_hooks.push_back(func);
	return STATUS_OK;
}

std::vector<void (*)(Button, int *)> *TileEntity::get_press_hooks() {
	return &press_hooks;
}

std::vector<void (*)(Button, int *)> *TileEntity::get_release_hooks() {
	return &release_hooks;
}
