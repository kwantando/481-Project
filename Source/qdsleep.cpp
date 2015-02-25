#include "qdsleep.h"

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else
#include <unistd.h>
#endif

void qdsleep(int ms)
{
    //usleep takes 1/1000 of a ms. no I don't know why
    #if defined _WIN32 || defined _WIN64
    Sleep(ms);
    #else
    usleep(ms * 1000);
    #endif
}
