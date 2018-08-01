//
// Created by chadb on 7/31/18.
//

#ifndef REDIS_TEST_LUASTREAMREAD_H
#define REDIS_TEST_LUASTREAMREAD_H

#include "RedisTest.h"

class RawStreamRead : public RedisTest
{
public:

    void Setup(cpp_redis::client *pClient) override;
    void Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter) override;
    void Reset() override;
    void Cleanup(cpp_redis::client *pClient) override;

private:
    std::string sha;
    bool first = false;
    void Helper(cpp_redis::client *pClient, std::atomic<int> *pCounter, std::string id);
};

#endif //REDIS_TEST_LUASTREAMREAD_H
