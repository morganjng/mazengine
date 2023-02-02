#include <boost/python.hpp>

#include <mazengine.h>
#include <menu.h>

using namespace boost::python;

BOOST_PYTHON_MODULE(libmazengine) { class_<mazengine::Engine>("Engine"); }
