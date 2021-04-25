cmake_minimum_required(VERSION 3.10)

set(LINUX_HEADERS
	linux/${SHARD_LIBC_TARGET_ARCH}/env.h
)

set(LINUX_INTERNAL_SOURCES
	# Startup assembly (I love assembly so it's fine)
	linux/${SHARD_LIBC_TARGET_ARCH}/crt0.s

	# Miscellaneous utility stuff
	linux/${SHARD_LIBC_TARGET_ARCH}/env.c
)

set(LINUX_STDLIB_SOURCES
	linux/stdlib/_exit.c
)

set(LINUX_UNISTD_SOURCES
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.c
	linux/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.s
	linux/unistd/write.c
)

set(WINDOWS_HEADERS
	win32/windows_stuff.h
	win32/env.h
	../include/excpt.h
	../include/ms_sal_fixup.h
)

set(WINDOWS_INTERNAL_SOURCES
	# Startup stuff (which can be written in C quite easily, unlike Linux)
	win32/crt0.c

	# Miscellaneous utility stuff
	win32/dll_loader.c
	win32/env.c
	win32/${SHARD_LIBC_TARGET_ARCH}/get_peb.asm
	win32/shutdown.c
)

set_source_files_properties(
	win32/${SHARD_LIBC_TARGET_ARCH}/get_peb.asm
	PROPERTY LANGUAGE ASM_MASM
)

set(WINDOWS_STDIO_SOURCES
	win32/stdio/init.c
)

set(WINDOWS_STDLIB_SOURCES
	win32/stdlib/_exit.c
)

set(WINDOWS_UNISTD_SOURCES
	win32/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.asm
	win32/unistd/write.c
)

set_source_files_properties(
	win32/${SHARD_LIBC_TARGET_ARCH}/unistd/syscall.asm
	PROPERTY LANGUAGE ASM_MASM
)

set(INTERNAL_HEADERS
	internal/registers.h
	internal/startup.h
)

set(INTERNAL_SOURCES
	internal/startup.c
)

set(STANDARD_HEADERS
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

set(STANDARD_SYS_HEADERS
	../include/sys/syscall.h
	../include/sys/types.h
)

set(STDLIB_SOURCES
	stdlib/abort.c
	stdlib/exit.c
	stdlib/malloc.c
)

set(STRING_SOURCES
	string/memccpy.c
	string/memcpy.c
	string/memmove.c
	string/memset.c
	string/strcmp.c
	string/strlen.c
	string/strncpy.c
)

set(WCHAR_SOURCES
	wchar/wcscmp.c
	wchar/wcslen.c
)

set(PUBLIC_SOURCES ${STDLIB_SOURCES} ${STRING_SOURCES} ${WCHAR_SOURCES})

if (MSVC)
	list(APPEND WINDOWS_INTERNAL_SOURCES
		win32/stack_fixup.c
	)
else()
	list(APPEND INTERNAL_SOURCES
		internal/stack_prot.c
	)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	include_directories(win32)
	set(WINDOWS_SOURCES ${WINDOWS_INTERNAL_SOURCES} ${WINDOWS_STDIO_SOURCES} ${WINDOWS_STDLIB_SOURCES} ${WINDOWS_UNISTD_SOURCES})
	list(APPEND INTERNAL_HEADERS ${WINDOWS_HEADERS})
	list(APPEND INTERNAL_SOURCES ${WINDOWS_SOURCES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	include_directories(linux/${SHARD_LIBC_TARGET_ARCH})
	set(LINUX_SOURCES ${LINUX_INTERNAL_SOURCES} ${LINUX_STDLIB_SOURCES} ${LINUX_UNISTD_SOURCES})
	list(APPEND INTERNAL_HEADERS ${LINUX_HEADERS})
	list(APPEND INTERNAL_SOURCES ${LINUX_SOURCES})
endif()

set(ALL_SOURCES ${INTERNAL_HEADERS} ${INTERNAL_SOURCES} ${PUBLIC_SOURCES} ${STANDARD_HEADERS} ${STANDARD_SYS_HEADERS})

add_library(libc_shard ${ALL_SOURCES})

# Fix the output name
if (NOT MSVC)
	set_target_properties(libc_shard PROPERTIES OUTPUT_NAME c_shard)
endif()

target_link_libraries(libc_shard)

if (${CMAKE_C_COMPILER} MATCHES "GCC")
	target_link_libraries(libc_shard gcc)
endif()

# IDE groupings
source_group("Header\ Files\\Linux" FILES ${LINUX_HEADERS})
source_group("Source\ Files\\Linux" FILES ${LINUX_INTERNAL_SOURCES})
source_group("Source\ Files\\Linux\\stdlib.h" FILES ${LINUX_STDLIB_SOURCES})
source_group("Source\ Files\\Linux\\unistd.h" FILES ${LINUX_UNISTD_SOURCES})
source_group("Header\ Files\\Windows" FILES ${WINDOWS_HEADERS})
source_group("Source\ Files\\Windows" FILES ${WINDOWS_INTERNAL_SOURCES})
source_group("Source\ Files\\Windows\\stdio.h" FILES ${WINDOWS_STDIO_SOURCES})
source_group("Source\ Files\\Windows\\stdlib.h" FILES ${WINDOWS_STDLIB_SOURCES})
source_group("Source\ Files\\Windows\\unistd.h" FILES ${WINDOWS_UNISTD_SOURCES})
source_group("Header\ Files\\Internal" FILES ${INTERNAL_HEADERS})
source_group("Source\ Files\\Internal" FILES ${INTERNAL_SOURCES})
source_group("Header\ Files\\Standard Headers" FILES ${STANDARD_HEADERS})
source_group("Header\ Files\\Standard Headers\\sys" FILES ${STANDARD_SYS_HEADERS})
source_group("Source\ Files\\stdlib.h" FILES ${STDLIB_SOURCES})
source_group("Source\ Files\\string.h" FILES ${STRING_SOURCES})
source_group("Source\ Files\\wchar.h" FILES ${WCHAR_SOURCES})
