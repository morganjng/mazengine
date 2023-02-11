#include <igame.h>
#include <io_2d_mouse.h>
#include <mazengine.h>
#include <tiles.h>

#include <iostream>

using namespace mazengine;

int load_prev() {
	tiles::Display d;
	std::string path;
	std::cout << "Enter the map title. " << std::endl;
	std::cin >> path;
	d.Load(path);
	d.Output(0, 0, 960, 720);
	Engine engine;
	IGame tile_test("tile_editor");
	IO2dMouse io;
	d.Editor();
	tile_test.AddElement(&d);
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
	return 0;
}

int main() {
	tiles::Display display;
	std::vector<std::string> ab;
	std::vector<int> vals;
	std::string response;
	std::cout << "Would you like to load a previous map? [y/N]" << std::endl;
	std::cin >> response;
	if (response == "y" || response == "Y") {
		return load_prev();
	} else if (response == "" || response == "N" || response == "n") {
		std::cout << "Making a new map. Enter the title. " << std::endl;
		std::cin >> response;
		display.Title(response);
		std::cout << "Enter the tileset path (relative to image dir)."
				  << std::endl;
		std::cin >> response;
		display.Tileset(response);
		ab.push_back(std::string(response));
		std::cout << "Enter the tile set width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile set height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		display.TilesetSize(vals[0], vals[1]);
		std::cout << "Enter the native display width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the native display height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		display.InternalSize(vals[2], vals[3]);
		std::cout << "Enter the tile width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		display.TileSize(vals[4], vals[5]);
		std::cout << "Enter the map witdh." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the map height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile preset." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		display.MapSize(vals[6], vals[7], vals[8]);
		std::cout << "Enter the following x point." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the following y point." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		display.FollowingPoint(vals[9], vals[10]);
	}
	Engine engine;
	IGame tile_test("tile_editor");
	IO2dMouse io;
	display.Output(0, 0, 960, 720);
	auto e = display.Editor();
	(void)e;
	tile_test.AddElement(&display);
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
	return 0;
}
