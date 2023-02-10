#include <igame.h>
#include <io_2d_mouse.h>
#include <mazengine.h>
#include <tiles.h>

#include <iostream>

using namespace mazengine;

int load_prev() {
	std::string path;
	std::cout << "Enter the map title. " << std::endl;
	std::cin >> path;
	Engine engine;
	IGame tile_test("tile_editor");
	IO2dMouse io;
	tile_test.AddElement(new tiles::Display(path));
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
	return 0;
}

int main() {
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
		ab.push_back(std::string(response));
		std::cout << "Entire the tileset path (relative to image dir)."
				  << std::endl;
		std::cin >> response;
		ab.push_back(std::string(response));
		std::cout << "Enter the tile set width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile set height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the native display width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the native display height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile width." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the tile height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the map witdh." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
		std::cout << "Enter the map height." << std::endl;
		std::cin >> response;
		vals.push_back(std::stoi(response));
	}

	Engine engine;
	IGame tile_test("tile_editor");
	IO2dMouse io;
	tile_test.AddElement(new tiles::Display(
		ab[0], ab[1], vals[0], vals[1], vals[2], vals[3], vals[4], vals[5],
		vals[6], vals[7], Rect(0, 0, 960, 720)));
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
	return 0;
}
