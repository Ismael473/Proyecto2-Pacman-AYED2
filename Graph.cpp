#include "Graph.h"
#include <vector>
#include <cassert>
#include "Tree.h"
#include <QDebug> // TODO remove

using namespace std;

Graph::Graph(){

}

/*!
 * \brief Graph::Graph
 * \param nodes
 * \param edges
 */
Graph::Graph(const unordered_set<Node> &nodes, const unordered_set<Edge> &edges): nodes_(nodes),edges_(edges){

}

/*!
 * \brief Graph::addNode
 * \param node
 * \return no retorna nada
 */
void Graph::addNode(const Node &node){
    nodes_.insert(node);
}

/*!
 * \brief Graph::addEdge
 * \param from
 * \param to
 * \param weight
 * \return no retorna nada
 */
void Graph::addEdge(const Node &from, const Node &to,  int weight){

    assert(contains(from));
    assert(contains(to));


    Edge edge(from,to,weight);


    edges_.insert(edge);
}

/*!
 * \brief Graph::nodes
 * \param no recibe parametros
 * \return los nodos actuales del grafo
 */
unordered_set<Node> Graph::nodes() const{
    return nodes_;
}

/*!
 * \brief Graph::edges
 * \param no recibe parametros
 * \return las aristas actuales del grafo
 */
unordered_set<Edge> Graph::edges() const{
    return edges_;
}

/*!
 * \brief Graph::outgoingEdges
 * \param from
 * \return un vector con las aristas actuales
 */
vector<Edge> Graph::outgoingEdges(const Node &from) const{

    vector<Edge> edges;
    for(auto edge : edges_){
        if (edge.from() == from){
            edges.push_back(edge);
        }
    }
    return edges;
}

/*!
 * \brief Graph::incomingEdges
 * \param to
 * \return un vector con las aristas que entran
 */
vector<Edge> Graph::incomingEdges(const Node &to) const{

    assert(contains(to));

    vector<Edge> edges;
    for(auto edge : edges_){
        if (edge.to() == to){
            edges.push_back(edge);
        }
    }
    return edges;
}

/*!
 * \brief Graph::outgoingNodes
 * \param from
 * \return un vector con los nodos que salen
 */
vector<Node> Graph::outgoingNodes(const Node &from) const{

    vector<Edge> outgoingE = outgoingEdges(from);


    vector<Node> outgoingN;
    for (auto edge:outgoingE){
        outgoingN.push_back(edge.to());
    }

    return outgoingN;
}

/*!
 * \brief Graph::incomingNodes
 * \param to
 * \return un vector con los nodos que entran
 */
vector<Node> Graph::incomingNodes(const Node &to) const{

    assert(contains(to));


    vector<Edge> incomingE = incomingEdges(to);


    vector<Node> incomingN;
    for (auto edge:incomingE){
        incomingN.push_back(edge.from());
    }

    return incomingN;
}

/*!
 * \brief Graph::contains
 * \param node
 * \return retorna true si el grafo contiene el nodo especificado
 */
bool Graph::contains(const Node &node) const{
    return (nodes_.count(node) == 1);
}

/*!
 * \brief Graph::contains
 * \param edge
 * \return retorna true si el grafo contiene la arista especificada
 */
bool Graph::contains(const Edge &edge) const{
    return (edges_.count(edge) == 1);
}

/*!
 * \brief Graph::shortestPath
 * \param from
 * \param to
 * \return el camino mas corto
 */
vector<Node> Graph::shortestPath(const Node &from, const Node &to) const{
    Tree t = spt(from);
    vector<Node> path = t.pathTo(to);
    return path;
}

/*!
 * \brief Graph::spt
 * \param source
 * \return
 */
Tree Graph::spt(const Node &source) const{

    assert(contains(source));


    Graph copy = *this;


    Node rootNode(0,0);


    copy.unpickAll();


    copy.initializeNodeWeights(source);


    bool isFirstNode = true;
    while (copy.hasUnpickedNode()){

        Node lightest = copy.lightestUnpickedNode();
        copy.pick(lightest);


        copy.updateNeighborWeights(lightest);


        if (isFirstNode){
            rootNode = lightest;
            isFirstNode = false;
            continue;
        }


        copy.pickConnetedEdge(lightest);
    }


    Graph graph(copy.pickedNodes_,copy.pickedEdges_);


    return Tree(graph,rootNode);

}

/*!
 * \brief Graph::pick
 * \param node
 * \return no retorna nada
 */
void Graph::pick(const Node &node){

    assert(unpickedNodes_.count(node) == 1);


    assert(!picked(node));


    pickedNodes_.insert(node);
    unpickedNodes_.erase(node);

}

/*!
 * \brief Graph::pick
 * \param edge
 * \return no retorna nada
 */
void Graph::pick(const Edge &edge){

    pickedEdges_.insert(edge);
    unpickedEdges_.erase(edge);

}

/*!
 * \brief Graph::picked
 * \param node
 * \return retorna true si el nodo especificado es el seleccionado
 */
bool Graph::picked(const Node &node) const{

    assert(contains(node));

    return (pickedNodes_.count(node) == 1);
}

/*!
 * \brief Graph::picked
 * \param edge
 * \return retorna true si la arista especificada es la seleccionada
 */
bool Graph::picked(const Edge &edge) const{

    assert(contains(edge));

    return (pickedEdges_.count(edge) == 1);
}

/*!
 * \brief Graph::setWeight
 * \param of
 * \param weight
 * \return no retorna nada
 */
void Graph::setWeight(const Node &of,  int weight){

    assert(contains(of));

    nodeWeight_[of] = weight;
}

/*!
 * \brief Graph::weight
 * \param of
 * \return retorna el peso del nodo especificado
 */
int Graph::weight(const Node &of) const{

    assert(contains(of));

    int weight = nodeWeight_.find(of)->second;
    return weight;
}

/*!
 * \brief Graph::edge
 * \param from
 * \param to
 * \return retorna la arista entre los dos nodos especificados
 */
Edge Graph::edge(const Node &from, const Node &to) const{

    assert(contains(from));
    assert(contains(to));

    for (Edge edge:edges_){
        if (edge.from() == from && edge.to() == to){
            return edge;
        }
    }


    assert(true);
    return Edge();
}

/*!
 * \brief Graph::unpickAll
 * \param no recibe parametros
 * \return no retorna nada
 */
void Graph::unpickAll(){

    for (Node node:nodes_){
        unpickedNodes_.insert(node);
    }


    for (Edge edge:edges_){
        unpickedEdges_.insert(edge);
    }
}

/*!
 * \brief Graph::initializeNodeWeights
 * \param source
 * \return no retorna nada
 */
void Graph::initializeNodeWeights(const Node &source){

    assert(contains(source));


    setWeight(source,0);


    for (Node node:nodes_){
        if (!(node == source)){
            setWeight(node,1000);
        }
    }
}

/*!
 * \brief Graph::hasUnpickedNode
 * \param no recibe parametros
 * \return retorna true si hay al menos un nodo sin seleccionar
 */
bool Graph::hasUnpickedNode() const{
    return (!unpickedNodes_.empty());
}

/*!
 * \brief Graph::lightestUnpickedNode
 * \param no recibe parametros
 * \return retorna el nodo con menor peso
 */
Node Graph::lightestUnpickedNode() const{

    assert(hasUnpickedNode());


    Node lightest = *(unpickedNodes_.begin());


    for (Node node: unpickedNodes_){
        if (weight(node) < weight(lightest)){
            lightest = node;
        }
    }

    return lightest;
}

/*!
 * \brief Graph::pickConnetedEdge
 * \param of
 * \return no retorna nada
 */
void Graph::pickConnetedEdge(const Node &of){
    Edge edge = updatedEdge_[of];
    pick(edge);

}

/*!
 * \brief Graph::unpickedNeighbors
 * \param of
 * \return un vector con los vecinos no seleccionados del nodo especificado
 */
vector<Node> Graph::unpickedNeighbors(const Node &of) const{

    vector<Node> neighbors = outgoingNodes(of);

    vector<Node> unpicked;
    for (auto neighbor:neighbors){
        if (!picked(neighbor)){
            unpicked.push_back(neighbor);
        }
    }

    return unpicked;

}

/*!
 * \brief Graph::updateNeighborsWeights
 * \param of
 * \return no retorna nada
 */
void Graph::updateNeighborWeights(const Node &of){

    for (Node neighbor:unpickedNeighbors(of)){

        Edge edgeToNeighbor = edge(of,neighbor);
        int edgeWeight = edgeToNeighbor.weight();


        int newTotalWeight = nodeWeight_[of] + edgeWeight;
        int oldWeight = nodeWeight_[neighbor];

        if (newTotalWeight < oldWeight){
            setWeight(neighbor,newTotalWeight);
            updatedEdge_[neighbor] = edgeToNeighbor;
        }

    }
}
