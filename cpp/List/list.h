#pragma once
#include <cstddef>

namespace task {

class Node {
 public:
  Node();
  Node(const int& data_, Node* prev_, Node* next_);

  ~Node();

  friend class list;

 private:
  int data;
  Node* prev;
  Node* next;
};

class list {
 public:
  list();
  list(size_t count, const int& value = int());
  list(const list& other);

  ~list();
  list& operator=(const list& other);

  int& front();
  const int& front() const;

  int& back();
  const int& back() const;

  bool empty() const;
  size_t size() const;
  void clear();

  void push_back(const int& value);
  void pop_back();
  void push_front(const int& value);
  void pop_front();
  void resize(size_t count);
  void swap(list& other);

  void remove(const int& value);
  void unique();
  void sort();

 private:
  Node* first;
  Node* last;
  size_t size_;
};

}  // namespace task
