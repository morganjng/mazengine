#include <igame.h>
#include <io_2d_mouse.h>
#include <io_mouse.h>
#include <mazengine.h>
#include <tiles.h>

#include <functional>
#include <map>

using namespace mazengine;

std::map<std::string, std::function<void(void)>> tests;

void tiles_test() {
	Engine engine;
	IGame tile_test("tile_test");
	IOMouse io;
	tile_test.AddElement(new tiles::Display("test", Rect(0, 0, 640, 480)));
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
}

void tiles_editor_test() {
	Engine engine;
	IGame tile_test("tile_editor");
	IO2dMouse io;
	tile_test.AddElement(new tiles::Display("edit_test", "tile.png", 32, 32,
											320, 240, 16, 16, 16, 16,
											Rect(0, 0, 960, 720)));
	engine.SetGame(&tile_test);
	engine.SetIO(&io);
	engine.Start();
}

void setup() {
	tests["tiles"] = tiles_test;
	tests["editor"] = tiles_editor_test;
}

int main(int argc, char *argv[]) {
	setup();
	if (argc == 1) {
		return 0;
	} else if (argc == 2) {
		std::cout << "Testing " << argv[1] << " if available." << std::endl;
		if (tests[static_cast<std::string>(argv[1])]) {
			tests[static_cast<std::string>(argv[1])]();
		} else {
			std::cout << "No test for " << argv[1] << " available. Sorry :("
					  << std::endl;
		}
	}
	return 0;
}
