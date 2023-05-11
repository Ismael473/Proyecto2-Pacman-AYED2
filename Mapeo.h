#ifndef MAPEO_H
#define MAPEO_H

#include "PathGrid.h"


class Mapeo{
public:

    Mapeo(int numCellsWide, int numCellsLong, int cellSize);

    bool filled(int x , int y) const;
    bool filledCell(int x, int y) const;
    vector<Node> nodes() const;
    vector<Node> shortestPath(int xfrom, int yfrom, int xto, int yto) const;
    int width()const;
    int height() const;
    int cellSize() const;
    int numCellsLong() const;
    int numCellsWide() const;


    void fill(int x, int y);
    void fillCell(int x, int y);
    void fillColumn(int i);
    void fillRow(int i);
    void unfill(int x, int y);
    void unfillCell(int x, int y);
    void setFilling(const vector<vector<int>>& vec);

private:

    PathGrid pathgGrid_;
    int cellSize_;
    int numCellsWide_;
    int numCellsLong_;

};

#endif // MAPEO_H
