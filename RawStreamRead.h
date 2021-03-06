
#ifndef REDIS_TEST_RAWSTREAMREAD_H
#define REDIS_TEST_RAWSTREAMREAD_H

#include "RedisTest.h"

class RawStreamRead : public RedisTest
{
public:
    virtual void Setup(cpp_redis::client *pClient) override;
    virtual void Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter) override;
    virtual void Reset() override;
    virtual void Cleanup(cpp_redis::client *pClient) override;

private:
    bool first = false;
    void Helper(cpp_redis::client *pClient, std::atomic<int> *pCounter, std::string id);
};

#endif //REDIS_TEST_RAWSTREAMREAD_H
