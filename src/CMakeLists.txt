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

set(LINUX_HEADERS
	linux/${SHARD_LIBC_TARGET_ARCH}/env.h
)

set(LINUX_SOURCES
	# Startup assembly
	linux/${SHARD_LIBC_TARGET_ARCH}/crt0.s
	linux/${SHARD_LIBC_TARGET_ARCH}/crti.s
	linux/${SHARD_LIBC_TARGET_ARCH}/crtn.s

	# Miscellaneous utility stuff
	linux/${SHARD_LIBC_TARGET_ARCH}/env.c

	# stdlib.h implementations that are platform specific
	linux/${SHARD_LIBC_TARGET_ARCH}/stdlib/exit.c

	# unistd.h implementations
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.c
)

set(WINDOWS_HEADERS
	win32/dumbass_windows_stuff.h
	win32/env.h
)

set(WINDOWS_SOURCES
	# Startup stuff (which can be written in C quite easily, unlike Linux)
	win32/crt0.c

	# Miscellaneous utility stuff
	win32/env.c

	# stdlib.h implementations that are platform specific
	win32/stdlib/exit.c
	win32/stdlib/malloc.c
)

set(INTERNAL_HEADERS
	internal/registers.h
	internal/startup.h
)

set(INTERNAL_SOURCES
	internal/startup.c
)

if (NOT MSVC)
	list(APPEND INTERNAL_SOURCES
		internal/stack_prot.c
	)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	list(APPEND INTERNAL_HEADERS ${WINDOWS_HEADERS})
	list(APPEND INTERNAL_SOURCES ${WINDOWS_SOURCES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	include_directories(linux/${SHARD_LIBC_TARGET_ARCH})
	list(APPEND INTERNAL_HEADERS ${LINUX_HEADERS})
	list(APPEND INTERNAL_SOURCES ${LINUX_SOURCES})
endif()

set(ALL_SOURCES ${INTERNAL_SOURCES} ${PUBLIC_SOURCES})

add_library(c_shard
	${INTERNAL_HEADERS}
	${ALL_SOURCES}
)

target_link_libraries(c_shard gcc)

if (${SHARD_LIBC_ENABLE_TESTS})
	add_custom_command(
		TARGET c_shard
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c_shard> ${CMAKE_BINARY_DIR}/tests
	)
endif()
