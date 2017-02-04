#include "graph.h"
#include <stdexcept>

namespace Graphs
{

constexpr edge_weight_type Graph::noConnection;

Graph::Graph() : m_matrix(), m_nodesCount(0) { }

Graph::Graph(uint32_t size) : m_matrix(size, std::vector<edge_weight_type>(size, noConnection)), m_nodesCount(size) { }

uint32_t Graph::getSize() const noexcept
{
    return m_nodesCount;
}

bool Graph::contains(Node::integral_type node) const noexcept
{
    return (node < m_nodesCount);
}

bool Graph::contains(Node const& node) const noexcept
{
    return contains(node.id);
}

bool Graph::areNodesConnected(Node::integral_type first, Node::integral_type second) const noexcept(false)
{
    if (!contains(first) || !contains(second))
    {
        throw std::invalid_argument("Could not check connection between non-existing nodes");
    }
    return (m_matrix[first][second] != noConnection);
}

bool Graph::areNodesConnected(Node const& first, Node const& second) const noexcept(false)
{
    return (areNodesConnected(first.id, second.id));
}

Edge Graph::insertEdge(Node::integral_type src, Node::integral_type target, EdgeDirection direction) noexcept(false)
{
    if (!contains(src) || !contains(target))
    {
        throw std::invalid_argument("Could not insert an edge between non-existing nodes");
    }

    m_matrix[src][target] = 0;
    if (direction == EdgeDirection::Undirected)
    {
        m_matrix[target][src] = 0;
    }
    return Edge{Node{src}, Node{target}, 0, direction};
}

Edge Graph::insertEdge(Node const& src, Node const& target, EdgeDirection direction) noexcept(false)
{
    return insertEdge(src.id, target.id, direction);
}

Edge Graph::insertEdge(Node::integral_type src, Node::integral_type target, edge_weight_type weight, EdgeDirection direction) noexcept(false)
{
    if (!contains(src) || !contains(target))
    {
        throw std::invalid_argument("Could not insert an edge between non-existing nodes");
    }

    m_matrix[src][target] = weight;
    if (direction == EdgeDirection::Undirected)
    {
        m_matrix[target][src] = weight;
    }
    return Edge{Node{src}, Node{target}, weight, direction};
}

Edge Graph::insertEdge(Node const& src, Node const& target, edge_weight_type weight, EdgeDirection direction) noexcept(false)
{
    return insertEdge(src.id, target.id, weight, direction);
}

std::vector<Node> Graph::getConnectedNodes(Node::integral_type node) const noexcept(false)
{
    if (!contains(node))
    {
        throw std::invalid_argument("Node does not exist");
    }

    std::vector<Node> ret;
    ret.reserve(m_nodesCount);
    for (Node::integral_type id = 0; id < m_nodesCount; ++id)
    {
        if (areNodesConnected(node, id))
        {
            ret.push_back(Node{id});
        }
    }
    ret.shrink_to_fit();
    return ret;
}

std::vector<Node> Graph::getConnectedNodes(Node const& node) const noexcept(false)
{
    return getConnectedNodes(node.id);
}

Node const Graph::getNode(Node::integral_type node) const noexcept(false)
{
    if (!contains(node))
    {
        throw std::invalid_argument("Node does not exist");
    }
    return Node{node};
}

Edge const Graph::getEdge(Node::integral_type src, Node::integral_type target) const noexcept(false)
{
    if (!contains(src) || !contains(target))
    {
        throw std::invalid_argument("Nodes do not exist");
    }
    else if (!areNodesConnected(src, target))
    {
        throw std::invalid_argument("Nodes are not connected");
    }
    return Edge{Node{src}, Node{target}, m_matrix[src][target],
                m_matrix[src][target] == m_matrix[target][src] ? EdgeDirection::Undirected : EdgeDirection::Directed};
}

Edge const Graph::getEdge(Node const& src, Node const& target) const noexcept(false)
{
    return getEdge(src.id, target.id);
}

edge_weight_type Graph::getEdgeWeight(Node::integral_type src, Node::integral_type target) const noexcept(false)
{
    if (!contains(src) || !contains(target))
    {
        throw std::invalid_argument("Nodes do not exist");
    }
    return m_matrix[src][target];
}

edge_weight_type Graph::getEdgeWeight(Node const& src, Node const& target) const noexcept(false)
{
    return getEdgeWeight(src.id, target.id);
}

std::string Graph::serialize() const
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Graph");

    uint32_t nodesCount = getSize();
    xmlWriter.writeAttribute("size", QString::number(nodesCount));

    xmlWriter.writeStartElement("Edges");
    for (uint32_t i = 0; i < nodesCount; ++i)
    {
        Node src{i};
        for (auto&& connected : getConnectedNodes(src))
        {
            xmlWriter.writeStartElement("Edge");
            xmlWriter.writeAttribute("src", QString::number(src.id));
            xmlWriter.writeAttribute("sink", QString::number(connected.id));
            xmlWriter.writeAttribute("weight", QString::number(getEdgeWeight(src, connected)));
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    return xml.toStdString();
}

void Graph::fromXml(const std::string &xml)
{
    QXmlStreamReader xmlReader(QString::fromStdString(xml));

    xmlReader.readNext();
    while (!xmlReader.atEnd())
    {
        if (xmlReader.isStartElement())
        {
            if (xmlReader.name() == "Graph")
            {
                for (QXmlStreamAttribute const& attribute : xmlReader.attributes())
                {
                    if (attribute.name().toString() == "size")
                    {
                        uint32_t size = attribute.value().toUInt();
                        m_matrix = std::vector<std::vector<edge_weight_type>>(size, std::vector<edge_weight_type>(size, noConnection));
                        m_nodesCount = {size};
                    }
                }
                xmlReader.readNext();
            }
            else if (xmlReader.name() == "Edges")
            {
                while (!xmlReader.atEnd())
                {
                    if (xmlReader.isStartElement())
                    {
                        if (xmlReader.isEndElement())
                        {
                            xmlReader.readNext();
                            break;
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
                            m_matrix[src.id][sink.id] = weight;
                        }
                        xmlReader.readNext();
                    }
                    else
                    {
                        xmlReader.readNext();
                    }
                }
            }
            else
            {
                xmlReader.readNext();
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
