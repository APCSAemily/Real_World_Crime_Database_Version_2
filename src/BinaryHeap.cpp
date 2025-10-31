#include "BinaryHeap.h"
#include <stdexcept>
#include "Crime.h"
#include <algorithm>
#include <vector>
using namespace std;

void BinaryHeap::up(size_t i){
  while(i > 0){
    size_t p = (i - 1) / 2;
    if(!(data[i].time < data[p].time)) break;
       std::swap(data[i], data[p]);
       i = p;
  }
}

void BinaryHeap::down(size_t i){
  size_t n = data.size();
  while(true){
    size_t best = i;
    size_t l = 2 * i + 1, r = 2 * i + 2;
    if(l < n && data[l].time < data[best].time) best = l;
    if(r < n && data[r].time < data[best].time) best = r;
    if( best == i) break;
    std::swap(data[i], data[best]);
    i = best;
  }
}

void BinaryHeap::push(const Crime& c){
  data.push_back(c);
  up(data.size() - 1);
}

Crime BinaryHeap::pop(){
  if(data.empty()) throw std::runtime_error("pop from empty heap");
  Crime root = data[0];
  data[0] = data.back();
  data.pop_back();
  if(!data.empty()) down(0);
  return root;
}

bool BinaryHeap::empty() const{
  return data.empty();
}
