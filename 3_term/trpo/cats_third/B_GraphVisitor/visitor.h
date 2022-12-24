#pragma once
#include <iostream>
#include <unordered_map>

template <class Vertex>
class BfsVisitor {
 public:
  BfsVisitor() {
    Data dat = {.vertex_set = false};
    data = std::make_shared<Data>(dat);
  }

  void ExamineVertex(const Vertex &vertex) { data->cur_vertex = vertex; }

  void DiscoverVertex(const Vertex &vertex) {
    if (!data->vertex_set) {
      data->vertex_set = true;
      data->sparse_graph.insert({vertex, vertex});
      return;
    }

    data->sparse_graph.insert({vertex, data->cur_vertex});
  }

  size_t DistanceTo(const Vertex &target) const {
    size_t path = 0;
    for (Vertex i = target; i != data->sparse_graph.at(i);
         i = data->sparse_graph.at(i))
      path++;

    return path;
  }

  Vertex Parent(const Vertex &vertex) const {
    return data->sparse_graph.at(vertex);
  }

 private:
  struct Data {
    std::unordered_map<Vertex, Vertex> sparse_graph;
    Vertex cur_vertex;
    bool vertex_set;
  };

  std::shared_ptr<Data> data;
};