#ifndef COMMONTYPES_HPP
#define COMMONTYPES_HPP

#include <cstdint>
#include <string>

namespace Graphs
{

using edge_weight_type = int16_t;

enum class EdgeDirection : uint8_t
{
    Directed,
    Undirected
};

struct Node
{
    using integral_type = uint32_t;
    integral_type id;

    explicit Node(integral_type _id);
    Node(Node const&) = default;
    Node(Node&&) = default;
    Node& operator=(Node const&) = default;
    Node& operator=(Node&&) = default;
    ~Node() = default;
};

bool operator==(Node const& lhs, Node const& rhs) noexcept;
bool operator!=(Node const& lhs, Node const& rhs) noexcept;

struct LabeledNode
{
    Node node;
    std::string label;

    LabeledNode(Node::integral_type _id, std::string const& _label);
    LabeledNode(Node _node, std::string const& _label);
    LabeledNode(LabeledNode const&) = default;
    LabeledNode(LabeledNode&&) = default;
    LabeledNode& operator=(LabeledNode const&) = default;
    LabeledNode& operator=(LabeledNode&&) = default;
    ~LabeledNode() = default;
};

bool operator==(LabeledNode const& lhs, LabeledNode const& rhs) noexcept;
bool operator!=(LabeledNode const& lhs, LabeledNode const& rhs) noexcept;

struct Edge
{
    Node const firstNode;
    Node const secondNode;
    edge_weight_type const weight;
    EdgeDirection const direction;

    Edge(Node first, Node second, edge_weight_type w, EdgeDirection d = EdgeDirection::Directed);
    Edge(Edge const&) = default;
    Edge(Edge&&) = default;
    Edge& operator=(Edge const&) = default;
    Edge& operator=(Edge&&) = default;
    ~Edge() = default;
};

bool operator==(Edge const& lhs, Edge const& rhs) noexcept;
bool operator!=(Edge const& lhs, Edge const& rhs) noexcept;

}

#endif // COMMONTYPES_HPP
