cmake_minimum_required(VERSION 3.10)

project(shard_libc VERSION 0.0.1 LANGUAGES C ASM-ATT)

option(SHARD_LIBC_ENABLE_TESTS "Whether build the tests or not" ON)
set(CMAKE_BUILD_TYPE "Debug") # This _should_ be the default, but it's not, so we have to do this

if (NOT DEFINED SHARD_LIBC_TARGET_ARCH)
	set(SHARD_LIBC_TARGET_ARCH "x86-64")
endif()

if (SHARD_LIBC_TARGET_ARCH STREQUAL "x86-64")
		set(CMAKE_C_FLAGS "-D_AMD64_")
	else()
		set(CMAKE_C_FLAGS "-D_X86_")
	endif()

if (MSVC)
	# Disable standard headers and libraries plus enable some other good flags
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Gm- -GR- -EHa- -Oi -X")
	set(CMAKE_EXE_LINKER_FLAGS "-nodefaultlib kernel32.lib shell32.lib -subsystem:console")
	include_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\um" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\shared")

	if (SHARD_LIBC_TARGET_ARCH STREQUAL "x86-64")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -machine:X64")
	else()
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -machine:X86")
	endif()
else()
	set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -nostdinc -march=${SHARD_LIBC_TARGET_ARCH}")

	if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/linux/include ${CMAKE_CURRENT_LIST_DIR}/deps/linux/usr/include)
	endif()
endif()

include_directories(include src ${CMAKE_BINARY_DIR})

add_subdirectory(src)
if (${SHARD_LIBC_ENABLE_TESTS})
	add_subdirectory(tests)
endif()
