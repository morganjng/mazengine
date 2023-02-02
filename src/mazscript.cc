#include <boost/python.hpp>

#include <mazengine.h>

using namespace boost::python;

BOOST_PYTHON_MODULE(mazengine) {
	Py_Initialize();

	class_<mazengine::Engine>("Engine");
};
