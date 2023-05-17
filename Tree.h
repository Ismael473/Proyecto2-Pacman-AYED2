#ifndef TREE_H
#define TREE_H

#include "Graph.h"
#include "Node.h"
#include <vector>

using namespace std;

class Tree{
public:

    Tree(const Node& root);
    Tree(const Graph& graph, const Node& root);


    vector<Node> pathTo(const Node& node) const;
    unordered_set<Node> nodes() const;
    unordered_set<Edge> edges() const;


    void addChild(const Node& to, const Node& child, int weight);

private:

    Graph graph_;
    Node root_;


    unordered_set<Node> visitedNodes_;


    void visit(const Node& node);
    bool isVisited(const Node& node);
    bool hasUnvisitedChild(const Node& node);
    Node anUnvisitedChild(const Node& of);
    vector<Node> dfs(const Node& node, const Node& target, vector<Node> path);

};

#endif // TREE_H
