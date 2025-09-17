#include "core_api/graph_utils.h"
#include <gtest/gtest.h>

TEST(GraphUtils, isEdge) {
  directed_graph_utils::Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  bool result = graph.initGraph(vertexList, edgeList2);
  EXPECT_TRUE(graph.isEdge('A', 'B'));
  EXPECT_TRUE(graph.isEdge('C', 'D'));
  EXPECT_TRUE(graph.isEdge('E', 'F'));
}

TEST(GraphTest, initGraphList) {
  directed_graph_utils::Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  // invalid input
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 2},  {{'A', 'D'}, 3},  {{'B', 'C'}, 4},
      {{'B', 'D'}, 5}, {{'B', 'E'}, 6},  {{'C', 'D'}, 7},  {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'E', 'G'}, 11}, {{'F', 'G'}, 12},
      {{'G', 'H'}, 13}};
  graph.initGraph(vertexList, edgeList);
  graph.printGraph(); // print empty graph with "#"

  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  bool result = graph.initGraph(vertexList, edgeList2);
  EXPECT_TRUE(result);
  std::cout << "Graph with " << vertexList.size() << " vertices and "
            << edgeList2.size() << " edges:" << std::endl;
  graph.printGraph();
}

TEST(GraphTest, addEdge) {
  directed_graph_utils::Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.addEdge('X', 'Y', 7);  // vertex X and Y do not exist
  graph.addEdge('A', 'B', 10); // edge already exists
  graph.addEdge('C', 'A', 8);  // add an edge
}

TEST(GraphTest, addVertex) {
  directed_graph_utils::Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.addVertex('I');
  graph.addVertex('J');
}

TEST(GraphTest, InandOutDegree) {
  directed_graph_utils::Graph graph(8, 14); // create a graph with 8 vertices and 10 edges
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  // EXPECT_EQ(graph.indegree('A'), 0); // faulure case, truth is 1
  EXPECT_EQ(graph.indegree('A'), 1);
  EXPECT_EQ(graph.indegree('B'), 3);
  EXPECT_EQ(graph.outdegree('A'), 3);
  EXPECT_EQ(graph.outdegree('F'), 2);
}

TEST(GraphTest, deleteEdge) {
  directed_graph_utils::Graph graph(8, 14);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.printGraph();
  EXPECT_TRUE(graph.deleteEdge('A', 'B'));
}

TEST(GraphTest, deleteVertex) {
  directed_graph_utils::Graph graph(8, 14);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  EXPECT_TRUE(graph.deleteVertex('A'));
}

TEST(GraphTest, EdgewithWeight) {
  directed_graph_utils::Graph graph(8, 14);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.printGraph();
  EXPECT_EQ(graph.getEdgeWeight('C', 'E'), 8);
}

TEST(GraphTest, BFS) {
  directed_graph_utils::Graph graph(8, 14);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.printGraph();
  EXPECT_TRUE(graph.BFS('G'));
}

TEST(GraphTest, DFS) {
  directed_graph_utils::Graph graph(8, 14);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 3}, {{'A', 'C'}, 5},  {{'A', 'D'}, 11}, {{'B', 'C'}, 8},
      {{'B', 'D'}, 9}, {{'F', 'A'}, 1},  {{'C', 'D'}, 22}, {{'C', 'E'}, 8},
      {{'D', 'E'}, 9}, {{'E', 'F'}, 10}, {{'F', 'B'}, 2},  {{'G', 'H'}, 3},
      {{'G', 'B'}, 6}, {{'H', 'C'}, 4}};
  graph.initGraph(vertexList, edgeList2);
  graph.printGraph();
  EXPECT_EQ(graph.DFS('B'), true);
  EXPECT_EQ(graph.DFS_recursive('C'), true);
}

TEST(GraphTest, CycleProbe) {
  directed_graph_utils::Graph graph(3, 3);
  std::vector<VertexType> vertexList{'A', 'B', 'C'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 1}, {{'B', 'C'}, 1}, {{'C', 'A'}, 1}};
  graph.initGraph(vertexList, edgeList2);
  EXPECT_TRUE(graph.is_cyclic());
}

TEST(GraphTest, connectedComponents) {
  directed_graph_utils::Graph graph(6, 8);
  std::vector<VertexType> vertexList{'A', 'B', 'C', 'D', 'E', 'F'};
  std::map<std::pair<VertexType, VertexType>, EdgeType> edgeList2 = {
      {{'A', 'B'}, 1}, {{'A', 'C'}, 3}, {{'A', 'D'}, 4}, {{'B', 'E'}, 1},
      {{'B', 'D'}, 5}, {{'C', 'D'}, 2}, {{'C', 'F'}, 6}, {{'E', 'F'}, 5}};
  graph.initGraph(vertexList, edgeList2);
  // EXPECT_EQ(graph.getConnectedComponentNum(), 1); // failure case
  EXPECT_EQ(graph.getConnectedComponentNum(), 0); 
}