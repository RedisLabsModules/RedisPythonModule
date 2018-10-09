all: py_bridge.o

py_bridge.o: py_bridge.c
	gcc -fPIC -c -o py_bridge.o -I/home/ubuntu/redis/src -I../redis_modules_py -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu  py_bridge.c -lpython3.6

pythonhost3.6: pythonhost.c py_bridge.c
	gcc -o pythonhost3.6 -I../redis_modules_py -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu pythonhost.c py_bridge.c -lpython3.6
