#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <map>
#include <stack>
#include <utility>
#include <vector>
// #include <linalg> c++26

// template <typename T1, typename T2>
// auto zip(const std::vector<T1> &v1, const std::vector<T2> &v2) {
//   std::vector<std::pair<T1, T2>> result;
//   result.reserve(std::min(v1.size(), v2.size()));
//   for (std::size_t i = 0; i < std::min(v1.size(), v2.size()); i++) {
//     result.emplace_back(v1[i], v2[i]);
//   }
//   return result;
// }

const char NULL_VERTEX = '#';
typedef char VertexType;
typedef int EdgeType;

namespace common_graph_utils {
struct Edge {
  int _src;
  int _dest;
  EdgeType _weight;
};

struct Matrix {
private:
  bool _isDirected;
  bool _compacted;
  unsigned int _numOfVertices;
  unsigned int _numOfEdges;
  unsigned int _connectedComponentNum; // 连通分量数
  std::vector<VertexType> _vertexList; // 也可以考虑set
  std::map<std::pair<VertexType, VertexType>, EdgeType>
      _edgeList; // 选择map只在表示边的唯一性时有用, 其他情况下可以用vector
  std::vector<std::vector<EdgeType>> _matrix;

public:
  Matrix(bool isDirected = false, bool compacted = false,
         unsigned int numOfVertices = 6, unsigned int numOfEdges = 8);
  ~Matrix();
  void
  initMatrix(std::vector<VertexType> &vertexList,
             std::map<std::pair<VertexType, VertexType>, EdgeType> &edgeList);
  void initEdge(const VertexType &src, const VertexType &dest,
                const EdgeType &weight);
  void initVertex(const std::vector<VertexType> &vertex);
  void printMatrix();
  void addVertex(const VertexType &vertex);
  void deleteVertex(const VertexType &vertex);
  void addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &weight);
  void deleteEdge(const VertexType &src, const VertexType &dest);
  void connectedComponent();
  // BFS有点过于简单,直接按序读行,故不实现
  void DFS(const VertexType &start);
  void unionSet(std::vector<int> &parent, int v1, int v2, bool check);
  void printMST(const std::pair<std::vector<Edge>, int> &mstEdges);
  bool isEdge(const VertexType &src, const VertexType &dest);
  bool isVertex(const VertexType &vertex);
  int find(std::vector<int> &parent, int vertexIdx);
  int position(const VertexType &vertex);
  int indegree(const VertexType &vertex);
  int degree(const VertexType &vertex);
  int outdegree(const VertexType &vertex);
  std::pair<std::vector<Edge>, int> MinimumSpanningTreePrim();
  std::pair<std::vector<Edge>, int> MinimumSpanningTreeBoruvka();
  std::pair<std::vector<Edge>, int> MinimumSpanningTreeKruskal();
  std::vector<VertexType> getAdjacentVertices(const VertexType &vertex);
  EdgeType getEdgeWeight(const VertexType &src, const VertexType &dest);
};
} // namespace common_graph_utils

namespace directed_graph_utils {
struct AdjListNode {
  VertexType _vertex;
  EdgeType _weight;
  AdjListNode *_next;
  AdjListNode(const VertexType &vertex, const EdgeType &weight);
};

struct VertexNode {
  VertexType _vertex;
  AdjListNode *_firstEdge;
};

struct Graph {
private:
  unsigned int _numOfVertices;
  unsigned int _numOfEdges;
  std::vector<VertexNode> _vertexList;
  std::map<std::pair<VertexType, VertexType>, EdgeType> _edgeList; // optional
  std::vector<bool> visited;
  std::vector<bool> recStack;
  std::vector<VertexType> path;
  std::vector<std::vector<VertexType>> cycles;

public:
  Graph(unsigned int numOfVertices = 8, unsigned int numOfEdges = 10);
  ~Graph();
  Graph transpose() const; // 逆邻接图
  int getConnectedComponentNum();
  int position(const VertexType &vertex);
  int indegree(const VertexType &vertex);
  int outdegree(const VertexType &vertex);
  int shortestPath(const VertexType &src, const VertexType &dest);
  std::vector<std::vector<VertexType>> Kosaraju_StronglyConnectedComponents();
  void initEdge(const VertexType &src, const VertexType &dest,
                const EdgeType &weight);
  void printGraph();
  void printCycle(const std::vector<VertexType> &cycle);
  void DFS_recursive_util(const VertexType &current,
                          std::vector<bool> &visited);
  void fillOrder(VertexType v, std::stack<VertexType> &stack);
  bool
  initGraph(std::vector<VertexType> &vertexList,
            std::map<std::pair<VertexType, VertexType>, EdgeType> &edgeList);
  bool addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &weight);
  bool addVertex(const VertexType &vertex);
  bool deleteEdge(const VertexType &src, const VertexType &dest);
  bool deleteVertex(const VertexType &vertex);
  bool DFS(const VertexType &start);
  bool DFS_recursive(const VertexType &start);
  bool BFS(const VertexType &start);
  bool isEdge(const VertexType &src, const VertexType &dest);
  bool isCyclicDFS(const VertexType &current);
  bool isVertex(const VertexType &vertex);
  bool is_cyclic();
  EdgeType getEdgeWeight(const VertexType &src, const VertexType &dest);
};
} // namespace directed_graph_utils
#endif // GRAPH_UTILS_H