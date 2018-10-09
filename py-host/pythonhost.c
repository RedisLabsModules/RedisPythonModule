#include <Python.h>
#include <stdio.h>




int rl_init_python_runtime();
int
main(int argc, char *argv[])
{
  rl_init_python_runtime();
  rl_run_python_file(argv[1]);
  rl_finialize_python_runtime();
  return 0;
}
