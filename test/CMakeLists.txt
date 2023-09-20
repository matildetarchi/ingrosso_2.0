cmake_minimum_required(VERSION 3.21)


add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp EngineFixture.cpp StoreFixture.cpp CartFixture.cpp FavouritesFixture.cpp UsersFixture.cpp OrdersFixture.cpp)
add_executable(runIngTests ${TEST_SOURCE_FILES})
target_link_libraries(runIngTests gtest gtest_main core)

target_link_libraries(runIngTests SQLiteCpp sqlite3)
target_include_directories(runIngTests PRIVATE SQLiteCpp/include)