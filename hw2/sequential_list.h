#include <cstring>
#include <iostream>
#include <vector>

struct SqList {
  int* data = nullptr;  // allocated size is equal or larger than `length`
  unsigned int length = 0;

  SqList(std::vector<int> data) {
    this->data = new int[data.size()];
    this->length = data.size();
    for (unsigned int i = 0; i < data.size(); i++) {
      this->data[i] = data[i];
    }
  }

  // Enlarge `list` by `amount`
  void Enlarge(unsigned int amount) {
    if (amount == 0) {
      return;
    }
    int* new_data = new int[this->length + amount];
    memcpy(new_data, this->data, this->length * sizeof(int));
    delete[] this->data;
    this->data = new_data;
    this->length += amount;
  }
};

std::ostream& operator<<(std::ostream& os, const SqList& list) {
  if (list.length == 0) {
    os << "[]";
    return os;
  }
  if (list.length == 1) {
    os << "[" << list.data[0] << "]";
    return os;
  }
  os << "[";
  for (unsigned i = 0; i < list.length - 1; i++) {
    os << list.data[i] << ", ";
  }
  os << list.data[list.length - 1] << "]";
  return os;
}

bool operator==(const SqList& lhs, const SqList& rhs) {
  if (lhs.length != rhs.length) {
    return false;
  }
  for (unsigned i = 0; i < lhs.length; i++) {
    if (lhs.data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}