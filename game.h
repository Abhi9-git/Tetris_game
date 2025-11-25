#pragma once
#include "Tetromino.h"
#include <memory>

class Game {
private:
    int grid[GRID_HEIGHT][GRID_WIDTH]{};
    std::unique_ptr<Tetromino> currentPiece;
    std::unique_ptr<Tetromino> nextPiece;
    int score;
    bool gameOver;
    float fallSpeed;

public:
    Game();
    void spawnTetromino();
    bool checkCollision(int dx, int dy, int rotationChange);
    void mergeTetromino();
    void clearLines();
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotate();
    void draw();
    bool isGameOver() const { return gameOver; }
    float getFallSpeed() const { return fallSpeed; }
    void resetGame();
};
