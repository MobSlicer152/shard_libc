cmake_minimum_required(VERSION 3.10)

project(shard_libc VERSION 0.0.1 LANGUAGES C ASM-ATT)

option(SHARD_LIBC_ENABLE_TESTS "Whether build the tests or not" ON)
set(CMAKE_BUILD_TYPE "Debug") # This _should_ be the default, but it's not so we have to do this

if (NOT DEFINED SHARD_LIBC_TARGET_ARCH)
	set(SHARD_LIBC_TARGET_ARCH "x86-64")
endif()

if (MSVC)
	# Disables SAL and standard headers plus some other good flags
	set(CMAKE_C_FLAGS "-Gm- -GR- -EHa- -Oi -X -D_In_ -D_Inout_ -D_Out_ -D_Outptr_ -D_In_opt_ -D_Inout_opt_ -D_Out_opt_ -D_Outptr_opt")
	set(CMAKE_EXE_LINKER_FLAGS "-nodefaultlib kernel32.lib shell32.lib -subsystem:console")
	include_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Include\\${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\\include\\um")

	if (SHARD_LIBC_TARGET_ARCH STREQUAL "x86-64")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_AMD64_")
		set(CMAKE_C_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -machine:X64")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_X86_")
		set(CMAKE_C_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -machine:X86")
	endif()
else()
	set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -march=${SHARD_LIBC_TARGET_ARCH}")
endif()

include_directories(include src ${CMAKE_BINARY_DIR})

add_subdirectory(src)
if (${SHARD_LIBC_ENABLE_TESTS})
	add_subdirectory(tests)
endif()
