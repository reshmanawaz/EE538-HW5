#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

//PopulateSuccessorsAndPredecessors
TEST(q1, t1){
    std::set<int> n {1,2};
    std::set<std::pair<int, int>> e{std::make_pair(1,2)};
    Graph g(n,e);
    g.PopulateSuccessorsAndPredecessors();
    EXPECT_EQ(g.successors_[1], std::vector<int>{2});
    EXPECT_EQ(g.predecessors_[2], std::vector<int>{1});
}

//BFS
TEST(q1, t2){
    std::set<int> n = {0,1,2,3};
    std::set<std::pair<int, int>> e = {{0,1}, {0,2}, {1,3}, {2,3}};
    Graph g(n,e);

    std::vector<int> d; 
    g.BFS(0,d);
    EXPECT_EQ(d[0], 0);
    EXPECT_EQ(d[1], 1);
    EXPECT_EQ(d[2], 1);
    EXPECT_EQ(d[3], 2);
}

// //findshortestpath
TEST(q1, t3) {
    std::set<int> n = {0, 1, 2, 3}; // Nodes
    std::set<std::pair<int, int>> e = {{0, 1}, {0, 2}, {0, 3}}; // Edges
    std::map<std::pair<int, int>, int> w = {{{0, 1}, 1}, {{0, 2}, 1}, {{0, 3}, 1}}; // Weights
    Graph g(n, e, w); 
    std::vector<int> d;
    
    bool fsp = g.FindShortestDistance(0, d);
    
    EXPECT_FALSE(fsp);
    
    EXPECT_EQ(d[0], 0);
    EXPECT_EQ(d[1], 1);
    EXPECT_EQ(d[2], 1);
    EXPECT_EQ(d[3], 1);
}

//Bellman Ford 
TEST(q1, t4) {
    std::set<int> n = {0, 1, 2, 3}; // Nodes
    std::set<std::pair<int, int>> e = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}; // Edges
    std::map<std::pair<int, int>, int> w = {{{0, 1}, 1}, {{1, 2}, 3}, {{2, 3}, -4}, {{3, 0}, -2}}; // Weights
    Graph g(n, e, w); 
    std::vector<int> d;
    bool x = g.BellmanFord(0, d);
    EXPECT_EQ(x, true); 
}

//Dijkstra  
TEST(q1, t5) {
    std::set<int> n = {0, 1, 2, 3}; // Nodes
    std::set<std::pair<int, int>> e = {{0, 1}, {1, 2}, {2, 3}}; // Edges
    std::map<std::pair<int, int>, int> w = {{{0, 1}, 2}, {{1, 2}, 3}, {{2, 3}, 4}}; // Weights
    Graph g(n, e, w); 
    std::vector<int> d = {0, 2, 5, 9};
    std::vector<int> output; 
    g.Dijkstra(0, output);
    ASSERT_EQ(output.size(), d.size());
}

//disconnect graph 
TEST(q1, t6) {
    std::set<int> n = {0, 1, 2, 3, 4}; // Nodes
    std::set<std::pair<int, int>> e = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}; // Edges
    std::map<std::pair<int, int>, int> w = {{{0, 1}, 1}, {{1, 2}, 3}, {{2, 3}, -4}, {{3, 0}, -2}}; // Weights
    Graph g(n, e, w); 
    std::vector<int> d;
    bool x = g.BellmanFord(0, d);
    EXPECT_EQ(x, true); 
    EXPECT_EQ(d[4], INT_MAX);
}
