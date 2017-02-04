#include "labeledgraph.h"
#include <stdexcept>
#include <algorithm>

namespace Graphs
{

LabeledGraph::LabeledGraph() : m_graph{}, m_labels{} { }

LabeledGraph::LabeledGraph(uint32_t size) : m_graph{size}, m_labels(size, "") { }

Graph const& LabeledGraph::getRawGraph() const noexcept
{
    return m_graph;
}

uint32_t LabeledGraph::getSize() const noexcept
{
    return m_graph.getSize();
}

void LabeledGraph::setLabel(Node::integral_type node, std::string const& label) noexcept
{
    m_labels[node] = label;
}

void LabeledGraph::setLabel(LabeledNode node, std::string&& label) noexcept
{
    m_labels[node.node.id] = std::move(label);
}

std::string const& LabeledGraph::getLabel(Node::integral_type node) const noexcept
{
    return m_labels[node];
}

std::string const& LabeledGraph::getLabel(LabeledNode const& node) const noexcept
{
    return m_labels[node.node.id];
}

bool LabeledGraph::contains(Node::integral_type node) const noexcept
{
    return m_graph.contains(node);
}

bool LabeledGraph::contains(LabeledNode const& node) const noexcept
{
    return contains(node.node.id);
}

Node::integral_type LabeledGraph::findNode(std::string const& label) const noexcept
{
    auto iter = std::find(m_labels.begin(), m_labels.end(), label);
    if (iter == m_labels.end())
    {
        throw std::invalid_argument("There is no such label in the graph");
    }
    return std::distance(m_labels.begin(), iter);
}

bool LabeledGraph::contains(std::string const& label) const noexcept
{
    try
    {
        (void)findNode(label);
        return true;
    }
    catch (std::invalid_argument&)
    {
        return false;
    }
}

bool LabeledGraph::areNodesConnected(Node::integral_type first, Node::integral_type second) const noexcept(false)
{
    return m_graph.areNodesConnected(first, second);
}

bool LabeledGraph::areNodesConnected(LabeledNode const& first, LabeledNode const& second) const noexcept(false)
{
    return areNodesConnected(first.node.id, second.node.id);
}

bool LabeledGraph::areNodesConnected(std::string const& first, std::string const& second) const noexcept(false)
{
    return m_graph.areNodesConnected(findNode(first), findNode(second));
}

Edge LabeledGraph::insertEdge(Node::integral_type src, Node::integral_type target, EdgeDirection direction) noexcept(false)
{
    return m_graph.insertEdge(src, target, direction);
}

Edge LabeledGraph::insertEdge(LabeledNode const& src, LabeledNode const& target, EdgeDirection direction) noexcept(false)
{
    return insertEdge(src.node.id, target.node.id, direction);
}

Edge LabeledGraph::insertEdge(const std::string& src, const std::string& target, EdgeDirection direction) noexcept(false)
{
    return insertEdge(findNode(src), findNode(target), direction);
}

Edge LabeledGraph::insertEdge(Node::integral_type src, Node::integral_type target, edge_weight_type weight, EdgeDirection direction) noexcept(false)
{
    return m_graph.insertEdge(src, target, weight, direction);
}

Edge LabeledGraph::insertEdge(LabeledNode const& src, LabeledNode const& target, edge_weight_type weight, EdgeDirection direction) noexcept(false)
{
    return insertEdge(src.node.id, target.node.id, weight, direction);
}

Edge LabeledGraph::insertEdge(std::string const& src, std::string const& target, edge_weight_type weight, EdgeDirection direction) noexcept(false)
{
    return insertEdge(findNode(src), findNode(target), weight, direction);
}

std::vector<LabeledNode> LabeledGraph::getConnectedNodes(Node::integral_type node) const noexcept(false)
{
    std::vector<Node> connectedNodes = m_graph.getConnectedNodes(node);
    std::vector<LabeledNode> ret;
    ret.reserve(connectedNodes.size());
    for (auto&& n : connectedNodes)
    {
        ret.push_back(LabeledNode{n, m_labels[n.id]});
    }
    return ret;
}

std::vector<LabeledNode> LabeledGraph::getConnectedNodes(LabeledNode const& node) const noexcept(false)
{
    return getConnectedNodes(node.node.id);
}

std::vector<LabeledNode> LabeledGraph::getConnectedNodes(std::string const& node) const noexcept(false)
{
    return getConnectedNodes(findNode(node));
}

LabeledNode const LabeledGraph::getNode(Node::integral_type node) const noexcept(false)
{
    Node n = m_graph.getNode(node);
    return LabeledNode{n, m_labels[n.id]};
}

LabeledNode const LabeledGraph::getNode(std::string const& node) const noexcept(false)
{
    return LabeledNode{findNode(node), node};
}

Edge const LabeledGraph::getEdge(Node::integral_type src, Node::integral_type target) const noexcept(false)
{
    return m_graph.getEdge(src, target);
}

Edge const LabeledGraph::getEdge(LabeledNode const& src, LabeledNode const& target) const noexcept(false)
{
    return getEdge(src.node.id, target.node.id);
}

Edge const LabeledGraph::getEdge(std::string const& src, std::string const& target) const noexcept(false)
{
    return getEdge(findNode(src), findNode(target));
}

edge_weight_type LabeledGraph::getEdgeWeight(Node::integral_type src, Node::integral_type target) const noexcept(false)
{
    return m_graph.getEdgeWeight(src, target);
}

edge_weight_type LabeledGraph::getEdgeWeight(LabeledNode const& src, LabeledNode const& target) const noexcept(false)
{
    return getEdgeWeight(src.node.id, target.node.id);
}

edge_weight_type LabeledGraph::getEdgeWeight(std::string const& src, std::string const& target) const noexcept(false)
{
    return getEdgeWeight(findNode(src), findNode(target));
}

std::string LabeledGraph::serialize() const
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setCodec("utf-16");

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("LabeledGraph");

    uint32_t nodesCount = getSize();
    xmlWriter.writeAttribute("size", QString::number(nodesCount));

    xmlWriter.writeStartElement("Nodes");
    for (uint32_t i = 0; i < nodesCount; ++i)
    {
        xmlWriter.writeStartElement("Node");
        xmlWriter.writeAttribute("id", QString::number(i));
        xmlWriter.writeAttribute("label", QString::fromStdString(m_labels[i]));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Edges");
    for (uint32_t i = 0; i < nodesCount; ++i)
    {
        for (auto&& connected : getConnectedNodes(i))
        {
            xmlWriter.writeStartElement("Edge");
            xmlWriter.writeAttribute("src", QString::number(i));
            xmlWriter.writeAttribute("sink", QString::number(connected.node.id));
            xmlWriter.writeAttribute("weight", QString::number(getEdgeWeight(i, connected.node.id)));
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    return xml.toStdString();
}

void LabeledGraph::fromXml(std::string const& xml)
{
    QXmlStreamReader xmlReader(QString::fromStdString(xml));

    xmlReader.readNext();
    while (!xmlReader.atEnd())
    {
        if (xmlReader.isStartElement())
        {
            if (xmlReader.name() == "LabeledGraph")
            {
                for (QXmlStreamAttribute const& attribute : xmlReader.attributes())
                {
                    if (attribute.name().toString() == "size")
                    {
                        uint32_t size = attribute.value().toUInt();
                        m_graph = Graph{size};
                        m_labels = std::vector<std::string>(size, "");
                    }
                }
                xmlReader.readNext();
            }
            else
            {
                while (!xmlReader.atEnd())
                {
                    if (xmlReader.isStartElement())
                    {
                        if (xmlReader.name() == "Node")
                        {
                            LabeledNode n{0, ""};
                            for (QXmlStreamAttribute const& attribute : xmlReader.attributes())
                            {
                                QString attrName = attribute.name().toString();
                                if (attrName == "id")
                                {
                                    n.node.id = attribute.value().toUInt();
                                }
                                else if (attrName == "label")
                                {
                                    n.label = attribute.value().toString().toStdString();
                                }
                            }
                            m_labels[n.node.id] = n.label;
                        }
                        else if (xmlReader.name() == "Edge")
                        {
                            Node src{0};
                            Node sink{0};
                            edge_weight_type weight = 0U;
                            for (QXmlStreamAttribute const& attribute : xmlReader.attributes())
                            {
                                QString attrName = attribute.name().toString();
                                if (attrName == "src")
                                {
                                    src.id = attribute.value().toUInt();
                                }
                                else if (attrName == "sink")
                                {
                                    sink.id = attribute.value().toUInt();
                                }
                                else if (attrName == "weight")
                                {
                                    weight = attribute.value().toUInt();
                                }
                            }
                            m_graph.insertEdge(src.id, sink.id, weight);
                        }
                        xmlReader.readNext();
                    }
                    else
                    {
                        xmlReader.readNext();
                    }
                }
            }
        }
        else
        {
            xmlReader.readNext();
        }
    }

    if (xmlReader.hasError())
    {
        throw std::runtime_error(xmlReader.errorString().toStdString());
    }
}

}
