#include "Mapeo.h"

using namespace std;

/*!
 * \brief Mapeo::Mapeo
 * \param numCellsWide
 * \param numCellsLong
 * \param cellSize
 */
Mapeo::Mapeo( int numCellsWide,  int numCellsLong,  int cellSize):
    numCellsWide_(numCellsWide),
    numCellsLong_(numCellsLong),
    cellSize_(cellSize),
    pathGrid_(numCellsWide,numCellsLong) {


}

/*!
 * \brief Mapeo::filled
 * \param x
 * \param y
 * \return true si las coordenadas dadas estan llenas
 */
bool Mapeo::filled( int x,  int y) const{

    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    return pathGrid_.filled(xGrid,yGrid);
}

/*!
 * \brief Mapeo::filledCell
 * \param x
 * \param y
 * \return retorna true si la celda dada esta llena
 */
bool Mapeo::filledCell( int x,  int y) const{
    return pathGrid_.filled(x,y);
}

/*!
 * \brief Mapeo::nodes
 * \param no recibe parametros
 * \return retorna los nodos actualizados
 */
vector<Node> Mapeo::nodes() const{

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

/*!
 * \brief Mapeo::shortestPath
 * \param xfrom
 * \param yfrom
 * \param xto
 * \param yto
 * \return retorna el camino mas corto
 */
vector<Node> Mapeo::shortestPath( int xfrom,  int yfrom,  int xto,  int yto) const{

    vector<Node> path = pathGrid_.shortestPath(Node(xfrom/cellSize_,yfrom/cellSize_),Node(xto/cellSize_,yto/cellSize_));
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

/*!
 * \brief Mapeo::width
 * \param no recibe parametros
 * \return retorna el numero de celdas
 */
int Mapeo::width() const{
    return cellSize_ * numCellsWide_;
}

/*!
 * \brief Mapeo::height
 * \param no recibe parametros
 * \return
 */
int Mapeo::height() const{
    return cellSize_ * numCellsLong_;
}

/*!
 * \brief Mapeo::cellSize
 * \param no recibe parametros
 * \return
 */
int Mapeo::cellSize() const{
    return cellSize_;
}

/*!
 * \brief Mapeo::numCellsLong
 * \no recibe parametros
 * \return
 */
int Mapeo::numCellsLong() const{
    return numCellsLong_;
}

/*!
 * \brief Mapeo::numCellsWide
 * \no recibe parametros
 * \return
 */
int Mapeo::numCellsWide() const{
    return numCellsWide_;
}

/*!
 * \brief Mapeo::fill
 * \param x
 * \param y
 * \return no retorna nada
 */
void Mapeo::fill( int x,  int y){

    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.fill(xGrid,yGrid);
}

/*!
 * \brief Mapeo::fillCell
 * \param x
 * \param y
 * \return no retorna nada
 */
void Mapeo::fillCell( int x,  int y){
    pathGrid_.fill(x,y);
}

/*!
 * \brief Mapeo::fillColumn
 * \param i
 * \return no retorna nada
 */
void Mapeo::fillColumn( int i){
    pathGrid_.fillColumn(i);
}

/*!
 * \brief Mapeo::fillRow
 * \param i
 * \return no retorna nada
 */
void Mapeo::fillRow( int i){
    pathGrid_.fillRow(i);
}

/*!
 * \brief Mapeo::unfill
 * \param x
 * \param y
 * \return no retorna nada
 */
void Mapeo::unfill( int x,  int y){

    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.unfill(xGrid,yGrid);
}

/*!
 * \brief Mapeo::unfillCell
 * \param x
 * \param y
 * \return no retorna nada
 */
void Mapeo::unfillCell( int x,  int y){
    pathGrid_.unfill(x,y);
}

/*!
 * \brief Mapeo::setFilling
 * \param vec
 * \return no retorna nada
 */
void Mapeo::setFilling(const vector<vector<int> > &vec){
    pathGrid_.setFilling(vec);
}
