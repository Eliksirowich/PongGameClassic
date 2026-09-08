#pragma once
#include <raylib.h>
class button
{
private:
    Texture2D texture;
    Vector2 position;
public:
    button(const char* imagePath, Vector2 imagePosition, float scale);
    ~button();
    void Draw();
    bool isPressed(Vector2 mousePos, bool mousePressed);
};

