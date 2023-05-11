#ifndef EDGE_H
#define EDGE_H

#include "Node.h"


class Edge{
public:

    Edge();
    Edge(const Node& from, const Node& to, int weight);


    Node from() const;
    Node to() const;
    int weight() const;

private:

    int weight_;
    Node from_;
    Node to_;
};

bool operator==(const Edge& lhs, const Edge& rhs);

namespace std {
template <> struct hash<Edge>
{
    size_t operator()(const Edge& edge) const{
        return hash<Node>()(edge.from()) + hash<Node>()(edge.to());
    }
};
}

#endif // EDGE_H
