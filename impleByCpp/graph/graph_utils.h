#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <map>
#include <vector>
// #include <linalg> c++26

const char NULL_VERTEX = '#';
typedef char VertexType;
typedef int EdgeType;

// --------- Matrix (for both directed and undirected graph)----------
struct Matrix {
private:
  bool _isDirected;
  bool _compacted;
  unsigned int _numOfVertices;
  unsigned int _numOfEdges;
  std::vector<VertexType> _vertexList;
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
  bool isEdge(const VertexType &src, const VertexType &dest);
  bool isVertex(const VertexType &vertex);
  int position(const VertexType &vertex);
  int indegree(const VertexType &vertex);
  int degree(const VertexType &vertex);
  int outdegree(const VertexType &vertex);
  EdgeType getEdgeWeight(const VertexType &src, const VertexType &dest);
};

// --------- Directed Graph ---------
// Adjacency List
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
  // VertexNode *_vertexList;
  std::vector<VertexNode> _vertexList;

  std::vector<bool> visited;
  std::vector<bool> recStack;
  std::vector<VertexType> path;
  std::vector<std::vector<VertexType>> cycles;

public:
  Graph(unsigned int numOfVertices = 8, unsigned int numOfEdges = 10);
  ~Graph();
  int position(const VertexType &vertex);
  int indegree(const VertexType &vertex);
  int outdegree(const VertexType &vertex);
  void
  initGraph(std::vector<VertexType> &vertexList,
            std::map<std::pair<VertexType, VertexType>, EdgeType> &edgeList);
  void initEdge(const VertexType &src, const VertexType &dest,
                const EdgeType &weight);
  void addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &weight);
  void addVertex(const VertexType &vertex);
  void deleteEdge(const VertexType &src, const VertexType &dest);
  void deleteVertex(const VertexType &vertex);
  bool isEdge(const VertexType &src, const VertexType &dest);
  bool isVertex(const VertexType &vertex);
  void printGraph();
  void printCycle(const std::vector<VertexType> &cycle);
  void DFS(const VertexType &start);
  void DFS_recursive(const VertexType &start);
  void DFS_recursive_util(const VertexType &current,
                          std::vector<bool> &visited);
  void BFS(const VertexType &start);
  bool isCyclicDFS(const VertexType &current);
  bool is_cyclic();
  EdgeType getEdgeWeight(const VertexType &src, const VertexType &dest);
};

// --------- Undirected Graph ---------

#endif // GRAPH_UTILS_H