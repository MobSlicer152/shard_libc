#include "string.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(memset)
#endif

void *memset(void *restrict __dst, int __c, size_t __n)
{
	size_t i;
	uint64_t *cur;
	size_t qc;

	/* Set bytes until we have a quad-aligned address */
	for (i = 0; i < __n / sizeof(uint64_t); i++)
		((unsigned char *)__dst)[i] = __c;

	/* Now set qwords */
	qc = (__c) ? ((uint64_t)__c | ((uint64_t)__c << 8) |
		      ((uint64_t)__c << 16) | ((uint64_t)__c << 24) |
		      ((uint64_t)__c << 32) | ((uint64_t)__c << 40) |
		      ((uint64_t)__c << 48) | ((uint64_t)__c << 56)) :
			   0;
	cur = ((unsigned char *)__dst + i);
	while (cur < ((unsigned char *)__dst + __n)) {
		*cur = qc;
		cur++;
	}

	return __dst;
}

#ifdef __cplusplus
}
#endif
