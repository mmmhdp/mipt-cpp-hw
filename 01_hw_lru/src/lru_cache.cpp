#include <list>
#include <sys/types.h>
#include <unordered_map>
#include "lru_cache.hpp"

LruCache:: LruCache (int capacity): Cache(capacity), nhit(0), nattempt(0) {}

std::list<int>::iterator LruCache::retrive(int obj_idx) {
  auto pobj = ltb.find(obj_idx);

  nattempt++;
  if (pobj != ltb.end())
  {
    nhit++;
    cache.splice(cache.begin(), cache, pobj->second);
    return pobj->second;
  }

  cache.push_front(obj_idx);
  ltb[obj_idx] = cache.begin();

  while (cache.size() > capacity)
  {
    auto to_delele_record = ltb.find(cache.back());
    ltb.erase(to_delele_record);
    cache.pop_back();
  }

  return cache.begin();
}

int LruCache::get_hits()
{
  return nhit;
}
