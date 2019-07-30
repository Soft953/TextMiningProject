cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME textmining)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++17 -pedantic -g")

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CompilerSRC
    src/TextMiningCompiler/main.cc
    src/reader.cc
    src/ptrie.cc
)

set(AppSRC
    src/TextMiningApp/main.cc
    src/reader.cc
    src/ptrie.cc
)

set(testSRC
    test/test.cc
)

link_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (TextMiningCompiler ${CompilerSRC})

add_executable (TextMiningApp ${CompilerSRC})

add_executable (UnitTest ${testSRC})

target_link_libraries(UnitTest dl)
TARGET_LINK_LIBRARIES( UnitTest LINK_PUBLIC ${Boost_LIBRARIES} )

target_link_libraries(TextMiningApp dl)
TARGET_LINK_LIBRARIES( TextMiningApp LINK_PUBLIC ${Boost_LIBRARIES} )

target_link_libraries(TextMiningCompiler dl)
TARGET_LINK_LIBRARIES( TextMiningCompiler LINK_PUBLIC ${Boost_LIBRARIES} )
