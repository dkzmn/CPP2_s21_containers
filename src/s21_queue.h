#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using size_type = size_t;

  queue() : container_(){};
  queue(std::initializer_list<value_type> const& items) : container_(items){};
  queue(queue const& q) : container_(q.container_){};

  queue& operator=(queue const& q) {
    container_ = q.container_;
    return *this;
  }

  queue(queue&& q) noexcept : container_(std::move(q.container_)){};

  queue& operator=(queue&& q) noexcept {
    container_ = std::move(q.container_);
    return *this;
  }

  ~queue() = default;

  const_reference front() { return container_.front(); }
  const_reference back() { return container_.back(); }
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_front(); }
  void swap(queue& other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    container_.insert_many_back(args...);
  }

 private:
  Container container_;
};
}  // namespace s21

#endif  // SRC_S21_QUEUE_H_
