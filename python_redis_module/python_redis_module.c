#include "redismodule.h"
#include "py_bridge.h"
#include "redis_modules.h"


int PythonModule_Load(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2)
        return RedisModule_WrongArity(ctx);

    const char* file_name = RedisModule_StringPtrLen(argv[1], NULL);

    rl_run_python_file(file_name);
    RedisModule_ReplyWithNull(ctx);
    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx)
{
    globalContext = ctx;
    rl_init_python_runtime();
    if (RedisModule_Init(ctx, "PythonModule", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx, "PythonModule.load", PythonModule_Load, "readonly", 0, 0, 0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
