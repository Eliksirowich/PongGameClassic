#pragma once

#include<raylib.h>
class Paddle
{

public:
    int RectangleY;

    int posX;

    Paddle() {}


    Paddle(int posX);

    void MovePlayerOne();

    void MovePlayerTwo();

    void MoveAI(int ballY);

    void Draw();
};



