
#ifndef METRICS_UNIFORM_RESERVOIR_H_
#define METRICS_UNIFORM_RESERVOIR_H_

#include <vector>
#include "reservoir.h"
#include "atomic.h"
#include "thirdparty/boost/thread.hpp"

using namespace std;

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

/**
 * A random sampling reservoir of a stream of {@code long}s. Uses Vitter's Algorithm R to produce a
 * statistically representative sample.
 *
 * @see <a href="http://www.cs.umd.edu/~samir/498/vitter.pdf">Random Sampling with a Reservoir</a>
 */

class UniformReservoir: public Reservoir
{
public:
    UniformReservoir(RandomGenerator& random);
    UniformReservoir(RandomGenerator& random, size_t size);
    virtual ~UniformReservoir();

public:
    size_t size();
    uint64_t get_count();
    void update(uint64_t);
    void make_snapshot(/* out */SnapShot& snapshot);
    void reset();

private:
    void init(size_t size);

private:
    mutable MfsAtomic m_counter;
    mutable std::vector<MfsAtomic> m_data;
};

}
}
}
}

#endif /* METRICS_UNIFORM_RESERVOIR_H_ */
