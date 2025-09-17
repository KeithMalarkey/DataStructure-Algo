#include "core_api/array_utils.h"
#include <algorithm>
#include <iostream>

// !在每个sort实现中,给出了相应的视频参考,以便对更好理解
// *先备知识:
// *时空复杂度
// *稳定排序
// *原地排序
// *循环不变式
// *分治->递归(先/后递归)
namespace ArrayUtils {

/**
 * @brief 基数排序
 *
 * @param list
 */
void radix_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::for_each(list.begin(), list.end(), [](int &x) {
    if (x < 0) {
      std::cout << "Radix sort does not support negative numbers.\n";
      return;
    }
  });

  int max = *std::max_element(list.begin(), list.end());
  for (int exp = 1; max / exp > 0; exp *= 10) {
    std::vector<int> count(10, 0);
    std::vector<int> output(list.size());

    for (int i = 0; i < list.size(); ++i)
      count[(list[i] / exp) % 10]++;

    for (int i = 1; i < 10; ++i)
      count[i] += count[i - 1];

    for (int i = list.size() - 1; i >= 0; --i) {
      int idx = (list[i] / exp) % 10;
      output[--count[idx]] = list[i];
    }

    for (int i = 0; i < list.size(); ++i)
      list[i] = output[i];
  }

  std::cout << "radix_sort result:\n";
}

/**
 * @brief 计数排序
 *
 * @param arr
 * @param min_val 最小值
 * @param max_val 最大值
 */
void count_sort(std::vector<int> &arr, const int &min_val, const int &max_val) {
  if (arr.empty()) {
    return;
  }

  // 验证范围有效性
  if (min_val > max_val) {
    throw std::invalid_argument("min_val cannot be greater than max_val");
  }

  size_t n = arr.size();
  int range = max_val - min_val + 1;

  // 创建计数数组，初始化为0
  std::vector<int> count(range, 0);

  // 统计每个元素出现的次数
  for (size_t i = 0; i < n; i++) {
    if (arr[i] < min_val || arr[i] > max_val) {
      throw std::out_of_range("Element out of specified range");
    }
    count[arr[i] - min_val]++;
  }

  // 计算累积计数（确定元素的位置）
  for (int i = 1; i < range; i++) {
    count[i] += count[i - 1];
  }

  // 创建输出数组
  std::vector<int> output(n);

  // 从后往前遍历，保证稳定性
  for (int i = n - 1; i >= 0; i--) {
    output[count[arr[i] - min_val] - 1] = arr[i];
    count[arr[i] - min_val]--;
  }

  // 将排序结果复制回原数组
  arr = output;
}

/**
 * @brief 希尔排序
 *
 * @param list
 */
void shell_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::cout << "shell_sort result:\n";
  for (int gap = list.size() / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < list.size(); ++i) {
      int temp = list[i];
      int j = i;
      while (j >= gap && list[j - gap] > temp) {
        list[j] = list[j - gap];
        j -= gap;
      }
      list[j] = temp;
    }
  }
}

/**
 * @brief 多路合并
 *
 * @param list
 * @param left
 * @param mid
 * @param right
 */
void merge(std::vector<int> &list, const int &left, const int &mid,
           const int &right) {
  int i = left, j = mid + 1;
  std::vector<int> temp;

  while (i <= mid && j <= right) {
    if (list[i] <= list[j])
      temp.push_back(list[i++]);
    else
      temp.push_back(list[j++]);
  }
  while (i <= mid)
    temp.push_back(list[i++]);
  while (j <= right)
    temp.push_back(list[j++]);

  for (int k = 0; k < temp.size(); ++k)
    list[left + k] = temp[k];
}

/**
 * @brief 归并排序
 *
 * @param list
 * @param left
 * @param right
 */
void merge_sort(std::vector<int> &list, const int &left, const int &right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort(list, left, mid);
    merge_sort(list, mid + 1, right);
    merge(list, left, mid, right);
  }
}

/**
 * @brief 冒泡排序
 *
 * @param list
 */
void bubble_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::cout << "bubble_sort result: ";
  for (int i = 0; i < list.size() - 1; ++i) {
    for (int j = 0; j < list.size() - i - 1; ++j) {
      if (list[j] > list[j + 1])
        std::swap(list[j], list[j + 1]);
    }
  }
}

/**
 * @brief 优化的冒泡排序
 *
 * @param list
 */
void opt_bubble_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::cout << "Optimized bubble_sort result:\n";
  for (int i = 0; i < list.size() - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < list.size() - i - 1; ++j) {
      if (list[j] > list[j + 1]) {
        std::swap(list[j], list[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

/**
 * @brief 选择排序
 *
 * @param list
 */
void selection_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::cout << "selection_sort result: ";
  for (int i = 0; i < list.size() - 1; ++i) {
    int minIndex = i;
    for (int j = i + 1; j < list.size(); ++j)
      if (list[j] < list[minIndex])
        minIndex = j;
    if (minIndex != i)
      std::swap(list[i], list[minIndex]);
  }
}

/**
 * @brief 按pivot分区操作
 *
 * @param list
 * @param low
 * @param high
 * @return int
 */
int partition(std::vector<int> &list, const int &low, const int &high) {
  if (list.empty() || low < 0 || high >= list.size() || low >= high)
    return -(1 << 10);

  int pivot = list[high];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (list[j] < pivot) {
      ++i;
      std::swap(list[i], list[j]);
    }
  }
  std::swap(list[i + 1], list[high]);
  return i + 1;
}

/**
 * @brief 快速排序
 *
 * @param list
 * @param low
 * @param high
 */
void quick_sort(std::vector<int> &list, const int &low, const int &high) {
  if (list.empty() || low < 0 || high >= list.size() || low >= high)
    return;
  if (low < high) {
    int partitionIndex = partition(list, low, high);
    quick_sort(list, low, partitionIndex - 1);
    quick_sort(list, partitionIndex + 1, high);
  }
}

/**
 * @brief 插入排序
 *
 * @param list
 */
void insertion_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  std::cout << "insertion_sort result:\n";
  for (int i = 1; i < list.size(); ++i) {
    int key = list[i];
    int j = i - 1;
    while (j >= 0 && list[j] > key) {
      list[j + 1] = list[j];
      --j;
    }
    list[j + 1] = key;
  }
}

/**
 * @brief 构建最大堆/大顶堆
 *
 * @param list
 * @param n
 * @param i
 */
void heapify(std::vector<int> &list, const int &n, const int &i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && list[left] > list[largest])
    largest = left;
  if (right < n && list[right] > list[largest])
    largest = right;
  if (largest != i) {
    std::swap(list[i], list[largest]);
    heapify(list, n, largest);
  }
}

/**
 * @brief 堆排序
 *
 * @param list list
 */
void heap_sort(std::vector<int> &list) {
  if (list.empty())
    return;

  for (int i = list.size() / 2 - 1; i >= 0; --i)
    heapify(list, list.size(), i);
  for (int i = list.size() - 1; i > 0; --i) {
    std::swap(list[0], list[i]);
    heapify(list, i, 0);
  }
}

/**
 * @brief 打印线性表
 *
 * @param list
 */
void printList(const std::vector<int> &list) {
  if (list.empty()) {
    std::cout << "List is empty.\n";
    return;
  }
  std::for_each(list.begin(), list.end(), [](int x) { std::cout << x << " "; });
  std::cout << "\n";
}
} // namespace ArrayUtils