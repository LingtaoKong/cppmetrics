/***
 * Metrics.h
 */

#ifndef _METRICS_H_
#define _METRICS_H_

#include <string>
#include <fstream>

#include "metrics_map.h"
#include "reporter.h"

#include "thirdparty/boost/thread/thread.hpp"
#include "thirdparty/boost/filesystem/path.hpp"
#include "thirdparty/boost/filesystem/operations.hpp"
#include "thirdparty/boost/date_time.hpp"
#include "thirdparty/glog/logging.h"
#include "thirdparty/gflags/gflags.h"

using namespace std;

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

class MetricsRegistry
{
public:
    
    MetricsRegistry();
    virtual ~MetricsRegistry();

    //
    // 返回指定的Meter对象， 如果没有， 则创建一个新的
    //
    Meter & getMeter(const string & metername);

    //
    // 返回指定的Reservoir对象， 如果没有， 则创建一个新的
    //
    UniformReservoir & getReservoir(const string & reservoirname, size_t initsize = DEFAULT_SIZE);

    //
    // 注册reporter, 启动report线程
    //
    virtual void reporter_register(Reporter * reporter);

private:
    
    //
    // 返回所有的Meter
    //
    void get_meter_map_snapshot(METER_MAP & metermap_ss);

    //
    // 返回所有的 UniformReservoir
    //
    void get_reservoir_map_snapshot(RESERVOIR_MAP & reservoir_ss);

    //
    // 向注册的reporter推送metrics信息
    //
    
    void report_func();

    void report_func_real();

private:
    
    boost::shared_ptr<boost::thread> _report_thread; // Report thread
    
    RandomGenerator _rg;

    METER_MAP _meter_hashmap;
    /**
     * TODO： 在目前的情况的下， 应该没有还性能的问题
     * 如果在实际的使用中，需要检测的点变的很多的时候，可以使用分片的锁
     */
    boost::mutex _meter_lock;

    RESERVOIR_MAP _reservoir_hashmap;
    boost::mutex _reservoir_lock;

    std::vector<boost::shared_ptr<Reporter> > reporters; //注册的Reporters;
    boost::mutex _reporters_lock;
};

}
}
}
}

#endif
