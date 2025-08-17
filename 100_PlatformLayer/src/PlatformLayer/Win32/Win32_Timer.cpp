#include "Win32_Timer.h"

namespace Fierce {

	Win32_Timer::Win32_Timer(){
		QueryPerformanceFrequency(&m_frequency);
		m_1_frequency = 1000.0 / m_frequency.QuadPart;
	}

	void Win32_Timer::start(){
		if (!m_running) {
			QueryPerformanceCounter(&m_lastTime);
			m_running = true;
		}
	}

	void Win32_Timer::stop(){
		if (m_running) {
			m_running = false;
		}
	}

	double Win32_Timer::getElapsedTime(){
		LARGE_INTEGER now, result;
		if (m_running) {
			QueryPerformanceCounter(&now);
			result.QuadPart = now.QuadPart - m_lastTime.QuadPart;
			m_lastTime = now;
		}
		return static_cast<double>(result.QuadPart) * m_1_frequency;
	}
}