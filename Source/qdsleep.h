#ifndef QDS_H
#define QDS_H
#if defined TARGET_OS_MAC || defined __linux__
#include <unistd.h>
#elif defined _WIN32 || defined _WIN64
#include <windows.h>
#else
#error "no os found"
#endif

void qdsleep(int ms)
{
    #if defined TARGET_OS_MAC || defined __linux__
    usleep(ms * 1000);
    //usleep takes 1/1000 of a ms. no I don't know why
    #elif defined _WIN32 || defined _WIN64
    Sleep(ms);
    #endif
}

#endif