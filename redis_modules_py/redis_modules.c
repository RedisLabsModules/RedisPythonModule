#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include "redismodule.h"
#include "redis_modules.h"
#include "cpp_utils.h"

#define MODULE_NAME "redis_modules"
#define MODULE_DOC_STRING "Allow usage of Redis modules API via Python"


#define INIT_FUNC PyInit_redis_modules
//#define INIT_FUNC init_redis_modules
//

RedisModuleCtx* globalContext;

static char* get_string_from_py_unicode(PyObject* obj)
{
    if (obj == NULL)
    {
        return NULL;
    }
    PyObject* temp_obj = PyUnicode_AsEncodedString(obj, "UTF-8", "strict");
    if (temp_obj == NULL)
    {
        return NULL;
    }
    char* temp_char = PyBytes_AS_STRING(temp_obj);
    return temp_char;
}


PyObject* CreateCommandParams(PyObject* self, PyObject* args)
{
    PyObject *param1;
    PyObject *param2;

    if (PyArg_UnpackTuple(args, "ref", 2, 5, &param1, &param2)) {
        PyObject_CallFunctionObjArgs(param1, param2, NULL);
    }
}

int RedisModuleCreateCmdFuncWrapper(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    PyObject* py_object_args_tuple = PyTuple_New(argc-1);
    size_t len;

    int i;
    for (i = 1; i < argc; i++) {
        const char* str_arg = RedisModule_StringPtrLen(argv[i], &len);
        PyObject* py_str_arg = PyUnicode_FromStringAndSize(str_arg, len);
        PyTuple_SetItem(py_object_args_tuple, i-1, py_str_arg);
    }

    // TODO: maybe we should use the PythonObj or RedisModuleString for cmd_name
    const char* cmd_name = RedisModule_StringPtrLen(argv[0], &len);
    PyObject* actualCmd = GetCommand(cmd_name);
    PyObject* return_value = PyObject_CallObject(actualCmd, py_object_args_tuple);
    char* return_str = get_string_from_py_unicode(return_value);
    RedisModule_ReplyWithSimpleString(ctx, return_str);
//    RedisModule_Call(ctx, "s", argv ,argc);
}


//RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...);
PyObject* ParseReply(RedisModuleCallReply* reply) {
    int type = RedisModule_CallReplyType(reply);

    if (type == REDISMODULE_REPLY_NULL) {
        Py_RETURN_NONE;
    }

    if (type == REDISMODULE_REPLY_STRING) {
        size_t len;
        const char* str = RedisModule_CallReplyStringPtr(reply, &len);
        PyObject* py_str = PyUnicode_FromStringAndSize(str, len);
        return py_str;
    }

    if (type == REDISMODULE_REPLY_ARRAY) {
        size_t array_size = RedisModule_CallReplyLength(reply);
        PyObject* python_list = PyList_New(array_size);
        size_t i;
        for (i = 0; i < array_size; i++)
        {
            RedisModuleCallReply* curr_reply = RedisModule_CallReplyArrayElement(reply, i);
            PyObject* curr_item = ParseReply(curr_reply);
            PyList_SetItem(python_list, i, curr_item);
        }
        return python_list;
    }

    Py_RETURN_NONE;
}

PyObject* Call(PyObject* self, PyObject* args) {
    PyObject *py_cmdname;
    PyObject *py_arg1 = NULL;
    PyObject *py_arg2 = NULL;
    PyObject *py_arg3 = NULL;
    size_t call_args_size = PyTuple_Size(args);
    py_cmdname = PyTuple_GetItem(args, 0);
    RedisModuleString** args_vector = malloc(sizeof(RedisModuleString*) * (call_args_size-1));
    size_t i;
    for (i = 1; i < call_args_size; i++) {
        PyObject *curr_arg = PyTuple_GetItem(args, i);
        char *curr_str = get_string_from_py_unicode(curr_arg);
        size_t curr_str_len = strlen(curr_str);
        args_vector[i-1] = RedisModule_CreateString(globalContext, curr_str, curr_str_len);
    }
    char* s_cmdname = get_string_from_py_unicode(py_cmdname);

    RedisModuleCallReply* reply = NULL;

    reply = RedisModule_Call(globalContext, s_cmdname, "v", args_vector, call_args_size-1);

    // TODO: someone really needs to put a minute to release all the information
    // allocated here...
    return ParseReply(reply);
}


PyObject* CreateCommand(PyObject* self, PyObject* args) {
    PyObject *py_name, *py_cmdfunc, *py_strflags, *py_firstkey, *py_lastkey, *py_keystep;
    if (PyArg_UnpackTuple(args, "ref", 6, 6, &py_name, &py_cmdfunc, &py_strflags, &py_firstkey, &py_lastkey, &py_keystep)) {
        char* s_name = get_string_from_py_unicode(py_name);
        int s_firstkey= PyLong_AsLong(py_firstkey);
        int s_lastkey= PyLong_AsLong(py_lastkey);
        int s_keystep = PyLong_AsLong(py_keystep);
        char* s_strflags = get_string_from_py_unicode(py_strflags);

        AddCommand(s_name, py_cmdfunc);

        RedisModule_CreateCommand(globalContext, s_name, RedisModuleCreateCmdFuncWrapper, s_strflags, s_firstkey, s_lastkey, s_keystep);
    }
    return self;
}



PyObject* Init(PyObject* self, PyObject* args) {
    PyObject *py_module_name, *py_module_version, *py_api_version;
    if (PyArg_UnpackTuple(args, "ref", 3, 3, &py_module_name, &py_module_version, &py_api_version)) {
        char* s_module_name = (char*) PyUnicode_AsWideCharString(py_module_name, NULL);
        int s_module_version = PyLong_AsLong(py_module_version);
        int s_api_version = PyLong_AsLong(py_api_version);

        RedisModule_Init(globalContext, s_module_name, s_module_version, s_api_version);
    }
    return self;
}



//static PyMethodDef CallMeMethodTable[] = {
//    {"create_command_params",  CreateCommandParams, METH_VARARGS, "Create a new Module with params"},
//    {"create_command",  CreateCommand, METH_VARARGS, "Create a new Module with params"},
//    {NULL}
//};

//static struct PyModuleDef s_module_def = {
//    PyModuleDef_HEAD_INIT,
//    MODULE_NAME,
//    MODULE_DOC_STRING,
//    -1,
//    CallMeMethodTable
//};


//PyMODINIT_FUNC
//INIT_FUNC(void)
//{
//    PyModule_Create(&s_module_def);
//}
