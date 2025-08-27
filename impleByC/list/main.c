#include "linklist.h"
#include "utils.h"
#include <stdio.h>

// !在每个sort实现中,给出了相应的视频参考,以便对更好理解
// *先备知识:
// *时空复杂度
// *稳定排序
// *原地排序
// *循环不变式
// *分治->递归(先/后递归)
// todo跳表

int main() {
  LinearList list;
  list.data = NULL; // 假设数据指针未初始化
  list.size = 0;
  list.capacity = 0;

  // 测试 isEmpty
  if (isEmpty(&list)) {
    printf("List is empty.\n");
  } else {
    printf("List is not empty.\n");
  }

  // 测试 getSize
  printf("Size of list: %d\n", getSize(&list));

  // 测试 getCapacity
  printf("Capacity of list: %d\n", getCapacity(&list));

  // 测试 getFirst
  int first = getFirst(&list);
  if (first == -(1 << 10)) {
    printf("List is empty, no first element.\n");
  } else {
    printf("First element: %d\n", first);
  }

  // 测试 getLast
  int last = getLast(&list);
  if (last == -(1 << 10)) {
    printf("List is empty, no last element.\n");
  } else {
    printf("Last element: %d\n", last);
  }

  LinearList anotherList;
  anotherList.data = (int[]){1, 2, 3, 4, 5};
  anotherList.size = 5;
  anotherList.capacity = 10;

  for (int i = 0; i < anotherList.size; i++) {
    printf("Element %d: %d\n", i, anotherList.data[i]);
  }

  printf("First element of another list: %d\n", getFirst(&anotherList));
  printf("Last element of another list: %d\n", getLast(&anotherList));

  LinearList sortList;
  sortList.data = (int[]){7, 3, 31, 10, 2};
  sortList.size = 5;
  sortList.capacity = 10;

  // bubble_sort(&sortList);
  // quick_sort(&sortList, 0, sortList.size - 1);
  // selection_sort(&sortList);
  // heap_sort(&sortList);
  //   insertion_sort(&sortList);
  // merge_sort(&sortList, 0, sortList.size - 1);
  // shell_sort(&sortList);
  // count_sort(&sortList);
  // opt_bubble_sort(&sortList);
  radix_sort(&sortList);
  printList(&sortList);

  test_on_linklist();
  return 0;
}

// ------------------------------------- LinearList
// --------------------------------

/**
 * @brief 基数排序
 * 计数排序无法对负数排序,这里不给出负数的处理;
 * 一种解决方案是对所有数字+offset变为正值,排序后再减去offset
* feauture:
  * 1. 稳定排序
  * 2. 空间复杂度为 O(n + k)，其中 n 是元素个数，k 是基数（通常为
10,十进制故为 10）
  * 3. 时间复杂度为 O(d * (n + k))，其中 d 是数字的位数，n 是元素个数，k
是基数（通常为 10）
  * 4. 最坏时间复杂度为 O(d * (n + k))
  * 5. 最好时间复杂度为 O(d * (n + k))
  * 6. 平均时间复杂度为 O(d * (n + k))
 * ref:
 * https://www.bilibili.com/video/BV1KrzrYeEDw/?spm_id_from=333.1391.0.0&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void radix_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  // 检查是否有负数
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] < 0) {
      printf("Radix sort does not support negative numbers.\n");
      return;
    }
  }

  // 找到最大值
  int max = getMax(list);
  if (max == -(1 << 10)) {
    printf("List is empty, cannot perform radix sort.\n");
    return;
  }

  // 计算位数
  int exp;
  for (exp = 1; max / exp > 0; exp *= 10) {
    // 创建计数数组
    int count[10] = {0};
    int *output = (int *)malloc(list->size * sizeof(int));
    if (output == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }

    // 存储每个数字的计数
    for (int i = 0; i < list->size; i++) {
      count[(list->data[i] / exp) % 10]++;
    }

    // 累加计数
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }

    // 构建输出数组
    for (int i = list->size - 1; i >= 0; i--) {
      output[count[(list->data[i] / exp) % 10] - 1] = list->data[i];
      count[(list->data[i] / exp) % 10]--;
    }

    // 拷贝回原数组
    for (int i = 0; i < list->size; i++) {
      list->data[i] = output[i];
    }

    free(output);
  }

  printf("radix_sort result:\n");
}

/**
 * @brief 计数排序
 * 计数排序是一种非比较型排序算法，适用于整数范围较小的情况。
 * feature:
 * 1. 稳定排序
 * 2. 空间复杂度为 O(n + k)，其中 n 是元素个数，k 是最大值 - 最小值 + 1
 * 3. 平均时间复杂度为 O(n + k)
 * 4. 最坏时间复杂度为 O(n + k)
 * 5. 最好时间复杂度为 O(n + k)
 * ref:
 * https://www.bilibili.com/video/BV1sU4y1R7pm/?spm_id_from=333.1391.0.0&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void count_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  // 找到最大值和最小值
  int min = list->data[0], max = list->data[0];
  for (int i = 1; i < list->size; i++) {
    if (list->data[i] < min)
      min = list->data[i];
    if (list->data[i] > max)
      max = list->data[i];
  }

  int range = max - min + 1;
  int *count = (int *)calloc(range, sizeof(int));
  if (count == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  // 计数每个元素出现次数
  for (int i = 0; i < list->size; i++) {
    count[list->data[i] - min]++;
  }

  // 累加计数
  for (int i = 1; i < range; i++) {
    count[i] += count[i - 1];
  }

  // 输出排序结果到临时数组
  int *output = (int *)malloc(list->size * sizeof(int));
  if (output == NULL) {
    free(count);
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  for (int i = list->size - 1; i >= 0; i--) {
    output[--count[list->data[i] - min]] = list->data[i];
  }

  // 拷贝回原数组
  for (int i = 0; i < list->size; i++) {
    list->data[i] = output[i];
  }

  free(count);
  free(output);

  printf("count_sort result:\n");
}

/**
 * @brief 希尔排序
 * 希尔排序是一种基于插入排序的改进算法，通过分组来减少比较次数。
 * feature:
 * 1. 不稳定排序
 * 2. 原地排序
 * 3. 最坏时间复杂度为 O(n^2)
 * 4. 最好时间复杂度为 O(n log n)
 * 5. 平均时间复杂度为 O(n^(3/2))
 * ref:
 * https://www.bilibili.com/video/BV1bm42137UZ/?spm_id_from=333.1391.0.0&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void shell_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  printf("shell_sort result:\n");
  int gap, i, j, temp;
  // 增量折半递减
  for (gap = list->size / 2; gap > 0; gap /= 2) {
    // 对每个增量序列进行插入排序
    for (i = gap; i < list->size; i++) {
      temp = list->data[i];
      for (j = i; j >= gap && list->data[j - gap] > temp; j -= gap) {
        list->data[j] = list->data[j - gap];
      }
      list->data[j] = temp;
    }
  }
}

/**
 * @brief 多路合并操作
 *
 * @param list
 * @param left 左低位index
 * @param mid 中间位index
 * @param right 右高位index
 */
void merge(LinearList *list, int left, int mid, int right) {
  int i = left;    // 左子数组的起始索引
  int j = mid + 1; // 右子数组的起始索引
  int k = 0;       // 临时数组的索引

  int *temp = (int *)malloc((right - left + 1) * sizeof(int));
  if (temp == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  // 外部排序
  while (i <= mid && j <= right) {
    if (list->data[i] <= list->data[j]) {
      temp[k++] = list->data[i++];
    } else {
      temp[k++] = list->data[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = list->data[i++];
  }

  while (j <= right) {
    temp[k++] = list->data[j++];
  }

  // reload to the original list
  for (i = left, k = 0; i <= right; i++, k++) {
    list->data[i] = temp[k];
  }

  free(temp);
}

/**
 * @brief 合并排序
 * 归并排序是一种基于分治法的排序算法，时间复杂度为 O(n log n)。
 * feature:
 * 1. 稳定排序
 * 2. 空间复杂度为 O(n)
 * 3. 最坏时间复杂度为 O(n log n)
 * 4. 最好时间复杂度为 O(n log n)
 * 5. 平均时间复杂度为 O(n log n)
 * ref:
 * https://www.bilibili.com/video/BV1em1oYTEFf/?spm_id_from=333.1391.0.0&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 * @param left 左低位index
 * @param right 右高位index
 */
void merge_sort(LinearList *list, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // 递归排序左半部分
    merge_sort(list, left, mid);
    // 递归排序右半部分
    merge_sort(list, mid + 1, right);

    // 合并两个已排序的子数组
    merge(list, left, mid, right);
  }
}

// 获取线性表的第一个元素
int getFirst(const LinearList *list) {
  if (isEmpty(list)) {
    return -(1 << 10);
  }
  return list->data[0];
}

// 获取线性表的最后一个元素
int getLast(const LinearList *list) {
  if (isEmpty(list)) {
    return -(1 << 10);
  }
  return list->data[list->size - 1];
}

/**
 * @brief 置空
 *
 * @param list
 */
void freeList(LinearList *list) {
  if (list->data != NULL) {
    free(list->data);
    list->data = NULL;
  }
  list->size = 0;
  list->capacity = 0;
}

/**
 * @brief 冒泡排序
 * 冒泡排序是一种简单的排序算法，时间复杂度为 O(n^2)。
 * feature:
 * 1. 稳定排序
 * 2. 原地排序
 * 3. 最坏时间复杂度为 O(n^2)
 * 4. 最好时间复杂度为 O(n)
 * 5. 平均时间复杂度为 O(n^2)
 * ref:
 * https://www.bilibili.com/video/BV181421876R/?spm_id_from=333.1387.search.video_card.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void bubble_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  printf("bubble_sort result:\n");
  for (int i = 0; i < list->size - 1; i++) {
    for (int j = 0; j < list->size - i - 1; j++) {
      if (list->data[j] > list->data[j + 1]) {
        // 交换
        // int temp = list->data[j];
        // list->data[j] = list->data[j + 1];
        // list->data[j + 1] = temp;
        swap(&list->data[j], &list->data[j + 1]);
      }
    }
  }
}

/**
 * @brief 改进/优化冒泡排序
 * ref:
 * https://www.bilibili.com/video/BV181421876R/?spm_id_from=333.337.search-card.all.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void opt_bubble_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  printf("Optimized bubble_sort result:\n");
  int swapped;
  for (int i = 0; i < list->size - 1; i++) {
    swapped = 0; // 重置标志
    for (int j = 0; j < list->size - i - 1; j++) {
      if (list->data[j] > list->data[j + 1]) {
        // 交换
        swap(&list->data[j], &list->data[j + 1]);
        swapped = 1; // 标记有交换发生
      }
    }
    if (!swapped) {
      break; // 如果没有交换，说明已经排序好了
    }
  }
}

/**
 * @brief 选择排序
 * 选择排序是一种简单的排序算法，时间复杂度为 O(n^2)。
 * feature:
 * 1. 不稳定排序
 * 2. 原地排序
 * 3. 最坏时间复杂度为 O(n^2)
 * 4. 最好时间复杂度为 O(n^2)
 * 5. 平均时间复杂度为 O(n^2)
 * ref:
 * https://www.bilibili.com/video/BV1kjsuenE8v/?spm_id_from=333.1387.search.video_card.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void selection_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  printf("selection_sort result:\n");
  for (int i = 0; i < list->size - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < list->size; j++) {
      if (list->data[j] < list->data[minIndex]) {
        minIndex = j;
      }
    }
    // 交换
    if (minIndex != i) {
      // int temp = list->data[i];
      // list->data[i] = list->data[minIndex];
      // list->data[minIndex] = temp;
      swap(&list->data[i], &list->data[minIndex]);
    }
  }
}

/**
 * @brief 按pivot元素划分线性表
 *
 * @param list
 * @param low 左低位index
 * @param high 右高位index
 * @return int
 */
int partition(LinearList *list, int low, int high) {
  // robust
  if (isEmpty(list) || low < 0 || high >= list->size || low >= high) {
    return -(1 << 10); // 错误处理
  }

  int pivot = list->data[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (list->data[j] < pivot) {
      i++;
      // 交换
      // int temp = list->data[i];
      // list->data[i] = list->data[j];
      // list->data[j] = temp;
      swap(&list->data[i], &list->data[j]);
    }
  }
  // 交换 pivot
  // int temp = list->data[i + 1];
  // list->data[i + 1] = list->data[high];
  // list->data[high] = temp;
  swap(&list->data[i + 1], &list->data[high]);

  return i + 1;
}

/**
 * @brief 快速排序
 * 快速排序是一种基于分治法的排序算法，时间复杂度为 O(n log n)。
 * feature:
 * 1. 不稳定排序
 * 2. 空间复杂度为 O(log n)
 * 3. 最坏时间复杂度为 O(n^2)
 * 4. 最好时间复杂度为 O(n log n)
 * 5. 平均时间复杂度为 O(n log n)
 * ref:
 * https://www.bilibili.com/video/BV1y4421Z7hK/?spm_id_from=333.1387.search.video_card.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 * @param low 低位起始索引
 * @param high 高位结束索引
 */
void quick_sort(LinearList *list, int low, int high) {
  // robust
  if (isEmpty(list) || low < 0 || high >= list->size || low >= high) {
    return; // 错误处理
  }

  if (low < high) {
    int partitionIndex = partition(list, low, high);
    // 递归排序
    quick_sort(list, low, partitionIndex - 1);
    quick_sort(list, partitionIndex + 1, high);
  }
}

/**
 * @brief 插入排序
 * 插入排序是一种简单的排序算法，时间复杂度为 O(n^2)。
 * feature:
 * 1. 稳定排序
 * 2. 原地排序
 * 3. 最坏时间复杂度为 O(n^2)
 * 4. 最好时间复杂度为 O(n)
 * 5. 平均时间复杂度为 O(n^2)
 *
 * ref:
 * https://www.bilibili.com/video/BV1tf421Q7eh/?spm_id_from=333.1387.search.video_card.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void insertion_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  printf("insertion_sort result:\n");
  for (int i = 1; i < list->size; i++) {
    int key = list->data[i];
    int j = i - 1;

    // 将大于 key 的元素移动到后面
    while (j >= 0 && list->data[j] > key) {
      list->data[j + 1] = list->data[j];
      j--;
    }
    list->data[j + 1] = key;
  }
}

/**
 * @brief 大顶堆构建
 *
 * @param list
 * @param n 结点数
 * @param i index of root node
 */
void heapify(LinearList *list, int n, int i) {
  int largest = i;       // 初始化最大值为根节点
  int left = 2 * i + 1;  // 左子节点
  int right = 2 * i + 2; // 右子节点

  // 如果左子节点大于根节点
  if (left < n && list->data[left] > list->data[largest]) {
    largest = left;
  }

  // 如果右子节点大于当前最大值
  if (right < n && list->data[right] > list->data[largest]) {
    largest = right;
  }

  // 如果最大值不是根节点
  if (largest != i) {
    // int temp = list->data[i];
    // list->data[i] = list->data[largest];
    // list->data[largest] = temp;
    swap(&list->data[i], &list->data[largest]);

    // 递归调用 heapify
    heapify(list, n, largest);
  }
}

/**
 * @brief 堆排序
 * 堆排序是一种基于比较的排序算法，时间复杂度为 O(n log n)。
 * feature:
 * 1. 不稳定排序
 * 2. 原地排序
 * 3. 最坏时间复杂度为 O(n log n)
 * 4. 最好时间复杂度为 O(n log n)
 * 5. 平均时间复杂度为 O(n log n)
 * ref:
 * https://www.bilibili.com/video/BV1HYtseiEQ8/?spm_id_from=333.1387.search.video_card.click&vd_source=2df38eb18d0383a8d619977c0e144fd6
 * @param list
 */
void heap_sort(LinearList *list) {
  if (isEmpty(list)) {
    return;
  }

  // 构建最大堆
  for (int i = list->size / 2 - 1; i >= 0; i--) {
    heapify(list, list->size, i);
  }

  // 提取元素
  for (int i = list->size - 1; i > 0; i--) {
    // 交换
    // int temp = list->data[0];
    // list->data[0] = list->data[i];
    // list->data[i] = temp;
    swap(&list->data[0], &list->data[i]);

    heapify(list, i, 0);
  }
}

/**
 * @brief 线性表遍历
 *
 * @param list
 */
void printList(const LinearList *list) {
  if (isEmpty(list)) {
    printf("List is empty.\n");
    return;
  }
  for (int i = 0; i < list->size; i++) {
    printf("Element %d: %d\n", i, list->data[i]);
  }
}

/**
 * @brief 线性表初始化
 *
 * @param list 线性表
 * @param capacity 容量
 */
void initializeList(LinearList *list, int capacity) {
  list->data = (int *)malloc(capacity * sizeof(int));
  if (list->data == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  list->size = 0;
  list->capacity = capacity;
}

/**
 * @brief Get the Max val
 * for array
 * @param list
 * @return int
 */
int getMax(const LinearList *list) {
  if (isEmpty(list)) {
    return -(1 << 10); // 错误处理
  }

  int max = list->data[0];
  for (int i = 1; i < list->size; i++) {
    if (list->data[i] > max) {
      max = list->data[i];
    }
  }
  return max;
}

// ------------------------------------------ 链表
// ----------------------------------------

//----------------------------------------单链表---------------------------
void test_on_linklist() {
  LinkList *list = initList();
  printf("List is empty: %d\n", isEmptyList(list));
  int arr[] = {12, 23, 37, 46, 58};
  for (int i = 0; i < 5; i++) {
    LinkNode *node = create_node(&arr[i]);
    insertNode2head(list, node);
  }

  print_list(list);
  printf("List is empty: %d\n", isEmptyList(list));
  int app = 65;
  insertNode2tail(list, create_node(&app));
  print_list(list);
  printf("List size: %d\n", list->size);
  reverse_list(list);
  printf("List is after reverse:\n");
  print_list(list);

  deleteNode(list, 37);
  printf("after deleting 37,List size: %d\n", list->size);
  printf("after deleting 37,List is\n");
  print_list(list);

  Map *map = checkin_node(list);
  print_map(map);
  free_map(map);

  destroyList(list);
}

void print_list(LinkList *list) {
  int i = 0;
  for (LinkNode *node = list->head; node != NULL; node = node->next) {
    printf("Node %d data: %d\n", i++, node->data);
  }
}

bool isEmptyList(const LinkList *list) {
  return list->size == 0 || list == NULL;
}

/**
 * @brief Create a node in singly linked list
 *
 * @param data
 * @return LinkNode*
 */
LinkNode *create_node(NodeData *data) {
  if (!data) {
    return NULL;
  }

  LinkNode *node = malloc(sizeof(LinkNode));
  if (!node) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  node->data = *data;
  node->next = NULL;

  return node;
}

/**
 * @brief initilize a singly linked list
 *
 * @return LinkList*
 */
LinkList *initList() {
  LinkList *list = malloc(sizeof(LinkList));
  if (!list) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}

void create_list(int arr[]) {
  LinkList *list = initList();
  for (int i = 0; i < 5; i++) {
    LinkNode *node = create_node(&arr[i]);
    insertNode2tail(list, node);
  }
}

/**
 * @brief 注销单链表,释放单链表内存
 *
 * @param list
 */
void destroyList(LinkList *list) {
  if (!list) {
    return;
  }

  LinkNode *node = list->head;
  while (node) {
    LinkNode *tmp = node;
    node = node->next;
    free(tmp);
  }
  free(list);
}

/**
 * @brief 插入结点到头部
 *
 * @param list
 * @param node
 */
void insertNode2head(LinkList *list, LinkNode *node) {
  if (!list || !node) {
    return;
  }

  if (!list->head) {
    list->head = node;
    list->tail = node;
  } else {
    node->next = list->head;
    list->head = node;
  }
  list->size++;
}

/**
 * @brief 插入结点到尾部
 *
 * @param list
 * @param node
 */
void insertNode2tail(LinkList *list, LinkNode *node) {
  if (!list || !node) {
    return;
  }

  if (!list->tail) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  list->size++;
}

/**
 * @brief 按值删除结点
 *
 * @param list
 * @param data 待删除的结点数据
 */
void deleteNode(LinkList *list, NodeData data) {
  if (!list || !list->head) {
    return;
  }

  LinkNode *current = list->head;
  LinkNode *prev = NULL;
  LinkNode *temp = NULL;

  while (current) {
    if (current->data == data) {
      // 保存要删除的节点
      temp = current;

      // 删除结点
      if (prev) {
        prev->next = current->next;
      } else {
        list->head = current->next;
      }

      if (current == list->tail) {
        list->tail = prev;
      }

      // 移动到下一个节点
      current = current->next;

      // 释放内存
      free(temp);
      list->size--;
    } else {
      // 继续遍历
      prev = current;
      current = current->next;
    }
  }
}

/**
 * @brief 按位置删除结点
 *
 * @param list
 * @param position 0...size-1
 */
void _deleteNode(LinkList *list, int position) {
  if (isEmptyList(list)) {
    return;
  }
  if (position < 0 || position >= list->size) {
    return;
  }

  LinkNode *current = list->head;
  LinkNode *prev = NULL;
  int i = 0;
  while (current) {
    if (i == position) {
      // 保存要删除的节点
      LinkNode *temp = current;

      // 删除结点
      if (prev) {
        prev->next = current->next;
      } else {
        list->head = current->next;
      }

      if (current == list->tail) {
        list->tail = prev;
      }

      // 移动到下一个节点
      current = current->next;

      // 释放内存
      free(temp);
      list->size--;
      return;
    } else {
      // 继续遍历
      prev = current;
      current = current->next;
      i++;
    }
  }
}

/**
 * @brief map初始化
 *
 * @param map
 */
void map_init(Map *map) {
  map->entries = NULL;
  map->size = 0;
  map->capacity = 0;
}

/**
 * @brief map添加元素
 *
 * @param map
 * @param position
 * @param data
 * @return int
 */
int map_append(Map *map, int position, LinkNode *data) {
  // 检查是否需要扩容
  if (map->size >= map->capacity) {
    int new_capacity = (map->capacity == 0) ? 4 : map->capacity * 2;
    struct MapEntry *new_data = (struct MapEntry *)realloc(
        map->entries, new_capacity * sizeof(struct MapEntry));

    if (new_data == NULL) {
      return -1; // 内存分配失败
    }

    map->entries = new_data;
    map->capacity = new_capacity;
  }

  // 添加新元素
  map->entries[map->size].pos = position;
  map->entries[map->size].node = data;
  map->size++;

  return 0;
}

/**
 * @brief 释放map
 *
 * @param map
 */
void free_map(Map *map) {
  free(map->entries);
  map->entries = NULL;
  map->size = 0;
  map->capacity = 0;
}

/**
 * @brief 打印map
 *
 * @param map
 */
void print_map(Map *map) {
  printf("Found %d matches:\n", map->size);
  for (int i = 0; i < map->size; i++) {
    printf("  Position: %d, Data: %d\n", map->entries[i].pos,
           map->entries[i].node->data);
  }
}

/**
 * @brief 符合要求的结点加入Map
 *
 * @param list
 * @return Map*
 */
Map *checkin_node(LinkList *list) {
  Map *map = (Map *)malloc(sizeof(Map));
  map_init(map);
  LinkNode *current = list->head;
  int i = 0;
  while (current) {
    if (current->data % 2 == 0) { // 自由更改条件
      map_append(map, i, current);
    }
    current = current->next;
    i++;
  }

  return map;
}

/**
 * @brief 反转链表
 * 
 * @param list 
 */
void reverse_list(LinkList *list) {
  LinkNode *prev = NULL;
  LinkNode *current = list->head;
  LinkNode *next = NULL;

  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  list->head = prev;
}

// ---------------------------------- 双链表 -----------------------------

// --------------------------------------- 循环双链表
// ------------------------------