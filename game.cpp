#include "Game.h"
#include "Constants.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

Game::Game(){
    srand(time(0));
    resetGame();
}

void Game::resetGame(){
    for(int i=0;i<GRID_HEIGHT;i++)
        for(int j=0;j<GRID_WIDTH;j++)
            grid[i][j]=0;
    score=0;
    gameOver=false;
    fallSpeed=BASE_FALL_SPEED;
    spawnTetromino();
    nextPiece = std::make_unique<Tetromino>(rand()%7);
}

void Game::spawnTetromino(){
    if(nextPiece) currentPiece = std::move(nextPiece);
    else currentPiece = std::make_unique<Tetromino>(rand()%7);
    nextPiece = std::make_unique<Tetromino>(rand()%7);

    if(checkCollision(0,0,0)) gameOver = true;
}

bool Game::checkCollision(int dx,int dy,int rotationChange){
    Tetromino temp = *currentPiece;
    temp.setX(temp.getX()+dx);
    temp.setY(temp.getY()+dy);
    if(rotationChange) temp.rotate();
    const auto &shape = temp.getShape();
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            if(shape[i][j]){
                int nx=temp.getX()+j;
                int ny=temp.getY()+i;
                if(nx<0||nx>=GRID_WIDTH||ny>=GRID_HEIGHT) return true;
                if(ny>=0 && grid[ny][nx]) return true;
            }
        }
    return false;
}

void Game::mergeTetromino(){
    const auto &shape=currentPiece->getShape();
    int x=currentPiece->getX(), y=currentPiece->getY();
    int color=currentPiece->getColorIndex();
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(shape[i][j] && y+i>=0) grid[y+i][x+j]=color+1;

    clearLines();
    spawnTetromino();
}

void Game::clearLines(){
    for(int i=GRID_HEIGHT-1;i>=0;i--){
        bool full=true;
        for(int j=0;j<GRID_WIDTH;j++) if(grid[i][j]==0){ full=false; break;}
        if(full){
            for(int k=i;k>0;k--)
                for(int j=0;j<GRID_WIDTH;j++)
                    grid[k][j]=grid[k-1][j];
            for(int j=0;j<GRID_WIDTH;j++) grid[0][j]=0;
            i++;
            score+=100;
            if(score%500==0 && fallSpeed>0.1f) fallSpeed-=0.05f;
        }
    }
}

void Game::moveLeft(){ if(!checkCollision(-1,0,0)) currentPiece->setX(currentPiece->getX()-1); }
void Game::moveRight(){ if(!checkCollision(1,0,0)) currentPiece->setX(currentPiece->getX()+1); }
void Game::moveDown(){ if(!checkCollision(0,1,0)) currentPiece->setY(currentPiece->getY()+1); else mergeTetromino();}
void Game::rotate(){ if(!checkCollision(0,0,1)) currentPiece->rotate(); }

void Game::draw(){
    ClearBackground(BG_COLOR);

    // Grid background
    DrawRectangle(0,0,GRID_WIDTH*BLOCK_SIZE,GRID_HEIGHT*BLOCK_SIZE,UI_BG_COLOR);
    // Grid lines
    for(int i=0;i<=GRID_HEIGHT;i++) DrawLine(0,i*BLOCK_SIZE,GRID_WIDTH*BLOCK_SIZE,i*BLOCK_SIZE,GRID_LINE_COLOR);
    for(int j=0;j<=GRID_WIDTH;j++) DrawLine(j*BLOCK_SIZE,0,j*BLOCK_SIZE,GRID_HEIGHT*BLOCK_SIZE,GRID_LINE_COLOR);

    // Draw placed blocks
    for(int i=0;i<GRID_HEIGHT;i++)
        for(int j=0;j<GRID_WIDTH;j++)
            if(grid[i][j]) DrawRectangle(j*BLOCK_SIZE,i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,COLORS[grid[i][j]-1]);

    // Draw current piece
    const auto &shape=currentPiece->getShape();
    int x=currentPiece->getX(), y=currentPiece->getY();
    int color=currentPiece->getColorIndex();
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(shape[i][j] && y+i>=0)
                DrawRectangle((x+j)*BLOCK_SIZE,(y+i)*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,COLORS[color]);

    // Next piece preview
    DrawText("Next:",GRID_WIDTH*BLOCK_SIZE+20,20,20,WHITE);
    const auto &nextShape=nextPiece->getShape();
    int nextColor=nextPiece->getColorIndex();
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(nextShape[i][j])
                DrawRectangle(GRID_WIDTH*BLOCK_SIZE+40+j*BLOCK_SIZE/2,50+i*BLOCK_SIZE/2,BLOCK_SIZE/2,BLOCK_SIZE/2,COLORS[nextColor]);

    // Score
    DrawText(TextFormat("Score: %d",score),GRID_WIDTH*BLOCK_SIZE+20,200,20,WHITE);

    // Game over screen
    if(gameOver){
        DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,Fade(BLACK,0.7f));
        DrawText("GAME OVER",SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-60,40,RED);
        DrawText("Press R to Retry",SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2,20,WHITE);
        DrawText("Press Q to Quit",SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2+30,20,WHITE);
    }
}
