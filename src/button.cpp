#include "button.hpp"

button::button(const char *imagePath, Vector2 imagePosition, float scale)
{
    Image image =LoadImage(imagePath);
    int originalWidth = image.width;
    int originalHight=image.height;
    int newWidth=static_cast<int>(originalWidth * scale);
    int newHight=static_cast<int>(originalHight * scale);
    ImageResize(&image,newWidth,newHight);
    texture=LoadTextureFromImage(image);
    UnloadImage(image);
    position=imagePosition;
}
button::~button()
{
    UnloadTexture(texture);
}
void button::Draw()
{
    DrawTextureV(texture, position,WHITE);
}

bool button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rec ={position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if (CheckCollisionPointRec(mousePos,rec)&& mousePressed)
    {
        return true;
    }
    return false;
    
}
