#include <vector>
#pragma once
#define _dim 6
typedef enum {eBigger, eLess, eEqual} eCompare;
extern eCompare monomeOrder(const  std::vector<int> &pow1, const std::vector<int> &pow2);
