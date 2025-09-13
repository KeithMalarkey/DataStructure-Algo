#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

int linearSearch(const std::vector<int> &arr, const int &target);
int binarySearch(const std::vector<int> &arr, const int &target);
int fibonacciSearch(const std::vector<int> &arr, const int &target);
int interpolationSearch(const std::vector<int> &arr, const int &target);

#endif