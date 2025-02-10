#pragma once

#include <Windows.h>

namespace Fierce {
	class Timer {
    public:
        Timer();

        void start();
        void stop();

        double getElapsedTime();

    private:
        LARGE_INTEGER m_frequency;  // Stores the clock frequency
        double m_1_frequency;
        LARGE_INTEGER m_lastTime;
        bool m_running=false; // Timer state
	};
}