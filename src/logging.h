#ifndef POTATO_BUCKET_LOGGING_H
#define POTATO_BUCKET_LOGGING_H

#ifdef __EMSCRIPTEN__
#define LOG(...)
#else
#include <iostream>
template<typename... Args>
void log_impl(Args... args)
{
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

#define LOG(...) log_impl(__VA_ARGS__)
#endif

#endif // LOGGING_H
