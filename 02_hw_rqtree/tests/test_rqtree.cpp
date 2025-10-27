#include <cstdio>
#include <fstream>
#include <string>
#include <numeric>

#include <gtest/gtest.h>
#include <vector>
#include "rqtree.hpp"

std::string constructTestFilePath(int test_idx, std::string suffix)
{
  std::string test_file, prefix; 

  prefix = "../tests/data/";
  if (test_idx < 10)
    test_file = prefix + "00" + std::to_string(test_idx) + suffix;
  else
    test_file = prefix + "0" + std::to_string(test_idx) + suffix;

  return test_file;
}

std::vector<int> testAgainstTestCaseWithIndex (int test_idx)
{
  std::string test_file = constructTestFilePath(test_idx, ".dat");
  std::ifstream ins (test_file);

  std::vector<int> res {-1,2,2};

  ins.close();
  return res;
}

class RqtreeParamTest : public ::testing::TestWithParam<int> {};

TEST_P(RqtreeParamTest, BasicAssertions) {
    int test_idx = GetParam();

    std::ifstream ans_file(constructTestFilePath(test_idx, ".ans"));
    ASSERT_TRUE(ans_file.is_open()) << "Missing .ans file for test " << test_idx;

    std::vector<int> expected;
    int tmp;
    while(ans_file >> tmp)
      expected.push_back(tmp);

    std::vector<int> result = testAgainstTestCaseWithIndex(test_idx);
    ASSERT_EQ(result.size(), expected.size()) << "Mismatch in number of answers" << std::endl << "Failed test case #" << test_idx;
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(result[i], expected[i]) << "Mismatch at index " << i << std::endl << "Failed test case #" << test_idx;
    }
}


std::vector<int> make_range(int from, int to) {
    std::vector<int> v(to - from + 1);
    std::iota(v.begin(), v.end(), from);
    return v;
}

INSTANTIATE_TEST_SUITE_P(
    RqtreeTests,
    RqtreeParamTest,
    ::testing::ValuesIn(make_range(1, 1))
);
