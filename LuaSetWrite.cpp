//
// Created by chadb on 7/31/18.
//

#include "LuaSetWrite.h"

void LuaSetWrite::Setup(cpp_redis::client * pClient)
{
    sha = LoadScript(pClient, "AddLog.lua");
    std::cout << "Staring Lua ZSet write test" << std::endl;
}

void LuaSetWrite::Execute(cpp_redis::client * pClient, std::atomic<int> * pCounter)
{
    std::vector<std::string> keys;
    keys.push_back("ct");
    keys.push_back("logs");

    std::vector<std::string> args;
    args.push_back(generateRandomData());

    pClient->evalsha(sha, (int)keys.size(), keys, args, [=](cpp_redis::reply& reply){
        if (reply.is_error())
        {
            printf("Error\n");
        }
        else if (reply.is_integer())
        {
            auto logLine = reply.as_integer();
        }
        else
        {
            printf("Unexpected\n");
        }
        *pCounter -= 1;
    });
    pClient->commit();
}

void LuaSetWrite::Cleanup(cpp_redis::client * pClient)
{
    std::cout << "Finished Lua ZSet write test" << std::endl;
}