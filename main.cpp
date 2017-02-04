#include <iostream>
#include "graph.h"
#include "labeledgraph.h"
#include "algorithms.h"

std::string graphXml = "<?xml version=\"1.0\"?>"
        "<Graph size=\"3\">"
            "<Edges>"
                "<Edge src=\"0\" sink=\"1\" weight=\"120\"/>"
                "<Edge src=\"1\" sink=\"0\" weight=\"120\"/>"
                "<Edge src=\"1\" sink=\"2\" weight=\"60\"/>"
                "<Edge src=\"2\" sink=\"1\" weight=\"60\"/>"
            "</Edges>"
        "</Graph>";
//std::string labeledGraphXml = "<?xml version=\"1.0\"?>"
//        "<LabeledGraph size=\"2\">"
//            "<Nodes>"
//                "<Node id=\"0\" label=\"Lodz\"/>"
//                "<Node id=\"1\" label=\"Warszawa\"/>"
//            "</Nodes>"
//            "<Edges>"
//                "<Edge src=\"0\" sink=\"1\" weight=\"60\"/>"
//                "<Edge src=\"1\" sink=\"0\" weight=\"60\"/>"
//            "</Edges>"
//        "</LabeledGraph>";

int main()
{
    Graphs::Graph graph{};
    try
    {
        graph.fromXml(graphXml);
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::boolalpha;
    std::cout << "graph.getSize(): " << graph.getSize() << std::endl;
    std::cout << "graph.contains(0): " << graph.contains(0)  << std::endl;
    std::cout << "graph.contains(1): " << graph.contains(1) << std::endl;
    std::cout << "graph.contains(2): " << graph.contains(2) << std::endl;
    std::cout << "graph.areNodesConnected(0, 1): " << graph.areNodesConnected(0, 1) << std::endl;
    std::cout << "graph.areNodesConnected(1, 2): " << graph.areNodesConnected(1, 2) << std::endl;
    std::cout << "graph.areNodesConnected(1, 0): " << graph.areNodesConnected(1, 0) << std::endl;
    std::cout << "graph.areNodesConnected(2, 1): " << graph.areNodesConnected(2, 1) << std::endl;
    std::cout << "graph.areNodesConnected(0, 2): " << graph.areNodesConnected(0, 2) << std::endl;
    std::cout << "graph.getEdgeWeight(0, 1): " << graph.getEdgeWeight(0, 1) << std::endl;
    std::cout << "graph.getEdgeWeight(1, 2): " << graph.getEdgeWeight(1, 2) << std::endl;
    std::cout << "graph.getEdgeWeight(1, 0): " << graph.getEdgeWeight(1, 0) << std::endl;
    std::cout << "graph.getEdgeWeight(2, 1): " << graph.getEdgeWeight(2, 1) << std::endl;
    std::cout << "graph.getEdgeWeight(0, 2): " << graph.getEdgeWeight(0, 2) << std::endl;
    std::cout << "graph.getEdge(0, 1).weight: " << graph.getEdge(0, 1).weight << std::endl;
    std::cout << "graph.getEdge(1, 2).weight: " << graph.getEdge(1, 2).weight << std::endl;
    std::cout << "graph.getEdge(1, 0).weight: " << graph.getEdge(1, 0).weight << std::endl;
    std::cout << "graph.getEdge(2, 1).weight: " << graph.getEdge(2, 1).weight << std::endl;
    try
    {
        std::cout << "graph.getEdge(0, 2).weight: " << graph.getEdge(0, 2).weight << std::endl;
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "graph.getEdge(0, 2).weight: " << e.what() << std::endl;
    }
    std::cout << "Algorithms::isConsistent(graph): " << Graphs::Algorithms::isConsistent(graph) << std::endl;

    Graphs::Node start{0};
    Graphs::Node finish{2};
    std::cout << "Algorithms::depthFirstSearch(graph, 0, 2): " << Graphs::Algorithms::depthFirstSearch(graph, start, finish) << std::endl;
    std::cout << "Algorithms::breadthFirstSearch(graph, 0, 2): " << Graphs::Algorithms::breadthFirstSearch(graph, start, finish) << std::endl;
    std::cout << "Algorithms::findShortestPath(graph, 0, 2): " << Graphs::Algorithms::findShortestPath(graph, start, finish) << std::endl;
    std::cout << "graph.serialize(): " << graph.serialize() << std::endl;
    return 0;
}
