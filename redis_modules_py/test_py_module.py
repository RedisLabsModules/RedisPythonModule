import redis_modules

def some_func(param):
    print("Some func is running now!")
    print("Our param is {}".format(param))

redis_modules.create_command_params(some_func, "hello")