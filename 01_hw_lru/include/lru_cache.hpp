#include <list>
#include <unordered_map>

class Cache {
protected: 
  int capacity;

public:
  Cache (int capacity): capacity(capacity) {}
  virtual ~Cache () = default;
};


class LruCache : Cache {
private:
  int nattempt;
  int nhit;
protected:
  std::list<int> cache;
  std::unordered_map<int, std::list<int>::iterator> ltb;
public:
  LruCache (int capacity);
  std::list<int>::iterator retrive(int obj_idx);
  int get_hits();
};
