#include <SDL2/SDL.h>
#include <iostream>
#include <tile_game.h>

using namespace mazengine;

int tile_game::initial_tick() {
	if (name == "UNSET") {
		std::cout << "name not yet set" << std::endl;
		return UNSET_VALUE_ERROR;
	}
	YAML::Node mz = YAML::LoadFile("mazzycat");
	audio_path = mz["audio_path"].as<std::string>();
	img_path = mz["img_path"].as<std::string>();
	data_path = mz["data_path"].as<std::string>();

	this->tiles = new tile_renderer(
		renderer, img_path, YAML::LoadFile(data_path + "img.yaml")["tilesets"],
		tile_width, tile_height, tile_size, tile_size);

	player = new tile_player(data_path);

	map_key = player->map_key;
	map_yaml = YAML::LoadFile(data_path + "map.yaml");
	current_map =
		new tile_map(data_path + map_yaml[map_key]["path"].as<std::string>(),
					 map_yaml[map_key]["name"].as<std::string>(), renderer);

	return STATUS_OK;
}

int tile_game::tick(int status) {
	int rv = STATUS_OK;
	std::vector<tile_entity> *objs = current_map->get_objects();
	std::vector<void (*)(button, int *)> funcs;
	player->tick(presses, releases);
	for (button press : *presses) {
		if (press == KILL) {
			return ENGINE_KILL;
		}
		for (tile_entity obj : *objs) {
			funcs = *obj.get_press_hooks();
			for (auto func : funcs) {
				func(press, &rv);
			}
		}
	}
	for (button release : *releases) {
		for (tile_entity obj : *objs) {
			funcs = *obj.get_release_hooks();
			for (auto func : funcs) {
				func(release, &rv);
			}
		}
	}
	return rv;
}

int tile_game::draw() {
	tiles->clear(current_map->bg_color);
	// std::cout << SDL_GetError() << std::endl;
	std::vector<tile_layer> *layers = current_map->get_layers();
	for (tile_layer layer : *layers) {
		tiles->draw_layer(&layer, player->position_x - player->center_offset_x,
						  player->position_y - player->center_offset_y);
	}
	tiles->draw_sprite(
		player->key, player->id,
		((tile_width + 3) / 2) * tile_size +
			(player->position_x - player->center_offset_x) % tile_size,
		((tile_height + 3) / 2) * tile_size +
			(player->position_y - player->center_offset_y) % tile_size);
	tiles->draw_to_renderer(
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

int tile_game::present() {
	tiles->present();
	return STATUS_OK;
}

int tile_game::reaction(int idx) { return STATUS_OK; }
