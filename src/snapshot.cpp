// Copyright (c) 2011, XiaoMi Inc.
// All rights reserved.
//
// snapshot.cpp
//
// Author: Zhang Hong Qiang <zhanghongqiang@xiaomi.com>
// Created on: May 6, 2013
// Description:
//

#include "snapshot.h"
#include <math.h>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <sstream>

using namespace com::xiaomi::mfs::metrics;

SnapShot::SnapShot()
{
}

SnapShot::SnapShot(const std::vector<uint64_t>& collection)
{
    set_collection(collection);
}

SnapShot::~SnapShot()
{
}

void SnapShot::set_collection(const std::vector<uint64_t>& collection)
{
    if (collection.empty())
    {
        return;
    }
    
    m_collection = collection;
    std::sort(m_collection.begin(), m_collection.end());
}

size_t SnapShot::size() const
{
    return m_collection.size();
}

double SnapShot::get_value(double quantile)
{
    if (quantile > 1.0f)
    {
        quantile = 1.0f;
    }
    
    if (quantile < 0.0f)
    {
        quantile = 0.0f;
    }
    
    if (m_collection.empty())
    {
        return 0.0f;
    }
    
    double pos = quantile * (m_collection.size() + 1);
    
    if (pos < 1)
    {
        return m_collection[0];
    }
    
    if (pos >= m_collection.size())
    {
        return m_collection[m_collection.size() - 1];
    }
    
    uint64_t lower = m_collection[(int) pos - 1];
    uint64_t upper = m_collection[(int) pos];
    
    return lower + (pos - floor(pos)) * (upper - lower);
}

double SnapShot::get_median()
{
    return get_value(0.5f);
}

double SnapShot::get_75th_percentile()
{
    return get_value(0.75f);
}

double SnapShot::get_90th_percentile()
{
    return get_value(0.90f);
}

double SnapShot::get_95th_percentile()
{
    return get_value(0.95f);
}
double SnapShot::get_99th_percentile()
{
    return get_value(0.99f);
    
}
double SnapShot::get_999th_percentile()
{
    return get_value(0.999f);
}

double SnapShot::get_max()
{
    if (m_collection.empty())
    {
        return 0.0f;
    }
    
    return static_cast<double>(*m_collection.rbegin());
}

double SnapShot::get_min()
{
    if (m_collection.empty())
    {
        return 0.0f;
    }
    
    return static_cast<double>(*m_collection.begin());
}

double SnapShot::get_mean()
{
    if (m_collection.empty())
    {
        return 0.0f;
    }
    
    return std::accumulate(m_collection.begin(), m_collection.end(), (uint64_t)0) * 1.0f / m_collection.size();
}

std::string SnapShot::to_report_string()
{
    std::ostringstream oss;
    oss << m_collection.size() << ";" << std::fixed << get_min() << ";" << std::fixed << get_max() << ";" << std::fixed
            << get_mean() << ";" << std::fixed << get_median() << ";" << std::fixed << get_75th_percentile() << ";"
            << std::fixed << get_90th_percentile() << ";" << std::fixed << get_95th_percentile() << ";" << std::fixed
            << get_99th_percentile() << ";" << std::fixed << get_999th_percentile();
    return oss.str();
}

const std::vector<uint64_t> & SnapShot::get_values()
{
    return m_collection;
}

