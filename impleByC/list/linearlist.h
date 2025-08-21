#ifndef LINEARLIST_H
#define LINEARLIST_H

// 主要引入数组实现的线性表
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;    // 数据指针
  int size;     // 当前元素个数
  int capacity; // 容量
} LinearList;

int getFirst(const LinearList *list);
int getLast(const LinearList *list);
void freeList(LinearList *list);
void bubble_sort(LinearList *list);    // 冒泡排序
void selection_sort(LinearList *list); // 选择排序
int partition(LinearList *list, int low, int high);
void quick_sort(LinearList *list, int low, int high); // 快速排序
void insertion_sort(LinearList *list);                // 插入排序
void heapify(LinearList *list, int n, int i);
void heap_sort(LinearList *list); // 堆排序
void merge(LinearList *list, int left, int mid, int right);
void merge_sort(LinearList *list, int left, int right); // 归并排序
void shell_sort(LinearList *list);                      // 希尔排序
void count_sort(LinearList *list);                      // 计数排序
void bucket_sort(LinearList *list);                     // 桶排序
void radix_sort(LinearList *list);                      // 基数排序
void opt_bubble_sort(LinearList *list);                 // 优化的冒泡排序

// 判断线性表是否为空
static inline int isEmpty(const LinearList *list) {
  return list == NULL || list->size == 0;
}

// 获取线性表的大小
static inline int getSize(const LinearList *list) { return list->size; }

// 获取线性表的容量
static inline int getCapacity(const LinearList *list) { return list->capacity; }

// 交换
static inline void swap(int *a, int *b) {
  if (*a != *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
  }
}

#endif // LINEARLIST_H