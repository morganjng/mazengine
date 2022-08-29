#include <tile_map.h>

std::vector<tile_layer> *tile_map::get_layers() { return &layers; }

std::vector<mazengine::entity> *tile_map::get_objects() { return &objects; }
