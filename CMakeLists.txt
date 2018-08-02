cmake_minimum_required(VERSION 3.10)
project(redis_exp)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

set (SOURCE main.cpp LuaSetWrite.cpp LuaStreamWrite.cpp RawStreamWrite.cpp RawStreamRead.cpp ZRangeRead.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} cpp_redis tacopie ${CMAKE_THREAD_LIBS_INIT})
