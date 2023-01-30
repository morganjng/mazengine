#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "<mazengine.h>"

auto *GetGame_doc = PyDoc_STR("Gets the game associated with the given name.");
static PyObject *GetGame(PyObject *self, PyObject *args) { Py_RETURN_NONE; }

auto *SetGame_doc =
	PyDoc_STR("Sets the game to the one associated with the given name.");
static PyObject *SetGame(PyObject *self, PyObject *args) { Py_RETURN_NONE; }

auto *SetWindowSize_doc =
	PyDoc_STR("Sets the window size to the provided resolution.");
static PyObject *SetWindowSize(PyObject *self, PyObject *args) {
	Py_RETURN_NONE;
}

PyMethodDef maz_mod_methods[] = {{
									 "GetGame",
									 (PyCFunction)GetGame,
									 METH_VARARGS,
									 GetGame_doc,
								 },
								 {
									 "SetGame",
									 (PyCFunction)SetGame,
									 METH_VARARGS,
									 SetGame_doc,
								 },
								 {
									 "SetWindowSize",
									 (PyCFunction)SetWindowSize,
									 METH_VARARGS,
									 SetWindowSize_doc,
								 },
								 {NULL}};

auto *maz_doc = PyDoc_STR("Module for Mazengine Python bindings");
PyModuleDef maz_mod = {
	PyModuleDef_HEAD_INIT,
	"maz",
	maz_doc,
	-1,
	maz_mod_methods,
	NULL,
	NULL,
	NULL,
	NULL,
};

PyMODINIT_FUNC PyInit_maz(void) {
	auto mod = PyModule_Create(&maz_mod);
	return mod;
}
