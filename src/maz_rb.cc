#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include <mazengine.h>

using namespace Rice;

Object get_game() {
	if (mazengine::Engine::engine) {
		return String(mazengine::Engine::engine->GetGame()->name);
	} else {
		return String("Sorry! There isn't any engine running");
	}
}

extern "C" void Init_libmaz_rb() {
	Module rb_mMaz =
		define_module("Maz").define_module_function("GetGame", &get_game);
}
