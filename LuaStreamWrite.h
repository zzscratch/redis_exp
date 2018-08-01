#ifndef REDIS_TEST_LUASTREAMWRITE_H
#define REDIS_TEST_LUASTREAMWRITE_H

#include "RedisTest.h"

class LuaStreamWrite : public RedisTest
{
public:
    void Setup(cpp_redis::client *pClient) override;
    void Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter) override;
    void Cleanup(cpp_redis::client *pClient) override;

private:
    std::string sha;
};

#endif //REDIS_TEST_LUASTREAMWRITE_H
