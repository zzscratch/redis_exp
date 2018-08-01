//
// Created by chadb on 7/31/18.
//

#include "RawStreamRead.h"

void RawStreamRead::Setup(cpp_redis::client *pClient)
{
    std::cout << "Staring Raw XRead read test" << std::endl;
}

void RawStreamRead::Execute(cpp_redis::client *pClient, std::atomic<int> *pCounter)
{
    // hack to only pick up first read request
    if (first)
        return;
    first = true;

    Helper(pClient, pCounter, "0");
}


void RawStreamRead::Reset()
{
    first = false;
}

void RawStreamRead::Cleanup(cpp_redis::client *pClient)
{
    std::cout << "Staring Raw XRead read test" << std::endl;
}

void RawStreamRead::Helper(cpp_redis::client *pClient, std::atomic<int> *pCounter, std::string id)
{
    std::vector<std::string> options{"count", "100", "block", "0"};
    std::vector<std::string> keys{"xlogs"};
    std::vector<std::string> ids{id};

    pClient->xread(options, keys, ids, [=](cpp_redis::reply& reply){
        if (!reply.is_array()) {
            std::cout << "Unexpected reply top" << std::endl;
            return;
        }
        // only expecting 1 key
        auto key = reply.as_array()[0];
        if (!key.is_array()) {
            std::cout << "Unexpected reply keys" << std::endl;
            return;
        }

        // extract key name
        auto keyName = key.as_array()[0].as_string();
        if (keyName.compare("xlogs") != 0)
        {
            std::cout << "Unexpected key name" << std::endl;
            return;
        }

        // extract log lines
        auto lines = key.as_array()[1].as_array();
        std::string id;
        for (int x = 0; x < lines.size(); x += 1) {
            id = lines[x].as_array()[0].as_string();
            auto payload = lines[x].as_array()[1].as_array();
        }
        *pCounter -= lines.size();

        /*
        int idx = id.find("-");
        std::string time = id.substr(0,idx);
        std::string seq = id.substr(idx+1);
        std::string newId = time + "-" + std::to_string(std::stoi(seq) + 1);
        */

        // get more log entries
        if (*pCounter > 0)
        {
            Helper(pClient,pCounter, id);
        }
    });
    pClient->commit();
}