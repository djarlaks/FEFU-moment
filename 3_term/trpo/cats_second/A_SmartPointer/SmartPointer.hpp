#pragma once

#include <memory>

#include "Test.hpp"

namespace smart_pointer {
class exception : std::exception {
  using base_class = std::exception;
  using base_class::base_class;
};

// `SmartPointer` class declaration
template <typename T, typename Allocator>
class SmartPointer {
  // don't remove this macro
  ENABLE_CLASS_TESTS;

 public:
  using value_type = T;

  explicit SmartPointer(value_type *data = nullptr) {
    core = data ? new Core(data) : nullptr;
  }

  // copy constructor
  SmartPointer(const SmartPointer &other) {
    core = other.core;
    inc_not_null();
  }

  // move constructor
  SmartPointer(SmartPointer &&other) {
    core = other.core;
    other.core = nullptr;
  }

  // copy assigment
  SmartPointer &operator=(const SmartPointer &other) {
    this->~SmartPointer();
    core = other.core;
    inc_not_null();
    return *this;
  }

  // move assigment
  SmartPointer &operator=(SmartPointer &&other) {
    this->~SmartPointer();
    core = other.core;
    other.core = nullptr;
    return *this;
  }

  //
  SmartPointer &operator=(value_type *ptr) {
    this->~SmartPointer();
    core = ptr ? new Core(ptr) : nullptr;
    return *this;
  }

  ~SmartPointer() {
    if (core) core->~Core();
  }

  // return reference to the object of class/type T
  // if SmartPointer contains nullptr throw `SmartPointer::exception`
  value_type &operator*() {
    if (!core) {
      throw smart_pointer::exception();
    }

    T *ptr = core->data;
    if (!ptr) {
      throw smart_pointer::exception();
    }

    return *ptr;
  }

  const value_type &operator*() const {
    if (!core) {
      throw smart_pointer::exception();
    }

    T *ptr = core->data;
    if (!ptr) {
      throw smart_pointer::exception();
    }

    return *ptr;
  }

  // return pointer to the object of class/type T
  value_type *operator->() const { return get(); }

  inline value_type *get() const { return core ? core->data : nullptr; }

  // if pointer == nullptr => return false
  operator bool() const { return core ? core->data ? true : false : false; }

  // if pointers points to the same address or both null => true
  template <typename U, typename AnotherAllocator>
  bool operator==(const SmartPointer<U, AnotherAllocator> &other) const {
    void *this_data = static_cast<void *>(get());
    void *other_data = static_cast<void *>(other.get());

    return (this_data == other_data) ||
           (this_data == nullptr && other_data == nullptr);
  }

  // if pointers points to the same address or both null => false
  template <typename U, typename AnotherAllocator>
  bool operator!=(const SmartPointer<U, AnotherAllocator> &other) const {
    return !(*this == other);
  }

  // if smart pointer contains non-nullptr => return count owners
  // if smart pointer contains nullptr => return 0
  std::size_t count_owners() const { return core ? core->ref_count : 0; }

 private:
  class Core {
   public:
    value_type *data;
    std::size_t ref_count;

    explicit Core(value_type *ptr = nullptr) {
      data = ptr;
      ref_count = data ? 1 : 0;
    }

    void inc_ref_count() { ref_count++; }

    ~Core() {
      if (!ref_count) {
        delete data;
      }
    }
  };

  void inc_not_null() {
    if (core) core->inc_ref_count();
  }

  Core *core;
};
}  // namespace smart_pointer
