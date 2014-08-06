#ifndef METRICS_SNAPSHOT_H_
#define METRICS_SNAPSHOT_H_

#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <string>

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{

class SnapShot
{
public:
    SnapShot();
    explicit SnapShot(const std::vector<uint64_t>& collection);
    virtual ~SnapShot();

public:
    void set_collection(const std::vector<uint64_t>& collection);

    /**
     * Returns the value at the given quantile
     *
     * @param quantile a given quantile, in {@code [0..1]}
     * @return the value in the distribute
     */
    double get_value(double quantile);

    /**
     * Returns the size of collection in the snapshot
     */
    size_t size() const;

    /**
     * Returns the median value in the distribution.
     */
    double get_median();

    double get_75th_percentile();
    double get_90th_percentile();
    double get_95th_percentile();
    double get_99th_percentile();
    double get_999th_percentile();

    double get_max();
    double get_min();
    double get_mean();

    virtual std::string to_report_string();

    //
    // Just for testing
    //
    const std::vector<uint64_t> & get_values();

private:
    std::vector<uint64_t> m_collection;
};

}
}
}
}

#endif /* METRICS_SNAPSHOT_H_ */
