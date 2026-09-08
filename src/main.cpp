#if defined(_WIN32) && defined(NDEBUG)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif



#include<raylib.h>
#include<iostream>
#include<random>
#include "button.hpp"
using namespace std;


int round_ball_flag=0;



void random_rounf(int &ballY, int &speedX_flagX , int &speedY_flagY, int &ball_speedX, int &ball_speedY, int &round_ball_flag, int &ballX ,random_device &rd,mt19937 &gen,uniform_int_distribution<int>& distrib,
    uniform_int_distribution<int>& speedX,uniform_int_distribution<int>& speedY, uniform_int_distribution<int>& ball_speedX_random,uniform_int_distribution<int>& ball_speedY_random)  
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
int main()
{
    int RectangleY=400;
    int RectangleTwoY=400;
    InitWindow(800,800,"Pong Classic");
    Color green={20,160,133,255};
    int ballX=400;
    int ballY;
    int ball_speedX=7;
    int ball_speedY=7;
    int speedX_flagX=0;
    int speedY_flagY=0;
    int pointsHero=0;
    int pointsEnemy=0;
    int hero_goal_flag = 0;     
    int enemy_goal_flag = 0;    
    bool IsGameStarted=false;
    bool Enemy_Intelligence=true;
    bool IsGamePaused=false;
    Vector2 ballPosition;
    
    Rectangle paddle1;
    Rectangle paddle2;
    Rectangle wallUp={0, (float)0, 800, 20};
    Rectangle wallDown={0, (float)780, 800, 20};
    Rectangle hero_football_goal={10, (float)20, 10, 760};
    Rectangle enemy_football_goal={780, (float)20, 10, 760};
    SetTargetFPS(60);

    Image ImgMainMenu=LoadImage("Graphics/MainMenuPong.png");
    ImageResize(&ImgMainMenu,800,800);
    Texture2D background=LoadTextureFromImage(ImgMainMenu);
    
    button startButton {"Graphics/oneplayer.png",{300,150},0.65};
    button twoplayersButton{"Graphics/twoplayers.png",{300,250},0.65};

    button exitButton {"Graphics/exit.png",{300,400},0.62};

    button exitPauseButton {"Graphics/exit.png",{300,450},0.62};
    button continuePauseButton {"Graphics/continue.png",{300,350},0.62};
    button restartPauseButton {"Graphics/restart.png",{300,250},0.62};
    button mainmenuButton {"Graphics/mainmenu.png",{300,350},0.62};
    
    random_device rd;
    mt19937 gen(12345);
    uniform_int_distribution<int>distrib(0,800);
    uniform_int_distribution<int>speedX(3, 10);
    uniform_int_distribution<int>speedY(3, 10);
    uniform_int_distribution<int>ball_speedX_random(0,1);
    uniform_int_distribution<int>ball_speedY_random(0,1);
    
    
    
        ballY=distrib(gen);
        speedX_flagX=ball_speedX_random(gen);
        speedY_flagY=ball_speedX_random(gen);
        ball_speedX=speedX(gen);
        ball_speedY=speedY(gen);
        //round_ball_flag=1;

    
    
    bool exit=false;
    
   
    while (WindowShouldClose()==false && exit==false)
    {
        Vector2 mousePosition=GetMousePosition();
        bool mousePressed= IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        BeginDrawing();
        if (IsGameStarted==false)
        {
            
            ClearBackground(green);
            DrawTexture(background,0,0,WHITE);
            startButton.Draw();
            exitButton.Draw();
            twoplayersButton.Draw();
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
            
            ClearBackground(green);
            if (IsGamePaused==false)
            {
                    if (IsKeyDown(KEY_S)&& (RectangleY+100 <800 ) )
                {
                    RectangleY+=10; 
                }else if(IsKeyDown(KEY_W)&& (RectangleY>=30 )){
                    RectangleY-=10;
                }
                
                

                // 1. ДВИЖЕНИЕ ПО ГОРИЗОНТАЛИ (X)
                if (speedX_flagX == 1)
                {
                    ballX += ball_speedX; // летит вправо
                }
                else
                {
                    ballX -= ball_speedX; // летит влево
                }

                // 2. ДВИЖЕНИЕ ПО ВЕРТИКАЛИ (Y)
                if (speedY_flagY == 1)
                {
                    ballY += ball_speedY; // летит вниз
                }
                else
                {
                    ballY -= ball_speedY; // летит вверх
                }



                random_rounf(ballY, speedX_flagX , speedY_flagY,ball_speedX, ball_speedY, round_ball_flag, ballX ,rd,gen,distrib,speedX,speedY, ball_speedX_random, ball_speedY_random);

                
                ballPosition={(float)ballX,(float)ballY};
                paddle1 = {100, (float)RectangleY, 20, 80};
                paddle2 = {600, (float)RectangleTwoY, 20, 80};
                if (CheckCollisionCircleRec(ballPosition,10,paddle1))
                {
                    speedX_flagX = 1;
                    //ball_speedY=-ball_speedY;
                }

                if (CheckCollisionCircleRec(ballPosition,10,paddle2))
                {
                    speedX_flagX = 0;
                // ball_speedY=-ball_speedY;
                }
                if (CheckCollisionCircleRec(ballPosition,10,wallUp))
                {
                // ball_speedX=-ball_speedX;
                    speedY_flagY = 1;
                }
                if (CheckCollisionCircleRec(ballPosition,10,wallDown))
                {
                // ball_speedX=-ball_speedX;
                    speedY_flagY = 0;
                }
            // ballX += 1+ball_speedX;
                //ballY +=1+ ball_speedY;   
                
                if (Enemy_Intelligence==true)
                {
                    if ( (RectangleTwoY+100 <800)&& (ballY>RectangleTwoY) )
                    {
                        RectangleTwoY+=5;
                    }else if((RectangleTwoY>=30)&&(ballY<RectangleTwoY) ){
                        RectangleTwoY=ballY;
                    }
                }
                else if (Enemy_Intelligence==false)
                {
                    if (IsKeyDown(KEY_DOWN)&& (RectangleTwoY+100 <800 ) )
                    {
                        RectangleTwoY+=10; 
                    }else if(IsKeyDown(KEY_UP)&& (RectangleTwoY>=30 )){
                        RectangleTwoY-=10;
                    }
                }
                
                
                



                if (CheckCollisionCircleRec(ballPosition,10,hero_football_goal) && hero_goal_flag==0)
                {
                    hero_goal_flag=1;
                    
                    pointsEnemy+=1;
                    round_ball_flag=1;
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
                    round_ball_flag=1; 

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
            
            
            
            
           

            
            
            DrawCircle(ballX,ballY,10,WHITE);
            DrawRectangle(100,RectangleY,20,80,RED);
            DrawRectangle(600,RectangleTwoY,20,80,RED);
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
                if (exitPauseButton.isPressed(mousePosition,mousePressed))
                {
                    exit=true;
                }
                continuePauseButton.Draw();
                if (continuePauseButton.isPressed(mousePosition,mousePressed))
                {
                    IsGamePaused=false;
                }

                restartPauseButton.Draw();
                if (restartPauseButton.isPressed(mousePosition,mousePressed))
                {
                    RectangleY = 400;     
                    RectangleTwoY = 400;  
                    ballX = 400;          
                    pointsHero=0;
                    pointsEnemy=0;
                    round_ball_flag = 1;
                    IsGamePaused=false;
                    

                }
                
                

            }
            
        }
        if (pointsHero==10 || pointsEnemy==10)
        {
            
            DrawRectangle(0, 0, 800, 800, DARKGREEN);
            if (pointsHero==10)
            {
                DrawText(TextFormat("Player number 1 won!"),185,50,40,WHITE);
            }
            else if (pointsEnemy==10)
            {
                DrawText(TextFormat("Player number 2 won!"),185,50,40,WHITE);
            }
            restartPauseButton.Draw();
            if (restartPauseButton.isPressed(mousePosition,mousePressed))
            {
                RectangleY = 400;     
                RectangleTwoY = 400;  
                ballX = 400;          
                pointsHero=0;
                pointsEnemy=0;
                round_ball_flag = 1;
                IsGameStarted = true;
                IsGamePaused = false;

            }
            exitPauseButton.Draw();
            if (exitPauseButton.isPressed(mousePosition,mousePressed))
            {
                exit=true;
            }
            mainmenuButton.Draw();
            if (mainmenuButton.isPressed(mousePosition,mousePressed))
            {
                IsGameStarted=false;
                IsGamePaused = false;
                pointsEnemy=0;
                pointsHero=0;
            }
            

        }
        
        
        
        
        EndDrawing();

    }
    
    CloseWindow();
    return 0;
}





// hero_goal_flag = 0;     
// enemy_goal_flag = 0;