all: redis_modules.o cpp_utils.o

call_me_python.o: call_me_python.c
	gcc -fPIC -c -o call_me_python.o -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu  call_me_python.c -lpython3.6

cpp_utils.o: cpp_utils.c
	gcc -fPIC -c -o cpp_utils.o -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu  cpp_utils.c -lpython3.6

redis_modules.o: redis_modules.c
	gcc -fPIC -c -o redis_modules.o -I/home/ubuntu/redis/src -I/home/ubuntu/hackathon_env/include/python3.6m -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu  redis_modules.c -lpython3.6
