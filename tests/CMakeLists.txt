cmake_minimum_required(VERSION 3.10)

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

	if (SHARD_LIBC_TARGET_ARCH STREQUAL "x86-64")
		set(CMAKE_C_FLAGS "-include /usr/include/x86_64-linux-gnu/asm/unistd_64.h")
	else()
		set(CMAKE_C_FLAGS "-include /usr/include/x86_64-linux-gnu/asm/unistd_32.h")
	endif()
endif()

add_executable(test_main test_main/main.c)
target_link_libraries(test_main c_shard)
