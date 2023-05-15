#include "PathGrid.h"
#include <cassert>
#include <QDebug>
#include "Tree.h"

using namespace std;

PathGrid::PathGrid(int numCols, int numRows): nodes_(), filled_()
{
    assert((numCols > 0) && (numRows > 0));


    for (size_t i = 0; i < numCols; i ++){

        std::vector<Node> colOfNodes;

        for (size_t j = 0; j < numRows; j++){

            Node node(i,j);
            colOfNodes.push_back(node);
        }
        nodes_.push_back(colOfNodes);
    }

    for (Node node:nodes()){
        filled_[node] = false;
    }
}


void PathGrid::fill(const Node &node){
    filled_[node] = true;
}


void PathGrid::fill(int x, int y){
    fill(Node(x,y));
}

void PathGrid::unfill(const Node &node){
    filled_[node] = false;
}


void PathGrid::unfill(int x, int y){
    unfill(Node(x,y));
}

void PathGrid::fillColumn(int i){
    for (Node node:column(i)){
        fill(node);
    }
}

void PathGrid::fillRow(int i){
    for (Node node:row(i)){
        fill(node);
    }
}

void PathGrid::setFilling(const std::vector<std::vector<int>>& vec){
    for (int y = 0, n = nodes_[0].size(); y < n; y++){
        for (int x = 0, p = nodes_.size(); x < p; x++){
            if (vec[y][x] == 0){
                unfill(x,y);
            }
            else{
                fill(x,y);
            }
        }
    }
}


std::vector<Node> PathGrid::nodes() const{
    vector<Node> allNodes;
    for (auto col:nodes_){
        for (auto node:col){
            allNodes.push_back(node);
        }

    }
    return allNodes;
}

bool PathGrid::filled(const Node &node) const{
    return filled_.find(node)->second;
}


bool PathGrid::filled(int x, int y) const{
    return filled(Node(x,y));
}

vector<Node> PathGrid::unfilledNeighbors(const Node &of) const{
    int numCols = nodes_.size();
    int numRows = nodes_[0].size();

    std::vector<Node> neighbors;

    if (of.y() > 0){
        Node upNode(of.x(),of.y()-1);
        if (!filled(upNode)){
            neighbors.push_back(upNode);
        }
    }

    if (of.y() < numRows - 1){
        Node downNode(of.x(),of.y()+1);
        if (!filled(downNode)){
            neighbors.push_back(downNode);
        }
    }

    // left
    if (of.x() > 0){
        Node leftNode(of.x()-1,of.y());
        if (!filled(leftNode)){
            neighbors.push_back(leftNode);
        }
    }

    // right
    if (of.x() < numCols - 1){
        Node rightNode(of.x()+1,of.y());
        if (!filled(rightNode)){
            neighbors.push_back(rightNode);
        }
    }

    return neighbors;
}

Graph PathGrid::graph() const{
    Graph g;


    for (Node node:nodes()){
        g.addNode(node);
    }

    for (Node node:g.nodes()){

        if (filled(node)){
            continue;
        }

        vector<Node> neighbors = unfilledNeighbors(node);
        for (Node neighbor:neighbors){
            g.addEdge(node, neighbor, 1);
            g.addEdge(neighbor, node, 1);
        }
    }
    return g;
}

vector<Node> PathGrid::shortestPath(const Node &from, const Node &to) const{
    return graph().shortestPath(from,to);
}

vector<Node> PathGrid::column(int i) const{
    return nodes_[i];
}

vector<Node> PathGrid::row(int i) const{
    vector<Node> nodes;
    for (vector<Node> col:nodes_){

        nodes.push_back(col[i]);

    }
    return nodes;
}









