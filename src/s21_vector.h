#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <stddef.h>

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n) : size_(n), capacity_(n) {
    if (n > 0) {
      data_ = new value_type[n];
      std::fill(begin(), end(), 0);
    } else {
      data_ = nullptr;
    }
  }

  vector(std::initializer_list<value_type> const &items)
      : data_(new value_type[items.size()]),
        size_(items.size()),
        capacity_(items.size()) {
    std::copy(items.begin(), items.end(), data_);
  }

  vector(const vector &v)
      : data_(new value_type[v.capacity_]),
        size_(v.size_),
        capacity_(v.capacity_) {
    std::copy(v.data_, v.data_ + size_, data_);
  }

  vector(vector &&v) : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  ~vector() { setZero_(); }

  vector &operator=(vector &&v) {
    if (this != &v) {
      setZero_();
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = v.data_;
      v.size_ = 0;
      v.capacity_ = 0;
      v.data_ = nullptr;
    }
    return *this;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      setZero_();
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = nullptr;
      if (size_ > 0) {
        data_ = new value_type[capacity_];
        std::copy(v.data_, v.data_ + size_, data_);
      }
    }
    return *this;
  }

  reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }
  const_reference operator[](size_type pos) const { return at(pos); }

  const_reference front() const {
    if (size_ == 0) {
      throw std::logic_error("Vector size is zero");
    }
    return data_[0];
  }

  const_reference back() const {
    if (size_ == 0) {
      throw std::logic_error("Vector size is zero");
    }
    return data_[size_ - 1];
  }

  iterator data() noexcept { return &data_[0]; }

  iterator begin() noexcept { return &data_[0]; }

  iterator end() noexcept { return &data_[size_]; }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size > capacity_) {
      iterator tmp = data_;
      data_ = new value_type[size];
      std::copy(tmp, tmp + size_, data_);
      delete[] tmp;
      capacity_ = size;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      iterator tmp = new value_type[size_];
      std::copy(data_, data_ + size_, tmp);
      delete[] data_;
      data_ = tmp;
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Pos must point to vector element");
    }
    size_type index_pos = pos - begin();
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    iterator new_pos = begin() + index_pos;
    for (iterator iter = end(); iter > new_pos; iter--) {
      *iter = *(iter - 1);
    }
    *new_pos = value;
    size_++;
    return new_pos;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Pos must point to vector element");
    }
    for (iterator iter = pos; iter < end() - 1; iter++) {
      *iter = *(iter + 1);
    }
    size_--;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() {
    if (size_ == 0) {
      throw std::length_error("Cant pop_back from zero length vector");
    }
    size_--;
  }

  void swap(vector &other) {
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
    std::swap(other.data_, data_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    iterator tmp_pos = (iterator)pos;
    for (auto &i : args_v) {
      tmp_pos = insert(tmp_pos, i) + 1;
    }
    return tmp_pos - 1;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

 private:
  iterator data_;
  size_type size_;
  size_type capacity_;

  void setZero_() {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
    size_ = 0;
    capacity_ = 0;
  }
};
}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
