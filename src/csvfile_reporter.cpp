#include <fstream>

#include "csvfile_reporter.h"

#include "thirdparty/glog/logging.h"
#include "thirdparty/gflags/gflags.h"

#include "thirdparty/boost/filesystem.hpp"

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

CSVFileReporter::CSVFileReporter(const std::string & report_path) :
        m_report_path(report_path)
{
}

CSVFileReporter::~CSVFileReporter()
{
}

void CSVFileReporter::report(const METER_MAP & meter_map, const RESERVOIR_MAP & reservoir_map)
{
    try
    {
        // 判断指定的目录是否存在
        if (!boost::filesystem::exists(m_report_path))
        {
            boost::system::error_code ec;
            if (!boost::filesystem::create_directories(m_report_path, ec) || ec)
            {
                LOG(WARNING)<<"create the specified directory is failed: "<< m_report_path<< " : "<< ec.message();
                return;
            }
        }
        // 判断是否是目录
        if(!boost::filesystem::is_directory(m_report_path))
        {   
            LOG(WARNING)<<"create the specified directory is failed: "<< m_report_path;
            return;
        }

    }
    catch(boost::filesystem::filesystem_error& err)
    {   
        LOG(WARNING)<<"prepare directory catch exception: "<<err.what();
        return;
    }

    // 获取当前时间
    time_t now = time(0);

    // 打开meter结果文件文件
    string meter_result_filename = m_report_path + "/meter_result.csv";
    std::ofstream meter_result_file(meter_result_filename.c_str(), std::ofstream::app|std::ofstream::out);
    if(!meter_result_file.is_open())
    {   
        LOG(WARNING)<<"create meter result file failed: "<< meter_result_filename;
    }
    else
    {   
        if(!meter_map.empty())
        {   
            for(METER_MAP::const_iterator it = meter_map.begin(); it != meter_map.end(); ++it)
            {   
                meter_result_file<< now <<";"<<it->first<<";"<<it->second->get_count()<<";"<<it->second->get_one_min_rate()<<
                ";"<<it->second->get_five_min_rate()<<";"<<it->second->get_fifteen_min_rate()<<endl;
            }
        }

        meter_result_file.close();
    }

    // 打开reservoir结果文件文件
    string reservoir_result_filename = m_report_path + "/reservoir_result.csv";
    ofstream reservoir_result_file(reservoir_result_filename.c_str(), ios::app|ios::out);
    if(!reservoir_result_file.is_open())
    {   
        LOG(WARNING)<<"create meter result file failed: "<< meter_result_filename;
    }
    else
    {   
        if(!reservoir_map.empty())
        {   
            for(RESERVOIR_MAP::const_iterator it = reservoir_map.begin(); it != reservoir_map.end(); ++it)
            {   
                SnapShot ss;
                it->second->make_snapshot(ss);
                reservoir_result_file<<now <<";"<<it->first<<";"<<ss.to_report_string()<<endl;
            }
        }

        reservoir_result_file.close();
    }
}

}
}
}
}
