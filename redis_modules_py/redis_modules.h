#ifndef __PY_REDIS_MODULES__
#define __PY_REDIS_MODULES__

#define MODULE_NAME "redis_modules"
#define MODULE_DOC_STRING "Enable writing Redis modules in Python"

#include <Python.h>
#include "redismodule.h"

PyObject* CreateCommand(PyObject* self, PyObject* args);

PyObject* CreateCommandParams(PyObject* self, PyObject* args);

PyObject* Call(PyObject* self, PyObject* args);

PyObject* Init(PyObject* self, PyObject* args);

extern RedisModuleCtx* globalContext;

#endif
