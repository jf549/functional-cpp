#include <iostream>
#include <vector>

template<typename FnT, typename ContainerT>
void map_inplace(FnT&& fn, ContainerT&& container) {
  for (auto& x : container) { fn(x); }
}

// (a' -> b') * a' container -> b' container
template <typename F,
          template <typename, typename...> class Container,
          typename Value,
          typename... Ts>
auto map(F&& f, const Container<Value, Ts...>& in) {
  Container<std::result_of_t<F(Value)>> out;
  out.reserve(in.size());
  std::transform(begin(in), end(in), std::back_inserter(out), std::forward<F>(f));
  return out;
}

template<typename ContainerT>
void print(ContainerT&& container) {
  for (const auto& x : container) { std::cout << x << " "; }
  std::cout << std::endl;
}

int main() {
  auto twice = [](auto& x){ x = x + x; };

  std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
  print(v);
  map_inplace(twice, v);
  print(v);

  std::vector<std::string> v2{ "One", "Two", "Three", "Four", "Five", "Six" };
  print(v2);
  map_inplace([](auto& x){ x.append("!"); }, v2);
  print(v2);

  std::vector<std::vector<int>> vs{ {1, 2}, {3, 4}, {5, 6} };
  map_inplace([](auto& xs){ print(xs); }, vs);
  map_inplace([&twice = twice](auto& xs){ map_inplace(twice, xs); }, vs);
  map_inplace([](auto& xs){ print(xs); }, vs);

  std::vector<int> v3{ 1, 2, 3, 4 };
  print(v3);
  auto v4 = map([](auto x){ return x < 3 ? std::string("Hi") : std::string("Bye"); }, v3);
  print(v4);
}
