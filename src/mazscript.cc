#include <boost/core/noncopyable.hpp>
#include <boost/python.hpp>

#include <boost/python/class.hpp>
#include <mazengine.h>
#include <menu.h>
#include <tiles.h>

using namespace boost::python;

void SetGame(std::string game_name) {
	if (MZ::engine)
		mazengine::Engine::engine->SetGame(game_name);
}

void Kill() {
	if (MZ::engine)
		mazengine::Engine::engine->Stop();
}

tuple GetWindowDimensions() {
	return make_tuple(MZ::window_width, MZ::window_height);
}

void SetWindowDimensions(int width, int height) {
	MZ::window_width = width;
	MZ::window_height = height;
	MZ::engine->update_dims = true;
}

BOOST_PYTHON_MODULE(libmazengine) {
	class_<mazengine::MenuWrapper>("Menu").def(
		"SetWidget", &mazengine::MenuWrapper::SetWidget);
	class_<mazengine::tiles::EFWrapper>(
		"Editor", init<mazengine::tiles::EditorFollow *>())
		.def("Move", &mazengine::tiles::EFWrapper::Move)
		.def("Paint", &mazengine::tiles::EFWrapper::Paint);
	def("SetGame", &SetGame);
	def("Kill", &Kill);
	def("GetWindowDimensions", &GetWindowDimensions);
	def("SetWindowDimensions", &SetWindowDimensions);
}
