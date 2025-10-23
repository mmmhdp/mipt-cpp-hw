#include <iostream>
#include "lru_cache.hpp"

int main(void) {
  int cache_size, nq; 

  std::cin >> cache_size;
  std::cin >> nq;

  LruCache c = LruCache(cache_size);

  int nhit = 0;
  for (int q = 0; q < nq; q++)
  {
    int page_idx;

    std::cin >> page_idx;
    c.retrive(page_idx);
  }

  nhit = c.get_hits();
  std::cout << nhit << std::endl;

  return 0;
}
