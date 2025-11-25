#include "raylib.h"
#include "Game.h"
#include "Constants.h"

int main(){
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Tetris Pro UI");
    SetTargetFPS(60);

    Game game;
    float fallTimer=0.0f;

    while(!WindowShouldClose()){
        if(!game.isGameOver()){
            // Input
            if(IsKeyPressed(KEY_LEFT)) game.moveLeft();
            if(IsKeyPressed(KEY_RIGHT)) game.moveRight();
            if(IsKeyPressed(KEY_UP)) game.rotate();
            if(IsKeyDown(KEY_DOWN)) game.moveDown(); // soft drop

            // Automatic fall
            fallTimer+=GetFrameTime();
            if(fallTimer>game.getFallSpeed()){
                game.moveDown();
                fallTimer=0.0f;
            }
        } else {
            if(IsKeyPressed(KEY_R)) game.resetGame();
            if(IsKeyPressed(KEY_Q)) break;
        }

        BeginDrawing();
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
