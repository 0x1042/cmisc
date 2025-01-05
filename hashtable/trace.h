#pragma once

#ifdef TRACE
#    define DEBUG(fmt, ...) \
        printf("\033[36m[DEBUG] %s:%d %s " fmt "\033[0m\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#    define DEBUG(fmt, ...)
#endif

#define STR(x) #x
