#include "Mapeo.h"

Mapeo::Mapeo(int numCellsWide, int numCellsLong, int cellSize):
    numCellsWide_(numCellsWide),
    numCellsLong_(numCellsLong),
    cellSize_(cellSize),
    pathGrid_(numCellsWide, numCellsLong){


}

bool Mapeo::filled(int x, int y) const{

    int xGrid = x/ cellSize_;
    int yGrid = y/ cellSize_;

    return pathGrid_.filled(xGrid, yGrid);
}

bool Mapeo::filledCell(int x, int y) const{
    return pathGrid_.filled(x,y);
}

Vector<Node> Mapeo::nodes() const{

    vector<Node> nodes;

    for (Node node:pathGrid_.nodes()){

        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        nodes.push_back(node);
    }
    return nodes;
}


vector<Node> Mapeo::shortestPath(int xfrom, int yfrom, int xto, int yto) const{

    vector<Node> path = pathGrid_.shortestPath(Node(xfrom/cellSize_, yfrom/cellSize_), Node(xto/cellSize_, yto/cellSize_));

    vector<Node> scaledPath;

    for (Node node:path){

        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        scaledPath.push_back(node);
    }

    return scaledPath;
}

int Mapeo::width() const{
    return cellSize_ * numCellsLong_;
}

int Mapeo::height() const{
    return cellSize_ * numCellsWide_;
}

int Mapeo::cellSize() const{
    return cellSize_;
}

int Mapeo::numCellsWide() const{
    return numCellsWide_;
}

int Mapeo::numCellsLong() const{
    return numCellsWide_;
}

void Mapeo::fill(int x, int y){

    int xGrid = x/ cellSize_;
    int yGrid = y/ cellSize_;

    pathGrid_.fill(xGrid,yGrid);
}

void Mapeo::fillCell(int x, int y){
    pathGrid_.fill(x,y);
}

void Mapeo::fillColumn(int i){
    pathGrid_.fillColumn(i);
}

void Mapeo::fillRow( int i){
    pathGrid_.fillRow(i);
}

void Mapeo::unfill(int x, int y){
    int xGrid = x/cellSize_;
    int yGrid = y/cellSize_;
    pathGrid_.unfill(xGrid, yGrid);
}

void Mapeo::unfillCell(int x, int y){
    pathGrid_.unfill(x,y);
}

void Mapeo::setFilling(const vector<vector<int> > &vec){
    pathGrid_.setFilling(vec);
}
