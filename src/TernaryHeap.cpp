// src/TernaryHeap.cpp
#include "TernaryHeap.h"
#include <stdexcept>
#include <algorithm>

void TernaryHeap::heapifyUp(int i) {
    while (i > 0) {
        int p = parent(i);
        if (!(data[i].severity() < data[p].severity())) break;
        std::swap(data[i], data[p]);
        i = p;
    }
}

void TernaryHeap::heapifyDown(int i) {
    int n = static_cast<int>(data.size());
    while (true) {
        int best = i;
        int c1 = child1(i), c2 = child2(i), c3 = child3(i);
        if (c1 < n && data[c1].severity() < data[best].severity()) best = c1;
        if (c2 < n && data[c2].severity() < data[best].severity()) best = c2;
        if (c3 < n && data[c3].severity() < data[best].severity()) best = c3;
        if (best == i) break;
        std::swap(data[i], data[best]);
        i = best;
    }
}

void TernaryHeap::push(const Crime& c) {
    data.push_back(c);
    heapifyUp(static_cast<int>(data.size()) - 1);
}

Crime TernaryHeap::pop() {
    if (data.empty()) throw std::runtime_error("pop from empty ternary heap");
    Crime root = data[0];
    data[0] = data.back();
    data.pop_back();
    if (!data.empty()) heapifyDown(0);
    return root;
}

bool TernaryHeap::empty() const {
    return data.empty();
}
