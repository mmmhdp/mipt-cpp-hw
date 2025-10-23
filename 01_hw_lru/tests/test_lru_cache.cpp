#include <cstdio>
#include <fstream>
#include <string>
#include <numeric>

#include <gtest/gtest.h>
#include "lru_cache.hpp"

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

int testAgainstTestCaseWithIndex (int test_idx)
{
  std::string test_file = constructTestFilePath(test_idx, ".dat");
  std::ifstream ins (test_file);

  int cache_size, nq; 

  ins >> cache_size;
  ins >> nq;

  LruCache c = LruCache(cache_size);

  int nhit = 0;
  for (int q = 0; q < nq; q++)
  {
    int page_idx;

    ins >> page_idx;
    c.retrive(page_idx);
  }
  nhit = c.get_hits();

  std::cout << test_file << std::endl;

  ins.close();
  return nhit;
}

class LruCacheParamTest : public ::testing::TestWithParam<int> {};

TEST_P(LruCacheParamTest, BasicAssertions) {
    int test_idx = GetParam();

    std::ifstream ans_file(constructTestFilePath(test_idx, ".ans"));
    ASSERT_TRUE(ans_file.is_open()) << "Missing .ans file for test " << test_idx;

    int expected;
    ans_file >> expected;

    int result = testAgainstTestCaseWithIndex(test_idx);

    EXPECT_EQ(result, expected) << "Failed test case #" << test_idx;
}


std::vector<int> make_range(int from, int to) {
    std::vector<int> v(to - from + 1);
    std::iota(v.begin(), v.end(), from);
    return v;
}

INSTANTIATE_TEST_SUITE_P(
    LruCacheTests,
    LruCacheParamTest,
    ::testing::ValuesIn(make_range(1, 17))
);
