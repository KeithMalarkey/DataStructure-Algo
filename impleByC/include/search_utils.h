#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct {
  int *data;    // 数据指针
  int size;     // 当前元素个数
  int capacity; // 容量
} LinearList;

void swap(int *a, int *b);                              // 交换两个整数
void sort(LinearList *arr);                             // 排序数组
void binary_search(int arr[], int size, int target);    // 二分查找
void linear_search(int arr[], int size, int target);    // 线性查找
void sort_array(int arr[], int size);                   // 数组排序
void print_array(LinearList *arr);                      // 打印数组
void interploation_search(LinearList *arr, int target); // 插值查找
void fibonacci_search(LinearList *arr, int target);     // 斐波那契查找

#endif