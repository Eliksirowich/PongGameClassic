#pragma once

#include<raylib.h>
#include<iostream>
#include "button.hpp"
#include "ball.h"
#include "paddle.h"

class Gameplay
{

    public:

        int pointsHero;

        int pointsEnemy;

        int hero_goal_flag ; 

        int enemy_goal_flag ; 

        bool IsGameStarted;

        bool Enemy_Intelligence;

        bool IsGamePaused;

        bool exit;

        

        Rectangle wallUp;

        Rectangle wallDown;

        Rectangle hero_football_goal;

        Rectangle enemy_football_goal;

        Color green;

        Vector2 ballPosition;

        Image ImgMainMenu;

        Texture2D background;
    
        button startButton;

        button twoplayersButton;

        button exitButton;

        button exitPauseButton ;

        button continuePauseButton ;

        button restartPauseButton ;

        button mainmenuButton ;

        Ball ball;

        Paddle paddle1;

        Paddle paddle2;

        Vector2 mousePosition;

        bool mousePressed;

        Gameplay();

        void InitGameplay();

        void CheckCollisions();

        void CheckGoals(Vector2 mousePosition, bool mousePressed);

        void Update();

        void Draw();

};


