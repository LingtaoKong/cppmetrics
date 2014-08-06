// Copyright (c) 2011, XiaoMi Inc.
// All rights reserved.
//
// meter.cpp
//
// Author: Zhang Hong Qiang <zhanghongqiang@xiaomi.com>
//                          <pcman.zhang@gmail.com>
// Created on: May 7, 2013
// Description:
//

#include "meter.h"
#include <time.h>

using namespace com::xiaomi::mfs::metrics;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class EWMA
//
// An exponentially weighted moving average
//
// @see <a href=http://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average" />
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EWMA::EWMA(double alpha, uint64_t interval) :
        m_rate(0.0f), m_alpha(alpha), m_interval(interval * NANOS_PER_SECONDS), m_inited(0)
{
}

EWMA::~EWMA()
{
}

void EWMA::tick(MfsAtomic & counter)
{
    tick(counter.get_value());
}

void EWMA::tick(uint64_t count)
{
    double instant_rate = (double) count / m_interval;
    
    // atomic get and set
    if (m_inited.set(1L) != (uint64_t) 0)
    {
        m_rate += (m_alpha * (instant_rate - m_rate));
    }
    else
    {
        m_rate = instant_rate;
    }
}

double EWMA::get_rate()
{
    return m_rate * NANOS_PER_SECONDS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Meter
//
// An exponentially weighted moving average
//
// @see <a href=http://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average" />
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Meter::Meter() :
        m_counter(0), m_counted(0), m_tick((uint64_t) time(NULL)), // NL
        m_m1_rate(M1_ALPHA, METER_TICK_INTERVAL_SEC), // rate for one min
        m_m5_rate(M5_ALPHA, METER_TICK_INTERVAL_SEC), // rate for five min
        m_m15_rate(M15_ALPHA, METER_TICK_INTERVAL_SEC) // rate for fiften min
{
}

Meter::~Meter()
{
}

void Meter::inc(int value)
{
    m_counter += (uint64_t) value;
}

void Meter::inc()
{
    inc(1L);
}

uint64_t Meter::get_count()
{
    return m_counter.get_value();
}

void Meter::reset()
{
    // only reset counter, no need to reset alpha and rate
    m_counter.set(0L);
}

void Meter::tick_if_necessary()
{
    uint64_t old_tick = m_tick.get_value();
    uint64_t new_tick = (uint64_t) time(NULL);
    int interval = new_tick - old_tick;
    
    // atomic, because if compare_and_set return false, tick() will not be executed
    if (interval >= METER_TICK_INTERVAL_SEC && m_tick.compare_and_set(old_tick, new_tick))
    {
        uint64_t requiredTicks = interval / METER_TICK_INTERVAL_SEC;
        for (uint64_t i = 0; i < requiredTicks; i++)
        {
            uint64_t count = m_counter.get_value() - m_counted.get_value(); // get the value and reset it
            m_counted += count;
            m_m1_rate.tick(count);
            m_m5_rate.tick(count);
            m_m15_rate.tick(count);
        }
    }
}

double Meter::get_one_min_rate()
{
    tick_if_necessary();
    return m_m1_rate.get_rate();
}

double Meter::get_five_min_rate()
{
    tick_if_necessary();
    return m_m5_rate.get_rate();
}

double Meter::get_fifteen_min_rate()
{
    tick_if_necessary();
    return m_m15_rate.get_rate();
}
