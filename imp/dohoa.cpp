#include "../header/dohoa.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

float per1000(int number)
{
    return (float)number / 1000;
}

char *intTochar(int number)
{
    string str = to_string(number);
    char *result = &str[0];
    return result;
}

void SetSizeWindow()
{
    int display = GetCurrentMonitor();

    int MONITOR_WIDTH = GetMonitorWidth(display), MONITOR_HEIGHT = GetMonitorHeight(display);
    if (IsWindowMaximized())
        return;
    int W, H;
    if (MONITOR_WIDTH < 1000 || MONITOR_HEIGHT <= 720)
    {
        W = 700;
        H = 400;
    }
    if (MONITOR_WIDTH <= 1280 || MONITOR_HEIGHT <= 800)
    {
        W = 1000;
        H = 600;
    }
    if (MONITOR_WIDTH > 1280)
    {
        W = 1280;
        if (MONITOR_HEIGHT > 800)
            H = 720;
        else
            H = 600;
    }
    if (MONITOR_WIDTH > 1700)
    {
        W = 1530;
        H = 795;
    }
    SetWindowSize(W, H);
    SetWindowPosition(120, 75);
}

Vector2 GetVMousePosition()
{
    float scaleW = (float)GetScreenWidth() / WINDOW_WIDTH, scaleH = (float)GetScreenHeight() / WINDOW_HEIGHT;

    Vector2 mouse = GetMousePosition();

    Vector2 virtualMouse = {0};
    virtualMouse.x = (mouse.x - (GetScreenWidth() - (WINDOW_WIDTH * scaleW)) * 0.5f) / scaleW;
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (WINDOW_HEIGHT * scaleH)) * 0.5f) / scaleH;
    virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0, 0}, (Vector2){(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT});
    return virtualMouse;
}

bool CreateButton(float pos_x, float pos_y, float width, float height, char *titlle, Font font)
{
    Rectangle Button = {pos_x, pos_y, width, height};
    Vector2 MousePos = {0.0f, 0.0f};
    Vector2 TextPos = {(width / 2.0f) + pos_x - (MeasureTextEx(font, titlle, height / 2.0f, 0).x / 2.0f), height / 5.0f + pos_y};
    Color isHovered = {153, 255, 153, 255};
    Color isnotHovered = {153, 255, 153, 200};
    Color isPressed = {4, 0, 255, 255};
    int btnState = 0;
    bool btnAction = false;
    DrawRectangleRec(Button, isnotHovered);
    DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BLACK);
    MousePos = GetVMousePosition();

    if (CheckCollisionPointRec(MousePos, Button))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(Button, isPressed);
            DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, WHITE);
        }
        else
        {
            DrawRectangleRec(Button, isHovered);
            DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BLACK);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            return true;
        else
            return false;
    }
    return false;
}

void CreateHomePage()
{
    const int png_screen_w = 698;
    const int split_screen_w = 4;
    const int button_screen_w = 798;
    const int home_tittle_h = 60;
    const int button_tittle = 80;

    const float empty_space_left = per1000(10) * WINDOW_WIDTH;
    const float empty_space_top = per1000(40) * WINDOW_HEIGHT;

    Font ARIAL_font = LoadFontEx("../src/font/arial.ttf", 50, 0, 250);
    Font Futura = LoadFontEx("../src/font/Futura_Light_Italic.ttf", 50, 0, 250);
    Image LogoPTIT = LoadImage("../src/img/Logo_PTIT_University.png"); // load ảnh

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetWindowMinSize(700, 400);
    SetSizeWindow();
    // Màn hình trình bày chính
    Rectangle mainScreen = {per1000(10) * WINDOW_WIDTH,
                            per1000(40) * WINDOW_HEIGHT + home_tittle_h,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT - home_tittle_h};
    // Thanh chia màn hình
    Rectangle splitScreen = {per1000(10) * WINDOW_WIDTH + png_screen_w,
                             per1000(40) * WINDOW_HEIGHT + home_tittle_h,
                             split_screen_w,
                             SCREEN_HEIGHT - home_tittle_h};
    // Màn hình chứa ảnh
    Rectangle pngScreen = {per1000(10) * WINDOW_WIDTH,
                           per1000(40) * WINDOW_HEIGHT + home_tittle_h,
                           png_screen_w,
                           SCREEN_HEIGHT - home_tittle_h};
    // Màn hình chứa nút chọn chức năng
    Rectangle buttonScreen = {per1000(10) * WINDOW_WIDTH + png_screen_w + split_screen_w,
                              per1000(40) * WINDOW_HEIGHT + home_tittle_h + button_tittle,
                              button_screen_w,
                              SCREEN_HEIGHT - home_tittle_h - button_tittle};

    // Rectangle

    // Vị trí tiêu đề
    Vector2 tittleHomePos = {200, 10};
    Vector2 pngPos = {pngScreen.x, pngScreen.y};

    ImageResize(&LogoPTIT, pngScreen.width, pngScreen.height); // Chỉnh size ảnh

    RenderTexture2D renderTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT); // Load nội dung màn hình như một ảnh

    Texture2D PNG_logo = LoadTextureFromImage(LogoPTIT); // Load ảnh vào biến (ram)
    while (!WindowShouldClose())
    {
        // tạo màn hình theo chỉ số tĩnh
        BeginTextureMode(renderTexture);
        ClearBackground(DARKBLUE);
        DrawRectangleRec(mainScreen, WHITE);
        DrawTexture(PNG_logo, pngScreen.x, pngScreen.y, RED);
        DrawRectangleRec(splitScreen, GRAY);
        DrawTextEx(ARIAL_font, "DO AN QUAN LY MAY BAY - NHOM 7", tittleHomePos, 50, 0, BLACK);
        DrawTextureEx(PNG_logo, pngPos, 0, 1, WHITE);
        // DrawRectangleRec(buttonScreen, BLUE);
        if (CreateButton(buttonScreen.x + 40, buttonScreen.y + 30, buttonScreen.width / 2, buttonScreen.height / 10, "QUAN LY VE MAY BAY", ARIAL_font))
            cout << "Button is pressed" << endl;
        EndTextureMode();
        cout << buttonScreen.x + 40 << " " << buttonScreen.y + 30 << " " << buttonScreen.x + 40 + buttonScreen.width / 2 << " " << buttonScreen.y + 30 + buttonScreen.height / 10 << " / "
             << GetMouseX() << " " << GetMouseY() << endl;
        BeginDrawing();
        // xuất màn hình tĩnh theo chỉ sô động6
        DrawTexturePro(
            renderTexture.texture,
            Rectangle{0, 0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height)},
            Rectangle{0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
            Vector2{0, 0},
            0,
            WHITE);
        EndDrawing();
    }
    UnloadFont(ARIAL_font);
}

// Chưa hoàn chỉnh
//----------------------------------------------------------------
void CreateTextInputBox()
{
    Font ARIAL_font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 200, 0, 250);
    Font Futura = LoadFontEx("../src/font/Futura_Light_Italic.ttf", 200, 0, 250);

    char name[120] = "\0";
    char name_cpy[120] = "\0";
    bool mouseOnText = false;
    int letterCount = 0;
    int framesCounter = 0;
    int fHold_BS = 0, fHold_RIGHT = 0, fHold_LEFT = 0;
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
            if (IsKeyDown(KEY_BACKSPACE))
                fHold_BS++;
            else
                fHold_BS = 0;
            if (IsKeyDown(KEY_RIGHT))
                fHold_RIGHT++;
            else
                fHold_RIGHT = 0;
            if (IsKeyDown(KEY_LEFT))
                fHold_LEFT++;
            else
                fHold_LEFT = 0;
            if ((IsKeyDown(KEY_BACKSPACE) && letterCount + indexPoint > 0 && (fHold_BS > 200) && (fHold_BS % 20 == 0)) ||
                IsKeyPressed(KEY_BACKSPACE) && letterCount + indexPoint > 0)
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
            if ((IsKeyDown(KEY_LEFT) && (letterCount + indexPoint) > 0 && (fHold_LEFT > 200) && (fHold_LEFT % 50 == 0)) ||
                (IsKeyPressed(KEY_LEFT) && (letterCount + indexPoint) > 0))
            {
                indexPoint--;
            }
            if ((IsKeyDown(KEY_RIGHT) && indexPoint < 0 && (fHold_RIGHT > 200) && (fHold_RIGHT % 50 == 0)) ||
                (IsKeyPressed(KEY_RIGHT) && indexPoint < 0))
            {
                indexPoint++;
            }
        }
        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 80, 1280, 680, DARKBLUE);
        DrawRectangleRec(textBox, GRAY);
        DrawTextEx(Futura, name, textBoxPos, 30, 0, BLACK);
        // cout << "index: " << indexPoint << endl;
        if (mouseOnText && ((framesCounter % 300 >= 120)))
            DrawTextEx(ARIAL_font, "|", textBoxDot, 30, 0, MAROON);

        EndDrawing();
    }
}