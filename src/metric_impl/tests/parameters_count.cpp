#include "metric_impl/parameters_count.hpp"

#include <gtest/gtest.h>

#include "file.hpp"
#include "function.hpp"

namespace analyzer::metric::metric_impl {

namespace {

auto GetFirstFunction(const std::string &filename) {
    file::File file(filename);
    function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);
    return functions.at(0);
}

}  // namespace

// simple.py: def test_simple() — 0 параметров
TEST(ParametersCount, NoParameters) {
    auto func = GetFirstFunction("simple.py");
    CountParametersMetric metric;
    auto result = metric.Calculate(func);
    EXPECT_EQ(result.metric_name, "Parameters count");
    EXPECT_EQ(result.value, 0);
}

// if.py: def testIf(x) — 1 параметр
TEST(ParametersCount, SingleParameter) {
    auto func = GetFirstFunction("if.py");
    CountParametersMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 1);
}

// nested_if.py: def Testnestedif(x, y) — 2 параметра
TEST(ParametersCount, TwoParameters) {
    auto func = GetFirstFunction("nested_if.py");
    CountParametersMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 2);
}

// comments.py: def Func_comments(result, a, b) — 3 параметра
TEST(ParametersCount, ThreeParameters) {
    auto func = GetFirstFunction("comments.py");
    CountParametersMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 3);
}

// many_parameters.py: def __test_multiparameters__(a, b, c=5, *args, **kwargs) — 5 параметров
TEST(ParametersCount, ManyParameters) {
    auto func = GetFirstFunction("many_parameters.py");
    CountParametersMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 5);
}

}  // namespace analyzer::metric::metric_impl
