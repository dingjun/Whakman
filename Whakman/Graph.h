#pragma once

#include <unordered_map>

class Graph {
public:
  Graph();

  const std::vector<int>& get_neighbors(const int& node) { return _edges[node]; }

private:
  const unsigned char k_TILE_TYPE_NONE = 0b0000;

  void add_edge(const int& node1, const int& node2) {
    _edges[node1].push_back(node2);
    _edges[node2].push_back(node1);
  }

  std::unordered_map<int, std::vector<int>> _edges;
};
