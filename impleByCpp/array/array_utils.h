#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H
// 主要引入数组实现的线性表

// #include <algorithm>
// #include <iostream>
// #include <memory>
#include <vector>

void printList(const std::vector<int> &list);
void bubble_sort(std::vector<int> &list);    // 冒泡排序
void selection_sort(std::vector<int> &list); // 选择排序
int partition(std::vector<int> &list, const int &low, const int &high);
void quick_sort(std::vector<int> &list, const int &low,
                const int &high);            // 快速排序
void insertion_sort(std::vector<int> &list); // 插入排序
void heapify(std::vector<int> &list, const int &n, const int &i);
void heap_sort(std::vector<int> &list); // 堆排序
void merge(std::vector<int> &list, const int &left, const int &mid,
           const int &right);
void merge_sort(std::vector<int> &list, const int &left,
                const int &right);            // 归并排序
void shell_sort(std::vector<int> &list);      // 希尔排序
void count_sort(std::vector<int> &list);      // 计数排序
void bucket_sort(std::vector<int> &list);     // 桶排序
void radix_sort(std::vector<int> &list);      // 基数排序
void opt_bubble_sort(std::vector<int> &list); // 优化的冒泡排序

// 交换
static inline void swap(int &a, int &b) {
  if (a != b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
  }
}

#endif // ARRAY_UTILS_H