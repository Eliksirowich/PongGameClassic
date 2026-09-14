#include "gameplay.h"
#include<raylib.h>
#include<iostream>
#include "button.hpp"
#include "ball.h"
#include "paddle.h"
using namespace std;

Gameplay::Gameplay()
{
    pointsHero=0;

    pointsEnemy=0;

    hero_goal_flag = 0; 

    enemy_goal_flag = 0; 

    IsGameStarted=false;

    Enemy_Intelligence=true;

    IsGamePaused=false;

    exit=false;

    wallUp={0, (float)0, 800, 20};

    wallDown={0, (float)780, 800, 20};

    hero_football_goal={10, (float)20, 10, 760};
        
    enemy_football_goal={780, (float)20, 10, 760};

    paddle1.posX = 100;
    paddle2.posX = 680;

}

void Gameplay::InitGameplay()
{
    InitWindow(800,800,"Pong Classic");

    green={20,160,133,255};

    ImgMainMenu=LoadImage("Graphics/MainMenuPong.png");

    ImageResize(&ImgMainMenu,800,800);

    background=LoadTextureFromImage(ImgMainMenu);

    UnloadImage(ImgMainMenu);
    
    startButton.Init("Graphics/oneplayer.png", {300,150}, 0.65);

    twoplayersButton.Init("Graphics/twoplayers.png", {300,250}, 0.65);

    exitButton.Init("Graphics/exit.png", {300,400}, 0.62);

    exitPauseButton.Init("Graphics/exit.png", {300,450}, 0.62);

    continuePauseButton.Init("Graphics/continue.png", {300,350}, 0.62);

    restartPauseButton.Init("Graphics/restart.png", {300,250}, 0.62);

    mainmenuButton.Init("Graphics/mainmenu.png", {300,350}, 0.62);
}

void Gameplay::CheckCollisions()
{
    Vector2 ballPosition = {(float)ball.ballX, (float)ball.ballY};

    if (CheckCollisionCircleRec(ballPosition,10,{(float)paddle1.posX, (float)paddle1.RectangleY, 20, 80}))
    {
        ball.speedX_flagX = 1;
    }

    if (CheckCollisionCircleRec(ballPosition,10,{(float)paddle2.posX, (float)paddle2.RectangleY, 20, 80}))
    {
        ball.speedX_flagX = 0;
    }
    if (CheckCollisionCircleRec(ballPosition,10,wallUp))
    {
        ball.speedY_flagY = 1;
    }
    if (CheckCollisionCircleRec(ballPosition,10,wallDown))
    {
        ball.speedY_flagY = 0;
    }


    if (CheckCollisionCircleRec(ballPosition,10,hero_football_goal) && hero_goal_flag==0)
    {
        hero_goal_flag=1;
                    
        pointsEnemy+=1;

        ball.round_ball_flag=1;

        if (pointsEnemy==10)
        {
            IsGamePaused = true;
        }
                    
    }

        if (CheckCollisionCircleRec(ballPosition,10,hero_football_goal)==false && hero_goal_flag==1)
        {
            hero_goal_flag=0;                        
        }


        if (CheckCollisionCircleRec(ballPosition,10,enemy_football_goal) && enemy_goal_flag==0)
        {
            enemy_goal_flag=1;
                    
            pointsHero+=1;

            ball.round_ball_flag=1; 

            if (pointsHero==10)
            {
                IsGamePaused = true;
            }
                
        }

        if (CheckCollisionCircleRec(ballPosition,10,enemy_football_goal)==false && enemy_goal_flag==1)
        {
            enemy_goal_flag=0;                                 
        }
}


void Gameplay::CheckGoals(Vector2 mousePosition, bool mousePressed)

{
    if (IsGamePaused == true && pointsHero < 10 && pointsEnemy < 10)
    {           
        if (exitPauseButton.isPressed(mousePosition,mousePressed))
        {
            exit=true;
        }
              
        if (continuePauseButton.isPressed(mousePosition,mousePressed))         
        {
            IsGamePaused=false;
        }
        if (restartPauseButton.isPressed(mousePosition,mousePressed))
        {                 
            ball.ballX = 400; 

            pointsHero=0;

            pointsEnemy=0;

            ball.round_ball_flag = 1;

            IsGamePaused=false;            
        }
    }  
        
        if (pointsHero==10 || pointsEnemy==10)
        {
            if (restartPauseButton.isPressed(mousePosition,mousePressed))
            {
                ball.ballX = 400;       
                ball.ballY = 400;
                paddle1.RectangleY = 400; 
                paddle2.RectangleY = 400; 

                pointsHero=0;

                pointsEnemy=0;

                ball.round_ball_flag = 1;

                IsGameStarted = true;

                IsGamePaused = false;

            }
            
            

            if (exitPauseButton.isPressed(mousePosition,mousePressed))
            {
                exit=true;
            }

            


            if (mainmenuButton.isPressed(mousePosition,mousePressed))
            {
                IsGameStarted=false;

                IsGamePaused = false;

                pointsEnemy=0;

                pointsHero=0;
            }
            

        }
    
}
 
void Gameplay::Update()
{
    mousePosition=GetMousePosition();

    mousePressed= IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (IsGameStarted==false)
    {
            
        if (startButton.isPressed(mousePosition,mousePressed))
        {
            cout<<"start button pressed"<< endl;
                
            Enemy_Intelligence = true;
            IsGameStarted = true;
        }
        if (exitButton.isPressed(mousePosition,mousePressed))
        {
            exit=true;
        }
        if (twoplayersButton.isPressed(mousePosition,mousePressed))
        {
            Enemy_Intelligence = false;
            IsGameStarted = true;
        }
    }

    if (IsGameStarted==true)
    {
        if (IsKeyPressed(KEY_P))
        {
            IsGamePaused=true;        
        }
            
        
        if (IsGamePaused == false && pointsHero < 10 && pointsEnemy < 10)
        {
            paddle1.MovePlayerOne();

            ball.Move();

            ball.BallRandomRound();

            if (Enemy_Intelligence==true)
            {
                paddle2.MoveAI(ball.ballY);
            }

            else if (Enemy_Intelligence==false)
            {
                paddle2.MovePlayerTwo();
            }
                             
        }
    }
    CheckCollisions();

    CheckGoals(mousePosition, mousePressed);
}


void Gameplay::Draw()
{  
     ClearBackground(green);
    if (IsGameStarted == false)
    {
        

        DrawTexture(background,0,0,WHITE);

        startButton.Draw();

        exitButton.Draw();

        twoplayersButton.Draw();
    }
    
        if (IsGameStarted == true)
    {
        
        ball.Draw();

        paddle1.Draw();

        paddle2.Draw();

        DrawRectangle(0,0,800,20,RED);

        DrawRectangle(0, 780, 800, 20, RED);

        DrawRectangle(395, 20, 10, 760, WHITE);

        DrawRectangle(10, 20, 10, 760, WHITE);

        DrawRectangle(780, 20, 10, 760, WHITE);

        DrawText(TextFormat("%d:%d",pointsHero,pointsEnemy),50,50,40,WHITE);

        if (IsGamePaused == true && pointsHero < 10 && pointsEnemy < 10)
        {
            DrawRectangle(200, 200, 400, 400, MAROON);

            DrawRectangle(210, 210, 380, 380, DARKGREEN);
                    
            exitPauseButton.Draw(); 

            restartPauseButton.Draw();

            continuePauseButton.Draw();
        }

        
        if (pointsHero == 10 || pointsEnemy == 10)
        {
            DrawRectangle(0, 0, 800, 800, DARKGREEN); 

            if (pointsHero == 10)
            {
                DrawText(TextFormat("Player number 1 won!"),185,50,40,WHITE);
            }
            
            else if (pointsEnemy == 10)
            {
                DrawText(TextFormat("Player number 2 won!"),185,50,40,WHITE);
            }

            restartPauseButton.Draw()
            ; 
            exitPauseButton.Draw();

            mainmenuButton.Draw(); 
        }
    }


}       