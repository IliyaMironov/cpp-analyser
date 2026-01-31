#include "metric_accumulator_impl/average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(AverageAccumulator, SingleValue) {
    AverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 10});
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), 10.0);
}

TEST(AverageAccumulator, MultipleValues) {
    AverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 4});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 6});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 8});
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), 6.0);
}

TEST(AverageAccumulator, GetBeforeFinalizeThrows) {
    AverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 5});
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulator, FinalizeWithNoDataThrows) {
    AverageAccumulator acc;
    EXPECT_THROW(acc.Finalize(), std::runtime_error);
}

TEST(AverageAccumulator, ResetAndReuse) {
    AverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 10});
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), 10.0);

    acc.Reset();
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 2});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 4});
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), 3.0);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
