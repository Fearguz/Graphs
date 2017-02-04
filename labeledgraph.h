#ifndef LABELEDGRAPH_H
#define LABELEDGRAPH_H

#include "graph.h"
#include "iserializable.h"

namespace Graphs
{

class LabeledGraph : public IXmlSerializable
{
private:
    Graph m_graph;
    std::vector<std::string> m_labels;

public:
    LabeledGraph();
    LabeledGraph(uint32_t size);
    LabeledGraph(LabeledGraph const&) = default;
    LabeledGraph(LabeledGraph&&) = default;
    LabeledGraph& operator=(LabeledGraph const&) = default;
    LabeledGraph& operator=(LabeledGraph&&) = default;
    ~LabeledGraph() = default;

    Graph const& getRawGraph() const noexcept;

    uint32_t getSize() const noexcept;

    void setLabel(Node::integral_type node, std::string const& label) noexcept;
    void setLabel(LabeledNode node, std::string&& label) noexcept;
    std::string const& getLabel(Node::integral_type node) const noexcept;
    std::string const& getLabel(LabeledNode const& node) const noexcept;

    bool contains(Node::integral_type node) const noexcept;
    bool contains(LabeledNode const& node) const noexcept;
    bool contains(std::string const& node) const noexcept;

    bool areNodesConnected(Node::integral_type first, Node::integral_type second) const noexcept(false);
    bool areNodesConnected(LabeledNode const& first, LabeledNode const& second) const noexcept(false);
    bool areNodesConnected(std::string const& first, std::string const& second) const noexcept(false);

    Edge insertEdge(Node::integral_type src, Node::integral_type target, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(LabeledNode const& src, LabeledNode const& target, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(std::string const& src, std::string const& target, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(Node::integral_type src, Node::integral_type target, edge_weight_type weight, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(LabeledNode const& src, LabeledNode const& target, edge_weight_type weight, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);
    Edge insertEdge(std::string const& src, std::string const& target, edge_weight_type weight, EdgeDirection direction = EdgeDirection::Undirected) noexcept(false);

    std::vector<LabeledNode> getConnectedNodes(Node::integral_type node) const noexcept(false);
    std::vector<LabeledNode> getConnectedNodes(LabeledNode const& node) const noexcept(false);
    std::vector<LabeledNode> getConnectedNodes(std::string const& node) const noexcept(false);

    LabeledNode const getNode(Node::integral_type node) const noexcept(false);
    LabeledNode const getNode(std::string const& node) const noexcept(false);

    Edge const getEdge(Node::integral_type src, Node::integral_type target) const noexcept(false);
    Edge const getEdge(LabeledNode const& src, LabeledNode const& target) const noexcept(false);
    Edge const getEdge(std::string const& src, std::string const& target) const noexcept(false);

    edge_weight_type getEdgeWeight(Node::integral_type src, Node::integral_type target) const noexcept(false);
    edge_weight_type getEdgeWeight(LabeledNode const& src, LabeledNode const& target) const noexcept(false);
    edge_weight_type getEdgeWeight(std::string const& src, std::string const& target) const noexcept(false);

    std::string serialize() const override;
    void fromXml(std::string const& xml) override;

private:
    uint32_t findNode(std::string const& label) const noexcept;
};

}

#endif // LABELEDGRAPH_H
