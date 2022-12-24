#pragma once

#include <algorithm>
#include <type_traits>

template <class T, class Iterator>
Iterator ImplFind(const T &value, Iterator first, Iterator last,
                  std::random_access_iterator_tag) {
  Iterator end = last;

  while (first != last) {
    Iterator middle = first + ((last - first) / 2);
    if (*middle < value) {
      first = middle + 1;
    } else {
      last = middle;
    }
  }

  if (*last == value) return last;

  return end;
}

template <class T, class Iterator>
Iterator ImplFind(const T &value, Iterator first, Iterator last, ...) {
  for (Iterator it = first; it != last; ++it) {
    if (*it == value) {
      return it;
    }
  }

  return last;
}

template <class T, class Iterator>
Iterator Find(const T &value, Iterator first, Iterator last) {
  using tag = typename std::iterator_traits<Iterator>::iterator_category;
  return ImplFind(value, first, last, tag());
}
