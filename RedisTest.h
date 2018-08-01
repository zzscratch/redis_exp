//
// Created by chadb on 7/31/18.
//

#ifndef REDIS_TEST_WRITETEST_H
#define REDIS_TEST_WRITETEST_H

#include <iostream>
#include <sstream>
#include <streambuf>
#include <cpp_redis/cpp_redis>
#include <fstream>

class RedisTest
{
public:
    virtual void Setup(cpp_redis::client * pClient) = 0;
    virtual void Execute(cpp_redis::client * pClient, std::atomic<int> * pCounter) = 0;
    virtual void Reset() {}
    virtual void Cleanup(cpp_redis::client * pClient) = 0;

    virtual std::string LoadScript(cpp_redis::client * pClient, const std::string & filename)
    {
        std::ifstream file(filename);
        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto reply = pClient->script_load(fileContents);
        pClient->sync_commit();
        return reply.get().as_string();
    }

    virtual std::string generateRandomData()
    {
        std::ostringstream tmp;
        tmp << "{\"sid\":655234, \"pid\":";
        tmp << std::rand();
        tmp << ", \"tid\":";
        tmp << std::rand();
        tmp << ", \"type\":1, \"data\":\"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"}";
        return tmp.str();
    }
};

#endif //REDIS_TEST_WRITETEST_H
