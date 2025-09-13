#include "core_api/array_utils.h"
#include "core_api/graph_utils.h"
#include "core_api/list_utils.h"
#include "core_api/search_utils.h"
#include "core_api/tree_utils.h"

int main() {
  // ---------------------------------------array list
  std::cout
      << "---------------------------- Linear List ----------------------------"
      << std::endl;
  std::vector<int> list{1, 2, 3, 4, 5};
  std::for_each(list.begin(), list.end(), [](int x) { std::cout << x << " "; });
  std::cout << std::endl;
  std::cout << "first element: " << list.front() << std::endl;
  std::cout << "last element: " << list.back() << std::endl;

  std::vector<int> sortList{7, 3, 31, 10, 2};
  // bubble_sort(sortList);
  // quick_sort(sortList, 0, sortList.size() - 1);
  // selection_sort(sortList);
  // heap_sort(sortList);
  // insertion_sort(sortList);
  // merge_sort(sortList, 0, sortList.size() - 1);
  // shell_sort(sortList);
  count_sort(list, *std::min_element(list.begin(), list.end()),
             *std::max_element(list.begin(), list.end()));
  // opt_bubble_sort(sortList);
  // radix_sort(sortList);
  printList(sortList);

  // -------------------------------------graph
  std::cout << "----------------------------------------- Adjacency List "
               "------------------------------------------\n";
  std::cout << "***************** invalid list input *****************\n";
  Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  // invalid input
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 2},  {{'A', 'D'}, 3},  {{'B', 'C'}, 4},
      {{'B', 'D'}, 5}, {{'B', 'E'}, 6},  {{'C', 'D'}, 7},  {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'E', 'G'}, 11}, {{'F', 'G'}, 12},
      {{'G', 'H'}, 13}};
  graph.initGraph(vertexList, edgeList);
  graph.printGraph(); // print empty graph with "#"

  std::cout << "***************** valid list input (Directed Graph #1) "
               "*****************\n";
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  std::cout << "Graph with " << vertexList.size() << " vertices and "
            << edgeList2.size() << " edges:" << std::endl;
  graph.printGraph();

  std::cout << "***************** valid list input (Directed Graph #2) "
               "************************\n";
  Graph graph2(6, 8);
  std::vector<VertexType> vertexList2{'A', 'B', 'C', 'D', 'E', 'F'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList3 = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 3}, {{'B', 'C'}, 4}, {{'B', 'D'}, 2},
      {{'C', 'D'}, 9}, {{'B', 'E'}, 5}, {{'C', 'F'}, 7}, {{'E', 'F'}, 8}};
  graph2.initGraph(vertexList2, edgeList3);
  graph2.DFS('A');
  graph2.DFS_recursive('A');
  graph2.BFS('A');
  graph2.printGraph();

  graph2.addVertex('I');
  graph2.addEdge('I', 'B', 2);
  graph2.addEdge('I', 'C', 3);
  graph2.deleteVertex('D');
  graph2.deleteEdge('B', 'C');
  std::cout << "After modifying the graph:" << std::endl;
  graph2.printGraph();

  std::cout << "********************* valid matrix input (Undirected Graph #3) "
               "*********************\n";
  Matrix matrix(false, false, 6, 8);
  std::vector<VertexType> vertexList3{'A', 'B', 'C', 'D', 'E', 'F'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList4 = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 3}, {{'A', 'D'}, 4}, {{'B', 'D'}, 2},
      {{'C', 'D'}, 9}, {{'B', 'E'}, 5}, {{'C', 'F'}, 7}, {{'E', 'F'}, 8}};
  matrix.initMatrix(vertexList3, edgeList4);
  std::cout << "Adjacency Matrix with " << vertexList3.size()
            << " vertices and " << edgeList4.size() << " edges:" << std::endl;
  matrix.printMatrix();

  std::cout << "Indegree of vertex B: " << matrix.indegree('B') << std::endl;
  std::cout << "Outdegree of vertex B: " << matrix.outdegree('B') << std::endl;
  std::cout << "Weight of edge (B, C):" << matrix.getEdgeWeight('B', 'C')
            << std::endl;
  std::cout << "Is vertex G in the graph? " << matrix.isVertex('G')
            << std::endl;
  std::cout << "Is edge (B, D) in the graph? " << matrix.isEdge('B', 'D')
            << std::endl;
  std::cout << "Is edge (C, F) in the graph? " << matrix.isEdge('C', 'F')
            << std::endl;
  std::cout << "Deep-First-Search (DFS) started from vertex B: ";
  matrix.DFS('B');
  matrix.connectedComponent();
  auto mstEdges_Kruskal = matrix.MinimumSpanningTreeKruskal();
  matrix.printMST(mstEdges_Kruskal);
  //   auto mstEdges_Prim = matrix.MinimumSpanningTreePrim();
  //   matrix.printMST(mstEdges_Prim);

  std::cout << "******************* valid matrix input (Directed Graph #4)"
               "*******************\n";
  Matrix matrix2(true, false, 6, 8);
  std::vector<VertexType> vertexList4{'A', 'B', 'C', 'D', 'E', 'F'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList5 = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 3}, {{'B', 'C'}, 4}, {{'B', 'D'}, 2},
      {{'C', 'D'}, 9}, {{'B', 'E'}, 5}, {{'C', 'F'}, 7}, {{'E', 'F'}, 8}};
  matrix2.initMatrix(vertexList4, edgeList5);
  std::cout << "Adjacency Matrix with " << vertexList4.size()
            << " vertices and " << edgeList5.size() << " edges:" << std::endl;
  matrix2.printMatrix();

  std::cout << "Indegree of vertex B: " << matrix2.indegree('B') << std::endl;
  std::cout << "Outdegree of vertex B: " << matrix2.outdegree('B') << std::endl;
  std::cout << "Weight of edge (B, C):" << matrix2.getEdgeWeight('B', 'C')
            << std::endl;
  std::cout << "Is vertex A in the graph? " << matrix2.isVertex('A')
            << std::endl;
  std::cout << "Is edge (B, C) in the graph? " << matrix2.isEdge('B', 'C')
            << std::endl;
  std::cout << "Is edge (C, F) in the graph? " << matrix2.isEdge('C', 'F')
            << std::endl;

  return 0;
}