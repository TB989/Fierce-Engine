#pragma once

#include <Windows.h>

#include "src/systems/ITimeDateSystem.h"

namespace Fierce {
	class Win32_Timer : public ITimer{
    public:
        Win32_Timer();

        void start() override;
        void stop() override;

        double getElapsedTime() override;

    private:
        bool m_running=false;

        LARGE_INTEGER m_frequency;
        double m_1_frequency;
        LARGE_INTEGER m_lastTime;
	};
}