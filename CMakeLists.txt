cmake_minimum_required(VERSION 3.10)

# Default library disabler from StackOverflow
file(WRITE "${CMAKE_BINARY_DIR}/MakeRulesOverwrite.cmake"
	[=[
	if (MSVC)
		set(CMAKE_C_STANDARD_LIBRARIES_INIT "ntdll.lib")
		set(CMAKE_CXX_STANDARD_LIBRARIES_INIT "ntdll.lib")
	endif()
	]=]
)
set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_BINARY_DIR}/MakeRulesOverwrite.cmake")

project(shard_libc VERSION 0.0.1 LANGUAGES C)

option(SHARD_LIBC_ENABLE_TESTS "Whether build the tests or not" ON)
set(CMAKE_BUILD_TYPE "Debug") # This _should_ be the default, but it's not, so we have to do this

if (${CMAKE_BUILD_TYPE} MATCHES ".*Rel.*")
	set(CMAKE_BUILD_TYPE "Release")
endif()

if (NOT DEFINED SHARD_LIBC_TARGET_ARCH)
	set(SHARD_LIBC_TARGET_ARCH "x86-64")
endif()

if (SHARD_LIBC_TARGET_ARCH STREQUAL "x86-64")
	set(CMAKE_C_FLAGS "-D_AMD64_")
else()
	set(CMAKE_C_FLAGS "-D_X86_")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__STD_C__")


if (MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -EHc- -Gm- -GS- -GR- -sdl- -X -w -analyze-")
	include_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\km" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\shared" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\um")

	enable_language(ASM_MASM)
else()
	set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -nostdinc -Wall -Wextra -march=${SHARD_LIBC_TARGET_ARCH}")

	enable_language(ASM_ATT)

	if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/linux/include ${CMAKE_CURRENT_LIST_DIR}/deps/linux/usr/include)
	endif()
endif()

include_directories(include src ${CMAKE_BINARY_DIR} deps/gperftools/src)

add_subdirectory(src)
if (${SHARD_LIBC_ENABLE_TESTS})
	add_subdirectory(tests)
endif()
