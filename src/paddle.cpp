#include "paddle.h"
#include <raylib.h>

using namespace std;

Paddle::Paddle(int posX)
{
    this->posX=posX;

    RectangleY=400;
}

void Paddle::MovePlayerOne()
{
    if (IsKeyDown(KEY_S)&& (RectangleY+100 <800 ) )
    {
        RectangleY+=10; 

    }
    else if(IsKeyDown(KEY_W)&& (RectangleY>=30 )){
        RectangleY-=10;
    }
}

void Paddle::MovePlayerTwo()
{
    if (IsKeyDown(KEY_DOWN)&& (RectangleY+100 <800 ) )
    {
        RectangleY+=10; 
    }
    else if(IsKeyDown(KEY_UP)&& (RectangleY>=30 ))
    {
        RectangleY-=10;
    }
}

void Paddle::MoveAI(int ballY)
{
    
    if ((RectangleY + 100 < 800) && (ballY > RectangleY + 40))
    {
        RectangleY += 6; 
    }
    else if ((RectangleY >= 30) && (ballY < RectangleY + 40))
    {
        RectangleY -= 6; 
    }
}

void Paddle::Draw()
{
    DrawRectangle(posX,RectangleY,20,80,RED);
}