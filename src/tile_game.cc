#include "mazengine/tile_game.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace mazengine;

int TileGame::InitialTick() {
	if (name == "UNSET" || renderer == nullptr) {
		std::cout << "name not yet set" << std::endl;
		return UNSET_VALUE_ERROR;
	}
	YAML::Node mz = YAML::LoadFile("Mazzycat");
	audio_path = mz["audio_path"].as<String>();
	img_path = mz["img_path"].as<String>();
	data_path = mz["data_path"].as<String>();

	this->tiles = new TileRenderer(
		renderer, img_path, YAML::LoadFile(data_path + "img.yaml")["tilesets"],
		tile_width, tile_height, tile_size, tile_size);

	player = new tile_player(data_path);

	map_key = player->map_key;
	map_yaml = YAML::LoadFile(data_path + "map.yaml");
	current_map =
		new TileMap(data_path + map_yaml[map_key]["path"].as<String>(),
					map_yaml[map_key]["name"].as<String>(), renderer);

	return STATUS_OK;
}

int TileGame::Tick(int status) {
	int rv = STATUS_OK;
	std::vector<TileEntity> *objs = current_map->get_objects();
	std::vector<void (*)(Button, int *)> funcs;
	player->Tick(presses, releases);
	for (Button press : *presses) {
		if (press == KILL) {
			return ENGINE_KILL;
		}
		for (TileEntity obj : *objs) {
			funcs = *obj.get_press_hooks();
			for (auto func : funcs) {
				func(press, &rv);
			}
		}
	}
	for (Button release : *releases) {
		for (TileEntity obj : *objs) {
			funcs = *obj.get_release_hooks();
			for (auto func : funcs) {
				func(release, &rv);
			}
		}
	}
	return rv;
}

int TileGame::Draw() {
	tiles->Clear(current_map->bg_color);
	// std::cout << SDL_GetError() << std::endl;
	std::vector<TileLayer> *layers = current_map->get_layers();
	for (TileLayer layer : *layers) {
		tiles->Draw_layer(&layer, player->position_x - player->center_offset_x,
						  player->position_y - player->center_offset_y);
	}
	tiles->DrawSprite(
		player->key, player->id,
		((tile_width + 3) / 2) * tile_size +
			(player->position_x - player->center_offset_x) % tile_size,
		((tile_height + 3) / 2) * tile_size +
			(player->position_y - player->center_offset_y) % tile_size);
	tiles->Draw_to_renderer(
		(player->position_x - player->center_offset_x) % tile_size,
		(player->position_y - player->center_offset_y) % tile_size);
	/* DRAW DEBUG
	std::cout << player->position_x << ", " << player->position_y << ", "
		  << player->position_x / 16 << ", " << player->position_y / 16
		  << ", " << player->position_x % 16 << ", "
		  << player->position_y % 16 << std::endl;
		  */
	return STATUS_OK;
}

int TileGame::Present() {
	tiles->Present();
	return STATUS_OK;
}

int TileGame::React(int idx) { return STATUS_OK; }
