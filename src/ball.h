#pragma once
#include<raylib.h>
#include<random>

class Ball
{
    
        

    public:
    
        int ballX=400;

        int ballY;

        int ball_speedX=7;

        int ball_speedY=7;

        int speedX_flagX=0;
        
        int speedY_flagY=0;

        int round_ball_flag=0;

        std::random_device rd;

        std::mt19937 gen;

        std::uniform_int_distribution<int> distrib;

        std::uniform_int_distribution<int> speedX;

        std::uniform_int_distribution<int> speedY;

        std::uniform_int_distribution<int> ball_speedX_random;

        std::uniform_int_distribution<int> ball_speedY_random;






        Ball();

        void Move();

        void BallRandomRound();

        void Draw();
};