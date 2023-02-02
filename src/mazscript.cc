#include <boost/core/noncopyable.hpp>
#include <boost/python.hpp>

#include <mazengine.h>
#include <menu.h>

using namespace boost::python;

struct GameWrap : mazengine::Game, wrapper<mazengine::Game> {};

BOOST_PYTHON_MODULE(libmazengine) {
	class_<GameWrap, boost::noncopyable>("Game", no_init);
}
