#pragma once
#include <vector>
#include "Constants.h"

class Tetromino {
private:
    int type;           // 0-6
    int rotation;       // 0-3
    int x, y;           // position on grid
    int colorIndex;     // fixed color per piece
    std::vector<std::vector<std::vector<std::vector<int>>>> shapes;

public:
    Tetromino(int t);
    const std::vector<std::vector<int>>& getShape() const;
    int getX() const;
    int getY() const;
    int getColorIndex() const { return colorIndex; }
    void setX(int newX);
    void setY(int newY);
    void rotate();
    void unrotate();
};
