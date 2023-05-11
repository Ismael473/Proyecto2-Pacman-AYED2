#include "Edge.h"
#include <cassert>

Edge::Edge(){

}

Edge::Edge(const Node &from, const Node &to, int weight): from_(from), to_(to), weight_(weight){

    assert(!(from == to));
}

Node Edge::from() const{
    return from_;
}

Node Edge::to() const{
    return to_;
}

int Edge::weight() const{
    return weight_;
}

bool operator==(const Edge lhs, const Edge rhs){
    return (lhs.from() == rhs.to()) && (lhs.to() == rhs.to());
}
