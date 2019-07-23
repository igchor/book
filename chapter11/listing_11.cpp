#include <experimental/type_traits>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cstdio>

struct pool_base {
    
};


  template <uint64_t slots>
  struct leaf_entries_t {
          uint64_t idxs[slots];
          size_t size;
  };

  template <typename Key, typename Value, uint64_t slots>
  class leaf_node_t {
  public:
         using key_type = Key;
         using value_type = std::pair<key_type, Value>;
         
         void insert_idx(uint64_t);
         void insert(pool_base &pop, const value_type &entry);
 private:
         value_type entries[slots];
         leaf_entries_t<slots> v[2];
         uint32_t current;
 };

template <typename Key, typename Value, uint64_t slots>
void leaf_node_t<Key, Value, slots>::insert_idx(uint64_t insert_pos) {
        std::lower_bound(v[current].idxs, v[current].idxs + v[current].size, entries[insert_pos].first,
                        [&](uint64_t idx1, const key_type &key) {
                                return entries[idx1].first < key;
                        });
}
template <typename Key, typename Value, uint64_t slots>
void leaf_node_t<Key, Value, slots>::insert (pool_base &pop, const value_type &entry) {
        size_t insert_pos = v[current].size;

        entries[insert_pos] = entry;
        //pop.flush(&(entries[insert_pos]), sizeof(entries[insert_pos]));

        insert_idx(insert_pos);
       // pop.persist(&v[1 - current], sizeof(leaf_entries_t));

        current = 1 - current;
        //pop.persist(&current, sizeof(current));
}

int main () {
   leaf_node_t<int, int, 10> node;
    
    pool_base pop;
    std::pair<int, int> e{1, 2};
    
   node.insert(pop, e);
    
}


