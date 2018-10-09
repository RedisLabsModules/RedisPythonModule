SUBDIRS = py-host python_redis_module redis_modules_py

all: python_redis_module.so

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

python_redis_module.so: subdirs
	ld -o python_redis_module.so python_redis_module/python_redis_module.o -L/home/ubuntu/hackathon_env/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6 py-host/py_bridge.o redis_modules_py/redis_modules.o redis_modules_py/cpp_utils.o -shared -Bsymbolic -lc


.PHONY: all
