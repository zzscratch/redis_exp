//
// Created by chadb on 7/31/18.
//

#include "LuaStreamWrite.h"

void LuaStreamWrite::Setup(cpp_redis::client *pClient)
{
    sha = LoadScript(pClient, "XAdd.lua");
    std::cout << "Staring Lua XAdd write test" << std::endl;
}

void LuaStreamWrite::Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter)
{
    std::vector<std::string> keys;
    keys.push_back("xlogs");

    std::vector<std::string> args;
    args.push_back(generateRandomData());

    pClient->evalsha(sha, (int)keys.size(), keys, args, [=](cpp_redis::reply& reply){
        if (reply.is_error())
        {
            printf("Error\n");
        }
        else if (reply.is_string())
        {
            auto logLine = reply.as_string();
        }
        else
        {
            printf("Unexpected\n");
        }
        *pCounter -= 1;
    });
    pClient->commit();
}

void LuaStreamWrite::Cleanup(cpp_redis::client *pClient)
{
    std::cout << "Finished Lua XAdd write test" << std::endl;
}
