#include "utils.h"

int main() {
  std::vector<int> nums = {1, 2, 3, 4, 5};
  int target = 3;
  int index = binarySearch(nums, target);
  if (index == -1) {
    std::cout << "Element not found in the array" << std::endl;
  } else {
    std::cout << "Element found at index " << index << std::endl;
  }
  return 0;
}

int linearSearch(const std::vector<int> &arr, const int &target) {
  int index = -1;
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == target) {
      index = i;
      break;
    }
  }
  return index;
}

int binarySearch(const std::vector<int> &arr, const int &target) {
  int left = 0, right = arr.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

int fibonacciSearch(const std::vector<int> &arr, const int &target) {
  int n = arr.size();
  int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm2 + fibMMm1;
  while (fibM < n) {
    fibMMm2 = fibMMm1;
    fibMMm1 = fibM;
    fibM = fibMMm2 + fibMMm1;
  }
  int offset = -1;
  while (fibM > 1) {
    int i = std::min(offset + fibMMm2, n - 1);
    if (arr[i] < target) {
      fibM = fibMMm1;
      fibMMm1 = fibMMm2;
      fibMMm2 = fibM - fibMMm1;
      offset = i;
    } else if (arr[i] > target) {
      fibM = fibMMm2;
      fibMMm1 = fibMMm1 - fibMMm2;
      fibMMm2 = fibM - fibMMm1;
    } else {
      return i;
    }
  }
  if (fibMMm1 and arr[offset + 1] == target) {
    return offset + 1;
  }
  return -1;
}

int interpolationSearch(const std::vector<int> &arr, const int &target) {
  int left = 0, right = arr.size() - 1;
  while (left <= right && arr[left] <= target && arr[right] >= target) {
    int pos =
        left + (target - arr[left]) * (right - left) / (arr[right] - arr[left]);
    if (arr[pos] == target) {
      return pos;
    } else if (arr[pos] < target) {
      left = pos + 1;
    } else {
      right = pos - 1;
    }
  }
  return -1;
}