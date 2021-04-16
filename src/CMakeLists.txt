cmake_minimum_required(VERSION 3.10)

set(LINUX_HEADERS
	linux/${SHARD_LIBC_TARGET_ARCH}/env.h
)
source_group("Linux" FILES ${LINUX_HEADERS})

set(LINUX_INTERNAL_SOURCES
	# Startup assembly
	linux/${SHARD_LIBC_TARGET_ARCH}/crt0.s

	# Miscellaneous utility stuff
	linux/${SHARD_LIBC_TARGET_ARCH}/env.c
)
source_group("Linux" FILES ${LINUX_INTERNAL_SOURCES})

set(LINUX_STDLIB_SOURCES
	linux/stdlib/_exit.c
)
source_group("Linux\\stdlib.h" FILES ${LINUX_STDLIB_SOURCES})

set(LINUX_UNISTD_SOURCES
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.s
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.c
	linux/unistd/write.c
)
source_group("Linux\\unistd.h" FILES ${LINUX_UNISTD_SOURCES})

set(LINUX_SOURCES ${LINUX_INTERNAL_SOURCES} ${LINUX_STDLIB_SOURCES} ${LINUX_UNISTD_SOURCES})

set(WINDOWS_HEADERS
	win32/dumbass_windows_stuff.h
	win32/env.h
	../include/excpt.h
	../include/ms_sal_fixup.h
)
source_group("Windows" FILES ${WINDOWS_HEADERS})

set(WINDOWS_INTERNAL_SOURCES
	# Startup stuff (which can be written in C quite easily, unlike Linux)
	win32/crt0.c

	# Miscellaneous utility stuff
	win32/env.c
	win32/stack_fixup.c
)
source_group("Windows" FILES ${WINDOWS_INTERNAL_SOURCES})

set(WINDOWS_STDLIB_SOURCES
	win32/stdlib/_exit.c
)
source_group("Windows\\stdlib.h" FILES ${WINDOWS_STDLIB_SOURCES})

set(WINDOWS_UNISTD_SOURCES
	win32/unistd/write.c
)
source_group("Windows\\unistd.h" FILES ${WINDOWS_UNISTD_SOURCES})

set(WINDOWS_SOURCES ${WINDOWS_INTERNAL_SOURCES} ${WINDOWS_STDLIB_SOURCES} ${WINDOWS_UNISTD_SOURCES})

set(INTERNAL_HEADERS
	internal/registers.h
	internal/startup.h
)

set(INTERNAL_SOURCES
	internal/startup.c
)
source_group("Internal" FILES ${INTERNAL_HEADERS} ${INTERNAL_SOURCES})

set(STANDARD_HEADERS
	../include/sys/syscall.h
	../include/sys/types.h
	../include/assert.h
	../include/ctype.h
	../include/errno.h
	../include/limits.h
	../include/malloc.h
	../include/stdarg.h
	../include/stdbool.h
	../include/stddef.h
	../include/stdint.h
	../include/stdio.h
	../include/stdlib.h
	../include/stdnoreturn.h
	../include/string.h
	../include/unistd.h
	../include/wchar.h
)
source_group("Standard Headers" FILES ${STANDARD_HEADERS})

set(STDLIB_SOURCES
	stdlib/abort.c
	stdlib/exit.c
	stdlib/malloc.c
)
source_group("stdlib.h" FILES ${STDLIB_SOURCES})

set(STRING_SOURCES
	string/memccpy.c
	string/memcpy.c
	string/memmove.c
	string/memset.c
	string/strlen.c
)
source_group("string.h" FILES ${STRING_SOURCES})

set(WCHAR_SOURCES
	wchar/wcslen.c
)
source_group("wchar.h" FILES ${WCHAR_SOURCES})

set(PUBLIC_SOURCES ${STDLIB_SOURCES} ${STRING_SOURCES} ${WCHAR_SOURCES})

if (NOT MSVC)
	list(APPEND INTERNAL_SOURCES
		internal/stack_prot.c
	)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	include_directories(win32)
	list(APPEND INTERNAL_HEADERS ${WINDOWS_HEADERS})
	list(APPEND INTERNAL_SOURCES ${WINDOWS_SOURCES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	include_directories(linux/${SHARD_LIBC_TARGET_ARCH})
	list(APPEND INTERNAL_HEADERS ${LINUX_HEADERS})
	list(APPEND INTERNAL_SOURCES ${LINUX_SOURCES})
endif()

set(ALL_SOURCES ${INTERNAL_HEADERS} ${INTERNAL_SOURCES} ${PUBLIC_SOURCES} ${STANDARD_HEADERS})

add_library(libc_shard ${ALL_SOURCES})

# Fix the output name
if (NOT MSVC)
	set_target_properties(libc_shard PROPERTIES OUTPUT_NAME c_shard)
endif()

target_link_libraries(libc_shard)

if (${CMAKE_C_COMPILER} MATCHES "GCC")
	target_link_libraries(libc_shard gcc)
endif()
