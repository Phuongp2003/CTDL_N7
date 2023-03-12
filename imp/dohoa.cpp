#include "../header/dohoa.h"

using namespace std;

char *intTochar(int number)
{
    string str = to_string(number);
    char *result = &str[0];
    return result;
}

void CreateScreen()
{
    Font ARIAL_font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 30, 0, 250);

    char name[120] = "\0";
    char name_cpy[120] = "\0";
    bool mouseOnText = false;
    int letterCount = 0;
    int framesCounter = 0;
    int indexPoint = 0;
    Rectangle textBox = {300, 300, 700, 56};
    Vector2 textBoxPos = {textBox.x + 5, textBox.y + 8};
    Vector2 textBoxPos2 = {textBox.x + 5, textBox.y + 8 + 50};
    while (!WindowShouldClose())
    {
        strcpy(name_cpy, name);
        name_cpy[letterCount + indexPoint] = '\0';
        Vector2 textBoxDot = {textBox.x + MeasureTextEx(ARIAL_font, name_cpy, 30, 0).x, textBox.y + 8};
        if (CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            mouseOnText = true;
        else if (IsKeyPressed(KEY_ENTER))
            mouseOnText = false;

        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (mouseOnText)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 27))
                {
                    for (int i = letterCount; i > letterCount + indexPoint; i--)
                    {
                        name[i] = name[i - 1];
                    }
                    name[letterCount + indexPoint] = char(key);
                    name[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }
            while (IsKeyDown(KEY_BACKSPACE) && letterCount + indexPoint > 0)
            {
                for (int i = letterCount + indexPoint - 1; i < letterCount; i++)
                {
                    name[i] = name[i + 1];
                }
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                name[letterCount] = '\0';
                if (IsKeyUp(KEY_BACKSPACE))
                    break;
            }
            if (IsKeyPressed(KEY_LEFT) && (letterCount + indexPoint) > 0)
            {
                indexPoint--;
            }
            if (IsKeyPressed(KEY_RIGHT) && indexPoint < 0)
            {
                indexPoint++;
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 80, 1280, 680, DARKBLUE);
        DrawRectangleRec(textBox, GRAY);
        DrawTextEx(ARIAL_font, name, textBoxPos, 30, 0, BLACK);
        // cout << "index: " << indexPoint << endl;
        if (mouseOnText && (((framesCounter / 300) % 2) == 0))
            DrawTextEx(ARIAL_font, "|", textBoxDot, 30, 0, MAROON);

        EndDrawing();
    }
}

void CreateRec(int width, int height)
{
}