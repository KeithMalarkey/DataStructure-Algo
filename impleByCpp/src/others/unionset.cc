#include <iostream>
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

// int main() {
//   UnionFind uf(10); // 10个元素

//   std::cout << "初始连通分量: " << uf.getCount() << std::endl;

//   // 合并操作
//   uf.unionSet(0, 1);
//   uf.unionSet(2, 3);
//   uf.unionSet(4, 5);
//   uf.unionSet(1, 2); // 连接两个集合

//   std::cout << "合并后连通分量: " << uf.getCount() << std::endl;

//   // 查询操作
//   std::cout << "0和3是否连通: " << uf.isConnected(0, 3) << std::endl; // true
//   std::cout << "0和4是否连通: " << uf.isConnected(0, 4) << std::endl; // false

//   return 0;
// }