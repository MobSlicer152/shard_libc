#define _AMD64_

#include <string.h>
#include <unistd.h>
#include <win32/windows_stuff.h>

/* Definitions for symbols and structures needed */
#define FILE_GENERIC_WRITE 0x100106
#define FILE_SYNCHRONOUS_IO_NONALERT 0x20
#define FILE_OVERWRITE_IF 0x5
#define FILE_ATTRIBUTE_NORMAL 0x80

int main(void)
{
	void *file;
	OBJECT_ATTRIBUTES atrs;
	UNICODE_STRING fname;
	IO_STATUS_BLOCK iostat;
	LARGE_INTEGER thiccness;
	unsigned long ret;
	
	memset(&atrs, sizeof(atrs), 0);
	RtlInitUnicodeString(&fname, L"\\??\\C:\\test.txt");
	atrs.len = sizeof(atrs);
	atrs.root_dir = NULL;
	atrs.name = &fname;
	atrs.attrs = OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE;
	*((long long *)&thiccness) = 69;
	*((long long *)&thiccness.u) = 69;
	thiccness.quad = 69;

	/* Call the function */
	syscall_r(ret, 0x55, &file, FILE_GENERIC_WRITE, &atrs, &iostat, &thiccness,
		     FILE_ATTRIBUTE_NORMAL, 2, FILE_OVERWRITE_IF,
		     FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	/* Return to the program loader */
	return ret;
}
