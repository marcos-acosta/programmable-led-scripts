#include "queue.hpp"

Queue::Node::Node(int val): val_{val}, prev_{nullptr}, next_{nullptr} {
  // Nothing to see here, folks!
}

Queue::Node::Node(int val, Node *prev): val_{val}, prev_{prev}, next_{nullptr} {
  // Nothing to see here, folks!
}

Queue::Node::Node(int val, Node *prev, Node *next): val_{val}, prev_{prev}, next_{next} {
  // Nothing to see here, folks!
}

Queue::Queue(): head_{nullptr}, tail_{nullptr}, size_{0} {
  // Nothing to see here, folks!
}

Queue::~Queue() {
  while (tail_)
    pop();
}

size_t Queue::size() {
  return size_;
}

bool Queue::is_empty() {
  return size_ == 0;
}

int Queue::peek() {
  return head_ ? head_->val_ : 0;
}

int Queue::peek_back() {
  return tail_ ? tail_->val_ : 0;
}

void Queue::push(int val) {
  if (size() == 0) {
    head_ = new Node(val);
    tail_ = head_;
    ++size_;
    return;
  }
  
  if (size() == 1) {
    head_->next_ = new Node(val, head_);
  } else {
    tail_->next_ = new Node(val, tail_);
  }

  tail_->prev_ = tail_;
  tail_ = tail_->next_;
  ++size_;
}

void Queue::push_front(int val) {
  if (size() == 0) {
    push(val);
    return;
  }

  Node *new_head = new Node(val, nullptr, head_);
  head_->prev_ = new_head;
  head_ = new_head;
}

int Queue::pop() {
  if (size() == 0) {
    return 0;
  }

  Node *old_head = head_;
  int val = old_head->val_;

  // std::cout << val << std::endl;

  if (size() == 1) {
    tail_ = nullptr;
  } else if (size() == 2) {
    tail_ = head_;
  } else if (size() == 3) {
    tail_->prev_ = head_;
  }

  head_ = head_->next_;
  delete old_head;
  --size_;

  return val;
}
