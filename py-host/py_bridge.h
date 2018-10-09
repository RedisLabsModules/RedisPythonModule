#ifndef __PY_BRIDGE_MODULE__
#define __PY_BRIDGE_MODULE__
int rl_init_python_runtime();
int rl_run_python_file(const char *file_name);
int rl_finialize_python_runtime();

#endif
