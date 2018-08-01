//
// Created by chadb on 7/31/18.
//

#ifndef REDIS_TEST_LUASETWRITE_H
#define REDIS_TEST_LUASETWRITE_H

#include "RedisTest.h"

class LuaSetWrite : public RedisTest
{
public:
    virtual void Setup(cpp_redis::client * pClient) override;
    virtual void Execute(cpp_redis::client * pClient, std::atomic<int> * pCounter) override;
    virtual void Cleanup(cpp_redis::client * pClient) override;

private:
    std::string sha;
};

#endif //REDIS_TEST_LUASETWRITE_H
