cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME textmining)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++17 -pedantic -O3")

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(SRC
    src/main.cc
    src/reader.cc
)

link_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (textmining ${SRC})
target_link_libraries(textmining dl)
TARGET_LINK_LIBRARIES( textmining LINK_PUBLIC ${Boost_LIBRARIES} )
