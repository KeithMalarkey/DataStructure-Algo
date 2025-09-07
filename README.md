# Description

+ 数据结构(DS.)和算法(Algo.)三种实现方式:Cpp, C, Java
+ 📖主要内容:
  - Array, List, String, Tree, Graph;
  - Search & Sort;
  - 先后递归, 矩阵运算
  - 摊还分析, 动态规划, 贪心策略
  - 字符串匹配, 最短路径问题
  - NP完全性, 近似算法
+ 🚀适用: 
  - 考研党复习408的DS part
  - 工作党回顾Algo面试基础

# structure

<!-- todo: 增加更多内容 -->
```mermaid
graph LR
A[Data Structures] --> B[Array]
A --> C[List]
A --> D[String]
A --> E[Tree]
A --> F[Graph]
B --> G[Linear Array]
B --> H[Dynamic Array]
B --> I[Linear Stack]
B --> J[Linear Queue]
C --> K[Linked List]
C --> L[Doubly Linked List]
C --> M[Circular Linked List]
C --> d[Circular Doubly Linked List]
C --> c[Skip List]
C --> N[Stack]
C --> O[Queue]
D --> P[String]
D --> Q[Trie]
E --> R[Binary Tree]
E --> S[Binary Search Tree]
E --> T[AVL Tree]
E --> U[Red-Black Tree]
E --> V[B-Tree & B+Tree]
E --> a[Huffman Tree]
E --> b[Hash Tree]
E --> W[Trie]
F --> X[Graph]
F --> Y[Adjacency List]
F --> Z[Adjacency Matrix]
```

# environment

+ system: Arch Linux x86_64
+ compiler: g++/gcc 15.2.1, openjdk-24
+ cmake 4.1.1

# details
;) Stack和Queue的实现可以使用线性数组和链表,考虑到链表的易扩展性,故在本文中使用链表实现Stack和Queue.