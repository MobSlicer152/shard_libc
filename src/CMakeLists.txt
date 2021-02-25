cmake_minimum_required(VERSION 3.10)

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

	# stdlib.h implementations that are Linux specific
	linux/stdlib/_exit.c

	# unistd.h implementations
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.c
	linux/unistd/write.c
)

set(WINDOWS_HEADERS
	win32/dumbass_windows_stuff.h
	win32/env.h
)

set(WINDOWS_FIXUP_HEADERS
	../include/excpt.h
	../include/sal.h
)

set(WINDOWS_SOURCES
	# Startup stuff (which can be written in C quite easily, unlike Linux)
	win32/crt0.c

	# Miscellaneous utility stuff
	win32/env.c

	# stdlib.h implementations that are platform specific
	win32/stdlib/_exit.c
	win32/stdlib/malloc.c
)

set(INTERNAL_HEADERS
	internal/registers.h
	internal/startup.h
)

set(INTERNAL_SOURCES
	internal/startup.c
)

set(STANDARD_HEADERS
	../include/sys/syscall.h
	../include/ctype.h
	../include/stdarg.h
	../include/stddef.h
	../include/stdint.h
	../include/stdlib.h
	../include/string.h
	../include/unistd.h
)

set(STDLIB_SOURCES
	stdlib/exit.c
)

set(STRING_SOURCES
	string/memccpy.c
	string/memcpy.c
	string/memmove.c
	string/strlen.c
)

set(PUBLIC_SOURCES ${STDLIB_SOURCES} ${STRING_SOURCES})

if (NOT MSVC)
	list(APPEND INTERNAL_SOURCES
		internal/stack_prot.c
	)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	include_directories(win32)
	list(APPEND INTERNAL_HEADERS ${WINDOWS_HEADERS} ${WINDOWS_FIXUP_HEADERS})
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
