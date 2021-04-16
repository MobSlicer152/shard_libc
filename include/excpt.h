/*
 * @file This file fixes errors related to Microsoft's Structured Exception
 *  Handling stuff being undefined.
 */

#pragma once

#ifndef _INC_EXCPT
#define _INC_EXCPT 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma pack(push, 8)
#endif

typedef enum _EXCEPTION_DISPOSITION {
	ExceptionContinueExecution,
	ExceptionContinueSearch,
	ExceptionNestedException,
	ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

#ifdef _M_IX86
struct _EXCEPTION_RECORD;
struct _CONTEXT;

EXCEPTION_DISPOSITION __cdecl _except_handler(
	struct _EXCEPTION_RECORD *excpn_record, void *frame,
	struct _CONTEXT *ctx_record, void *disptch_ctx);
#endif

#if defined(_M_AMD64) || defined(_M_ARM) || defined(_M_ARM64) || \
	defined(_M_HYBRID)
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _DISPATCHER_CONTEXT;

#ifndef _M_CEE_PURE
EXCEPTION_DISPOSITION __cdecl __C_specific_handler(
	struct _EXCEPTION_RECORD *excpn_record, void *frame,
	struct _CONTEXT *ctx_record, struct _DISPATCHER_CONTEXT *disptch_ctx);
#endif
#endif

#ifdef _MSC_VER
#define GetExceptionCode _exception_code
#define exception_code _exception_code
#define GetExceptionInformation (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info (struct _EXCEPTION_POINTERS *)_exception_info
#define AbnormalTermination _abnormal_termination
#define abnormal_termination _abnormal_termination

unsigned long __cdecl _exception_code(void);
void *__cdecl _exception_info(void);
int __cdecl _abnormal_termination(void);
#endif

#define EXCEPTION_EXECUTE_HANDLER 1
#define EXCEPTION_CONTINUE_SEARCH 0
#define EXCEPTION_CONTINUE_EXECUTION -1

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif /* !_INC_EXCPT */
