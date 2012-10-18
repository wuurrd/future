cmake_minimum_required (VERSION 2.6)
project (FUTURE)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories (${FUTURE_SOURCE_DIR}/api ${Boost_INCLUDE_DIR})

add_library(future src/future.cpp)
add_executable (test src/test.cpp)

target_link_libraries (test future ${BOOST_SYSTEM_LIBRARY})
