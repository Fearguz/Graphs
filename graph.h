#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "commontypes.hpp"
#include "iserializable.h"

namespace Graphs
{

class Graph : public IXmlSerializable
{
private:
    std::vector<std::vector<edge_weight_type>> m_matrix;
    uint32_t m_nodesCount;
    static constexpr edge_weight_type noConnection = std::numeric_limits<edge_weight_type>::min();

public:
    Graph();
    Graph(uint32_t size);
    Graph(Graph const&) = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph const&) = default;
    Graph& operator=(Graph&&) = default;
    ~Graph() = default;

    uint32_t getSize() const noexcept;

    bool contains(Node::integral_type node) const noexcept;
    bool contains(Node const& node) const noexcept;

    bool areNodesConnected(Node::integral_type first, Node::integral_type second) const noexcept(false);
    bool areNodesConnected(Node const& first, Node const& second) const noexcept(false);

    Edge insertEdge(Node::integral_type src, Node::integral_type target, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(Node const& src, Node const& target, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(Node::integral_type src, Node::integral_type target, edge_weight_type weight, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(Node const& src, Node const& target, edge_weight_type weight, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);

    std::vector<Node> getConnectedNodes(Node::integral_type node) const noexcept(false);
    std::vector<Node> getConnectedNodes(Node const& node) const noexcept(false);

    Node const getNode(Node::integral_type node) const noexcept(false);

    Edge const getEdge(Node::integral_type src, Node::integral_type target) const noexcept(false);
    Edge const getEdge(Node const& src, Node const& target) const noexcept(false);

    edge_weight_type getEdgeWeight(Node::integral_type src, Node::integral_type target) const noexcept(false);
    edge_weight_type getEdgeWeight(Node const& src, Node const& target) const noexcept(false);

    std::string serialize() const override;
    void fromXml(std::string const& xml) override;
};

}

#endif // GRAPH_H
