
#ifndef REDIS_TEST_ZRANGEREAD_H
#define REDIS_TEST_ZRANGEREAD_H

#include "RedisTest.h"

class ZRangeRead : public RedisTest
{
public:
    virtual void Setup(cpp_redis::client *pClient) override;
    virtual void Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter) override;
    virtual void Reset() override;
    virtual void Cleanup(cpp_redis::client *pClient) override;

private:
    bool first = false;
    void Helper(cpp_redis::client *pClient, std::atomic<int> *pCounter, int id);
};

#endif //REDIS_TEST_ZRANGEREAD_H
