#include "Timer.h"

namespace Fierce {

	Timer::Timer(){
		QueryPerformanceFrequency(&m_frequency); // Get the performance counter frequency
		m_1_frequency = 1000.0 / m_frequency.QuadPart;
	}

	void Timer::start(){
		if (!m_running) {
			QueryPerformanceCounter(&m_lastTime);
			m_running = true;
		}
	}

	void Timer::stop(){
		if (m_running) {
			m_running = false;
		}
	}

	double Timer::getElapsedTime(){
		LARGE_INTEGER now, result;
		if (m_running) {
			QueryPerformanceCounter(&now);
			result.QuadPart = now.QuadPart - m_lastTime.QuadPart;
			m_lastTime = now;
		}
		return static_cast<double>(result.QuadPart) * m_1_frequency;
	}
}