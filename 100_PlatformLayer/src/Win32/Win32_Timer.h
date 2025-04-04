#pragma once

#include <Windows.h>

#include "src/include/TimeDateSystem.h"

namespace Fierce {
	class Win32_Timer : public Timer{
    public:
        Win32_Timer();

        void start() override;
        void stop() override;

        double getElapsedTime() override;

    private:
        LARGE_INTEGER m_frequency;
        double m_1_frequency;
        LARGE_INTEGER m_lastTime;
	};
}