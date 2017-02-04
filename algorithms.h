#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "commontypes.hpp"

namespace Graphs
{

// Forward declaration of Graph class
class Graph;
// Forward declaration of LabeledGraph class
class LabeledGraph;

namespace Algorithms
{

bool isConsistent(const Graph &graph) noexcept(false);
bool isConsistent(const LabeledGraph &graph) noexcept(false);

bool depthFirstSearch(Graph const& graph, Node const& root, Node const& target) noexcept(false);
bool depthFirstSearch(LabeledGraph const& graph, LabeledNode const& root, LabeledNode const& target) noexcept(false);
bool depthFirstSearch(LabeledGraph const& graph, std::string const& root, std::string const& target) noexcept(false);

bool breadthFirstSearch(Graph const& graph, Node const& root, Node const& target) noexcept(false);
bool breadthFirstSearch(LabeledGraph const& graph, LabeledNode const& root, LabeledNode const& target) noexcept(false);
bool breadthFirstSearch(LabeledGraph const& graph, std::string const& root, std::string const& target) noexcept(false);

int32_t findShortestPath(Graph const& graph, Node const& root, Node const& target) noexcept(false);
int32_t findShortestPath(LabeledGraph const& graph, LabeledNode const& root, LabeledNode const& target) noexcept(false);
int32_t findShortestPath(LabeledGraph const& graph, std::string const& root, std::string const& target) noexcept(false);

}

}

#endif // ALGORITHMS_H
