// Copyright (c) 2011, XiaoMi Inc.
// All rights reserved.
//
// uniform_reservoir.cpp
//
// Author: Zhang Hong Qiang <zhanghongqiang@xiaomi.com>
//                          <pcman.zhang@gmail.com>
// Created on: May 8, 2013
// Description:
//

#include "uniform_reservoir.h"
#include "thirdparty/glog/logging.h"
#include "thirdparty/gflags/gflags.h"
#include <stdint.h>

using namespace com::xiaomi::mfs::metrics;

UniformReservoir::UniformReservoir(RandomGenerator& random) :
        Reservoir(random), m_counter(0)
{
    init(DEFAULT_SIZE);
}

UniformReservoir::UniformReservoir(RandomGenerator& random, size_t size) :
        Reservoir(random), m_counter(0)
{
    init(size);
}

UniformReservoir::~UniformReservoir()
{
}

void UniformReservoir::init(size_t size)
{
    m_counter.set(0);
    m_data.resize(size);
}

size_t UniformReservoir::size()
{
    size_t size = m_counter.get_value();
    return (size < m_data.size()) ? size : m_data.size();
}

uint64_t UniformReservoir::get_count()
{
    return m_counter.get_value();
}

void UniformReservoir::update(uint64_t value)
{
    uint64_t count = ++m_counter;
    
    if (count < m_data.size())
    {
        m_data[count].set(value);
    }
    else
    {
        uint64_t rcount = get_next_int(m_data.size());
        m_data[rcount].set(value);
    }
}

void UniformReservoir::make_snapshot(/* out */SnapShot& snapshot)
{
    std::vector<uint64_t> data;
    
    data.resize(size());
    
    for (size_t i = 0; i < size(); ++i)
    {
        data[i] = m_data[i];
    }
    
    snapshot.set_collection(data);
}

void UniformReservoir::reset()
{
    for (std::vector<MfsAtomic>::iterator it = m_data.begin(); it != m_data.end(); ++it)
    {
        it->set(0L);
    }
    
    m_counter.set(0L);
}

