#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>

#include "../s21_containers.h"

TEST(Stack, Constructors_1) {
  s21::stack<int> test1{1, 2, 3, 4, 5};
  s21::stack<int> test2(test1);
  while (!test1.empty()) {
    EXPECT_EQ(test1.top(), test2.top());
    test1.pop();
    test2.pop();
  }
  ASSERT_TRUE(test2.empty());
}

TEST(Stack, Constructors_2) {
  s21::stack<int> test1{1, 2, 3, 4, 5};
  s21::stack<int> test2(std::move(test1));
  std::stack<int, std::list<int>> original;
  int i = 1;
  while (i < 6) {
    original.push(i);
    ++i;
  }
  while (!original.empty()) {
    EXPECT_EQ(original.top(), test2.top());
    original.pop();
    test2.pop();
  }
  ASSERT_TRUE(test1.empty());
  ASSERT_TRUE(test2.empty());
}

TEST(Stack, CopyMoveOperators) {
  s21::stack<int> test1{1, 2, 3, 4, 5};
  s21::stack<int> test2;
  test2 = test1;
  while (!test1.empty()) {
    EXPECT_EQ(test1.top(), test2.top());
    test1.pop();
    test2.pop();
  }
  ASSERT_TRUE(test2.empty());
  s21::stack<int> test3{5, 4, 3, 2, 1};
  test2 = std::move(test3);
  ASSERT_TRUE(test3.empty());
  EXPECT_EQ(5, test2.size());
  EXPECT_EQ(1, test2.top());
}

TEST(Stack, Swap) {
  s21::stack<char> test1 = {'a', 'b', 'c'};
  s21::stack<char> test2 = {'c', 'c', 'c', 'c', 'c'};
  test1.swap(test2);
  EXPECT_EQ(5, test1.size());
  EXPECT_EQ(3, test2.size());
  while (!test1.empty()) {
    EXPECT_EQ('c', test1.top());
    test1.pop();
  }
}

TEST(Stack, PushPop) {
  s21::stack<int> test1;
  std::stack<int, std::list<int>> original;
  int i = 10;
  while (i > 0) {
    test1.push(i);
    original.push(i);
    --i;
  }
  ASSERT_FALSE(test1.empty());
  EXPECT_EQ(original.size(), test1.size());
  while (!original.empty()) {
    EXPECT_EQ(original.top(), test1.top());
    original.pop();
    test1.pop();
  }
  ASSERT_TRUE(test1.empty());
}

TEST(Stack, InsertManyFront) {
  s21::stack<int> test1 = {3, 4, 5, 6};
  EXPECT_EQ(4, test1.size());
  test1.insert_many_front(0, 1, 2);
  EXPECT_EQ(7, test1.size());
  int check = 6;
  while (!test1.empty()) {
    EXPECT_EQ(check--, test1.top());
    test1.pop();
  }
  EXPECT_EQ(-1, check);
}

TEST(Queue, Constructors_1) {
  s21::queue<int> test1{1, 2, 3, 4, 5};
  s21::queue<int> test2(test1);
  while (!test1.empty()) {
    EXPECT_EQ(test1.front(), test2.front());
    test1.pop();
    test2.pop();
  }
  ASSERT_TRUE(test2.empty());
}

TEST(Queue, Constructors_2) {
  s21::queue<int> test1{1, 2, 3, 4, 5};
  s21::queue<int> test2(std::move(test1));
  std::queue<int, std::list<int>> original;
  int i = 1;
  while (i < 6) {
    original.push(i);
    ++i;
  }
  while (!original.empty()) {
    EXPECT_EQ(original.front(), test2.front());
    original.pop();
    test2.pop();
  }
  ASSERT_TRUE(test1.empty());
  ASSERT_TRUE(test2.empty());
}

TEST(Queue, CopyMoveOperators) {
  s21::queue<int> test1{1, 2, 3, 4, 5};
  s21::queue<int> test2;
  test2 = test1;
  while (!test1.empty()) {
    EXPECT_EQ(test1.front(), test2.front());
    test1.pop();
    test2.pop();
  }
  ASSERT_TRUE(test2.empty());
  s21::queue<int> test3{5, 4, 3, 2, 1};
  test2 = std::move(test3);
  ASSERT_TRUE(test3.empty());
  EXPECT_EQ(5, test2.size());
  EXPECT_EQ(1, test2.back());
  EXPECT_EQ(5, test2.front());
}

TEST(Queue, Swap) {
  s21::queue<char> test1 = {'a', 'b', 'c'};
  s21::queue<char> test2 = {'c', 'c', 'c', 'c', 'c'};
  test1.swap(test2);
  EXPECT_EQ(5, test1.size());
  EXPECT_EQ(3, test2.size());
  while (!test1.empty()) {
    EXPECT_EQ('c', test1.front());
    test1.pop();
  }
}

TEST(Queue, PushPop) {
  s21::queue<int> test1;
  std::queue<int, std::list<int>> original;
  int i = 10;
  while (i > 0) {
    test1.push(i);
    original.push(i);
    --i;
  }
  ASSERT_FALSE(test1.empty());
  EXPECT_EQ(original.size(), test1.size());
  while (!original.empty()) {
    EXPECT_EQ(original.front(), test1.front());
    original.pop();
    test1.pop();
  }
  ASSERT_TRUE(test1.empty());
}

TEST(Queue, InsertManyBack) {
  s21::queue<int> test1 = {0, 1, 2};
  EXPECT_EQ(3, test1.size());
  test1.insert_many_back(3, 4, 5, 6);
  EXPECT_EQ(7, test1.size());
  int check = 0;
  while (!test1.empty()) {
    EXPECT_EQ(check++, test1.front());
    test1.pop();
  }
  EXPECT_EQ(7, check);
}
