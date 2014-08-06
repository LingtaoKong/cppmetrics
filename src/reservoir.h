#ifndef METRICS_RESERVOIR_H_
#define METRICS_RESERVOIR_H_

#include <stdint.h>
#include "snapshot.h"
#include "snapshot.h"
#include "random_generator.h"

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

#define DEFAULT_SIZE  10280
class Reservoir
{
public:
    Reservoir(RandomGenerator& random);
    virtual ~Reservoir();

public:
    virtual int get_next_int(int32_t range);

public:
    //
    // 返回实际存储的值的个数
    //
    virtual size_t size() = 0;
    //
    // 返回一共记录过值的总数
    //
    virtual uint64_t get_count() = 0;
    virtual void update(uint64_t) = 0;
    virtual void make_snapshot(/* out */SnapShot& snapshot) = 0;
    virtual void reset() = 0;

private:
    RandomGenerator& m_random;
};

}
}
}
}

#endif /* METRICS_RESERVOIR_H_ */
