#include "../lib/h.h" // h::{ hash_t, hash }
#include <vector>     // std::vector

template <class T> class HashMap {
public:
  using key_type = h::hash_t;
  using value_type = T;
  using size_type = decltype (0zu);

  constexpr auto operator [](
    const std::string_view key_str) noexcept -> value_type & {
    const auto key = h::hash(key_str);
    auto idx = 0zu;
    for (const auto k: keys) {
      if (k == key) {
        return values[idx];
      }
      static_cast<void>(++idx);
    }
    keys.emplace_back(key);
    values.push_back(value_type{});
    return values[idx];
  }

private:
  std::vector<key_type> keys;
  std::vector<value_type> values;
};

auto main() -> int {
  HashMap<int> h{};
  h["LMAO"] = 0XDadBeef;
  return h["LMAO"] xor 0XDadBeef;
}
