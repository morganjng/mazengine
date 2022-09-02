#include <SDL2/SDL.h>
#include <iostream>
#include <tile_game.h>

using namespace mazengine;

void tile_game::set_audio_path(std::string path) { audio_path = path; }

void tile_game::set_data_path(std::string path) { data_path = path; }

void tile_game::set_img_path(std::string path) { img_path = path; }

int tile_game::initial_tick() {
    if (img_path == "UNSET") {
	std::cout << "img_path not yet set" << std::endl;
	return 2;
    }
    if (data_path == "UNSET") {
	std::cout << "data_path not yet set" << std::endl;
	return 2;
    }
    if (audio_path == "UNSET") {
	std::cout << "audio_path not yet set" << std::endl;
	return 2;
    }

    this->tiles = new tile_renderer(
	renderer, img_path, YAML::LoadFile(data_path + "img.yaml")["tilesets"],
	tile_width, tile_height, tile_size, tile_size);

    player = new tile_player(data_path);

    map_key = player->map_key;
    map_yaml = YAML::LoadFile(data_path + "map.yaml");
    current_map =
	new tile_map(data_path + map_yaml[map_key]["path"].as<std::string>(),
		     map_yaml[map_key]["name"].as<std::string>(), renderer);

    return 0;
}

int tile_game::tick(std::vector<button> *presses,
		    std::vector<button> *releases) {
    std::vector<entity> *objs = current_map->get_objects();
    std::vector<void (*)(button)> funcs;
    player->tick(presses, releases);
    for (button press : *presses) {
	if (press == KILL) {
	    return 1;
	}
	for (entity obj : *objs) {
	    funcs = *obj.get_press_hooks();
	    for (auto func : funcs) {
		func(press);
	    }
	}
    }
    for (button release : *releases) {
	for (entity obj : *objs) {
	    funcs = *obj.get_release_hooks();
	    for (auto func : funcs) {
		func(release);
	    }
	}
    }
    return 0;
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
    return 0;
}

int tile_game::present() {
    tiles->present();
    return 0;
}
