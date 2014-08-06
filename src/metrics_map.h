#ifndef METRICS_MAP_H_
#define METRICS_MAP_H_
#include "meter.h"
#include "uniform_reservoir.h"

typedef std::map<std::string, boost::shared_ptr<com::xiaomi::mfs::metrics::Meter> > METER_MAP;
typedef std::map<std::string, boost::shared_ptr<com::xiaomi::mfs::metrics::UniformReservoir> > RESERVOIR_MAP;
#endif
