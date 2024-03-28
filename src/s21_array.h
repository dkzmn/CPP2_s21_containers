#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

  array() {
    if (N != 0) fill_by_zero();
  }

  array(std::initializer_list<value_type> const& items) {
    if (N != 0) fill_by_zero();

    if (items.size() > N)
      throw std::out_of_range("excess elements in struct initializer");

    size_type counter = 0;
    for (auto n : items) {
      stat_array[counter++] = n;
    }
  }

  array(const array& a) {
    for (size_type i = 0; i < N; i++) {
      stat_array[i] = a.stat_array[i];
    }
  }

  array(array&& a) {
    for (size_type i = 0; i < N; i++) {
      stat_array[i] = a.stat_array[i];
    }
    a.~array();
  }

  ~array() = default;

  array& operator=(array&& a) {
    for (size_type i = 0; i < a.size(); i++) {
      stat_array[i] = a.stat_array[i];
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("array element is out_of_range");
    return stat_array[pos];
  }

  reference operator[](size_type pos) noexcept { return stat_array[pos]; }
  const_reference front() noexcept { return stat_array[0]; }
  const_reference back() noexcept { return stat_array[N - 1]; }
  iterator data() noexcept { return &stat_array[0]; }

  iterator begin() noexcept { return &stat_array[0]; }
  iterator end() noexcept { return &stat_array[N]; }

  bool empty() noexcept { return size() == 0; }
  size_type size() noexcept { return N; }
  size_type max_size() noexcept { return N; }

  void swap(array& other) noexcept {
    if (size() == other.size()) {
      value_type temp;
      for (size_type i = 0; i < N; i++) {
        temp = stat_array[i];
        stat_array[i] = other.stat_array[i];
        other.stat_array[i] = temp;
      }
    }
  }

  void fill(const_reference value) noexcept {
    for (size_type i = 0; i < N; i++) {
      stat_array[i] = value;
    }
  }

 private:
  value_type stat_array[N + 1];

  void fill_by_zero() noexcept {
    for (size_type i = 0; i < N; i++) {
      stat_array[i] = 0;
    }
  }
};

}  // namespace s21

#endif  // S21_ARRAY_H_
