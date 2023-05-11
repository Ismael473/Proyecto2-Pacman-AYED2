#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "Mapeo.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Game: public QGraphicsView{
    Q_OBJECT
public:

    //Constructores
    Game(int numCellsWide, int numCellsLong, int cellSize, QWidget * parent=nullptr);

    //Setters
    void createEnemy(int x, int y);
    void fill(int x, int y);
    bool filled(int x, int y);

    //Funcinones de ayuda
    Node pointToNode(const QPointF& point);
    QPointF nodeToPoint(const Node& node);

public slots:
    void setEnemyPaths();

private:
    //Atributos privados
    Mapeo mapeo_;
    QGraphicsScene * scene_;
    Player * player_;
    vector<Enemy*> enemies_;
    int cellSize_;

    void drawMap(const vector<vector<int>>& vec);


};

#endif // GAME_H
