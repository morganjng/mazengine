#include <tile_map.h>

using namespace mazengine;

std::vector<TileLayer> *tile_map::get_layers() { return &layers; }

std::vector<TileEntity> *tile_map::get_objects() { return &objects; }
