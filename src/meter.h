
#ifndef METRICS_METER_H_
#define METRICS_METER_H_

#include "atomic.h"

#include <iostream>
#include <math.h>

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class EWMA
//
// An exponentially weighted moving average
//
// @see <a href=http://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average" />
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const int METER_TICK_INTERVAL_SEC = 5;
static const double M1_ALPHA = 1.0f - exp(-(double) METER_TICK_INTERVAL_SEC / 60 / 1.0f);
static const double M5_ALPHA = 1.0f - exp(-(double) METER_TICK_INTERVAL_SEC / 60 / 5.0f);
static const double M15_ALPHA = 1.0f - exp(-(double) METER_TICK_INTERVAL_SEC / 60 / 15.0f);

#define NANOS_PER_SECONDS   1000000000

class EWMA
{
public:
    EWMA(double alpha, uint64_t interval);
    virtual ~EWMA();

public:
    void tick(MfsAtomic & counter);
    void tick(uint64_t counter);

    double get_rate();

private:
    double m_rate;
    double m_alpha;
    uint64_t m_interval;
    MfsAtomic m_inited;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Meter
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Meter
{
public:
    Meter();
    virtual ~Meter();

public:
    void inc();
    void inc(int value);
    void reset();

    uint64_t get_count();

    double get_one_min_rate();
    double get_five_min_rate();
    double get_fifteen_min_rate();

    void tick_if_necessary();

private:
    MfsAtomic m_counter;
    MfsAtomic m_counted;
    MfsAtomic m_tick;

    EWMA m_m1_rate;
    EWMA m_m5_rate;
    EWMA m_m15_rate;
};

}
}
}
}

#endif /* METRICS_METER_H_ */
