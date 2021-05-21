#pragma once

#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H 1

#ifdef __cplusplus
extern "C" {
#endif

/* Protection for mapped pages (only one is allowed) */
#define PROT_NONE 0x0 /* No access */
#define PROT_READ 0x4 /* Pages can be read */
#define PROT_WRITE 0x2 /* Pages can be written */
#define PROT_EXEC 0x1 /* Pages can be executed (be careful!) */

/* Mapping type */
#define MAP_FILE 0x1 /* Mapped from a file or device */
#define MAP_ANON 0x2 /* Allocated from virtual memory */
#define MAP_TYPE 0xf /* Mask for type field */
#define MAP_ANONYMOUS MAP_ANON

/* Sharing type */
#define MAP_COPY 0x20 /* Virtual copy of region at mapping time */
#define MAP_SHARED 0x10 /* Share changes */
#define MAP_PRIVATE 0x0 /* Changes are private and pages are copy-on-write */

/* Other stuff */
#define MAP_FIXED 0x100 /* Mapping must be at exactly the requested address */
#define MAP_NOEXTEND 0x200 /* When used with `MAP_FILE`, don't change the file size */
#define MAP_HASSEMAPHORE 0x400 /* Mapped region may contain semaphores */
#define MAP_INHERIT 0x800 /* Region is retained after calls to `exec*` */

#ifdef __cplusplus
}
#endif

#endif
