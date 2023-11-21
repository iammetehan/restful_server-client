cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UTIL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../util/src/Util.cpp")

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(COMMON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common/include")
set(UTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../util/include")

set(BOOST_LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/boost_1_83_0")

add_executable(client main.cpp
               src/Data.cpp
               src/Request.cpp
               ${COMMON_SRC}
               ${UTIL_SRC}
               include/Data.h
               include/Request.h)

include_directories(${INCLUDE_DIR}
                    ${BOOST_LIB_INCLUDE_DIR}
                    ${COMMON_INCLUDE_DIR}
                    ${UTIL_INCLUDE_DIR})

target_link_libraries(client PRIVATE ws2_32 wsock32)

install(TARGETS client LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
