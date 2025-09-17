#include "core_api/graph_utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

// * 邻接表可以表示无向图和有向图,但由于无向图的邻接表表示占用较大的内存空间,因此在此仅使用邻接矩阵表示无向图
// * 同时,给出了有向图和无向图的邻接矩阵表示
using namespace common_graph_utils;
using namespace directed_graph_utils;

// --------------------- Graph Utils Implementation ------------------
/**
 * @brief probe whether a cycle exists in the graph using DFS.
 *
 * @param current
 * @return true has cycle
 * @return false no cycle
 */
bool Graph::isCyclicDFS(const VertexType &current) {
  int currentIdx = position(current);
  if (currentIdx == -1) {
    std::cout << "Vertex " << current << " is not in the graph." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // if current vertex is already in the recursion stack,
  // it means we find a cycle
  if (recStack[currentIdx]) {
    // find the start position of the cycle in the current path
    auto it = std::find(path.begin(), path.end(), current);
    if (it != path.end()) {
      std::vector<VertexType> cycle(it, path.end());
      cycle.push_back(current); // 闭合环
      cycles.push_back(cycle);
    }
    return true;
  }

  // if the vertex is already visited and not in the recursion stack
  if (visited[currentIdx]) {
    return false;
  }

  // tag the vertex as visited and push it into the recursion stack
  visited[currentIdx] = true;
  recStack[currentIdx] = true;
  path.push_back(current);

  bool hasCycle = false;

  // visit all neighbors of current vertex
  AdjListNode *neighbor = _vertexList[currentIdx]._firstEdge;
  while (neighbor != nullptr) {
    if (isCyclicDFS(neighbor->_vertex)) {
      hasCycle = true;
    }
    neighbor = neighbor->_next;
  }

  // remove the vertex from the recursion stack and path
  recStack[currentIdx] = false;
  path.pop_back();

  return hasCycle;
}

/**
 * @brief Construct a new Adj List Node.
 *
 * @param vertex
 * @param weight
 */
AdjListNode::AdjListNode(const VertexType &vertex, const EdgeType &weight)
    : _vertex(vertex), _weight(weight), _next(nullptr) {}

int Matrix::find(std::vector<int> &parent, int vertexIdx) {
  if (parent[vertexIdx] == vertexIdx) {
    return vertexIdx;
  }
  return find(parent, parent[vertexIdx]);
}

/**
 * @brief Union-Find algorithm for finding the root of a vertex.
 *
 * @param parent
 * @param vertex1
 * @param vertex2
 * @param check
 */
void Matrix::unionSet(std::vector<int> &parent, int vertex1, int vertex2,
                      bool check = false) {
  int rootX = find(parent, vertex1);
  int rootY = find(parent, vertex2);
  if (rootX != rootY) {
    parent[rootY] = rootX;
    if (check) {
      _connectedComponentNum--;
    }
  }
}
// ------------------- Matrix (for both directed and undirected graph)
/**
 * @brief 确定连通分量
 *
 * @return void
 */
void Matrix::connectedComponent() {
  auto cmp = [](const Edge &a, const Edge &b) { return a._weight < b._weight; };
  std::set<Edge, decltype(cmp)> edges;
  for (int i = 0; i < _numOfVertices; i++) {
    for (int j = 0; j < _numOfVertices; j++) {
      if (_matrix[i][j] > 0) {
        edges.insert({i, j, _matrix[i][j]});
      }
    }
  }

  std::vector<int> parent(_numOfVertices);
  for (int i = 0; i < _numOfVertices; i++) {
    parent[i] = i;
  }

  std::vector<Edge> mstEdges;
  int weight = 0;
  for (const auto &edge : edges) {
    int rootSrc = find(parent, edge._src);
    int rootDest = find(parent, edge._dest);
    if (rootSrc != rootDest) {
      // add the edge to the MST
      mstEdges.push_back(edge);
      weight += edge._weight;
      unionSet(parent, edge._src, edge._dest, true);
    }
  }
}

/**
 * @brief Minimum Spanning Tree (MST) using Kruskal's algorithm.
 * 最小生成树算法Krusaal,特点:
 *    - 只适用于边稀疏无向图(稀疏图)
 *    - 连通分量一定为1,否则为生成森林
 *    - 时间复杂度: O(E log E)
 *    - 最小生成树可能不唯一,原因: 边的权值相同,无法确定唯一的生成树
 * @note 必须先确定连通分量是1,否则无法确定唯一的生成树
 * @return std::pair<std::vector<Edge>, int>
 */
std::pair<std::vector<Edge>, int> Matrix::MinimumSpanningTreeKruskal() {
  assert(_connectedComponentNum == 1 &&
         "The graph must be connected for Kruskal's algorithm.");
  std::cout << "Minimum Spanning Tree (MST) using Kruskal's algorithm:"
            << std::endl;
  // 1. initialize edge weight set and sort it by weight
  auto cmp = [](const Edge &a, const Edge &b) { return a._weight < b._weight; };
  std::set<Edge, decltype(cmp)> edges;
  for (int i = 0; i < _numOfVertices; i++) {
    for (int j = 0; j < _numOfVertices; j++) {
      if (_matrix[i][j] > 0) {
        edges.insert({i, j, _matrix[i][j]});
      }
    }
  }

  // 2. initialize parent array for Union-Find algorithm
  std::vector<int> parent(_numOfVertices);
  for (int i = 0; i < _numOfVertices; i++) {
    parent[i] = i;
  }

  // 3. iterate over edges and add them to the MST if they do not form a cycle
  std::vector<Edge> mstEdges;
  int weight = 0;
  for (const auto &edge : edges) {
    int rootSrc = find(parent, edge._src);
    int rootDest = find(parent, edge._dest);
    if (rootSrc != rootDest) {
      // add the edge to the MST
      mstEdges.push_back(edge);
      weight += edge._weight;
      unionSet(parent, edge._src, edge._dest);
    }
  }
  return std::pair<std::vector<Edge>, int>(mstEdges, weight);
}

/**
 * @brief 打印最小生成树,可以是kru/prim/boruvka算法的输出
 *
 * @param mstEdges
 */
void Matrix::printMST(const std::pair<std::vector<Edge>, int> &mstEdges) {
  std::cout << "Edges in the MST:" << std::endl;
  for (const auto &edge : mstEdges.first) {
    std::cout << "(" << edge._src << ", " << edge._dest << ") - ["
              << _vertexList[edge._src] << " --- " << _vertexList[edge._dest]
              << "] - weight: " << edge._weight << std::endl;
  }

  std::cout << "Total weight: " << mstEdges.second << std::endl;
}

/**
 * @brief Construct a new Matrix (Constructor)
 *
 * @param isDirected 有向/无向?
 * @param compacted 压缩存储? 如果压缩存储则使用下三角矩阵,否则使用全矩阵
 * @param numOfVertices 顶点数
 * @param numOfEdges 边数
 */
Matrix::Matrix(bool isDirected, bool compacted, unsigned int numOfVertices,
               unsigned int numOfEdges)
    : _isDirected(isDirected), _compacted(compacted),
      _numOfVertices(numOfVertices), _numOfEdges(numOfEdges),
      _connectedComponentNum(numOfVertices) {
  _vertexList.resize(_numOfVertices, NULL_VERTEX);
  _matrix.resize(_numOfVertices, std::vector<EdgeType>(_numOfVertices, 0));
}

/**
 * @brief Destroy the Matrix (Destructor)
 *
 */
Matrix::~Matrix() {
  std::cout << "Adjacency Matrix is destroyed." << std::endl;
  _vertexList.clear();
  _matrix.clear();
}

void Matrix::initMatrix(
    std::vector<VertexType> &vertexList,
    std::map<std::pair<VertexType, VertexType>, EdgeType> &edgeList) {
  initVertex(vertexList);
  if (edgeList.size() != _numOfEdges) {
    std::cout << "Wrong number of edges in the input." << std::endl;
    return;
  }
  for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
    initEdge(it->first.first, it->first.second, it->second);
  }
  _edgeList = edgeList;
  std::cout << "Adjacency Matrix is initialized." << std::endl;
}

void Matrix::initEdge(const VertexType &src, const VertexType &dest,
                      const EdgeType &weight) {
  int srcIdx = position(src);
  int destIdx = position(dest);
  if (srcIdx == -1 || destIdx == -1) {
    std::cout << "No such vertex in the graph." << std::endl;
    return; // ensure both vertices are in the graph
  }
  if (_isDirected) {
    _matrix[srcIdx][destIdx] = weight;
  } else {
    if (_compacted) {
      srcIdx > destIdx ? _matrix[srcIdx][destIdx] = weight
                       : _matrix[destIdx][srcIdx] = weight;
    } else {
      _matrix[srcIdx][destIdx] = weight;
      _matrix[destIdx][srcIdx] = weight;
    }
  }
}

void Matrix::initVertex(const std::vector<VertexType> &vertexList) {
  if (vertexList.empty()) {
    return;
  }
  if (vertexList.size() != _numOfVertices) {
    std::cout << "Invalid input for initializing the graph." << std::endl;
    return;
  }
  _vertexList = vertexList;
}

/**
 * @brief position of the given vertex in the vertex list.
 *
 * @param vertex
 * @return int
 */
int Matrix::position(const VertexType &vertex) {
  auto it = std::find(_vertexList.begin(), _vertexList.end(), vertex);
  if (it != _vertexList.end()) {
    return std::distance(_vertexList.begin(), it);
  }
  return -1;
}

/**
 * @brief Check if the given edge is in the graph.
 *
 * @param src
 * @param dest
 * @return true
 * @return false
 */
bool Matrix::isEdge(const VertexType &src, const VertexType &dest) {
  if (!isVertex(src) || !isVertex(dest)) {
    return false;
  }
  return _isDirected ? _matrix[position(src)][position(dest)] != 0
                     : _matrix[position(src)][position(dest)] != 0 ||
                           _matrix[position(dest)][position(src)] != 0;
}

/**
 * @brief Check if the given vertex is in the graph.
 *
 * @param vertex
 * @return true
 * @return false
 */
bool Matrix::isVertex(const VertexType &vertex) {
  return position(vertex) != -1;
}

/**
 * @brief indegree of the given vertex.
 *
 * @param vertex
 * @return int
 */
int Matrix::indegree(const VertexType &vertex) {
  int idx = position(vertex);
  if (idx == -1) {
    return -1;
  }
  int count = 0;
  for (int i = 0; i < _numOfVertices; i++) {
    if (_matrix[i][idx] > 0) {
      count++;
    }
  }
  // compacted matrix for undirected graph
  if (_compacted) {
    for (int j = 0; j < _numOfVertices; j++) {
      if (_matrix[idx][j] > 0) {
        count++;
      }
    }
  }
  return count;
}

/**
 * @brief outdegree of the given vertex.
 *
 * @param vertex
 * @return int
 */
int Matrix::outdegree(const VertexType &vertex) {
  int idx = position(vertex);
  if (idx == -1) {
    return -1;
  }
  int count = 0;
  for (int i = 0; i < _numOfVertices; i++) {
    if (_matrix[idx][i] > 0) {
      count++;
    }
  }
  // compacted matrix for undirected graph
  if (_compacted) {
    for (int j = 0; j < _numOfVertices; j++) {
      if (_matrix[j][idx] > 0) {
        count++;
      }
    }
  }
  return count;
}

/**
 * @brief Get the degree of the given vertex.
 *
 * @param vertex
 * @return int
 */
int Matrix::degree(const VertexType &vertex) {
  return _isDirected ? indegree(vertex) + outdegree(vertex) : outdegree(vertex);
}

/**
 * @brief add a vertex to the graph.
 *
 * @param vertex
 */
void Matrix::addVertex(const VertexType &vertex) {
  if (isVertex(vertex)) {
    return; // vertex already in the graph
  }
  _vertexList.push_back(vertex);
  _matrix.push_back(std::vector<EdgeType>(_numOfVertices, 0));
  _numOfVertices++;
}

/**
 * @brief delete a vertex from the graph.
 *
 * @param vertex
 */
void Matrix::deleteVertex(const VertexType &vertex) {
  if (!isVertex(vertex)) {
    return; // vertex not in the graph
  }
  int idx = position(vertex);
  _vertexList.erase(_vertexList.begin() + idx);
  for (int i = 0; i < _numOfVertices; i++) {
    _matrix[i].erase(_matrix[i].begin() + idx);
  }
  _numOfVertices--;
}

/**
 * @brief init edge with the given weight.
 *
 * @param src
 * @param dest
 * @param weight
 */
void Matrix::addEdge(const VertexType &src, const VertexType &dest,
                     const EdgeType &weight) {
  int srcIdx = position(src);
  int destIdx = position(dest);
  if (srcIdx == -1 || destIdx == -1) {
    return; // ensure both vertices are in the graph
  }
  if (!isEdge(src, dest)) {
    if (_isDirected) {
      _matrix[srcIdx][destIdx] = weight;
    } else {
      if (_compacted) {
        srcIdx > destIdx ? _matrix[srcIdx][destIdx] = weight
                         : _matrix[destIdx][srcIdx] = weight;
      } else {
        _matrix[srcIdx][destIdx] = weight;
        _matrix[destIdx][srcIdx] = weight;
      }
    }
    _edgeList[std::make_pair(src, dest)] = weight;
    _numOfEdges++;
  }
}

/**
 * @brief delete an edge from the graph.
 *
 * @param src
 * @param dest
 */
void Matrix::deleteEdge(const VertexType &src, const VertexType &dest) {
  int srcIdx = position(src);
  int destIdx = position(dest);
  if (srcIdx == -1 || destIdx == -1) {
    return; // ensure both vertices are in the graph
  }
  if (isEdge(src, dest)) {
    if (_isDirected) {
      _matrix[srcIdx][destIdx] = 0;
    } else {
      _matrix[srcIdx][destIdx] = 0;
      _matrix[destIdx][srcIdx] = 0;
    }
    _edgeList.erase(std::make_pair(src, dest));
    _numOfEdges--;
  }
}

void Matrix::DFS(const VertexType &start) {
  assert(!_isDirected && "Just for undirected graph");
  int startIdx = position(start);
  if (startIdx == -1) {
    std::cout << "Vertex " << start << " is not in the graph." << std::endl;
    return;
  }

  std::stack<int> stack;
  std::vector<bool> visited(_numOfVertices, false);
  stack.push(startIdx);
  visited[startIdx] = true;
  std::cout << start << " -> ";

  while (!stack.empty()) {
    int currIdx = stack.top();
    stack.pop();

    for (int neighborIdx = 0; neighborIdx < _numOfVertices; neighborIdx++) {
      if (_matrix[currIdx][neighborIdx] != 0 && !visited[neighborIdx]) {
        visited[neighborIdx] = true;
        std::cout << _vertexList[neighborIdx] << " -> ";
        stack.push(neighborIdx);
      }
    }
  }
  std::cout << "null" << std::endl;
}

std::vector<VertexType> Matrix::getAdjacentVertices(const VertexType &vertex) {
  if (!isVertex(vertex)) {
    return std::vector<VertexType>();
  }
  std::vector<VertexType> adjVertices;
  int idx = position(vertex);
  for (int i = 0; i < _numOfVertices; i++) {
    if (_matrix[idx][i] > 0) {
      adjVertices.push_back(_vertexList[i]);
    }
  }
  return adjVertices;
}

/**
 * @brief get the weight of an edge in the graph.
 *
 * @param src source vertex
 * @param dest destination vertex
 * @return EdgeType weight of the edge
 */
EdgeType Matrix::getEdgeWeight(const VertexType &src, const VertexType &dest) {
  int srcIdx = position(src);
  int destIdx = position(dest);
  if (srcIdx == -1 || destIdx == -1) {
    return -1;
  }
  return _compacted ? _matrix[srcIdx][destIdx] + _matrix[destIdx][srcIdx]
                    : _matrix[srcIdx][destIdx];
}

/**
 * @brief print the adjacency matrix of the graph and its properties.
 *
 */
void Matrix::printMatrix() {
  std::cout << "Adjacency Matrix info:" << std::endl;
  std::cout << "\tVertices: " << _numOfVertices << std::endl;
  std::cout << "\tEdges: " << _numOfEdges << std::endl;
  std::cout << "\tDirected: " << _isDirected << std::endl;
  std::cout << "\tCompacted: " << _compacted << std::endl;
  std::cout << "Matrix:" << std::endl;
  std::cout << "  ";
  std::for_each(_vertexList.begin(), _vertexList.end(),
                [](VertexType v) { std::cout << v << " "; });

  std::cout << std::endl;
  for (int i = 0; i < _numOfVertices; i++) {
    std::cout << _vertexList[i] << " ";
    for (int j = 0; j < _numOfVertices; j++) {
      std::cout << _matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

// --------------------- Directed Graph ------------------
/**
 * @brief Construct a new Graph:: Graph object
 * note: adjcent list is implemented as a linked list, and vertex node is
 * initialized with NULL_VERTEX and null edge(i.e, no adjcent node).
 *
 * @param numOfVertices
 * @param numOfEdges
 */
Graph::Graph(unsigned int numOfVertices, unsigned int numOfEdges)
    : _numOfVertices(numOfVertices), _numOfEdges(numOfEdges) {
  _vertexList.resize(numOfVertices);
}

Graph::~Graph() {
  for (int i = 0; i < _numOfVertices; i++) {
    AdjListNode *curr = _vertexList[i]._firstEdge;
    while (curr != nullptr) {
      AdjListNode *next = curr->_next;
      delete curr;
      curr = next;
    }
  }
  _vertexList.clear();
  _edgeList.clear();
  std::cout << "Graph object implemented as a adjacency list is destroyed."
            << std::endl;
}

/**
 * @brief Initialize the graph with the given vertex list and edge list.
 *
 * @param vertexList
 * @param edgeList
 */
bool Graph::initGraph(
    std::vector<VertexType> &vertexList,
    std::map<std::pair<VertexType, VertexType>, EdgeType> &edgeList) {
  if (vertexList.empty() || edgeList.empty()) {
    std::cout << "empty input." << std::endl;
    return false;
  }
  if (vertexList.size() != _numOfVertices || edgeList.size() != _numOfEdges) {
    std::cout << "Invalid input." << std::endl;
    return false;
  }
  for (int i = 0; i < _numOfVertices; i++) {
    _vertexList[i]._vertex = vertexList[i];
    _vertexList[i]._firstEdge = nullptr;
  }
  for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
    initEdge(it->first.first, it->first.second, it->second);
  }
  // TODO:计算强连通分量
  std::cout << "Graph initialized successfully." << std::endl;
  return true;
}

/**
 * @brief Get the position of the given vertex in the vertex list according to
 * the vertex value.
 *
 * @param vertex
 * @return int
 */
int Graph::position(const VertexType &vertex) {
  for (int i = 0; i < _numOfVertices; i++) {
    if (_vertexList[i]._vertex == vertex) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Check if the given edge is in the graph.
 *
 * @param src
 * @param dest
 * @return true
 * @return false
 */
bool Graph::isEdge(const VertexType &src, const VertexType &dest) {
  if (!isVertex(src) || !isVertex(dest)) {
    return false;
  }
  /* 链表遍历效率太低,当然如果不想用edgeList的话,可以改成链表遍历(可选) */
  // int pos = position(src);
  // AdjListNode *curr = _vertexList[pos]._firstEdge;
  // while (curr != nullptr && curr->_vertex != dest) {
  //   curr = curr->_next;
  // }
  // return curr != nullptr;
  return _edgeList.find(std::make_pair(src, dest)) != _edgeList.end();
}

/**
 * @brief Check if the given vertex is in the graph.
 *
 * @param vertex
 * @return true in case vertex is in the graph, false otherwise.
 * @return false
 */
bool Graph::isVertex(const VertexType &vertex) {
  return position(vertex) != -1;
}

/**
 * @brief Initialize an edge with the given weight.
 *
 * @param src
 * @param dest
 * @param weight
 */
void Graph::initEdge(const VertexType &src, const VertexType &dest,
                     const EdgeType &weight) {
  if (!isVertex(src) || !isVertex(dest)) {
    return; // ensure both vertices are in the graph
  }
  AdjListNode *newEdge = new AdjListNode(dest, weight);
  int pos = position(src); // then get the position of src vertex
  if (_vertexList[pos]._firstEdge == nullptr) {
    _vertexList[pos]._firstEdge = newEdge;
  } else {
    // head insertion
    newEdge->_next = _vertexList[pos]._firstEdge;
    _vertexList[pos]._firstEdge = newEdge;
  }
  std::pair<VertexType, VertexType> edge(src, dest);
  _edgeList[edge] = weight;
}

/**
 * @brief add an new edge to the graph.
 *
 * @param src
 * @param dest
 * @param weight
 * @return true
 * @return false
 */
bool Graph::addEdge(const VertexType &src, const VertexType &dest,
                    const EdgeType &weight) {
  if (!isVertex(src) || !isVertex(dest)) {
    std::cout << "plz add vertex first." << std::endl;
    return false; // ensure both vertices are in the graph
  }
  if (!isEdge(src, dest)) {
    initEdge(src, dest, weight);
    _numOfEdges++;
    std::cout << "Edge (" << src << ", " << dest << "[" << weight
              << "]) added to the graph." << std::endl;
  } else {
    std::cout << "Edge (" << src << ", " << dest << "[" << weight
              << "]) already in the graph." << std::endl;
  }
  return true;
}

/**
 * @brief Add a new vertex to the graph.
 *
 * @param vertex
 * @return true
 * @return false
 */
bool Graph::addVertex(const VertexType &vertex) {
  if (isVertex(vertex)) {
    return false;
  }
  _vertexList.resize(_numOfVertices + 1);
  _vertexList[_numOfVertices]._vertex = vertex;
  _vertexList[_numOfVertices]._firstEdge = nullptr;
  _numOfVertices++;
  std::cout << "Vertex " << vertex << " added to the graph." << std::endl;
  return true;
}

/**
 * @brief Delete an edge from the graph.
 *
 * @param src
 * @param dest
 * @return true
 * @return false
 */
bool Graph::deleteEdge(const VertexType &src, const VertexType &dest) {
  if (!isEdge(src, dest)) {
    return false;
    ;
  }
  int pos = position(src);
  AdjListNode *prev = nullptr;
  AdjListNode *curr = _vertexList[pos]._firstEdge;
  while (curr != nullptr && curr->_vertex != dest) {
    prev = curr;
    curr = curr->_next;
  }
  if (prev == nullptr) {
    _vertexList[pos]._firstEdge = curr->_next;
  } else {
    prev->_next = curr->_next;
  }
  delete curr;
  curr = nullptr;
  _edgeList.erase(std::make_pair(src, dest));
  _numOfEdges--;
  return true;
}

/**
 * @brief Delete a vertex from the graph.
 *
 * @param vertex
 */
bool Graph::deleteVertex(const VertexType &vertex) {
  if (!isVertex(vertex)) {
    std::cout << "Vertex " << vertex << " not found!" << std::endl;
    return false;
  }

  int pos = position(vertex);
  if (pos == -1)
    return false;

  // 1. 删除所有指向该顶点的边
  for (int i = 0; i < _numOfVertices; i++) {
    if (i == pos)
      continue; // 跳过自己

    AdjListNode *curr = _vertexList[i]._firstEdge;
    AdjListNode *prev = nullptr;

    while (curr != nullptr) {
      if (curr->_vertex == vertex) {
        // 找到要删除的边
        if (prev == nullptr) {
          _vertexList[i]._firstEdge = curr->_next;
        } else {
          prev->_next = curr->_next;
        }

        AdjListNode *toDelete = curr;
        curr = curr->_next;
        _edgeList.erase(std::make_pair(_vertexList[i]._vertex, vertex));
        delete toDelete;
        _numOfEdges--;
      } else {
        prev = curr;
        curr = curr->_next;
      }
    }
  }

  // 2. 释放该顶点的出边链表
  AdjListNode *curr = _vertexList[pos]._firstEdge;
  while (curr != nullptr) {
    AdjListNode *next = curr->_next;
    _edgeList.erase(std::make_pair(vertex, curr->_vertex));
    delete curr;
    _numOfEdges--;
    curr = next;
  }
  _vertexList[pos]._firstEdge = nullptr;
  _vertexList.erase(_vertexList.begin() + pos);
  _numOfVertices--;
  std::cout << "Vertex " << vertex << " deleted from the graph." << std::endl;
  return true;
}

/**
 * @brief Get the weight of an edge in the graph.
 *
 * @param src source vertex
 * @param dest destination vertex
 * @return EdgeType weight of the edge
 */
EdgeType Graph::getEdgeWeight(const VertexType &src, const VertexType &dest) {
  if (!isEdge(src, dest)) {
    return -1;
  }
  // int pos = position(src);
  // AdjListNode *curr = _vertexList[pos]._firstEdge;
  // while (curr != nullptr && curr->_vertex != dest) {
  //   curr = curr->_next;
  // }
  // return curr->_weight;
  return _edgeList[std::make_pair(src, dest)];
}

/**
 * @brief Get the indegree of the given vertex.
 *
 * @param vertex
 * @return int
 */
int Graph::indegree(const VertexType &vertex) {
  int count = 0;
  for (int i = 0; i < _numOfVertices; i++) {
    AdjListNode *curr = _vertexList[i]._firstEdge;
    while (curr != nullptr && curr->_vertex != vertex) {
      curr = curr->_next;
    }
    if (curr != nullptr) {
      count++;
    }
  }
  return count;
}

/**
 * @brief Get the outdegree of the given vertex.
 *
 * @param vertex
 * @return int
 */
int Graph::outdegree(const VertexType &vertex) {
  int count = 0;
  int pos = position(vertex);
  AdjListNode *curr = _vertexList[pos]._firstEdge;
  while (curr != nullptr) {
    count++;
    curr = curr->_next;
  }
  return count;
}

/**
 * @brief Print the adjacency list of the graph and its properties.
 *
 */
void Graph::printGraph() {
  std::cout << "Graph info:" << std::endl;
  std::cout << "\tVertices: " << _numOfVertices << std::endl;
  std::cout << "\tEdges: " << _numOfEdges << std::endl;
  std::cout << "Adjacency List:" << std::endl;
  for (int i = 0; i < _numOfVertices; i++) {
    std::cout << _vertexList[i]._vertex << " -> ";
    AdjListNode *curr = _vertexList[i]._firstEdge;
    while (curr != nullptr) {
      std::cout << curr->_vertex << "(" << curr->_weight << ") ";
      curr = curr->_next;
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Print the cycle found in the graph.
 *
 * @param cycle
 */
void Graph::printCycle(const std::vector<VertexType> &cycle) {
  for (size_t i = 0; i < cycle.size(); i++) {
    std::cout << cycle[i];
    if (i < cycle.size() - 1) {
      std::cout << " → ";
    }
  }
  std::cout << std::endl;
}

/**
 * @brief Check if the graph has any cycle. output all cycles found.
 *
 * @return true if the graph has any cycle, false otherwise.
 */
bool Graph::is_cyclic() {
  // Mark all the vertices as not visited and not part of recursion stack
  visited.assign(_numOfVertices, false);
  recStack.assign(_numOfVertices, false);
  cycles.clear();
  path.clear();

  // check each unvisited vertex
  for (unsigned int i = 0; i < _numOfVertices; i++) {
    if (!visited[i] && _vertexList[i]._vertex != NULL_VERTEX) {
      if (isCyclicDFS(_vertexList[i]._vertex)) {
        // if a cycle is found, continue checking other connected
        // components
        continue;
      }
    }
  }

  // output all cycles found
  if (!cycles.empty()) {
    std::cout << "Found " << cycles.size()
              << " cycle(s) in the graph:" << std::endl;
    for (size_t i = 0; i < cycles.size(); i++) {
      std::cout << "Cycle " << i + 1 << ": ";
      printCycle(cycles[i]);
    }
    return true;
  } else {
    std::cout << "No cycles found in the graph." << std::endl;
    return false;
  }
}

/**
 * @brief Deep-First Search (Iterative)
 *
 * @param startVertex
 * @return true
 * @return false
 */
bool Graph::DFS(const VertexType &startVertex) {
  int startIdx = position(startVertex);
  if (startIdx == -1) {
    std::cout << "Start vertex not found!" << std::endl;
    return false;
  }

  // 初始化访问数组
  std::vector<bool> visited(_numOfVertices, false);
  std::stack<VertexType> stack;

  std::cout << "DFS traversal (iterative): ";

  stack.push(startVertex);
  visited[startIdx] = true;

  while (!stack.empty()) {
    VertexType current = stack.top();
    stack.pop();
    std::cout << current << " ";

    int currentIdx = position(current);
    if (currentIdx == -1)
      continue;

    // 将未访问的邻居逆序入栈（保证顺序）
    AdjListNode *neighbor = _vertexList[currentIdx]._firstEdge;
    std::vector<VertexType> neighbors;

    while (neighbor != nullptr) {
      int neighborIdx = position(neighbor->_vertex);
      if (neighborIdx != -1 && !visited[neighborIdx]) {
        neighbors.push_back(neighbor->_vertex);
      }
      neighbor = neighbor->_next;
    }

    // 逆序入栈以保证正序访问
    for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
      int idx = position(*it);
      if (idx != -1 && !visited[idx]) {
        visited[idx] = true;
        stack.push(*it);
      }
    }
  }
  std::cout << std::endl;
  return true;
}

/**
 * @brief Deep-First Search (Recursive)
 *
 * @param startVertex
 * @return true
 * @return false
 */
bool Graph::DFS_recursive(const VertexType &startVertex) {
  int startIdx = position(startVertex);
  if (startIdx == -1) {
    std::cout << "Start vertex not found!" << std::endl;
    return false;
  }

  std::vector<bool> visited(_numOfVertices, false);
  std::cout << "DFS traversal (recursive): ";
  DFS_recursive_util(startVertex, visited);
  std::cout << std::endl;
  return true;
}

/**
 * @brief DFS Recursive Utility Function
 *
 * @param current
 * @param visited
 */
void Graph::DFS_recursive_util(const VertexType &current,
                               std::vector<bool> &visited) {
  int currentIdx = position(current);
  if (currentIdx == -1 || visited[currentIdx]) {
    return;
  }

  visited[currentIdx] = true;
  // std::cout << current << " ";

  // 递归访问所有邻居
  AdjListNode *neighbor = _vertexList[currentIdx]._firstEdge;
  while (neighbor != nullptr) {
    DFS_recursive_util(neighbor->_vertex, visited);
    neighbor = neighbor->_next;
  }
}

/**
 * @brief Width-First Search (Breadth-First Search)
 *
 * @param startVertex
 */
bool Graph::BFS(const VertexType &startVertex) {
  int startIdx = position(startVertex);
  if (startIdx == -1) {
    std::cout << "Start vertex not found!" << std::endl;
    return false;
  }

  // 初始化访问数组
  std::vector<bool> visited(_numOfVertices, false);
  std::queue<VertexType> queue;

  std::cout << "BFS traversal: ";

  queue.push(startVertex);
  visited[startIdx] = true;

  while (!queue.empty()) {
    VertexType current = queue.front();
    queue.pop();
    std::cout << current << " ";

    int currentIdx = position(current);
    if (currentIdx == -1)
      continue;

    // let all unvisited neighbors of current vertex into the queue
    AdjListNode *neighbor = _vertexList[currentIdx]._firstEdge;
    while (neighbor != nullptr) {
      int neighborIdx = position(neighbor->_vertex);
      if (neighborIdx != -1 && !visited[neighborIdx]) {
        visited[neighborIdx] = true;
        queue.push(neighbor->_vertex);
      }
      neighbor = neighbor->_next;
    }
  }
  std::cout << std::endl;
  return true;
}

void Graph::fillOrder(VertexType v, std::stack<VertexType> &stack) {
  int vIdx = position(v);
  if (vIdx == -1)
    return;

  visited[vIdx] = true;

  AdjListNode *neighbor = _vertexList[vIdx]._firstEdge;
  while (neighbor != nullptr) {
    int neighborIdx = position(neighbor->_vertex);
    if (neighborIdx != -1 && !visited[neighborIdx]) {
      fillOrder(neighbor->_vertex, stack);
    }
    neighbor = neighbor->_next;
  }

  stack.push(v);
}

Graph Graph::transpose() const {
  std::vector<VertexType> reverseList;
  for (auto it : _vertexList) {
    reverseList.push_back(it._vertex);
  }
  std::map<std::pair<VertexType, VertexType>, EdgeType> reverseEdgeList;
  for (auto it = _edgeList.begin(); it != _edgeList.end(); ++it) {
    reverseEdgeList[std::make_pair(it->first.second, it->first.first)] =
        it->second;
  }
  Graph transposeGraph(_numOfVertices, _numOfEdges);
  transposeGraph.initGraph(reverseList, reverseEdgeList);
  return transposeGraph;
}

/**
 * @brief 强连通分量(Kosaraju算法)
 *
 * @return std::vector<std::vector<VertexType>>
 */
std::vector<std::vector<VertexType>>
Graph::Kosaraju_StronglyConnectedComponents() {
  visited.assign(_numOfVertices, false);
  std::stack<VertexType> stack;
  std::vector<std::vector<VertexType>> scc;
  // 1. DFS填充
  for (int i = 0; i < _numOfVertices; i++) {
    if (!visited[i]) {
      fillOrder(_vertexList[i]._vertex, stack);
    }
  }

  // 2.转制图
  Graph transposeGraph = transpose();

  // 3. 重置访问数组
  visited.assign(_numOfVertices, false);

  // 4. DFS遍历转制图
  while (!stack.empty()) {
    VertexType current = stack.top();
    stack.pop();
    int currentIdx = position(current);
    if (currentIdx == -1 && !visited[currentIdx]) {
      std::vector<VertexType> sccComponent;
      transposeGraph.DFS_recursive_util(current, visited);
      scc.push_back(sccComponent);
    }
  }
  return scc;
}

int Graph::getConnectedComponentNum() {
  return Kosaraju_StronglyConnectedComponents().size();
}

// TODO
// int shortestPath(const VertexType &src, const VertexType &dest) {}