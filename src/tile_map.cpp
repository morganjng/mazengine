#include <tile_map.h>

using namespace mazengine;

std::vector<tile_layer> *tile_map::get_layers() { return &layers; }

std::vector<entity> *tile_map::get_objects() { return &objects; }
