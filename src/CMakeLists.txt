cmake_minimum_required(VERSION 3.10)

set(LINUX_HEADERS
	linux/${TARGET_ARCH}/env.h
)

set(LINUX_SOURCES
	# Startup assembly
	linux/${TARGET_ARCH}/crt0.s
	linux/${TARGET_ARCH}/crti.s
	linux/${TARGET_ARCH}/crtn.s

	# Miscellaneous utility stuff
	linux/${TARGET_ARCH}/env.c

	# stdlib.h implementations that are platform specific
	linux/${TARGET_ARCH}/stdlib/exit.c
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
	internal/startup.h
)

set(INTERNAL_SOURCES
	internal/startup.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	list(APPEND INTERNAL_HEADERS ${WINDOWS_HEADERS})
	list(APPEND INTERNAL_SOURCES ${WINDOWS_SOURCES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	include_directories(linux/${TARGET_ARCH})
	list(APPEND INTERNAL_HEADERS ${LINUX_HEADERS})
	list(APPEND INTERNAL_SOURCES ${LINUX_SOURCES})
endif()

set(ALL_SOURCES ${INTERNAL_SOURCES} ${PUBLIC_SOURCES})

add_library(c_shard
	${INTERNAL_HEADERS}
	${ALL_SOURCES}
)
