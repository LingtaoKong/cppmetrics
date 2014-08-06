
#ifndef METRICS_RANDOM_GENERATOR_H_
#define METRICS_RANDOM_GENERATOR_H_

#include <vector>
#include <stdlib.h>

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A thread safe random generator
// using GUN extended Thread Local Storage to make it high performance.
// For other compiler, this class will use a global random_r to instead it.
//
// This class is not implemented as Singleton pattern, because someone else may want to derive from this class and
// provide a better implementation.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RandomGenerator
{
    enum
    {
        DEFAULT_RANDOM_BUFF_SIZE = 512
    };

public:
    RandomGenerator();
    virtual ~RandomGenerator();

public:
    int32_t get_next_int();
    int32_t get_next_int(int32_t range);

private:
    struct random_data m_data;
    char m_state_buff[DEFAULT_RANDOM_BUFF_SIZE];
};

}
}
}
}

#endif /* METRICS_RANDOM_GENERATOR_H_ */
