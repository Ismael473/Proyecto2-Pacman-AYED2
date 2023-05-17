#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Mapeo.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"

class Game: public QGraphicsView {
    Q_OBJECT
public:

    Game( int numCellsWide,  int numCellsLong,
          int cellSize, QWidget* parent=nullptr);


    void createEnemy( int x,  int y);
    void fill( int x,  int y);
    bool filled(int x, int y);


    Node pointToNode(const QPointF& point);
    QPointF nodeToPoint(const Node& node);

public slots:
    void setEnemyPath();

private:

    Mapeo mapeo_;
    QGraphicsScene* scene_;
    Player* player_;
    vector<Enemy*> enemies_;
    int cellSize_;


    void drawMap(const vector<vector<int>>& vec);

};

#endif // GAME_H
