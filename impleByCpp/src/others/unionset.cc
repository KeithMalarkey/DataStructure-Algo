// #include <iostream>
#include <vector>

class UnionFind {
private:
  std::vector<int> parent;
  std::vector<int> rank;
  int count; // 连通分量数量

public:
  UnionFind(int n) : parent(n), rank(n, 0), count(n) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  // 查找根节点（路径压缩）
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  // 合并两个集合
  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
      // 按秩合并
      if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else {
        parent[rootY] = rootX;
        rank[rootX]++;
      }
      count--; // 连通分量减少
    }
  }

  // 判断是否连通
  bool isConnected(int x, int y) { return find(x) == find(y); }

  // 获取连通分量数量
  int getCount() const { return count; }

  // 获取每个元素所在的集合代表
  std::vector<int> getSets() {
    std::vector<int> roots(parent.size());
    for (int i = 0; i < parent.size(); i++) {
      roots[i] = find(i);
    }
    return roots;
  }
};