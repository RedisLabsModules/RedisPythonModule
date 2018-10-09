from setuptools import setup, Extension
# Compile the C module and make it available as a python module (calls the file's INIT func)
setup(name='redis_modules', ext_modules=[Extension('redis_modules',sources=['cpp_utils.cpp','redis_modules.c'])])
# setup(name='call_me_python', ext_modules=[Extension('call_me_python',sources=['call_me_python.c'])])