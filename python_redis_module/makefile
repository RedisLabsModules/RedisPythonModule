all: python_redis_module.o

python_redis_module.o: python_redis_module.c
	gcc -fPIC -I/home/ubuntu/redis/src/ -I../redis_modules_py -I../py-host/ -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu -std=gnu99 -c -o python_redis_module.o python_redis_module.c
