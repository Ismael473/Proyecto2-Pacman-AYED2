#include "Game.h"
#include <cassert>
#include <QDebug>
#include <QTimer>

Game::Game(int numCellsWide, int numCellsLong, int cellSize, QWidget *parent):
    QGraphicsView(parent),
    mapeo_(numCellsWide, numCellsLong, cellSize),
    scene_(new QGraphicsScene(this)),
    player_(new Player(this,cellSize)),
    enemies_(),
    cellSize_(cellSize)
{

    setScene(scene_);
    setSceneRect(0,0,numCellsWide*cellSize,numCellsLong*cellSize);

    player_->setPos(3*cellSize, 1*cellSize);
    scene_->addItem(player_);
    player_->setFocus();

    createEnemy(1,1);
    createEnemy(14,1);
    createEnemy(14,10);

    vector<vector<int>> vec {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    drawMap(vec);


    //Hace que los enemigos sigan al jugador
    QTimer* followTimer = new QTimer(this);
    connect(followTimer,SIGNAL(timeout()),this,SLOT(setEnemyPaths()));
    followTimer->start(1000);
}


void Game::createEnemy(int x, int y){
    Enemy * enemy = new Enemy(cellSize_);
    enemy->setPos(cellSize_*x,cellSize_*y);
    scene_->addItem(enemy);
    enemies_.push_back(enemy);

}

void Game::fill(int x, int y){
    mapeo_.fillCell(x,y);

    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0, cellSize_,cellSize_);
    rect->setPos(x*cellSize_,y*cellSize_);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    scene_->addItem(rect);
}

bool Game::filled(int x, int y){
    return mapeo_.filledCell(x,y);
}

void Game::setEnemyPaths(){
    for (Enemy * enemy:enemies_){
        vector<Node> nodePath = mapeo_.shortestPath(enemy->pos().x(),
                                                    enemy->pos().y(),
                                                    player_->pos().x(),
                                                    player_->pos().y());
        vector<QPointF> path;
        for (Node node:nodePath){
            path.push_back(QPointF(node.x(),node.y()));
        }

        enemy->setPoints(path);
    }
}

void Game::drawMap(const std::vector<std::vector<int> > &vec){

    assert((vec.size()) == (mapeo_.numCellsLong()));
    assert(vec[0].size() == mapeo_.numCellsWide());


    for (int y = 0, n = mapeo_.numCellsLong(); y < n; y++){
         for (int x = 0, p = mapeo_.numCellsWide(); x < p; x++){
             if (vec[y][x] != 0){
                 fill(x,y);
             }
        }
    }
}

Node Game::pointToNode(const QPointF &point){
    return Node(point.x()/cellSize_, point.y()/cellSize_);
}

QPointF Game::nodeToPoint(const Node &node){
    return QPointF(node.x()*cellSize_, node.y()*cellSize_);
}

