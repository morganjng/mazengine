#include <tiles/display.h>
#include <tiles/editor.h>

#include <fstream>

using namespace mazengine::tiles;

/**
 * Move side of a rectangle, changing width and height with it.
 *   * - 0 - *
 *   |       |
 *   3       1
 *   |       |
 *   * - 2 - *
 * */
void MoveSide(mazengine::Rect *rect, int side, int new_side) {
	switch (side) {
		case 0:
			rect->h = rect->h - (new_side - rect->y);
			rect->y = new_side;
			return;
		case 1:
			rect->w = new_side - rect->x;
			return;
		case 2:
			rect->h = new_side - rect->y;
			return;
		case 3:
			rect->w = rect->w - (new_side - rect->x);
			rect->x = new_side;
			return;
		default:
			return;
	}
}

Display *Display::Load(std::string title) {
	this->title = title;
	auto data = YAML::LoadFile(
		(Engine::data_path + "tiles/" + title + ".yaml").c_str());

	internal_size[0] = data["width"].as<int>();
	internal_size[1] = data["height"].as<int>();

	auto map_size_temp = data["map_size"].as<std::vector<int>>();
	map_size[0] = map_size_temp[0];
	map_size[1] = map_size_temp[1];

	auto tile_size_temp = data["tile_size"].as<std::vector<int>>();
	tile_size[0] = tile_size_temp[0];
	tile_size[1] = tile_size_temp[1];

	auto tileset_size_temp = data["tileset_size"].as<std::vector<int>>();
	tileset_size[0] = tileset_size_temp[0];
	tileset_size[1] = tileset_size_temp[1];

	auto following_pt_temp = data["following_point"].as<std::vector<int>>();
	following_point[0] = following_pt_temp[0];
	following_point[1] = following_pt_temp[1];

	tileset = new Texture(data["tileset"].as<std::string>());

	auto temp = data["tiles"].as<std::vector<std::vector<int>>>();
	tiles = std::vector<std::vector<int>>(temp);

	return this;
}

void Display::Save() {
	std::ofstream fout;
	fout.open(Engine::data_path + "tiles/" + title + ".yaml");

	YAML::Emitter out;
	out.SetIndent(4);

	std::vector<int> temp;
	std::vector<std::string> temp_str;

	out << YAML::BeginMap;

	out << YAML::Key << "triggers";
	out << YAML::Value << triggers;

	out << YAML::Key << "width";
	out << YAML::Value << internal_size[0];

	out << YAML::Key << "height";
	out << YAML::Value << internal_size[1];

	out << YAML::Key << "tileset";
	out << YAML::Value << tileset->path;

	temp.clear();
	temp.push_back(map_size[0]);
	temp.push_back(map_size[1]);

	out << YAML::Key << "map_size";
	out << YAML::Value << temp;

	temp.clear();
	temp.push_back(tile_size[0]);
	temp.push_back(tile_size[1]);

	out << YAML::Key << "tile_size";
	out << YAML::Value << temp;

	temp.clear();
	temp.push_back(tileset_size[0]);
	temp.push_back(tileset_size[1]);

	out << YAML::Key << "tileset_size";
	out << YAML::Value << temp;

	temp.clear();
	temp.push_back(following_point[0]);
	temp.push_back(following_point[1]);

	out << YAML::Key << "following_point";
	out << YAML::Value << temp;

	out << YAML::Key << "tiles";
	out << YAML::Value << tiles;
	out << YAML::EndMap;

	fout << out.c_str();

	fout.close();
}

Display *Display::Tileset(std::string tileset_path) {
	tileset = new Texture(tileset_path);
	return this;
}

Display *Display::Title(std::string title) {
	this->title = title;
	return this;
}

Display *Display::TileSize(int w, int h) {
	tile_size[0] = w;
	tile_size[1] = h;
	return this;
}
Display *Display::MapSize(int w, int h, int tile_preset) {
	map_size[0] = w;
	map_size[1] = h;
	for (int i = 0; i < h; i++) {
		tiles.push_back(std::vector<int>());
		for(int j = 0; j < w; j++) {
			tiles[i].push_back(tile_preset);
		}
	}
	return this;
}
Display *Display::TilesetSize(int w, int h) {
	tileset_size[0] = w;
	tileset_size[1] = h;
	return this;
}

Display *Display::InternalSize(int w, int h) {
	internal_size[0] = w;
	internal_size[1] = h;
	return this;
}

Display *Display::FollowingPoint(int x, int y) {
	following_point[0] = x;
	following_point[1] = y;
	return this;
}

Display *Display::Output(int x, int y, int w, int h) {
	this->output.x = x;
	this->output.y = y;
	this->output.w = w;
	this->output.h = h;
	return this;
}

EditorFollow *Display::Editor() {
	triggers.push_back("onclick");
	triggers.push_back("onpress");

	auto e = new EditorFollow(tile_size[0], tile_size[1], map_size[0],
							  map_size[1], this);

	Engine::engine->main_namespace["editor"] =
		boost::python::object(*new EFWrapper(e));
	following = e;

	entities.push_back(*e);
	status = 254;

	return e;
};

std::pair<int, int> Display::ScreenToWorld(int x, int y) {
	std::pair<int, int> a;
	if (!output.Contains(x, y)) {
		a.first = -1;
		a.second = -1;
		return a;
	}
	int w_scale = output.w / internal_size[0];
	int h_scale = output.h / internal_size[1];
	int _x = x - following_point[0] * w_scale +
		(following->location.w / 2 * w_scale) + following->location.x * w_scale;
	int _y = y - following_point[1] * h_scale +
		(following->location.h / 2 + h_scale) + following->location.y * h_scale;
	a.first = _x / (tile_size[0] * w_scale);
	a.second = _y / (tile_size[1] * h_scale);
	if (a.first < 0 || a.first > map_size[0]) {
		a.second = -1;
	}
	if (a.second < 0 || a.second > map_size[1]) {
		a.second = -1;
	}
	return a;
}

void Display::ConfigureRects(int x, int y) {
	if (x < 0 || y < 0 || x >= map_size[0] || y >= map_size[1] ||
		GetTile(x, y) == -1) {
		tile_location_rect.x = 0;
		tile_location_rect.y = 0;
		tile_location_rect.w = 0;
		tile_location_rect.h = 0;
		return;
	}
	int tile_index = GetTile(x, y);

	int w = tileset_size[0] / tile_size[0];

	texture_location_rect.x = (tile_index % w) * tile_size[0];
	texture_location_rect.y = (tile_index / w) * tile_size[1];

	texture_location_rect.w = tile_size[0];
	texture_location_rect.h = tile_size[1];

	tile_location_rect.w = tile_size[0] * (output.w / internal_size[0]);
	tile_location_rect.h = tile_size[1] * (output.h / internal_size[1]);

	int follow_point_x = following->location.x + (following->location.w / 2);
	int follow_point_y = following->location.y + (following->location.h / 2);

	int tl_x = -follow_point_x + following_point[0];
	int tl_y = -follow_point_y + following_point[1];

	int w_scale = output.w / internal_size[0];
	int h_scale = output.h / internal_size[1];

	tile_location_rect.x = ((x * tile_size[0] + tl_x) * w_scale) + output.x;
	tile_location_rect.y = ((y * tile_size[1] + tl_y) * h_scale) + output.y;

	if (tile_location_rect.x < output.x) {
		MoveSide(&texture_location_rect, 3,
				 ((output.x - tile_location_rect.x) / w_scale) +
					 texture_location_rect.x);
		MoveSide(&tile_location_rect, 3, output.x);
	}

	if (tile_location_rect.y < output.y) {
		MoveSide(&texture_location_rect, 0,
				 ((output.y - tile_location_rect.y) / h_scale) +
					 texture_location_rect.y);
		MoveSide(&tile_location_rect, 0, output.y);
	}

	if (tile_location_rect.x + tile_location_rect.w > output.x + output.w) {
		MoveSide(&texture_location_rect, 1,
				 ((output.x + output.w - tile_location_rect.x) / w_scale) +
					 texture_location_rect.x);
		MoveSide(&tile_location_rect, 1, output.x + output.w);
	}

	if (tile_location_rect.y + tile_location_rect.h > output.y + output.h) {
		MoveSide(&texture_location_rect, 2,
				 ((output.y + output.h - tile_location_rect.y) / h_scale) +
					 texture_location_rect.y);
		MoveSide(&tile_location_rect, 2, output.y + output.h);
	}
}

int Display::GetTile(int x, int y) { return tiles[y][x]; }

int Display::Tick() {
	for (std::string trigger : triggers) {
		for (Entity e : entities) {
			Engine::Execute(e.behaviors[trigger]);
		}
	}
	return 0;
}
int Display::Draw() {
	int off_x =
		(following->location.x + (following->location.w / 2)) / tile_size[0];
	int off_y =
		(following->location.y + (following->location.h / 2)) / tile_size[1];
	off_x = off_x - 1 - (internal_size[0] / tile_size[0] / 2);
	off_y = off_y - 1 - (internal_size[0] / tile_size[0] / 2);
	for (int i = 0; i < 2 + (internal_size[1] / tile_size[1]); i++) {
		for (int j = 0; j < 2 + (internal_size[0] / tile_size[0]); j++) {
			ConfigureRects(off_x + j, off_y + i);
			tileset->Draw(&texture_location_rect, &tile_location_rect);
		}
	}
	for (Entity entity : entities) {
	}
	if (status == 255) {
		tileset->Draw(nullptr, &output);
		int x_pos = *IO::cursor_x * Engine::window_width;
		int y_pos = *IO::cursor_y * Engine::window_height;
		int tile_w = tileset_size[0] / tile_size[0];
		int tile_h = tileset_size[1] / tile_size[1];
		tile_w = 960 / tile_w;
		tile_h = 720 / tile_h;
		int x = x_pos / tile_w;
		int y = y_pos / tile_h;
		x *= tile_w;
		y *= tile_h;
		Rect r(x, y, tile_w, tile_h);
		following->texture->Draw(nullptr, &r);
	}
	if (status == 254) {
		int x_pos = *IO::cursor_x * Engine::window_width;
		int y_pos = *IO::cursor_y * Engine::window_height;
		auto a = ScreenToWorld(x_pos, y_pos);
		ConfigureRects(a.first, a.second);
		following->texture->Draw(nullptr, &tile_location_rect);
	}
	return 0;
}

void Display::SetTile(int x, int y, int val) {
	if (x == -1 || y == -1) {
		return;
	}
	tiles[y][x] = val;
}
