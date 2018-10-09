#ifndef __PY_CALL_ME_PYTHON__
#define __PY_CALL_ME_PYTHON__

//#define MODULE_NAME "py_bridge"
#define MODULE_DOC_STRING "Enable writing Redis modules in Python"

#include <Python.h>

PyObject* hi();

PyObject* bye();

PyObject* RegisterCommand(PyObject* self, PyObject* cmd);

#endif
