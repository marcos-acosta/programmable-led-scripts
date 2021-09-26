#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// This is a minimal queue class to be used for Arduino.
class Queue {
 private:
  class Node;
  Node *head_;
  Node *tail_;
  size_t size_;

 public:
  Queue();
  ~Queue();

  int peek();
  int peek_back();
  bool is_empty();
  void push(int val);
  void push_front(int val);
  int pop();
  size_t size();

 private:
  class Node {
    public:
      Node(int val);
      Node(int val, Node* prev);
      Node(int val, Node* prev, Node* next);
      ~Node() = default;

   private:
      int val_;
      Node *prev_;
      Node *next_;

      friend class Queue;
  };
};

#endif