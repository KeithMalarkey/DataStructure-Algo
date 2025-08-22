#include "utils.h"
// #include <stddef.h>

int main() {
  LinearList *arr = malloc(sizeof(LinearList));
  arr->data = malloc(10 * sizeof(int));
  arr->size = 10;
  arr->capacity = 10;
  for (int i = 0; i < arr->size; i++) {
    arr->data[i] = rand() % 100; // Fill with random numbers
  }
  printf("Original array: ");
  print_array(arr);
  sort(arr);
  printf("Sorted array: ");
  print_array(arr);
  int target1 = 35, target2 = 50;
  printf("Searching for %d using binary search:\n", target1);
  binary_search(arr->data, arr->size, target1);
  printf("Searching for %d using linear search:\n", target2);
  linear_search(arr->data, arr->size, target2);

  for (int i = 0; i < arr->size; i++) {
    arr->data[i] = i * 2;
  }
  printf("Array for interpolation search: ");
  print_array(arr);
  int target3 = 5, target4 = 8;
  printf("Searching for %d using interpolation search:\n", target3);
  interploation_search(arr, target3);
  printf("Searching for %d using interpolation search:\n", target4);
  interploation_search(arr, target4);
  return 0;
}

/**
 * @brief 斐波那契查找
 * 适用于有序数组，使用斐波那契查找算法查找目标值
 * 斐波那契查找通过使用斐波那契数列来定位目标值
 * 它的时间复杂度为 O(log n)，适用于大多数有序数组。
 * 该算法通过将数组分割成斐波那契数列的部分来减少查找次数。
 *
 * @param arr
 * @param target
 */
void fibonacci_search(LinearList *arr, int target) {
  if (arr == NULL || arr->size == 0) {
    printf("Array is empty.\n");
    return;
  }
  int fibM2 = 0;            // (m-2)'th Fibonacci number
  int fibM1 = 1;            // (m-1)'th Fibonacci number
  int fibM = fibM1 + fibM2; // m'th Fibonacci number
  while (fibM < arr->size) {
    fibM2 = fibM1;
    fibM1 = fibM;
    fibM = fibM1 + fibM2;
  }
  int offset = -1;
  while (fibM > 1) {
    int i = (offset + fibM2 < arr->size - 1) ? offset + fibM2 : arr->size - 1;
    if (arr->data[i] < target) {
      fibM = fibM1;
      fibM1 = fibM2;
      offset = i;
    } else if (arr->data[i] > target) {
      fibM = fibM2;
      fibM1 -= fibM2;
    } else {
      printf("Found %d at index %d\n", target, i);
      return;
    }
  }
  if (fibM1 && offset + 1 < arr->size && arr->data[offset + 1] == target) {
    printf("Found %d at index %d\n", target, offset + 1);
  } else {
    printf("%d not found in the array\n", target);
  }
}

/**
 * @brief 插值算法
 * 适用于有序数组，使用插值查找算法查找目标值
 * 插值查找比二分查找更高效，尤其是当数据分布较均匀时。
 * 它通过估计目标值在数组中的位置来减少查找次数。
 * 该算法的时间复杂度为 O(log log n)，但在数据分布不均匀时可能退化为 O(n)。
 * @param arr
 * @param target 查询目标值
 */
void interploation_search(LinearList *arr, int target) {
  if (arr == NULL || arr->size == 0) {
    printf("Array is empty.\n");
    return;
  }
  int low = 0, high = arr->size - 1;
  while (low <= high && target >= arr->data[low] && target <= arr->data[high]) {
    if (low == high) {
      if (arr->data[low] == target) {
        printf("Found %d at index %d\n", target, low);
      } else {
        printf("%d not found in the array\n", target);
      }
      return;
    }
    int pos = low + ((double)(high - low) / (arr->data[high] - arr->data[low]) *
                     (target - arr->data[low]));
    if (arr->data[pos] == target) {
      printf("Found %d at index %d\n", target, pos);
      return;
    }
    if (arr->data[pos] < target) {
      low = pos + 1;
    } else {
      high = pos - 1;
    }
  }
  printf("%d not found in the array\n", target);
}

/**
 * @brief 交换两个整数
 *
 * @param a
 * @param b
 */
void swap(int *a, int *b) {
  if (*a != *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
  }
}

/**
 * @brief 打印数组
 *
 * @param list
 */
void print_array(LinearList *list) {
  for (int i = 0; i < list->size; i++) {
    printf("%d ", list->data[i]);
  }
  printf("\n");
}

/**
 * @brief 排序数组
 *
 * @param list
 */
void sort(LinearList *list) {
  for (int i = 0; i < list->size - 1; i++) {
    for (int j = 0; j < list->size - i - 1; j++) {
      if (list->data[j] > list->data[j + 1]) {
        swap(&list->data[j], &list->data[j + 1]);
      }
    }
  }
}

/**
 * @brief 二分查找
 * 适用于有序数组，使用二分查找算法查找目标值
 * 二分查找的时间复杂度为 O(log n)，适用于大多数有序数组。
 * 它通过每次将搜索范围缩小一半来快速定位目标值。
 * @param arr
 * @param size 数组大小
 * @param target 查找目标值
 */
void binary_search(int *arr, int size, int target) {
  int left = 0, right = size - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      printf("Found %d at index %d\n", target, mid);
      return;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  printf("%d not found in the array\n", target);
}

/**
 * @brief 线性查找
 * 查找时间复杂度为 O(n)，适用于无序数组或小规模数据。
 * 线性查找通过遍历数组中的每个元素来查找目标值
 * 这种方法简单直接，但在大规模数据中效率较低。
 * @param arr
 * @param size 数组大小
 * @param target 查找目标值
 */
void linear_search(int *arr, int size, int target) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      printf("Found %d at index %d\n", target, i);
      return;
    }
  }
  printf("%d not found in the array\n", target);
}