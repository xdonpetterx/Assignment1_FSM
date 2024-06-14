#pragma once

/* This is a Microsoft Visual Studio Compiler directive that
 * tells the linker to add the winmm.lib to the list of libraries
 * to be used in the linking process.winmm.lib is a Windows
 * specific library that provides multimedia functionality,
 * such as playing sound files.
 *
 * According to stack overflow (https://stackoverflow.com/questions/41637194/pragma-warning-clang-msvc-compatibility):
 * "clang supports the Microsoft #pragma pack feature for controlling record layout. GCC also contains support for this
 * feature, however where MSVC and GCC are incompatible clang follows the MSVC definition"
 *
 * So hopefully it means that linking to winmm.lib works in Windows -> OK
 * In Linux linking to winmm.lib doesn't work, GCC just skips it -> OK
 * In MacOs linking to winmm.lib works because of clang's compatability with MSVC but since the file doesn't
 * exist in MacOs the linker can't find the file and the linking process fails -> FAIL*/
//#pragma comment(lib, "winmm.lib")

//WINDOWS
#ifdef _WIN32
//#include <windows.h>
#endif

//MAC
#ifdef  __APPLE__
#include <ctime>
#include <cstdlib>

unsigned int timeGetTime(){
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec/1000;
}
//---------------
#endif


#define Clock CrudeTimer::Instance()
/*
class CrudeTimer
{
private:


    //set to the time (in seconds) when class is instantiated
    double m_dStartTime;

    //set the start time
    CrudeTimer(){m_dStartTime = timeGetTime() * 0.001;}

    //copy ctor and assignment should be private
    CrudeTimer(const CrudeTimer&);
    CrudeTimer& operator=(const CrudeTimer&);

public:

    static CrudeTimer* Instance();

    //returns how much time has elapsed since the timer was started
    double GetCurrentTime(){return timeGetTime() * 0.001 - m_dStartTime;}

};
*/

#include <chrono>

class CrudeTimer
{
private:
    //set to the time (in seconds) when class is instantiated
    std::chrono::steady_clock::duration m_dStartTime;




public:
    CrudeTimer(const CrudeTimer&) = delete;
    CrudeTimer& operator=(const CrudeTimer&) = delete;
    CrudeTimer() : m_dStartTime(std::chrono::steady_clock::now().time_since_epoch()) {}

    static CrudeTimer* Instance() {
        static CrudeTimer instance;

        return &instance;
    }

    //returns how much time has elapsed since the timer was started
    [[nodiscard]] double GetCurrentTime() const {
        auto current_time = std::chrono::steady_clock::now().time_since_epoch();
        return std::chrono::duration<double>(current_time - m_dStartTime).count();
    }
};