// Copyright (c) 2011, XiaoMi Inc.
// All rights reserved.
//
// random_generator.cpp
//
// Author: Zhang Hong Qiang <zhanghongqiang@xiaomi.com>
//                          <pcman.zhang@gmail.com>
// Created on: May 7, 2013
// Description:
//

#include "random_generator.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace com::xiaomi::mfs::metrics;

/**
 * Thread Safe 的 RandomGenerator
 */
RandomGenerator::RandomGenerator()
{
    memset(&m_data, 0, sizeof(m_data));
    memset(m_state_buff, 0, sizeof(m_state_buff));
    initstate_r(time(NULL), m_state_buff, sizeof(m_state_buff), &m_data);
}

RandomGenerator::~RandomGenerator()
{
}

/**
 * 获得一个随机数
 */
int32_t RandomGenerator::get_next_int()
{
    int32_t result = 0;
    
#ifdef __GNUC__  // The GUN Extended TLS Version
    static __thread char stat_buff[DEFAULT_RANDOM_BUFF_SIZE];
    static __thread random_data buff;
    static __thread bool inited = false;
    
    if (!inited)
    {
        // 避免使用时间来做随机种子
        // 这里使用的是<code>m_data</code>的随机数来做为种子
        int32_t seed = 0;
        random_r(&m_data, &seed);
        initstate_r(seed, stat_buff, sizeof(stat_buff), &buff);
        srandom_r(seed, &buff);
        inited = true;
    }
    
    random_r(&buff, &result);
    
#else
    random_r(&m_data, &result);
#endif
    
    return result;
}

int32_t RandomGenerator::get_next_int(int32_t range)
{
    if (range == 0)
    {
        return 0;
    }
    
    return get_next_int() % range;
}

