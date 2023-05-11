#include "Node.h"

Node::Node(){

}

Node::Node(int x, int y): x_(x), y_(y){


}

int Node::x() const{
    return x_;
}

int Node::y() const{
    return y_;
}

void Node:: setX(int  x){
    x_ = x;
}

void Node:: setY(int y){
    y_ = y;
}

bool operator==(const Node &lhs, const Node &rhs){
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}
