#pragma once

#include <vector>

template <class Type, typename Dimension>
auto initialize_vector(Type value, Dimension dimension) {
  return std::vector<Type>(dimension, value);
}

template <class Type, typename Dimension, typename... Other>
auto initialize_vector(Type value, Dimension dimension, Other... dimensions) {
  return std::vector<decltype(initialize_vector(value, dimensions...))>(
      dimension, initialize_vector(value, dimensions...));
}
