#include "Tree.h"
#include <cassert>
#include <QDebug>

using namespace std;

Tree::Tree(const Node &root): root_(root), graph_(){

    graph_.addNode(root);
}


Tree::Tree(const Graph &graph, const Node &root): graph_(graph), root_(root){

}


void Tree::addChild(const Node &to, const Node &child, int weight){

    assert(graph_.contains(to));


    graph_.addNode(child);


    graph_.addEdge(to,child,weight);
}


vector<Node> Tree::pathTo(const Node &node) const{

    Tree copy  = *this;
    vector<Node> empty;
    return copy.dfs(root_,node,empty);
}


unordered_set<Node> Tree::nodes() const{
    return graph_.nodes();
}


unordered_set<Edge> Tree::edges() const{
    return graph_.edges();
}


vector<Node> Tree::dfs(const Node &node, const Node &target, vector<Node> path){

    visit(node);


    if (node == target){
        path.push_back(node);
        return path;
    }


    if (!hasUnvisitedChild(node)){
        Node lastNode = path.back();
        path.pop_back();
        return dfs(lastNode,target,path);
    }


    if (hasUnvisitedChild(node)){
        path.push_back(node);
        Node unvisited = anUnvisitedChild(node);
        return dfs(unvisited,target,path);
    }

}


void Tree::visit(const Node &node){


    visitedNodes_.insert(node);
}


bool Tree::isVisited(const Node &node){
    return (visitedNodes_.count(node) == 1);
}


bool Tree::hasUnvisitedChild(const Node &node){

    vector<Node> children = graph_.outgoingNodes(node);


    int numUnvisited = 0;
    for (auto child : children){
        if (!isVisited(child)){
            numUnvisited++;
        }
    }

    return (numUnvisited > 0);
}


Node Tree::anUnvisitedChild(const Node &of){

    assert(hasUnvisitedChild(of));


    vector<Node> children = graph_.outgoingNodes(of);


    for (auto child : children){
        if (!isVisited(child)){
            return child;
        }
    }

}
