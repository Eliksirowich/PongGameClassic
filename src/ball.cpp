#include "ball.h"
#include <iostream>
#include <string>
using namespace std;



Ball::Ball()

{
    ballX = 400;

    ball_speedX = 7;

    ball_speedY = 7;

    speedX_flagX = 0;

    speedY_flagY = 0;

    round_ball_flag = 0;

    gen = std::mt19937(12345);

    distrib = std::uniform_int_distribution<int>(0, 800);

    speedX = std::uniform_int_distribution<int>(3, 10);

    speedY = std::uniform_int_distribution<int>(3, 10);

    ball_speedX_random = std::uniform_int_distribution<int>(0, 1);
    
    ball_speedY_random = std::uniform_int_distribution<int>(0, 1);

    ballY = distrib(gen);


}


void Ball::Move()
{
    if (speedX_flagX == 1)
    {
        ballX += ball_speedX; 
    }
    else
    {
        ballX -= ball_speedX; 
    }

                
    if (speedY_flagY == 1)
    {
        ballY += ball_speedY; 
    }
    else
    {
        ballY -= ball_speedY; 
    }

}

void Ball::BallRandomRound()
{
    if (round_ball_flag==1 )
    {
        ballY=distrib(gen);

        speedX_flagX=ball_speedX_random(gen);

        speedY_flagY=ball_speedX_random(gen);

        ball_speedX=7;

        ball_speedY=7;

        round_ball_flag=0;

        ballX=400;
    }
}




  
        


