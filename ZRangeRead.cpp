#include "ZRangeRead.h"

#include "RawStreamRead.h"

void ZRangeRead::Setup(cpp_redis::client *pClient)
{
    std::cout << "Staring ZRange read test" << std::endl;
}

void ZRangeRead::Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter)
{
    // hack to only pick up first read request
    if (first)
        return;
    first = true;

    Helper(pClient, pCounter, 0);
}

void ZRangeRead::Reset()
{
    first = false;
}

void ZRangeRead::Cleanup(cpp_redis::client *pClient)
{
    std::cout << "Finished ZRange read test" << std::endl;
}

void ZRangeRead::Helper(cpp_redis::client *pClient, std::atomic<int> *pCounter, int id)
{
    int start = id;
    int end = id + 10;
    pClient->zrangebyscore("logs", std::to_string(start), std::to_string(end), true, [=](cpp_redis::reply& reply){
        if (!reply.is_array()) {
            std::cout << "Unexpected reply top" << std::endl;
            return;
        }

        auto replies = reply.as_array();
        int lastid = 0;
        for (int i = 0; i < replies.size(); i += 2)
        {
            auto payload = replies[i].as_string();
            lastid = std::stoi(replies[i+1].as_string());
        }
        *pCounter -= (replies.size() / 2);

        // get more log entries
        if (*pCounter > 0)
        {
            Helper(pClient,pCounter, lastid);
        }
    });
    pClient->commit();
}
