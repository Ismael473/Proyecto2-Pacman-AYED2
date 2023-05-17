#include "Node.h"


Node::Node(){

}

/*!
 * \brief Node::Node
 * \param x
 * \param y
 */
Node::Node( int x,  int y): x_(x), y_(y){

}

/*!
 * \brief Node::x
 * \param no recibe parametros
 * \return retorna el valor de x del nodo
 */
int Node::x() const{
    return x_;
}

/*!
 * \brief Node::y
 * \param no recibe parametros
 * \return retorna el valor de y del nodo
 */
int Node::y() const{
    return y_;
}

/*!
 * \brief Node::setX
 * \param x
 * \return no retorna nada
 */
void Node::setX( int x){
    x_ = x;
}

/*!
 * \brief Node::setY
 * \param y
 * \return no retorna nada
 */
void Node::setY( int y){
    y_ = y;
}


bool operator==(const Node &lhs, const Node &rhs){
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}
