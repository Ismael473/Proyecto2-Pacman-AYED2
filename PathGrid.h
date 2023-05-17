#ifndef PATHGRID_H
#define PATHGRID_H

#include <vector>
#include "Node.h"
#include <unordered_map>
#include "Graph.h"

using namespace std;

class PathGrid{
public:

    PathGrid( int numCols,  int numRows);


    vector<Node> nodes() const;
    bool filled(const Node& node) const;
    bool filled( int x,  int y) const;
    vector<Node> unfilledNeighbors(const Node& of) const;
    Graph graph() const;
    vector<Node> shortestPath(const Node& from, const Node& to) const;
    vector<Node> column( int i) const;
    vector<Node> row( int i) const;


    void fill(const Node& node);
    void fill( int x,  int y);
    void unfill(const Node& node);
    void unfill( int x,  int y);
    void fillColumn( int i);
    void fillRow( int i);
    void setFilling(const vector<vector<int>>& vec);

private:

    vector<vector<Node>> nodes_;
    unordered_map<Node,bool> filled_;

};

#endif // PATHGRID_H
