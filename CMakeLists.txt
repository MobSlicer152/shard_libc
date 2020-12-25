cmake_minimum_required(VERSION 3.10)

project(shard_libc VERSION 0.0.1 LANGUAGES C ASM-ATT)

if (NOT DEFINED TARGET_ARCH)
	set(TARGET_ARCH "x86-64")
endif()

if (MSVC)
	set(CMAKE_C_FLAGS "-Gm- -GR- -EHa- -Oi -X")
	set(CMAKE_EXE_LINKER_FLAGS "-nodefaultlib kernel32.lib shell32.lib -subsystem:console")

	include_directories($ENV{UniversalCRTSdkDir}/include/um)

	if (TARGET_ARCH STREQUAL "x86-64")
		list(APPEND CMAKE_C_FLAGS "-D_AMD64_")
		list(APPEND CMAKE_EXE_LINKER_FLAGS "-machine:X64")
	else()
		list(APPEND CMAKE_C_FLAGS "-D_X86_")
		list(APPEND CMAKE_EXE_LINKER_FLAGS "-machine:X86")
else()
	set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -march=${TARGET_ARCH}")
endif()

include_directories(include src ${CMAKE_BINARY_DIR})

add_subdirectory(src)
if (${SHARD_LIBC_ENABLE_TESTS})
	add_subdirectory(tests)

	add_custom_command(
		POST_BUILD c_shard
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c_shard> ${CMAKE_BINARY_DIR}/tests
		BYPRODUCTS ${CMAKE_BINARY_DIR}/tests/$<TARGET_FILE_NAME:c_shard>
	)
endif()
