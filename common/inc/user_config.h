#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")
#define MAX_CLI_NUM 8
#define MAX_CONNECTION 10
/* Enable debug option, uncomment to logging*/
// #define ENABLE_DEBUG

/* For logging */
#ifdef ENABLE_DEBUG
#define LOG 1
#else
#define LOG 0
#endif

#define log(...)                                                       \
    {                                                                  \
        do                                                             \
        {                                                              \
            if ((LOG))                                                 \
            {                                                          \
                printf("\n[%s:%s:%d] ", __FILE__, __func__, __LINE__); \
                printf(__VA_ARGS__);                                   \
                printf("\n");                                          \
            }                                                          \
        } while (0);                                                   \
    } // Logging

#endif /* __USER_CONFIG_H__ */