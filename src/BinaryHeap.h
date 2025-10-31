#pragma once
#include "Crime.h"
#include "BinaryHeap.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
using namespace std;

struct Crime; // Forward declaration - we don't need full Crime definition
class BinaryHeap{
  std::vector<Crime> data;
  void up(size_t i);
  void down(size_t i);

  public:
    void push(const Crime& c);
    Crime pop();
    bool empty() const;
};
