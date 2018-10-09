#include "redis_modules.h"
#include <Python.h>


static PyMethodDef methodTable[] = {
    {"create_command_params",  CreateCommandParams, METH_VARARGS, "Create a new Module with params"},
    {"create_command",  CreateCommand, METH_VARARGS, "Create a new Module with params"},
    {"init",  Init, METH_VARARGS, "Initialize a new module"},
    {"call",  Call, METH_VARARGS, "Call a Redis method"},

    {NULL}
};


static struct PyModuleDef s_module_def = {
        PyModuleDef_HEAD_INIT,
        MODULE_NAME,
        MODULE_DOC_STRING,
        -1,
        methodTable
        };


PyMODINIT_FUNC
INIT_FUNC(void)
{
    PyObject* module = PyModule_Create(&s_module_def);
}


int rl_init_python_runtime()
{
  Py_SetProgramName(L"redis_python");

  //const char* home = getenv("HOME");
  //wchar_t w_home[100];

  //mbstowcs(w_home, home, 100);

  //wchar_t buffer[1000];

  //swprintf(buffer, 1000, L"%S/hackathon_env/lib/python3.6:%S/hackthon_env/lib/python3.6/site-packages", w_home);
  
  PyImport_AppendInittab(MODULE_NAME, INIT_FUNC); //register the resident C implemnted modules

  Py_SetPath(L"/home/ubuntu/hackathon_env/lib/python3.6:/home/ubuntu/hackathon_env/lib/python3.6/site-packages");

  Py_Initialize();
}

int rl_run_python_file(const char *file_name)
{
  FILE* py_file = fopen(file_name, "r");

  PyRun_SimpleFile(py_file, file_name);

  fclose(py_file);
  printf("Prefix path: %S\n", Py_GetPrefix());
  printf("Modules path: %S\n", Py_GetPath());
}

int rl_finialize_python_runtime()
{
  Py_Finalize();
}
