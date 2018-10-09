#include "call_me_python.h"
#include <stdio.h>
#include <Python.h>


#if PY_MAJOR_VERSION >= 3
#define INIT_FUNC PyInit_call_me_python
#else
#define INIT_FUNC initcall_me_python
#endif
PyObject* hi()
{
    return Py_BuildValue("s", "Hello, Python extensions world!");
}

PyObject* bye()
{
    return Py_BuildValue("s", "Goodbye, Python extensions world! Part 2");
}

PyObject* RegisterCommand(PyObject* self, PyObject* cmd)
{
    PyObject_CallFunction(cmd,NULL);
}

static PyMethodDef CallMeMethodTable[] = {
    {"hi",  hi, METH_VARARGS, "Saying hi"},
    {"bye",  bye, METH_VARARGS, "Saying bye"},
    {"regcmd",  RegisterCommand, METH_O, "calling a callback"},
    #if PY_MAJOR_VERSION >= 3
    {NULL}
    #else
    {NULL, NULL, 0, NULL}        /* Sentinel */
    #endif
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef s_module_def = {
    PyModuleDef_HEAD_INIT,
    MODULE_NAME,
    MODULE_DOC_STRING,
    -1,
    CallMeMethodTable
};
#endif


PyMODINIT_FUNC
INIT_FUNC(void)
{
#if PY_MAJOR_VERSION >= 3
    PyModule_Create(&s_module_def);
#else
    Py_InitModule(MODULE_NAME, CallMeMethodTable);
#endif    
}
