//
// Created by chadb on 7/31/18.
//

#ifndef REDIS_TEST_RAWSTREAMWRITE_H
#define REDIS_TEST_RAWSTREAMWRITE_H

#include "RedisTest.h"

class RawStreamWrite : public RedisTest
{
    void Setup(cpp_redis::client *pClient) override;

    void Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter) override;

    void Cleanup(cpp_redis::client *pClient) override;

public:

};

#endif //REDIS_TEST_RAWSTREAMWRITE_H
