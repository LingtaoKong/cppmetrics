#ifndef METRICS_CSVFILE_REPORTER_H_
#define METRICS_CSVFILE_REPORTER_H_

#include "reporter.h"

#include <string>

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

class CSVFileReporter: public Reporter
{
public:
    CSVFileReporter(const std::string & report_path);
    virtual void report(const METER_MAP & meter_map, const RESERVOIR_MAP & reservoir_map);

private:
    std::string m_report_path; // report files direcorty
    virtual ~CSVFileReporter(); // guarantee to new at Heap
};

}
}
}
}

#endif
