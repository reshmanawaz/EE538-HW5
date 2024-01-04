#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

// //  private:
/**
//    * The set of nodes in the graph.
//    */
//   std::set<int> nodes_;

//   /**
//    * The set of edges in the graph.
//    */
//   std::set<std::pair<int, int>> edges_;

//   /**
//    * The map of edges to weights.
//    */
//   std::map<std::pair<int, int>, int> weights_;

//   /**
//    * Map of node to successors.
//    */
//   std::unordered_map<int, std::vector<int>> successors_;

//   /**
//    * Map of node to predecessors.
//    */
//   std::unordered_map<int, std::vector<int>> predecessors_;

// TODO: Implement the following functions.
//-----------------------------------------------------------------------------
/**
 * Populates the successors_ and predecessors_ using edges_.
 * It is already called in the constructor.
 */
void Graph::PopulateSuccessorsAndPredecessors()
{

  // clearing predecessors and successors
  predecessors_.clear();
  successors_.clear();

  // using edges begin and end, create pair type
  std::vector<std::pair<int, int>> pair(edges_.begin(), edges_.end());
  auto size = pair.size();

  for (int i = 0; i < size; i++)
  {
    int p = pair[i].first;
    int s = pair[i].second;

    predecessors_[s].push_back(p); // successor added to the predecessor list
    successors_[p].push_back(s);   // predecessor added to the successor list
  }
}
//-----------------------------------------------------------------------------
/**
 * Finds the shortest paths from the given start node to all other nodes in
 * the graph.
 * It also checks for negative cycles.
 *
 * @param start The start node.
 * @param distances A vector to store the distances from the start node to all
 * other nodes.
 * @return true if there was a negative cycle and false otherwise.
 */
bool Graph::FindShortestDistance(int start, std::vector<int> &distances)
{
  distances.clear();
  distances.resize(nodes_.size(), INT_MAX); //resize to the nodes 
  distances[start] = 0; //starting node is at 0 

  auto size = nodes_.size();
  //iterates through all the nodes 
  for(int i = 0; i < size - 1; ++i){
      for(auto& e : weights_){
          int u = e.first.first;
          int v = e.first.second;
          int w = e.second;
          if(distances[u] != INT_MAX && distances[u] + w < distances[v]){ //if the node has a finite distance + if distance is a shorter path 
              distances[v] = distances[u] + w;
          }
      }
  }
  //negative cycles
  for(auto& e : weights_){
    int u = e.first.first;
    int v = e.first.second;
    int w = e.second;
    
    if (distances[u] != INT_MAX && distances[u] + w < distances[v])
      {
          return true; // negative cycle has been found
      }
  }
  return false;
}

void Graph::BFS(int start, std::vector<int> &distances)
{
  distances.resize(nodes_.size(), INT_MAX);
  distances[start] = 0;

  // use queues
  std::queue<int> q;
  q.push(start);

  while (!q.empty())
  {
    auto front = q.front();
    q.pop();

    std::vector<int> s = successors_[front];
    auto size = s.size();
    for (size_t i = 0; i < size; i++)
    {
      auto x = s[i];
      if (distances[x] == INT_MAX)
      {
        q.push(x);
        distances[x] = distances[front] + 1; //onto the next 
      }
    }
  }
}

/**
 * Performs the Dijkstra algorithm on the graph and stores the distances from
 * the start node to all other nodes in the `distances` vector.
 *
 * @param start The start node.
 * @param distances A vector to store the distances from the start node to all
 * other nodes.
 */
void Graph::Dijkstra(int start, std::vector<int> &distances)
{
  distances.resize(nodes_.size(), INT_MAX);
  distances[start] = 0;

  // use queues: stores the pairs of integer 
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
  q.push({0, start});

  //run until queue is empty 
  while (!q.empty())
  {
    auto front = q.top().second;
    auto len = q.top().first;
    q.pop();

    // base case: if nodes = updated
    if (len != distances[front])
    {
      continue;
    }

    // process successor of the node
    if (successors_.find(front) != successors_.end())
    {
      for (auto &i : successors_[front])
      {
        int w = weights_[{front, i}]; // retriving weights
        if (distances[front] != INT_MAX && distances[front] + w < distances[i]) //if the node has a finite distance + if distance is a shorter path 
        {
          distances[i] = distances[front] + w; //distances[front] + w is the distance from the node
          q.push({distances[i], i}); //if calc distance is less than the known short distance, then update 
        }
      }
    }
  }
}

/**
 * Performs the Bellman-Ford algorithm on the graph and stores the distances
 * from the start node to all other nodes in the `distances` vector.
 * It also checks for negative cycles.
 *
 * @param start The start node.
 * @param distances A vector to store the distances from the start node to all
 * other nodes.
 * @return true if there was a negative cycle and false otherwise.
 */
bool Graph::BellmanFord(int start, std::vector<int> &distances)
{
  distances.resize(nodes_.size(), INT_MAX); //same size as the nodes 
  std::vector<bool> check(nodes_.size(), false); //same size as nodes + initizale to false 

  //check is node is within the range 
  if(start >= nodes_.size() || start < 0){
    return false; 
  }

  //distance from start node = 0 and true 
  distances[start] = 0; 
  check[start] = true; 

  std::vector<std::pair<std::pair<int, int>, int>> v(weights_.begin(), weights_.end());

  auto size = nodes_.size();
  auto size1 = v.size();
  //outer loop iterates over all nodes of the graph 
  for (int i = 0; i < size; i++)
  {
    //inner loop iterates over the edges 
    for (int j = 0; j < size1; j++)
    {
      auto e = v[j];
      //nodes pairs (u, v)
      int u = e.first.first; 
      int v = e.first.second;
      int w = e.second;
      if (distances[u] != INT_MAX && distances[u] + w < distances[v]) //if the node has a finite distance + if distance is a shorter path 
      { 
        distances[v] = distances[u] + w;
        check[v] = true; 
      }
    }
  }

  //unreachable nodes = int_max
  for(int i = 0; i < size; i++){
    if(!check[i]){
      distances[i] = INT_MAX;
    }
  }

  // negative cycles
  for (int i = 0; i < size1; i++)
  {
    auto e = v[i];
    int u = e.first.first;
    int v = e.first.second;
    int w = e.second;

    if (distances[u] != INT_MAX && distances[u] + w < distances[v]) //if the node has a finite distance + if distance is a shorter path 
    {
      return true; // negative cycle has been found
    }
  }
  return false;
}