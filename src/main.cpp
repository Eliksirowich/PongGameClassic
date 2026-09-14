#if defined(_WIN32) && defined(NDEBUG)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#include<raylib.h>
#include<iostream>
#include<random>
#include "button.hpp"
#include "ball.h"
#include "ball.cpp"
#include "paddle.h"
#include "paddle.cpp"
#include"gameplay.h" 
#include"gameplay.cpp" 
using namespace std;

int main()
{
    Gameplay game;
   
    game.InitGameplay(); 
    
    SetTargetFPS(60); 

    while (WindowShouldClose()==false && game.exit==false)
    {
        game.Update();

        BeginDrawing();   

        game.Draw();   

        EndDrawing();
    }

    CloseWindow();

    return 0;
}





