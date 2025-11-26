#ifndef UTILS_ASSERTION_HPP
#define UTILS_ASSERTION_HPP

#include <cstdlib>
#include <spdlog/spdlog.h>

#ifdef NDEBUG
#define Assert(condition) static_cast<void>(0)
#else
#define Assert(condition)                                                                                \
    do {                                                                                                 \
        if (!(condition)) {                                                                              \
            spdlog::error("{}:{}: {}: Assertion '{}' failed", __FILE__, __LINE__, __func__, #condition); \
            std::abort();                                                                                \
        }                                                                                                \
    } while (0)
#endif

#endif
