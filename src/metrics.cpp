#include "metrics.h"

DEFINE_int32(metrics_report_interval_s, 60, "Metrics report interval(seconds)") ;

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

MetricsRegistry::MetricsRegistry()
{
    //启动Report thread
    if (!_report_thread.get())
        _report_thread.reset(new boost::thread(boost::bind(&MetricsRegistry::report_func, this)));
}

MetricsRegistry::~MetricsRegistry()
{
    //停止Report Thread
    if (_report_thread.get())
    {
        _report_thread->interrupt();
        _report_thread->join();
        _report_thread.reset();
    }
}

Meter & MetricsRegistry::getMeter(const string & metername)
{
    boost::mutex::scoped_lock lock(_meter_lock);
    METER_MAP::iterator it = _meter_hashmap.find(metername);
    if (it == _meter_hashmap.end())
    {
        boost::shared_ptr<Meter> meter(new Meter());
        std::pair<METER_MAP::iterator, bool> ret;
        ret = _meter_hashmap.insert(std::make_pair(metername, meter));
        return *(ret.first->second.get());
    }
    return *(it->second.get());
}

UniformReservoir & MetricsRegistry::getReservoir(const string & reservoirname, size_t initsize)
{
    boost::mutex::scoped_lock lock(_reservoir_lock);
    RESERVOIR_MAP::iterator it = _reservoir_hashmap.find(reservoirname);
    if (it == _reservoir_hashmap.end())
    {
        boost::shared_ptr<UniformReservoir> reservoir(new UniformReservoir(_rg, initsize));
        std::pair<RESERVOIR_MAP::iterator, bool> ret;
        ret = _reservoir_hashmap.insert(std::make_pair(reservoirname, reservoir));
        return *(ret.first->second.get());
    }
    return *(it->second.get());
    
}

void MetricsRegistry::get_meter_map_snapshot(METER_MAP & metermap_ss)
{
    _meter_lock.lock();
    metermap_ss = _meter_hashmap;
    _meter_lock.unlock();
}

void MetricsRegistry::get_reservoir_map_snapshot(RESERVOIR_MAP & reservoir_ss)
{
    _reservoir_lock.lock();
    reservoir_ss = _reservoir_hashmap;
    _reservoir_lock.unlock();
}

void MetricsRegistry::reporter_register(Reporter * reporter)
{
    boost::shared_ptr<Reporter> r(reporter);
    boost::mutex::scoped_lock(_reporters_lock);
    reporters.push_back(r);
}

void MetricsRegistry::report_func_real()
{
    METER_MAP meter_ss;
    RESERVOIR_MAP reservoir_ss;
    get_meter_map_snapshot(meter_ss);
    get_reservoir_map_snapshot(reservoir_ss);
    
    boost::mutex::scoped_lock(_reporters_lock);
    for (std::vector<boost::shared_ptr<Reporter> >::iterator it = reporters.begin(); it != reporters.end(); ++it)
    {
        it->get()->report(meter_ss, reservoir_ss);
    }
}

void MetricsRegistry::report_func()
{
    try
    {
        while (!boost::this_thread::interruption_requested())
        {
            
            boost::this_thread::sleep(boost::posix_time::seconds(FLAGS_metrics_report_interval_s)); // sleep 5 minutes by default
                    
            {
                report_func_real();
            }
        }
    } catch (boost::thread_interrupted& e)
    {
        report_func_real();
    }
    
}

}
}
}
}
