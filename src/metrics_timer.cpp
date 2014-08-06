#include "metrics_timer.h"

using namespace com::xiaomi::mfs::metrics;

/********************************************************
 * Extracted from ULIB
 ********************************************************/

inline void timer_start(TimerSpec *ts)
{
    clock_gettime(CLOCK_MONOTONIC, ts);
}

inline uint64_t timer_stop_ns(const TimerSpec *ts)
{
    TimerSpec tsnow;
    
    clock_gettime(CLOCK_MONOTONIC, &tsnow);
    
    return ((tsnow.tv_sec - ts->tv_sec) * 1000000000 + (tsnow.tv_nsec - ts->tv_nsec));
}

MetricsTimer::MetricsTimer(MetricsRegistry & metricsReg, const std::string & timename) :
        m_meter(metricsReg.getMeter(timename)), m_reservoir(metricsReg.getReservoir(timename))
{
    m_meter.inc();
    timer_start(&m_start_ts);
}
MetricsTimer::MetricsTimer(Meter & meter, Reservoir & reservoir) :
        m_meter(meter), m_reservoir(reservoir)
{
    m_meter.inc();
    timer_start(&m_start_ts);
}
MetricsTimer::~MetricsTimer()
{
    m_reservoir.update(timer_stop_ns(&m_start_ts));
}

