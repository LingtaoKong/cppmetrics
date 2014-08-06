// Copyright (c) 2011, XiaoMi Inc.
// All rights reserved.
//
// reservoir.cpp
//
// Author: Zhang Hong Qiang <zhanghongqiang@xiaomi.com>
//                          <pcman.zhang@gmail.com>
// Created on: May 8, 2013
// Description:
//

#include "reservoir.h"

using namespace com::xiaomi::mfs::metrics;

Reservoir::Reservoir(RandomGenerator& random) :
        m_random(random)
{
}

Reservoir::~Reservoir()
{
}

int Reservoir::get_next_int(int32_t range)
{
    return m_random.get_next_int(range);
}

