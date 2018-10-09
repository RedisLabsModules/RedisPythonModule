// #include <unordered_map>
// #include <string>
#include <Python.h>
#include <string.h>
#include "cpp_utils.h"

typedef struct KeyVal {
    const char * key;
    PyObject* val;
} KeyVal;


#define KV_SIZE 100
static KeyVal kvMap[KV_SIZE];
struct KeyVal * end = kvMap;
//static unordered_map<string,PyObject*> cmd_map;

   //typedef int (*RedisModuleCmdFunc) (RedisModuleCtx *ctx, RedisModuleString **argv, int argc);
    void AddCommand(const char* cmdName, PyObject* cmd)
    {
        char * newKey = strdup(cmdName);
        end->key = newKey;
        end->val = cmd;
        ++end;
        
    }
    PyObject* GetCommand(const char* cmdName)
    {
        PyObject* retVal = NULL;
        KeyVal * p = kvMap;
        while(p < end)
        {
            if(!strcmp(p->key, cmdName)){
                return p->val;
            }
            ++p;
        }
        
    }
