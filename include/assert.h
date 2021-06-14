#pragma once

#ifndef _ASSERT_H
#define _ASSERT_H 1

#ifdef NDEBUG
#define assert(__expr) ((void)0)
#else /* NDEBUG */
extern void abort(void);
#define assert(__expr) (!!(__expr) || (abort(), 0))
#endif /* NDEBUG */

#endif /* !_ASSERT_H */
