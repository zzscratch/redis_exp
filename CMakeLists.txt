cmake_minimum_required(VERSION 3.10)
project(redis_exp)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)

add_executable(redis_exp main.cpp LuaSetWrite.cpp LuaStreamWrite.cpp RawStreamWrite.cpp RawStreamRead.cpp)
target_link_libraries(redis_test cpp_redis tacopie ${CMAKE_THREAD_LIBS_INIT})
