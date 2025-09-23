#include <iostream>
#include <memory>
#include <random>
#include <vector>

template <typename Key, typename Value> struct SkipListNode {
  Key key_;
  Value value_;
  std::vector<std::shared_ptr<SkipListNode>> forward_; // 多级指针

  SkipListNode(const Key &k, const Value &v, int level)
      : key_(k), value_(v), forward_(level, nullptr) {}
};

template <typename Key, typename Value> class SkipList {
private:
  std::shared_ptr<SkipListNode<Key, Value>> head_; // 唯一头节点
  int maxLevel_;                                   // 最大层数
  int currentLevel_;                               // 当前层数, 从1开始
  std::mt19937 rng_;                               // 随机数生成器
  std::uniform_real_distribution<double> dist_;    // 均匀分布

public:
  SkipList(int maxLevel = 16, double p = 0.5);
  ~SkipList() = default;

  // core apis
  bool search(const Key &key) const;
  void insert(const Key &key, const Value &value);
  bool remove(const Key &key);
  Value *get(const Key &key) const;

  // query utils
  Key minimum() const;
  Key maximum() const;
  std::vector<std::pair<Key, Value>> rangeQuery(const Key &start,
                                                const Key &end) const;

  // utils
  int size() const;
  bool empty() const;
  void clear();
  void display() const;

private:
  int randomLevel();
  std::vector<std::shared_ptr<SkipListNode<Key, Value>>>
  findPredecessors(const Key &key) const; // todo: 待实现
};

template <typename Key, typename Value>
SkipList<Key, Value>::SkipList(int maxLevel, double p)
    : maxLevel_(maxLevel), currentLevel_(1), dist_(0.0, 1.0) {

  // 初始化头节点（包含最小键）
  Key minKey = std::numeric_limits<Key>::min();
  head_ = std::make_shared<SkipListNode<Key, Value>>(minKey, Value(), maxLevel);

  // 初始化随机数生成器
  std::random_device rd;
  rng_ = std::mt19937(rd());
}

template <typename Key, typename Value>
int SkipList<Key, Value>::randomLevel() {
  int level = 1;
  while (dist_(rng_) < 0.5 && level < maxLevel_) {
    level++;
  }
  return level;
}

/**
 * @brief 依据Key查询目标结点
 *
 * @tparam Key Type of the key
 * @tparam Value Type of the value
 * @param key target key
 * @return true target key exists
 * @return false target key does not exist
 */
template <typename Key, typename Value>
bool SkipList<Key, Value>::search(const Key &key) const {
  auto current = head_;

  // 从最高层开始搜索
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr &&
           current->forward_[i]->key_ < key) {
      current = current->forward_[i];
    }
  }

  // 到达最底层，检查下一个节点
  current = current->forward_[0];
  return current != nullptr && current->key_ == key;
}

/**
 * @brief 返回键对应的值
 *
 * @tparam Key
 * @tparam Value
 * @param key 目标key值
 * @return Value*
 */
template <typename Key, typename Value>
Value *SkipList<Key, Value>::get(const Key &key) const {
  auto current = head_;

  // 找到底层节点的前驱
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr &&
           current->forward_[i]->key_ < key) {
      current = current->forward_[i];
    }
  }

  // 假定底层目标节点存在,并检查
  current = current->forward_[0];
  if (current != nullptr && current->key_ == key) {
    return &(current->value_);
  }
  return nullptr;
}

/**
 * @brief 依据Key插入值
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @param value 
 */
template <typename Key, typename Value>
void SkipList<Key, Value>::insert(const Key &key, const Value &value) {
  std::vector<std::shared_ptr<SkipListNode<Key, Value>>> update(maxLevel_,
                                                                nullptr);
  auto current = head_;

  // 找到每层需要更新的节点
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr &&
           current->forward_[i]->key_ < key) {
      current = current->forward_[i];
    }
    update[i] = current;
  }

  current = current->forward_[0];

  // 如果键已存在，更新值
  if (current != nullptr && current->key_ == key) {
    current->value_ = value;
    return;
  }

  // 创建新节点
  int newLevel = randomLevel();
  auto newNode =
      std::make_shared<SkipListNode<Key, Value>>(key, value, newLevel);

  // 更新层数
  if (newLevel > currentLevel_) {
    for (int i = currentLevel_; i < newLevel; i++) {
      update[i] = head_;
    }
    currentLevel_ = newLevel;
  }

  // 更新指针
  for (int i = 0; i < newLevel; i++) {
    newNode->forward_[i] = update[i]->forward_[i];
    update[i]->forward_[i] = newNode;
  }
}

/**
 * @brief 依据Key删除结点
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @return true 
 * @return false 
 */
template <typename Key, typename Value>
bool SkipList<Key, Value>::remove(const Key &key) {
  std::vector<std::shared_ptr<SkipListNode<Key, Value>>> update(maxLevel_,
                                                                nullptr);
  auto current = head_;

  // 找到每层需要更新的节点
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr &&
           current->forward_[i]->key_ < key) {
      current = current->forward_[i];
    }
    update[i] = current;
  }

  current = current->forward_[0];

  // 如果键不存在
  if (current == nullptr || current->key_ != key) {
    return false;
  }

  // 更新指针
  for (int i = 0; i < currentLevel_; i++) {
    if (update[i]->forward_[i] != current) {
      break;
    }
    update[i]->forward_[i] = current->forward_[i];
  }

  // 更新层数
  while (currentLevel_ > 1 && head_->forward_[currentLevel_ - 1] == nullptr) {
    currentLevel_--;
  }

  return true;
}

/**
 * @brief 获取跳表最小值
 *
 * @tparam Key
 * @tparam Value
 * @return Key
 */
template <typename Key, typename Value>
Key SkipList<Key, Value>::minimum() const {
  if (head_->forward_[0] == nullptr) {
    throw std::runtime_error("SkipList is empty");
  }
  return head_->forward_[0]->key_;
}

/**
 * @brief 获取跳表最大值
 *
 * @tparam Key
 * @tparam Value
 * @return Key
 */
template <typename Key, typename Value>
Key SkipList<Key, Value>::maximum() const {
  auto current = head_;
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr) {
      current = current->forward_[i];
    }
  }
  if (current == head_) {
    throw std::runtime_error("SkipList is empty");
  }
  return current->key_;
}

/**
 * @brief 依据Key值范围查询相应的键值对
 *
 * @tparam Key
 * @tparam Value
 * @param start
 * @param end
 * @return std::vector<std::pair<Key, Value>>
 */
template <typename Key, typename Value>
std::vector<std::pair<Key, Value>>
SkipList<Key, Value>::rangeQuery(const Key &start, const Key &end) const {
  std::vector<std::pair<Key, Value>> result;
  auto current = head_;

  // 找到起始位置
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    while (current->forward_[i] != nullptr &&
           current->forward_[i]->key_ < start) {
      current = current->forward_[i];
    }
  }

  current = current->forward_[0];

  // 收集范围内的所有键值对
  while (current != nullptr && current->key_ <= end) {
    result.emplace_back(current->key_, current->value_);
    current = current->forward_[0];
  }

  return result;
}

/**
 * @brief 跳表大小
 *
 * @tparam Key
 * @tparam Value
 * @return int
 */
template <typename Key, typename Value> int SkipList<Key, Value>::size() const {
  int count = 0;
  auto current = head_->forward_[0];
  while (current != nullptr) {
    count++;
    current = current->forward_[0];
  }
  return count;
}

/**
 * @brief 跳表判空
 *
 * @tparam Key
 * @tparam Value
 * @return true
 * @return false
 */
template <typename Key, typename Value>
bool SkipList<Key, Value>::empty() const {
  return head_->forward_[0] == nullptr;
}

/**
 * @brief 跳表清空
 *
 * @tparam Key
 * @tparam Value
 */
template <typename Key, typename Value> void SkipList<Key, Value>::clear() {
  for (int i = 0; i < maxLevel_; i++) {
    head_->forward_[i] = nullptr;
  }
  currentLevel_ = 1;
}

/**
 * @brief 打印SkipList
 *
 * @tparam Key
 * @tparam Value
 */
template <typename Key, typename Value>
void SkipList<Key, Value>::display() const {
  for (int i = currentLevel_ - 1; i >= 0; i--) {
    auto current = head_->forward_[i];
    std::cout << "Level " << i << ": ";
    while (current != nullptr) {
      std::cout << "{" << current->key_ << ", " << current->value_ << "} ";
      current = current->forward_[i];
    }
    std::cout << std::endl;
  }
}