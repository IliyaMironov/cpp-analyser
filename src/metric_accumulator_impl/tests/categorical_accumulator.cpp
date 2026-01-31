

#include "metric_accumulator_impl/categorical_accumulator.hpp"

#include <gtest/gtest.h>

#include <stdexcept>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(CategoricalAccumulator, GetBeforeFinalizeThrows) {
    CategoricalAccumulator acc;
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(CategoricalAccumulator, FinalizeEmpty) {
    CategoricalAccumulator acc;
    acc.Finalize();
    EXPECT_TRUE(acc.Get().empty());
}

TEST(CategoricalAccumulator, Reset) {
    CategoricalAccumulator acc;
    acc.Finalize();
    EXPECT_TRUE(acc.Get().empty());
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
