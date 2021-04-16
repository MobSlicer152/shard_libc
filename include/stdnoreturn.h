#pragma once

#ifndef _STDNORETURN_H
#define _STDNORETURN_H 1

/* MSVC doesn't seem to support _Noreturn */
#ifdef _MSC_VER
#define _Noreturn __declspec(noreturn)
#endif /* _MSC_VER */

#endif /* !_STDNORETURN_H */
