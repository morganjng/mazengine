
#include <rice/rice.hpp>
#include <rice/stl.hpp>

using namespace Rice;

Object test_hello(Object) {
	String str("hello!");
	return str;
}

extern "C" void Init_libmaz_rb() {
	Class rb_cTest = define_class("Test").define_method("hello", &test_hello);
}
