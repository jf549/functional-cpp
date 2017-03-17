#include <iostream>
#include <vector>

template<typename FnT, typename ContainerT>
void map(FnT&& fn, ContainerT&& container) {
  for (auto& x : container) fn(x);
}

template<typename ContainerT>
void print(ContainerT&& container) {
  for (const auto& x : container) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

int main() {
  auto twice = [](auto& x){ x = x + x; };

  std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
  print(v);
  map(twice, v);
  print(v);

  std::vector<std::string> v2{ "One", "Two", "Three", "Four", "Five", "Six" };
  print(v2);
  map([](auto& x){ x.append("!"); }, v2);
  print(v2);

  std::vector<std::vector<int>> vs{ {1, 2}, {3, 4}, {5, 6} };
  map([](auto& xs){ print(xs); }, vs);
  map([&twice = twice](auto& xs){ map(twice, xs); }, vs);
  map([](auto& xs){ print(xs); }, vs);
}
