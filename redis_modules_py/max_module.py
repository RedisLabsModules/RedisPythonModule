import redis_modules

# RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...);

def max_list(key):
    key_list = redis_modules.call("smembers", key)

    return max(key_list, key=int)


#redis_modules.init("WinningModule", 1, 1)
redis_modules.create_command("WinningModule.MAX", max_list, "write", 1, 1, 1)


# redis-server --load-modules "python_redis_modules.so concat_module.py"
