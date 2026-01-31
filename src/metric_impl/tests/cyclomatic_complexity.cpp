#include "metric_impl/cyclomatic_complexity.hpp"

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

// simple.py: assert → 1 + 1 = 2
TEST(CyclomaticComplexity, SimpleWithAssert) {
    auto func = GetFirstFunction("simple.py");
    CyclomaticComplexityMetric metric;
    auto result = metric.Calculate(func);
    EXPECT_EQ(result.metric_name, "Cyclomatic Complexity");
    EXPECT_EQ(result.value, 2);
}

// if.py: 1 if_statement → 1 + 1 = 2
TEST(CyclomaticComplexity, SingleIf) {
    auto func = GetFirstFunction("if.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 2);
}

// loops.py: for + while + if → 1 + 3 = 4
TEST(CyclomaticComplexity, Loops) {
    auto func = GetFirstFunction("loops.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 4);
}

// nested_if.py: 2 if + 1 elif + 1 assert → 1 + 4 = 5
TEST(CyclomaticComplexity, NestedIf) {
    auto func = GetFirstFunction("nested_if.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 5);
}

// exceptions.py: try + finally + assert → 1 + 3 = 4
TEST(CyclomaticComplexity, Exceptions) {
    auto func = GetFirstFunction("exceptions.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 4);
}

// match_case.py: 3 case_clause → 1 + 3 = 4
TEST(CyclomaticComplexity, MatchCase) {
    auto func = GetFirstFunction("match_case.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 4);
}

// ternary.py: 2 conditional_expression → 1 + 2 = 3
TEST(CyclomaticComplexity, Ternary) {
    auto func = GetFirstFunction("ternary.py");
    CyclomaticComplexityMetric metric;
    EXPECT_EQ(metric.Calculate(func).value, 3);
}

}  // namespace analyzer::metric::metric_impl
