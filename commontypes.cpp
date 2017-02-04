#include "commontypes.hpp"

namespace Graphs
{

Node::Node(uint32_t _id) : id{_id}
{
}

bool operator==(Node const& lhs, Node const& rhs) noexcept
{
    return (lhs.id == rhs.id);
}

bool operator!=(Node const& lhs, Node const& rhs) noexcept
{
    return !(operator==(lhs, rhs));
}

LabeledNode::LabeledNode(uint32_t _id, std::string const& _label) : node{_id}, label{_label}
{
}

LabeledNode::LabeledNode(Node _node, std::string const& _label) : node{_node}, label{_label}
{
}

bool operator==(LabeledNode const& lhs, LabeledNode const& rhs) noexcept
{
    return ((lhs.node == rhs.node) && (lhs.label == rhs.label));
}

bool operator!=(LabeledNode const& lhs, LabeledNode const& rhs) noexcept
{
    return !(operator==(lhs, rhs));
}

Edge::Edge(Node first, Node second, edge_weight_type w, EdgeDirection d) : firstNode{first}, secondNode{second},
                                                                           weight{w}, direction{d}
{
}

bool operator==(Edge const& lhs, Edge const& rhs) noexcept
{
    return ((lhs.firstNode == rhs.firstNode)
            && (lhs.secondNode == rhs.secondNode)
            && (lhs.weight == rhs.weight)
            && (lhs.direction == rhs.direction));
}

bool operator!=(Edge const& lhs, Edge const& rhs) noexcept
{
    return !(operator==(lhs, rhs));
}

}
