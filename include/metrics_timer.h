// Copyright (c) 2013, XiaoMi Inc.
// All rights reserved.
//
// metrics_timer.h
//
// Author: Lingtao Kong <konglingtao@xiaomi.com>
//
// Created on: July 1, 2013
// Description:  Aggregates timing durations and provides duration statistics, plus
// throughput statistics via {@link Meter} liking Java Metrics Timer
//

#ifndef METRICS_TIMER_H_
#define METRICS_TIMER_H_

#include <time.h>
#include <string>

#include "metrics.h"

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{
typedef struct timespec TimerSpec;
/**
 * 这个类用于实现类似Java Metrics Timer类的功能
 * 记录Scoped 范围内的执行时间
 *
 */
class MetricsTimer
{
    
public:
    MetricsTimer(MetricsRegistry & metricsReg, const std::string & timename);
    MetricsTimer(Meter & meter, Reservoir & reservoir);
    ~MetricsTimer();

private:
    TimerSpec m_start_ts;
    Meter & m_meter;
    Reservoir & m_reservoir;
};

}
}
}
}

#endif
