#pragma once

#ifndef _LINUX_X86_64_ENV_H
#define _LINUX_X86_64_ENV_H 1

/**
 * @brief Finds where the environment variables start.
 * @param __argc The number of arguments (from the stack)
 * @param __argv The argument pointer (also from the stack)
 */
extern char **__get_envp(int __argc, char **__argv);

#endif /* _LINUX_X86_64_ENV_H */
