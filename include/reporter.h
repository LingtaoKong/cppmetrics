#ifndef METRICS_REPORTER_H_
#define METRICS_REPORTER_H_

#include "metrics_map.h"

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

class Reporter
{
public:
    virtual ~Reporter()
    {
    }
    ;  // explicit virtual is needed for boost::shared_ptr
    
    //
    // 执行report操作，将推送的信息输出
    //
    virtual void report(const METER_MAP & meter_map, const RESERVOIR_MAP & reservoir_map) = 0;

private:
};

}
}
}
}

#endif
