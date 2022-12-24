#pragma once

#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>

template <typename Container, typename... Types>
struct is_set : std::false_type {};

template <typename... Types>
struct is_set<std::set<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_map : std::false_type {};

template <typename... Types>
struct is_map<std::map<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_unordered_set : std::false_type {};

template <typename... Types>
struct is_unordered_set<std::unordered_set<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_unordered_map : std::false_type {};

template <typename... Types>
struct is_unordered_map<std::unordered_map<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_multiset : std::false_type {};

template <typename... Types>
struct is_multiset<std::multiset<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_multimap : std::false_type {};

template <typename... Types>
struct is_multimap<std::multimap<Types...>> : std::true_type {};

template <typename Container, typename... Types>
struct is_unordered_multiset : std::false_type {};

template <typename... Types>
struct is_unordered_multiset<std::unordered_multiset<Types...>>
    : std::true_type {};

template <typename Container, typename... Types>
struct is_unordered_multimap : std::false_type {};

template <typename... Types>
struct is_unordered_multimap<std::unordered_multimap<Types...>>
    : std::true_type {};

template <typename Container>
struct is_associative {
  static constexpr bool value =
      is_set<Container>::value || is_map<Container>::value ||
      is_unordered_set<Container>::value ||
      is_unordered_map<Container>::value || is_multiset<Container>::value ||
      is_multimap<Container>::value ||
      is_unordered_multiset<Container>::value ||
      is_unordered_multimap<Container>::value;
};

template <typename Container>
struct is_multicontainer {
  static constexpr bool value = is_multiset<Container>::value ||
                                is_multimap<Container>::value ||
                                is_unordered_multiset<Container>::value ||
                                is_unordered_multimap<Container>::value;
};

template <typename T1, typename T2>
struct is_same_data_type {
 private:
  template <class V1, class V2>
  typename std::enable_if<std::is_same_v<typename std::remove_cv_t<V1>,
                                         typename std::remove_cv_t<V2>>,
                          char>::type static constexpr test(const V1&,
                                                            const V2&) {}

  template <class K1, class K2, class V1, class V2>
  typename std::enable_if<
      std::is_same_v<typename std::remove_cv_t<K1>,
                     typename std::remove_cv_t<K2>> &&
          std::is_same_v<typename std::remove_cv_t<V1>,
                         typename std::remove_cv_t<V2>>,
      char>::type static constexpr test(const std::pair<K1, V1>&,
                                        const std::pair<K2, V2>&) {}

  static int test(...) { return 0; }
  static constexpr T1& t1 = nullptr;
  static constexpr T2& t2 = nullptr;

 public:
  static constexpr bool value = sizeof(test(t1, t2)) == sizeof(char);
};

template <class Container1, class Container2>
bool MergeAssociative(Container1* left, const Container2& right) {
  if constexpr (is_associative<Container1>::value &&
                is_associative<Container2>::value) {
    if constexpr (is_same_data_type<typename Container1::value_type,
                                    typename Container2::value_type>::value) {
      if constexpr (is_multicontainer<Container1>::value ||
                    (!is_multicontainer<Container1>::value &&
                     !is_multicontainer<Container2>::value)) {
        for (auto it = right.begin(); it != right.end(); ++it) {
          left->insert(*it);
        }
        return false;
      }
    }
  }
  return true;
}
