#pragma once

#ifndef _WIN32_ENV_H
#define _WIN32_ENV_H 1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets the environment variables for the program.
 * @param __argc Unused here
 * @param __argv Also unused
 */
extern char **__get_envp(int __argc, char **__argv);

#ifdef __cplusplus
}
#endif

#endif /* !_WIN32_ENV_H */
