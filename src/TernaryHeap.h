#pragma once
#include "Crime.h"
#include <vector>
using namespace std;

class TernaryHeap{
    vector<Crime> data;

    int parent(int i) const { return (i - 1) / 3;}
    int child1(int i) const { return 3 * i + 1; }
    int child2(int i) const { return 3 * i + 2; }
    int child3(int i) const { return 3 * i + 3; }

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    void push(const Crime& c);
    Crime pop();
    bool empty() const;
};
