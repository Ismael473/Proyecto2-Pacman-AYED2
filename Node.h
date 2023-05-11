#ifndef NODE_H
#define NODE_H

#include <vector>

class Graph;



class Node{

public:

    //Constructores

    Node();
    Node(int x, int y);

    int x() const;
    int y() const;


    void setX(int x);
    void setY(int y);

private:

    int x_;
    int y_;

};


bool operator==(const Node& lhs, const Node& rhs);
namespace std{
template <> struct hash<Node>
{
    size_t operator()(const Node& node) const{
        return hash<int>()(node.x()) + hash<int>()(node.y());
    }
};
}

#endif // NODE_H
