#include "RawStreamWrite.h"

void RawStreamWrite::Setup(cpp_redis::client *pClient)
{
    std::cout << "Staring Raw Xadd write test" << std::endl;
}

void RawStreamWrite::Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter)
{
    static const std::vector<std::string> options;

    std::multimap<std::string, std::string> logEntry;
    logEntry.insert(std::pair<std::string, std::string>("data", generateRandomData()));

    pClient->xadd("xlogs", options, "*", logEntry, [=](cpp_redis::reply& reply){
        if (reply.is_error())
        {
            printf("Error getting counter\n");
        }
        else if (reply.is_string())
        {
            auto line = reply.as_string();
        }
        *pCounter -= 1;
    });
    pClient->commit();
}

void RawStreamWrite::Cleanup(cpp_redis::client *pClient)
{
    std::cout << "Finished Raw Xadd write test" << std::endl;
}
