#include "PathGrid.h"
#include <cassert>
#include <QDebug>
#include "Tree.h"

using namespace std;

/*!
 * \brief PathGrid::PathGrid
 * \param numCols
 * \param numRows
 */
PathGrid::PathGrid( int numCols,  int numRows): nodes_(), filled_(){

    assert((numCols > 0) && (numRows > 0));


    for (size_t i = 0; i < numCols; i++){

        vector<Node> colOfNodes;
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

/*!
 * \brief PathGrid::fill
 * \param node
 * \return no retorna nada
 */
void PathGrid::fill(const Node &node){
    filled_[node] = true;
}

/*!
 * \brief PathGrid::fill
 * \param x
 * \param y
 * \return no retorna nada
 */
void PathGrid::fill( int x,  int y){
    fill(Node(x,y));
}

/*!
 * \brief PathGrid::unfill
 * \param node
 * \return no retorna nada
 */
void PathGrid::unfill(const Node &node){
    filled_[node] = false;
}

/*!
 * \brief PathGrid::unfill
 * \param x
 * \param y
 * \return no retorna nada
 */
void PathGrid::unfill( int x,  int y){
    unfill(Node(x,y));
}

/*!
 * \brief PathGrid::fillColumn
 * \param i
 * \return no retorna nada
 */
void PathGrid::fillColumn( int i){
    for (Node node:column(i)){
        fill(node);
    }
}

/*!
 * \brief PathGrid::fillRow
 * \param i
 * \return no retorna nada
 */
void PathGrid::fillRow( int i){
    for (Node node:row(i)){
        fill(node);
    }
}

/*!
 * \brief PathGrid::setFilling
 * \param vec
 * \return no retorna nada
 */
void PathGrid::setFilling(const vector<vector<int>>& vec){
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

/*!
 * \brief PathGrid::nodes
 * \param no recibe parametros
 * \return el vector con los nodos
 */
vector<Node> PathGrid::nodes() const{
    vector<Node> allNodes;
    for (auto col:nodes_){
        for (auto node:col){
            allNodes.push_back(node);
        }
    }

    return allNodes;
}

/*!
 * \brief PathGrid::filled
 * \param node
 * \return
 */
bool PathGrid::filled(const Node &node) const{
    return filled_.find(node)->second;
}

/*!
 * \brief PathGrid::filled
 * \param x
 * \param y
 * \return
 */
bool PathGrid::filled( int x,  int y) const{
    return filled(Node(x,y));
}

/*!
 * \brief PathGrid::unfilledNeighbors
 * \param of
 * \return retorna los vecinos del nodo deseado
 */
vector<Node> PathGrid::unfilledNeighbors(const Node &of) const{
    int numCols = nodes_.size();
    int numRows = nodes_[0].size();

    vector<Node> neighbors;


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


    if (of.x() > 0){
        Node leftNode(of.x()-1,of.y());
        if (!filled(leftNode)){
            neighbors.push_back(leftNode);
        }
    }


    if (of.x() < numCols - 1){
        Node rightNode(of.x()+1,of.y());
        if (!filled(rightNode)){
            neighbors.push_back(rightNode);
        }
    }

    return neighbors;

}

/*!
 * \brief PathGrid::graph
 * \param no recibe parametros
 * \return el grafo creado
 */
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
            g.addEdge(node,neighbor,1);
            g.addEdge(neighbor,node,1);
        }
    }

    return g;
}

/*!
 * \brief PathGrid::shortestPath
 * \param from
 * \param to
 * \return retorna el camino mas corto
 */
vector<Node> PathGrid::shortestPath(const Node &from, const Node &to) const{
    return graph().shortestPath(from,to);
}

/*!
 * \brief PathGrid::column
 * \param i
 * \return retorna un vector con los nodos de la columna
 */
vector<Node> PathGrid::column( int i) const{
    return nodes_[i];
}

/*!
 * \brief PathGrid::row
 * \param i
 * \return un vector con los nodos de la fila
 */
vector<Node> PathGrid::row( int i) const{
    vector<Node> nodes;
    for (vector<Node> col:nodes_){

        nodes.push_back(col[i]);
    }
    return nodes;
}
