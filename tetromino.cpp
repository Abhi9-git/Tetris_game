#include "Tetromino.h"
#include <cstdlib>
#include <ctime>

Tetromino::Tetromino(int t) : type(t), rotation(0) {
    colorIndex = type; // fixed color per piece
    srand(time(0));

    // Random x at top
    x = rand() % (GRID_WIDTH - 4 + 1); // 4 is max width of tetromino
    y = -2; // start slightly above screen

    shapes = {
        // I
        {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
         {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}},
        // O
        {{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}},
        // T
        {{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}},
        // S
        {{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
         {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
        // Z
        {{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
         {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},
        // J
        {{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
         {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}},
        // L
        {{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
         {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}}
    };
}

const std::vector<std::vector<int>>& Tetromino::getShape() const {
    return shapes[type][rotation % shapes[type].size()];
}

int Tetromino::getX() const { return x; }
int Tetromino::getY() const { return y; }
void Tetromino::setX(int newX) { x = newX; }
void Tetromino::setY(int newY) { y = newY; }
void Tetromino::rotate() { rotation = (rotation + 1) % shapes[type].size(); }
void Tetromino::unrotate() { rotation = (rotation - 1 + shapes[type].size()) % shapes[type].size(); }
