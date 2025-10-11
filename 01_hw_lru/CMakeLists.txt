cmake_minimum_required(VERSION 3.15)

project(
	mipt-cpp-hws
	LANGUAGES CXX)

file(
	GLOB_RECURSE
	ALL_CXX_SOURCE_FILES
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/include/*.h")

add_custom_target(
	run1
	COMMAND $<TARGET_FILE:hw_1>
	DEPENDS hw_1)

add_custom_target(
	format
	COMMAND clang-format -i ${ALL_CXX_SOURCE_FILES})

add_executable(
	hw_1
	${CMAKE_SOURCE_DIR}/src/main.cpp)

target_compile_options(
	hw_1 PRIVATE
	-Wall -Wextra -Wpedantic
	-fsanitize=address -fsanitize=leak -static-libasan
	-g -O0)

target_link_options(
	hw_1 PRIVATE
	-fsanitize=address)
