cmake_minimum_required(VERSION 3.10)

project(shard_libc VERSION 0.0.1 LANGUAGES C ASM-ATT)

option(SHARD_LIBC_ENABLE_TESTS "Whether build the tests or not" ON)
set(CMAKE_BUILD_TYPE "Debug") # This _should_ be the default, but it's not, so we have to do this

if (NOT DEFINED SHARD_LIBC_TARGET_ARCH)
	set(SHARD_LIBC_TARGET_ARCH "x86-64")
endif()

include_directories(include src ${CMAKE_BINARY_DIR})

add_subdirectory(src)
if (${SHARD_LIBC_ENABLE_TESTS})
	add_subdirectory(tests)
endif()
