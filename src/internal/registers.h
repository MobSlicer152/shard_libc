#pragma once

#ifndef _INTERNAL_REGISTERS_H
#define _INTERNAL_REGISTERS_H 1

#include "stdint.h"

#define __X86_64_REG_DEFS	register uint64_t rax __asm__("rax");	\
				register uint64_t rbx __asm__("rbx");	\
				register uint64_t rcx __asm__("rcx");	\
				register uint64_t rdx __asm__("rdx");	\
				register uint64_t rdi __asm__("rdi");	\
				register uint64_t rsi __asm__("rsi");	\
				register uint64_t rsp __asm__("rsp");	\
				register uint64_t r8 __asm__("r8");	\
				register uint64_t r9 __asm__("r9");	\
				register uint64_t r10 __asm__("r10");	\
				register uint64_t r11 __asm__("r11");	\
				register uint64_t r12 __asm__("r12");	\
				register uint64_t r13 __asm__("r13");	\
				register uint64_t r14 __asm__("r14");	\
				register uint64_t r15 __asm__("r15")

#endif /* !_INTERNAL_REGISTERS_H */
