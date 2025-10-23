cmake_minimum_required(VERSION 3.15...4.0)

project(mipt-cpp-hws LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(
GLOB_RECURSE CONFIGURE_DEPENDS
ALL_CXX_SOURCE_FILES
"${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.hpp"
"${CMAKE_SOURCE_DIR}/tests/*.cpp"
"${CMAKE_SOURCE_DIR}/tests/*.hpp"
"${CMAKE_SOURCE_DIR}/include/*.hpp"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE
)

add_custom_target(
run
COMMAND $<TARGET_FILE:hw_1> < ${CMAKE_SOURCE_DIR}/tests/data/001.dat
DEPENDS hw_1
)

add_custom_target(
	format
	COMMAND clang-format -i ${ALL_CXX_SOURCE_FILES}
)

add_executable(
	hw_1
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/lru_cache.cpp
)

target_include_directories(
hw_1 PRIVATE
${CMAKE_SOURCE_DIR}/include
)

target_link_options(
hw_1 PRIVATE
-fsanitize=address
)

include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
test_lru_cache
${CMAKE_SOURCE_DIR}/src/lru_cache.cpp
${CMAKE_SOURCE_DIR}/tests/test_lru_cache.cpp
)

target_link_libraries(
test_lru_cache
GTest::gtest_main
)

target_include_directories(
test_lru_cache PRIVATE
${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(test_lru_cache)
