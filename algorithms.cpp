#include "algorithms.h"
#include "graph.h"
#include "labeledgraph.h"

#include <queue>
#include <stack>
#include <vector>

#include <stdexcept>
#include <limits>

namespace Graphs
{

namespace Algorithms
{

static bool isConsistentImpl(const Graph &graph) noexcept(false);
static bool depthFirstSearchImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false);
static bool breadthFirstSearchImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false);
static int32_t findShortestPathImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false);

bool isConsistent(const Graph &graph) noexcept(false)
{
    return isConsistentImpl(graph);
}

bool isConsistent(const LabeledGraph &graph) noexcept(false)
{
    return isConsistentImpl(graph.getRawGraph());
}

bool depthFirstSearch(const Graph &graph, const Node &root, const Node &target) noexcept(false)
{
    return depthFirstSearchImpl(graph, root, target);
}

bool depthFirstSearch(const LabeledGraph &graph, LabeledNode root, LabeledNode target) noexcept(false)
{
    return depthFirstSearchImpl(graph.getRawGraph(), root.node, target.node);
}

bool depthFirstSearch(const LabeledGraph &graph, const std::string &root, const std::string &target) noexcept(false)
{
    return depthFirstSearchImpl(graph.getRawGraph(), graph.getNode(root).node, graph.getNode(target).node);
}

bool breadthFirstSearch(const Graph &graph, const Node &root, const Node &target) noexcept(false)
{
    return breadthFirstSearchImpl(graph, root, target);
}

bool breadthFirstSearch(const LabeledGraph &graph, LabeledNode root, LabeledNode target) noexcept(false)
{
    return breadthFirstSearchImpl(graph.getRawGraph(), root.node, target.node);
}

bool breadthFirstSearch(const LabeledGraph &graph, const std::string &root, const std::string &target) noexcept(false)
{
    return breadthFirstSearchImpl(graph.getRawGraph(), graph.getNode(root).node, graph.getNode(target).node);
}

int32_t findShortestPath(const Graph &graph, const Node &root, const Node &target) noexcept(false)
{
    return findShortestPathImpl(graph, root, target);
}

int32_t findShortestPath(const LabeledGraph &graph, LabeledNode root, LabeledNode target) noexcept(false)
{
    return findShortestPathImpl(graph.getRawGraph(), root.node, target.node);
}

int32_t findShortestPath(const LabeledGraph &graph, const std::string &root, const std::string &target) noexcept(false)
{
    return findShortestPathImpl(graph.getRawGraph(), graph.getNode(root).node, graph.getNode(target).node);
}

// =====================================================
//                   IMPLEMENTATION
// =====================================================

bool isConsistentImpl(const Graph &graph) noexcept(false)
{
    if (graph.getSize() == 0)
    {
        throw std::invalid_argument("The graph has no nodes");
    }
    Node root{0};
    std::vector<uint8_t> visited(graph.getSize(), 0);
    std::queue<Node> nodesQueue;
    for (auto&& connected : graph.getConnectedNodes(root))
    {
        nodesQueue.push(connected);
    }
    visited[root.id] = 1;

    while (!nodesQueue.empty())
    {
        Node node = nodesQueue.front();
        nodesQueue.pop();
        for (auto&& connected : graph.getConnectedNodes(node))
        {
            if (visited[connected.id] == 0)
            {
                nodesQueue.push(connected);
            }
        }
        visited[node.id] = 1;
    }

    bool isConsistent = true;
    for (auto&& v : visited)
    {
        if (v == 0)
        {
            isConsistent = false;
            break;
        }
    }
    return isConsistent;
}

bool depthFirstSearchImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false)
{
    if (!graph.contains(root) || !graph.contains(target))
    {
        throw std::invalid_argument("Root or target node does not exist in the graph");
    }
    std::vector<uint8_t> visited(graph.getSize(), 0);
    visited[root.id] = 1;
    if (root == target)
    {
        return true;
    }

    std::stack<Node> nodesQueue;
    for (auto&& connected : graph.getConnectedNodes(root))
    {
        nodesQueue.push(connected);
    }

    bool found = false;
    while (!nodesQueue.empty())
    {
        Node node = nodesQueue.top();
        nodesQueue.pop();
        if (node == target)
        {
            found = true;
            break;
        }

        for (auto&& connected : graph.getConnectedNodes(node))
        {
            if (visited[connected.id] == 0)
            {
                nodesQueue.push(connected);
            }
        }
        visited[node.id] = 1;
    }
    return found;
}

bool breadthFirstSearchImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false)
{
    if (!graph.contains(root) || !graph.contains(target))
    {
        throw std::invalid_argument("Root or target node does not exist in the graph");
    }
    std::vector<uint8_t> visited(graph.getSize(), 0);
    visited[root.id] = 1;
    if (root == target)
    {
        return true;
    }

    std::queue<Node> nodesQueue;
    for (auto&& connected : graph.getConnectedNodes(root))
    {
        nodesQueue.push(connected);
    }

    bool found = false;
    while (!nodesQueue.empty())
    {
        Node node = nodesQueue.front();
        nodesQueue.pop();
        if (node == target)
        {
            found = true;
            break;
        }

        for (auto&& connected : graph.getConnectedNodes(node))
        {
            if (visited[connected.id] == 0)
            {
                nodesQueue.push(connected);
            }
        }
        visited[node.id] = 1;
    }
    return found;
}

int32_t findShortestPathImpl(const Graph &graph, Node const& root, Node const& target) noexcept(false)
{
    if (!graph.contains(root) || !graph.contains(target))
    {
        throw std::invalid_argument("Root or target node does not exist in the graph");
    }
    std::vector<uint8_t> visited(graph.getSize(), 0);
    std::vector<edge_weight_type> weights(graph.getSize(), std::numeric_limits<edge_weight_type>::max());
    weights[root.id] = 0;

    std::queue<Node> nodesQueue;
    for (auto&& connected : graph.getConnectedNodes(root))
    {
        weights[connected.id] = graph.getEdgeWeight(root, connected);
        nodesQueue.push(connected);
    }
    visited[root.id] = 1;

    while (!nodesQueue.empty())
    {
        Node node = nodesQueue.front();
        nodesQueue.pop();
        if (visited[node.id] == 0)
        {
            for (auto&& connected : graph.getConnectedNodes(node))
            {
                uint16_t updatedCapacity = weights[node.id] + graph.getEdgeWeight(node, connected);
                if (updatedCapacity < weights[connected.id])
                {
                    weights[connected.id] = updatedCapacity;
                    visited[connected.id] = 0;
                    nodesQueue.push(connected);
                }
            }
            visited[node.id] = 1;
        }
    }
    return weights[target.id];
}

}

}
