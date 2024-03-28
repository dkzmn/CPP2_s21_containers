#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using size_type = size_t;

  stack() : container_(){};
  stack(std::initializer_list<value_type> const& items) : container_(items){};
  stack(stack const& s) : container_(s.container_){};

  stack& operator=(stack const& s) {
    container_ = s.container_;
    return *this;
  }

  stack(stack&& s) noexcept : container_(std::move(s.container_)){};

  stack& operator=(stack&& s) noexcept {
    container_ = std::move(s.container_);
    return *this;
  }

  ~stack() = default;

  const_reference top() { return container_.back(); }
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack& other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    container_.insert_many_front(args...);
  }

 private:
  Container container_;
};
}  // namespace s21

#endif  // SRC_S21_STACK_H_
