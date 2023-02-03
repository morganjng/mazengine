#include <boost/core/noncopyable.hpp>
#include <boost/python.hpp>

#include <mazengine.h>
#include <menu.h>

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

class MenuWrapper {
public:
	MenuWrapper() { menu = (mazengine::Menu *)MZ::engine->GetGame(); }
	mazengine::Menu *menu;
	void SetWidget(std::string u, size_t v, size_t w) {
		menu->SetWidgetValue(u, v, w);
	}
};

BOOST_PYTHON_MODULE(libmazengine) {
	class_<MenuWrapper>("Menu").def("SetWidget", &MenuWrapper::SetWidget);
	def("SetGame", &SetGame);
	def("Kill", &Kill);
	def("GetWindowDimensions", &GetWindowDimensions);
	def("SetWindowDimensions", &SetWindowDimensions)
}
