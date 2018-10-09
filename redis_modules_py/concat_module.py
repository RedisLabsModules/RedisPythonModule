import redis_modules

# RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...);

def concat_strings(dest_key, key2, key3):
    str2 = redis_modules.call("GET", key2)
    str3 = redis_modules.call("GET", key3)
    dest_str = str2 + str3

    redis_modules.call("SET", dest_key, dest_str)

    return dest_str


#redis_modules.init("WinningModule", 1, 1)
redis_modules.create_command("WinningModule.CONCAT", concat_strings, "write", 1, 1, 1)


# redis-server --load-modules "python_redis_modules.so concat_module.py"
