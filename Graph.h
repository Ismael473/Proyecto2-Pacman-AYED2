#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include "Node.h"
#include "Edge.h"

using namespace std;

class Tree;


class Graph{
public:

    Graph();
    Graph(const unordered_set<Node>& nodes, const unordered_set<Edge>& edges);


    unordered_set<Node> nodes() const;
    unordered_set<Edge> edges() const;
    vector<Edge> outgoingEdges(const Node& from) const;
    vector<Edge> incomingEdges(const Node& to) const;
    vector<Node> outgoingNodes(const Node& from) const;
    vector<Node> incomingNodes(const Node& to) const;
    bool contains(const Node& node) const;
    bool contains(const Edge& edge) const;
    vector<Node> shortestPath(const Node& from, const Node& to) const;
    Tree spt(const Node& source) const;


    void addNode(const Node& node);
    void addEdge(const Node& from, const Node& to,  int weight);

private:

    unordered_set<Node> nodes_;
    unordered_set<Edge> edges_;


    unordered_set<Node> pickedNodes_;
    unordered_set<Node> unpickedNodes_;
    unordered_set<Edge> pickedEdges_;
    unordered_set<Edge> unpickedEdges_;
    unordered_map<Node, int> nodeWeight_;
    unordered_map<Node,Edge> updatedEdge_;


    void pick(const Node& node);
    void pick(const Edge& edge);
    bool picked(const Node& node) const;
    bool picked(const Edge& edge) const;
    void setWeight(const Node& of,  int weight);
    int weight(const Node& of) const;
    Edge edge(const Node& from, const Node& to) const;
    void unpickAll();
    void initializeNodeWeights(const Node& source);
    bool hasUnpickedNode() const;
    Node lightestUnpickedNode() const;
    void pickConnetedEdge(const Node& of);
    vector<Node> unpickedNeighbors(const Node& of) const;
    void updateNeighborWeights(const Node& of);

};

#endif // GRAPH_H
