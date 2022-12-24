#pragma once

#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T, template <typename...> typename Container>
constexpr bool is_specialization_v = false;

template <template <typename...> typename Container, typename... Args>
constexpr bool is_specialization_v<Container<Args...>, Container> = true;

template <typename... Args, size_t... IdxFirst>
auto gen_tuple(const std::tuple<Args...>& tuple,
               std::index_sequence<IdxFirst...> tuple_index, std::size_t idx);

template <template <typename...> typename Tuple, typename... Args,
          size_t... IdxFirst>
auto gen_vectors(const std::vector<Tuple<Args...>>& vector,
                 std::index_sequence<IdxFirst...> tuple_index);

template <size_t Idx, template <typename...> typename Tuple, typename... Args>
auto gen_vector(const std::vector<Tuple<Args...>>& vector);

template <template <typename...> typename Tuple, typename... Args,
          size_t... IdxFirst>
auto gen_vectors(const std::vector<Tuple<Args...>>& vector,
                 std::index_sequence<IdxFirst...> tuple_index);

template <typename Arg1, typename Arg2>
auto TupleToVector(const std::pair<Arg1, Arg2>& pair);

template <typename Arg>
auto TupleToVector(const Arg& vector);

template <typename Arg>
auto VectorToTuple(const std::vector<Arg>& vector) {
  if constexpr (is_specialization_v<Arg, std::tuple>) {
    const std::size_t tuple_size = std::tuple_size_v<Arg>;
    auto indexes = std::make_index_sequence<tuple_size>{};

    auto res = gen_vectors(vector, indexes);
    if constexpr (std::tuple_size_v<decltype(res)> == 1) {
      return std::get<0>(res);
    } else {
      if constexpr (std::tuple_size_v<decltype(res)> == 2) {
        return std::make_pair(std::get<0>(res), std::get<1>(res));
      } else {
        return res;
      }
    }
  } else {
    if constexpr (is_specialization_v<Arg, std::pair>) {
      const std::size_t tuple_size = 2;
      auto indexes = std::make_index_sequence<tuple_size>{};

      auto res = gen_vectors(vector, indexes);
      if constexpr (std::tuple_size_v<decltype(res)> == 1) {
        return std::get<0>(res);
      } else {
        if constexpr (std::tuple_size_v<decltype(res)> == 2) {
          return std::make_pair(std::get<0>(res), std::get<1>(res));
        } else {
          return res;
        }
      }
    } else {
      return vector;
    }
  }
}

template <template <typename...> typename Tuple, typename... Args>
auto VectorToTuple(const std::vector<Tuple<Args...>>& vector) {
  const std::size_t tuple_size = std::tuple_size_v<Tuple<Args...>>;
  auto indexes = std::make_index_sequence<tuple_size>{};

  auto res = gen_vectors(vector, indexes);
  if constexpr (std::tuple_size_v<decltype(res)> == 1) {
    return std::get<0>(res);
  } else {
    if constexpr (std::tuple_size_v<decltype(res)> == 2) {
      return std::make_pair(std::get<0>(res), std::get<1>(res));
    } else {
      return res;
    }
  }
}

template <typename... Args, size_t... IdxFirst>
auto gen_tuple(const std::tuple<Args...>& tuple,
               std::index_sequence<IdxFirst...> tuple_index, std::size_t idx) {
  return std::tuple<typename std::remove_cv_t<
      typename std::remove_reference_t<typename std::remove_cv_t<
          typename std::remove_reference_t<Args>>::value_type>>...>(
      std::get<IdxFirst>(tuple)[idx]...);
}

template <typename Arg>
auto TupleToVector(const Arg& vector) {
  return vector;
}

template <typename Arg1, typename Arg2>
auto TupleToVector(const std::pair<Arg1, Arg2>& pair) {
  const std::size_t vector_size = std::get<0>(pair).size();

  std::vector<std::pair<
      typename std::remove_cv_t<
          typename std::remove_reference_t<decltype(std::get<0>(pair)[0])>>,
      typename std::remove_cv_t<
          typename std::remove_reference_t<decltype(std::get<1>(pair)[0])>>>>
      vector;

  for (std::size_t i = 0; i < vector_size; ++i) {
    vector.push_back(
        std::make_pair(std::get<0>(pair)[i], std::get<1>(pair)[i]));
  }

  return vector;
}

template <typename... Args>
auto TupleToVector(const std::tuple<Args...>& tuple) {
  const std::size_t tuple_size = std::tuple_size_v<std::tuple<Args...>>;
  const std::size_t vector_size = std::get<0>(tuple).size();
  auto indexes = std::make_index_sequence<tuple_size>{};

  if constexpr (tuple_size == 1) {
    std::vector<typename std::remove_cv_t<
        typename std::remove_reference_t<decltype(std::get<0>(tuple)[0])>>>
        vector;

    for (std::size_t i = 0; i < vector_size; ++i) {
      vector.push_back(std::get<0>(tuple)[i]);
    }

    return vector;
  } else {
    if constexpr (tuple_size == 2) {
      std::vector<
          std::pair<typename std::remove_cv_t<typename std::remove_reference_t<
                        decltype(std::get<0>(tuple)[0])>>,
                    typename std::remove_cv_t<typename std::remove_reference_t<
                        decltype(std::get<1>(tuple)[0])>>>>
          vector;

      for (std::size_t i = 0; i < vector_size; ++i) {
        vector.push_back(
            std::make_pair(std::get<0>(tuple)[i], std::get<1>(tuple)[i]));
      }

      return vector;
    } else {
      std::vector<typename std::remove_cv_t<typename std::remove_reference_t<
          decltype(gen_tuple(tuple, indexes, 0))>>>
          vector;

      for (std::size_t i = 0; i < vector_size; ++i) {
        vector.push_back(gen_tuple(tuple, indexes, i));
      }

      return vector;
    }
  }
}

template <size_t Idx, template <typename...> typename Tuple, typename... Args>
auto gen_vector(const std::vector<Tuple<Args...>>& vector) {
  std::vector<std::remove_cv_t<typename std::remove_reference_t<
      typename std::tuple_element_t<Idx, Tuple<Args...>>>>>
      v;
  for (const Tuple<Args...>& el : vector) {
    v.push_back(std::get<Idx>(el));
  }
  return v;
}

template <template <typename...> typename Tuple, typename... Args,
          size_t... IdxFirst>
auto gen_vectors(const std::vector<Tuple<Args...>>& vector,
                 std::index_sequence<IdxFirst...> tuple_index) {
  return std::tuple<std::vector<
      typename std::remove_cv_t<typename std::remove_reference_t<Args>>>...>(
      gen_vector<IdxFirst>(vector)...);
}
