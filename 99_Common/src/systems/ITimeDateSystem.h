#pragma once

#include "System.h"

namespace Fierce {

    class ITimer {
    public:
        virtual ~ITimer() = default;
        virtual void start()=0;
        virtual void stop()=0;
        virtual double getElapsedTime()=0;
    };

    class ITimeDateSystem:public System{
    public:
        virtual ~ITimeDateSystem() = default;

        virtual int getYear()=0;
        virtual int getMonth()=0;
        virtual int getDay()=0;

        virtual int getHours()=0;
        virtual int getMinutes()=0;
        virtual int getSeconds()=0;

        virtual ITimer* createTimer()=0;
        virtual void deleteTimer(ITimer* timer)=0;
    };

};