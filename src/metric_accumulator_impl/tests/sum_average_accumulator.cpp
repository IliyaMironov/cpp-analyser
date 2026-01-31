#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(SumAverageAccumulator, SingleValue) {
    SumAverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 7});
    acc.Finalize();
    auto result = acc.Get();
    EXPECT_EQ(result.sum, 7);
    EXPECT_DOUBLE_EQ(result.average, 7.0);
}

TEST(SumAverageAccumulator, MultipleValues) {
    SumAverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 3});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 5});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 7});
    acc.Finalize();
    auto result = acc.Get();
    EXPECT_EQ(result.sum, 15);
    EXPECT_DOUBLE_EQ(result.average, 5.0);
}

TEST(SumAverageAccumulator, GetBeforeFinalizeThrows) {
    SumAverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 1});
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulator, FinalizeWithNoDataThrows) {
    SumAverageAccumulator acc;
    EXPECT_THROW(acc.Finalize(), std::runtime_error);
}

TEST(SumAverageAccumulator, ResetAndReuse) {
    SumAverageAccumulator acc;
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 10});
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 20});
    acc.Finalize();
    EXPECT_EQ(acc.Get().sum, 30);
    EXPECT_DOUBLE_EQ(acc.Get().average, 15.0);

    acc.Reset();
    acc.Accumulate(metric::MetricResult{.metric_name = "test", .value = 4});
    acc.Finalize();
    EXPECT_EQ(acc.Get().sum, 4);
    EXPECT_DOUBLE_EQ(acc.Get().average, 4.0);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
