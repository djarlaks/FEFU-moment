#include <utility>

#pragma once
#ifdef DEBUG

template <class A, class B>
struct Convert;

#endif

using std::declval;

template <class F, class I>
struct is_customly_convertible {
 private:
  template <class From, class Into>
  static void detector(...);

  template <class From, class Into>
  static int detector(decltype(&Convert<From, Into>::operator()));

 public:
  static constexpr bool value =
      std::is_same<int, decltype(detector<F, I>(0))>::value;
};

class NoTriviallyConstructible {
  NoTriviallyConstructible() = delete;
};

class NoCopyConstructible {
  NoCopyConstructible(const NoCopyConstructible &) = delete;
  NoCopyConstructible &operator=(const NoCopyConstructible &) = delete;
};

template <>
struct Convert<NoTriviallyConstructible, int> {
  int operator()(const NoTriviallyConstructible &) { return 0; }
};

template <>
struct Convert<NoCopyConstructible, NoTriviallyConstructible> {
  NoTriviallyConstructible operator()(const NoCopyConstructible &) {
    return *reinterpret_cast<NoTriviallyConstructible *>(0xffff);
  }
};
