#pragma once

#include "src/utils/System.h"

namespace Fierce {

    class Timer {
    public:

        virtual void start()=0;
        virtual void stop()=0;

        virtual double getElapsedTime()=0;

    protected:
        bool m_running = false;
    };

    class TimeDateSystem :public System {
    public:
        int getYear() { return m_year; }
        int getMonth() { return m_month; }
        int getDay() { return m_day; }

        int getHours() { return m_hours; }
        int getMinutes() { return m_minutes; }
        int getSeconds() { return m_seconds; }

        virtual Timer* createTimer() = 0;
        virtual void deleteTimer(Timer* timer) = 0;

    protected:
        int m_year=-1;
        int m_month=-1;
        int m_day=-1;

        int m_hours=-1;
        int m_minutes=-1;
        int m_seconds = -1;
    };

};