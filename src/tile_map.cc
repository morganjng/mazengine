#include "mazengine/tile_map.h"

using namespace mazengine;

std::vector<TileLayer> *TileMap::get_layers() { return &layers; }

std::vector<TileEntity> *TileMap::get_objects() { return &objects; }
