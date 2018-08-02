#ifdef _WIN32
#include <Winsock2.h>
#endif

#include "RedisTest.h"
#include "RawStreamWrite.h"
#include "LuaSetWrite.h"
#include "LuaStreamWrite.h"
#include "RawStreamRead.h"
#include "ZRangeRead.h"

#include <chrono>
#include <inttypes.h>
#include <algorithm>
#include <cpp_redis/cpp_redis>

const int NUM_ENTRIES = 100000;

int main(int argc, char *argv[])
{
#ifdef _WIN32
    WORD version = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(version, &data) != 0) {
        std::cerr << "WSAStartup() failure" << std::endl;
        return -1;
    }
#endif

    cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
    cpp_redis::client client;
    client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
            std::cout << "client disconnected from " << host << ":" << port << std::endl;
        }
        else if (status == cpp_redis::client::connect_state::stopped) {
            std::cout << "giving up for " << host << ":" << port << std::endl;
        }
    }, 0, 10, 100);

    // login with default password
    auto loginReply = client.auth("foobared");
    client.sync_commit();

    // default run parameters
    std::unique_ptr<RedisTest> pTest = std::make_unique<LuaSetWrite>();
    int testIterations = 20;

    if (argc >= 2)
    {
        std::string cmd(argv[1]);
        std::transform(cmd.begin(),cmd.end(), cmd.begin(), ::tolower);
        if (cmd == "rawstreamwrite") {
            pTest = std::make_unique<RawStreamWrite>();
        } else if (cmd == "luasetwrite") {
            pTest = std::make_unique<LuaSetWrite>();
        } else if (cmd == "luastreamwrite") {
            pTest = std::make_unique<LuaStreamWrite>();
        } else if (cmd == "rawstreamread") {
            pTest = std::make_unique<RawStreamRead>();
        } else if (cmd == "zrangeread") {
            pTest = std::make_unique<ZRangeRead>();
        } else {
            std::cout << "Unknown cmd" << std::endl;
            exit(-1);
        }
    }
    if (argc >= 3)
    {
        int tmp = std::atoi(argv[2]);
        if (tmp > 0)
            testIterations = tmp;
    }

    pTest->Setup( &client );
    for (int x = 0; x < testIterations; x++)
    {
        std::atomic<int> counter(NUM_ENTRIES);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_ENTRIES; i++)
        {
            pTest->Execute(&client,&counter);
        }
        while (counter > 0)
            ;

        auto end = std::chrono::high_resolution_clock::now();
        int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double secs = ms / 1000.0;

        printf("Took %" PRId64 "ms -- %f logs per second\n", ms, NUM_ENTRIES / (double) secs);

        pTest->Reset();
    }
    pTest->Cleanup(&client);

    client.disconnect();
    #ifdef _WIN32
        WSACleanup();
    #endif
    return 0;
}

