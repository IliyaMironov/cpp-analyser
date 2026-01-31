#include "metric_impl/code_lines_count.hpp"

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

TEST(CodeLinesCount, Simple) {
    auto func = GetFirstFunction("simple.py");
    CodeLinesCountMetric metric;
    auto result = metric.Calculate(func);
    EXPECT_EQ(result.metric_name, "Code lines count");
    EXPECT_EQ(result.value, 5);
}

TEST(CodeLinesCount, Comments) {
    auto func = GetFirstFunction("comments.py");
    CodeLinesCountMetric metric;
    auto result = metric.Calculate(func);
    EXPECT_EQ(result.value, 3);
}

TEST(CodeLinesCount, ManyLines) {
    auto func = GetFirstFunction("many_lines.py");
    CodeLinesCountMetric metric;
    auto result = metric.Calculate(func);
    EXPECT_EQ(result.value, 10);
}

}  // namespace analyzer::metric::metric_impl
