#pragma once

//WINDOWS
#ifdef _WIN32
//#include <windows.h>
#endif

#define Clock CrudeTimer::Instance()

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