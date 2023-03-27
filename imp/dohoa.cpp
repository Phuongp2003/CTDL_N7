#include "../header/dohoa.h"

//==================================================================================================================================
// Define

struct BoMauNut
{
    Color isnotHovered;
    Color isHovered;
    Color isPressed;
    Color text1;
    Color text2;
    Color Rounder;
};

BoMauNut HomeButtonColor{
    {153, 255, 153, 255},
    {80, 255, 80, 255},
    {50, 50, 255, 255},
    BLACK,
    WHITE,
    GREEN};

BoMauNut MauThanhQuanLy{
    {87, 87, 255, 255},
    {25, 25, 255, 255},
    {253, 255, 133, 255},
    WHITE,
    BLACK,
    {25, 25, 255, 255},

};

//==================================================================================================================================
// Setup
/**
 * @brief vị trí con trỏ trỏ đến trang hiển thị
 * @note 0. Trang chủ\n
 * @note 1. Máy bay
 * @note 2. Chuyến bay
 * @note 3. Vé
 * @note 4. Hành khách
 * @note 5. Giới thiệu
 */
int current_page = 0;

Vector2 StartPos{per1000(10) * SCREEN_WIDTH, per1000(40) * SCREEN_HEIGHT};

Font FontArial;
Image LogoPTIT;
Texture2D PNG_logo; // Load ảnh vào biến (ram)
Image HomeIcon;
Texture2D PNG_home;

void LoadResources()
{
    FontArial = LoadFontEx("../src/font/arial.ttf", 50, 0, 9812);

    LogoPTIT = LoadImage("../src/img/Logo_PTIT_University.png"); // load ảnh
    ImageResize(&LogoPTIT, 698, 690);                            // Chỉnh size ảnh
    PNG_logo = LoadTextureFromImage(LogoPTIT);

    HomeIcon = LoadImage("../src/img/house_icon.png");
    ImageResize(&HomeIcon, 60, 50);
    PNG_home = LoadTextureFromImage(HomeIcon);
}

void UnloadResources()
{
    UnloadFont(FontArial);

    UnloadImage(LogoPTIT);
    UnloadImage(HomeIcon);

    UnloadTexture(PNG_logo);
    UnloadTexture(PNG_home);
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
    SetWindowPosition(50, 50);
}

//==================================================================================================================================
// Graphics

//---Home page----------------------------------------------------------------------------------------------------------------------
void CreateHomeBackground()
{
    ClearBackground(DARKBLUE);
    const int home_tittle_h = 60;
    Rectangle mainScreen = {StartPos.x,
                            StartPos.y + home_tittle_h,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT - home_tittle_h};
    DrawRectangleRec(mainScreen, WHITE);
}

void CreateHomePage()
{
    const int png_screen_w = 698;
    const int split_screen_w = 4;
    const int button_screen_w = 798;
    const int home_tittle_h = 60;
    const int button_tittle = 80;
    const int button_tittle_margin_top = 50;
    const int button_tittle_margin_bot = 10;
    const int button_margin_topbot = 20;
    const int button_width = 600;
    const int button_height = 60;
    const int empty_space_button_screen_left = 98;

    // Màn hình chứa ảnh
    Rectangle pngScreen = {StartPos.x,
                           StartPos.y + home_tittle_h,
                           png_screen_w,
                           SCREEN_HEIGHT - home_tittle_h};
    // Thanh chia màn hình
    Rectangle splitScreen = {pngScreen.x + png_screen_w,
                             pngScreen.y,
                             split_screen_w,
                             SCREEN_HEIGHT - home_tittle_h};
    // Màn hình chứa nút chọn chức năng
    Rectangle buttonScreen = {splitScreen.x + splitScreen.width,
                              splitScreen.y,
                              button_screen_w,
                              SCREEN_HEIGHT - home_tittle_h};

    // Tiêu dề
    const char *home_tittle = "ĐỒ ÁN QUẢN LÝ MÁY BAY - NHÓM 7 - KHOÁ D21",
               *button_tille = "CÁC CHỨC NĂNG",
               *button1_tittle = "QUẢN LÝ MÁY BAY",
               *button2_tittle = "QUẢN LÝ CHUYẾN BAY",
               *button3_tittle = "QUẢN LÝ VÉ",
               *button4_tittle = "QUẢN LÝ HÀNH KHÁCH",
               *button5_tittle = "GIỚI THIỆU VỀ SẢN PHẨM";

    // Vị trí tiêu đề
    Vector2 tittleHomePos =
        {CenterDataSetter(SCREEN_WIDTH, StartPos.x, MeasureTextEx(FontArial, home_tittle, 50, 0).x),
         StartPos.y};
    Vector2 tittleButtonPos =
        {CenterDataSetter(button_screen_w, buttonScreen.x, MeasureTextEx(FontArial, button_tille, 40, 0).x),
         buttonScreen.y + button_tittle_margin_top};

    // Vị trí ảnh
    Vector2 pngPos = {pngScreen.x, pngScreen.y};
    Vector2 buttonPos[5] =
        {
            {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
             tittleButtonPos.y + button_tittle + button_tittle_margin_bot + button_margin_topbot},
            {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
             buttonPos[0].y + button_height + button_margin_topbot * 2},
            {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
             buttonPos[1].y + button_height + button_margin_topbot * 2},
            {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
             buttonPos[2].y + button_height + button_margin_topbot * 2},
            {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
             buttonPos[3].y + button_height + button_margin_topbot * 2}

        };

    // tạo màn hình theo chỉ số tĩnh
    {
        CreateHomeBackground();
        DrawTexture(PNG_logo, pngScreen.x, pngScreen.y, RED);
        DrawRectangleRec(splitScreen, GRAY);
        DrawTextEx(FontArial, home_tittle, tittleHomePos, 50, 0, RED);
        DrawTextEx(FontArial, button_tille, tittleButtonPos, 40, 0, BLUE);

        DrawTextureEx(PNG_logo, pngPos, 0, 1, WHITE);
        // DrawRectangleRec(buttonScreen, BLUE);
        if (CreateButton(buttonPos[0].x, buttonPos[0].y, button_width, button_height, true, button1_tittle, FontArial, HomeButtonColor))
            current_page = 1;
        if (CreateButton(buttonPos[1].x, buttonPos[1].y, button_width, button_height, true, button2_tittle, FontArial, HomeButtonColor))
            current_page = 2;
        if (CreateButton(buttonPos[2].x, buttonPos[2].y, button_width, button_height, true, button3_tittle, FontArial, HomeButtonColor))
            current_page = 3;
        if (CreateButton(buttonPos[3].x, buttonPos[3].y, button_width, button_height, true, button4_tittle, FontArial, HomeButtonColor))
            current_page = 4;
        if (CreateButton(buttonPos[4].x, buttonPos[4].y, button_width, button_height, true, button5_tittle, FontArial, HomeButtonColor))
            current_page = 5;
    }
}

// ---Các trang thành phần----------------------------------------------------------------------------------------------------------
void CreatePageBackground()
{
    ClearBackground(DARKBLUE);
    const int home_tittle_h = 60;
    Rectangle mainScreen = {StartPos.x,
                            StartPos.y + home_tittle_h,
                            SCREEN_WIDTH - 1,
                            SCREEN_HEIGHT - home_tittle_h};
    Rectangle splitScreen = {mainScreen.x + 1199,
                             mainScreen.y,
                             2, // dày 2
                             SCREEN_HEIGHT - home_tittle_h};
    DrawRectangleRec(mainScreen, WHITE);
    DrawRectangleRec(splitScreen, BLACK);
}

// =-MayBay
void CreatePage_QLMB()
{
    CreatePageBackground();
    CreateTable_QLMB();
}

void CreateTable_QLMB()
{
    DrawTextEx(FontArial, "DANH SÁCH MÁY BAY", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);
    float cellW[5] = {100, 300, 380, 150, 150};
    CreateTable(5, cellW);
}

// =-ChuyenBay

void CreatePage_QLCB()
{
    CreatePageBackground();
    const char *test = CreateTextInputBox();
    char hello[27] = "\0";
    strcpy(hello, test);
    if (hello[0] != '\0')
        cout << hello << endl;
    // CreateTable();
}

void CreatePage_QLVe()
{
    CreatePageBackground();
    // CreateTable();
}
void CreatePage_QLHK()
{
    CreatePageBackground();
    // CreateTable();
}

void CreatePage_GioiThieu()
{
    CreatePageBackground();
}

/**
 * @brief Create a Table object
 *
 * @param cellW tổng các phần tử phải bằng 1080
 *
 * @note Số hàng luôn bằng 10, chiều cao ô luôn là 40, ô tiêu đề là 50
 */
void CreateTable(int soCot, float cellW[])
{
    const int empty_spaces_left = 60;
    const int empty_spaces_top = 60 + 100 + 80;
    const int firstLineH = 50;
    const int lineH = 40;
    const int total_table_w = 1080;

    Vector2 Point_row[2][soCot + 1];
    Point_row[0][0] = {StartPos.x + empty_spaces_left, StartPos.y + empty_spaces_top};
    Point_row[1][0] = {StartPos.x + empty_spaces_left, StartPos.y + empty_spaces_top + firstLineH + lineH * 10};
    DrawLineEx(Point_row[0][0], Point_row[1][0], 2, BROWN);

    for (int i = 1; i <= soCot + 1; i++)
    {
        Point_row[0][i] = {Point_row[0][i - 1].x + cellW[i - 1], Point_row[0][0].y};
        Point_row[1][i] = {Point_row[1][i - 1].x + cellW[i - 1], Point_row[1][0].y};
        DrawLineEx(Point_row[0][i], Point_row[1][i], 2, BROWN);
    }

    Vector2 Point_line[11][2];
    Point_line[0][0] = {StartPos.x + empty_spaces_left, StartPos.y + empty_spaces_top};
    Point_line[0][1] = {StartPos.x + empty_spaces_left + total_table_w, StartPos.y + empty_spaces_top};

    DrawLineEx(Point_line[0][0], Point_line[0][1], 2, BROWN);

    Point_line[1][0] = {Point_line[0][0].x, Point_line[0][0].y + firstLineH};
    Point_line[1][1] = {Point_line[0][1].x, Point_line[0][1].y + firstLineH};

    DrawLineEx(Point_line[1][0], Point_line[1][1], 2, BROWN);

    for (int i = 2; i <= 11; i++)
    {
        Point_line[i][0] = {Point_line[0][0].x, Point_line[i - 1][0].y + lineH};
        Point_line[i][1] = {Point_line[0][1].x, Point_line[i - 1][1].y + lineH};
        DrawLineEx(Point_line[i][0], Point_line[i][1], 2, BROWN);
    }
}

void ThanhQuanLy()
{
    const int button_width = 360;
    const int button_height = 50;

    const char
        *button1_tittle = "QUẢN LÝ MÁY BAY",
        *button2_tittle = "QUẢN LÝ CHUYẾN BAY",
        *button3_tittle = "QUẢN LÝ VÉ",
        *button4_tittle = "QUẢN LÝ HÀNH KHÁCH";

    Vector2 buttonPos[6] =
        {
            {StartPos.x, StartPos.y},
            {buttonPos[0].x + 60, StartPos.y},
            {buttonPos[1].x + button_width, StartPos.y},
            {buttonPos[2].x + button_width, StartPos.y},
            {buttonPos[3].x + button_width, StartPos.y}};
    if (CreateButtonWithPicture(buttonPos[0].x, buttonPos[0].y, 60, button_height, false, PNG_home, MauThanhQuanLy))
        current_page = 0;
    if (current_page != 1)
    {
        if (CreateButton(buttonPos[1].x, buttonPos[1].y, button_width, button_height, false, button1_tittle, FontArial, MauThanhQuanLy))
            current_page = 1;
    }
    else
    {
        DrawRectangleRec({buttonPos[1].x, buttonPos[1].y, button_width, button_height}, MauThanhQuanLy.isPressed);
        DrawTextEx(FontArial,
                   button1_tittle,
                   {CenterDataSetter(button_width, buttonPos[1].x, MeasureTextEx(FontArial, button1_tittle, button_height / 2.0f, 0).x),
                    button_height / 5.0f + buttonPos[1].y},
                   button_height / 2.0f, 0, MauThanhQuanLy.text2);
    };
    if (current_page != 2)
    {
        if (CreateButton(buttonPos[2].x, buttonPos[2].y, button_width, button_height, false, button2_tittle, FontArial, MauThanhQuanLy))
            current_page = 2;
    }
    else
    {
        DrawRectangleRec({buttonPos[2].x, buttonPos[2].y, button_width, button_height}, MauThanhQuanLy.isPressed);
        DrawTextEx(FontArial,
                   button2_tittle,
                   {CenterDataSetter(button_width, buttonPos[2].x, MeasureTextEx(FontArial, button2_tittle, button_height / 2.0f, 0).x),
                    button_height / 5.0f + buttonPos[2].y},
                   button_height / 2.0f, 0, MauThanhQuanLy.text2);
    };
    if (current_page != 3)
    {
        if (CreateButton(buttonPos[3].x, buttonPos[3].y, button_width, button_height, false, button3_tittle, FontArial, MauThanhQuanLy))
            current_page = 3;
    }
    else
    {
        DrawRectangleRec({buttonPos[3].x, buttonPos[3].y, button_width, button_height}, MauThanhQuanLy.isPressed);
        DrawTextEx(FontArial,
                   button3_tittle,
                   {CenterDataSetter(button_width, buttonPos[3].x, MeasureTextEx(FontArial, button3_tittle, button_height / 2.0f, 0).x),
                    button_height / 5.0f + buttonPos[3].y},
                   button_height / 2.0f, 0, MauThanhQuanLy.text2);
    };
    if (current_page != 4)
    {
        if (CreateButton(buttonPos[4].x, buttonPos[4].y, button_width, button_height, false, button4_tittle, FontArial, MauThanhQuanLy))
            current_page = 4;
    }
    else
    {
        DrawRectangleRec({buttonPos[4].x, buttonPos[4].y, button_width, button_height}, MauThanhQuanLy.isPressed);
        DrawTextEx(FontArial,
                   button4_tittle,
                   {CenterDataSetter(button_width, buttonPos[4].x, MeasureTextEx(FontArial, button4_tittle, button_height / 2.0f, 0).x),
                    button_height / 5.0f + buttonPos[4].y},
                   button_height / 2.0f, 0, MauThanhQuanLy.text2);
    };
}

// ---Các hàm hỗ trợ ngoài vìa------------------------------------------------------------------------------------------------------

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua, float obj_width)
{
    return (doDai_khung_chua / 2.0f) + vi_tri_khung_chua - (obj_width / 2.0f);
}

bool CreateButton(float pos_x, float pos_y, float width, float height, bool BoTron, const char *titlle, Font font, BoMauNut BoMau)
{
    Rectangle Button = {pos_x, pos_y, width, height};
    Vector2 MousePos = {0.0f, 0.0f};
    Vector2 TextPos = {CenterDataSetter(width, pos_x, MeasureTextEx(font, titlle, height / 2.0f, 0).x),
                       height / 5.0f + pos_y};
    // DrawRectangleRec(Button, BoMau.isnotHovered);
    if (BoTron)
    {
        DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isnotHovered);
        DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text1);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isPressed);
                DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text2);
            }
            else
            {
                DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isHovered);
                DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text1);
            }
            DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, BoMau.Rounder);

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    else
    {
        DrawRectangleRec(Button, BoMau.isnotHovered);
        DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text1);
        DrawRectangleRoundedLines(Button, 0, 0, 2, BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(Button, BoMau.isPressed);
                DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text2);
            }
            else
            {
                DrawRectangleRec(Button, BoMau.isHovered);
                DrawTextEx(font, titlle, TextPos, height / 2.0f, 0, BoMau.text1);
            }
            DrawRectangleRoundedLines(Button, 0, 0, 2, BoMau.Rounder);

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    return false;
}

bool CreateButtonWithPicture(float pos_x, float pos_y, float width, float height, bool BoTron, Texture2D Picture, BoMauNut BoMau)
{
    Rectangle Button = {pos_x, pos_y, width, height};
    Vector2 MousePos = {0.0f, 0.0f};
    // DrawRectangleRec(Button, BoMau.isnotHovered);
    if (BoTron)
    {
        DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isnotHovered);
        DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isPressed);
                DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isPressed);
            }
            else
            {
                DrawRectangleRounded(Button, 0.5f, 0.5f, BoMau.isHovered);
                DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isHovered);
            }
            DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, BoMau.Rounder);

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    else
    {
        DrawRectangleRec(Button, BoMau.isnotHovered);
        DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0, 0, 2, BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(Button, BoMau.isPressed);
                DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isPressed);
            }
            else
            {
                DrawRectangleRec(Button, BoMau.isHovered);
                DrawTextureEx(Picture, {pos_x, pos_y}, 0, 1, BoMau.isHovered);
            }
            DrawRectangleRoundedLines(Button, 0, 0, 2, BoMau.Rounder);

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    return false;
}

// Chưa hoàn chỉnh
const char *CreateTextInputBox()
{
    static char name[120] = "\0";
    char name_cpy[120] = "\0";
    char *resuit = new char[120];
    static bool mouseClickOnText = false;
    static bool Done = false;
    static int letterCount = 0;
    static int framesCounter = 0;
    static int fHold_BS = 0, fHold_RIGHT = 0, fHold_LEFT = 0;
    static int indexPoint = 0;

    Rectangle textBox = {300, 300, 700, 40};
    Vector2 textBoxPos = {textBox.x + 5, CenterDataSetter(40, textBox.y, MeasureTextEx(FontArial, name, 30, 0).y)};

    strcpy(name_cpy, name);
    name_cpy[letterCount + indexPoint] = '\0';

    Vector2 textBoxDot = {textBox.x + MeasureTextEx(FontArial, name_cpy, 30, 0).x, CenterDataSetter(40, textBox.y, MeasureTextEx(FontArial, name_cpy, 30, 0).y)};
    if (CheckCollisionPointRec(GetVMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        mouseClickOnText = true;
    else if (IsKeyPressed(KEY_ENTER))
    {
        mouseClickOnText = false;
        strcpy(resuit, name);
        name[0] = '\0';
        indexPoint = 0;
        letterCount = 0;
        Done = true;
    }
    else if (!CheckCollisionPointRec(GetVMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        mouseClickOnText = false;

    if (CheckCollisionPointRec(GetVMousePosition(), textBox))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    }
    else
    {
        SetMouseCursor(1);
    }

    if (mouseClickOnText)
    {
        framesCounter++;
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
        if ((IsKeyDown(KEY_BACKSPACE) && letterCount + indexPoint > 0 && (fHold_BS > 150) && (fHold_BS % 10 == 0)) ||
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
        }
        if ((IsKeyDown(KEY_LEFT) && (letterCount + indexPoint) > 0 && (fHold_LEFT > 150) && (fHold_LEFT % 10 == 0)) ||
            (IsKeyPressed(KEY_LEFT) && (letterCount + indexPoint) > 0))
        {
            indexPoint--;
        }
        if ((IsKeyDown(KEY_RIGHT) && indexPoint < 0 && (fHold_RIGHT > 150) && (fHold_RIGHT % 10 == 0)) ||
            (IsKeyPressed(KEY_RIGHT) && indexPoint < 0))
        {
            indexPoint++;
        }
    }
    else
        framesCounter = 0;
    DrawRectangleRec(textBox, GRAY);
    DrawTextEx(FontArial, name, textBoxPos, 30, 0, BLACK);
    // cout << "index: " << indexPoint << endl;
    if (mouseClickOnText && ((framesCounter % 300 >= 120)))
        DrawTextEx(FontArial, "|", textBoxDot, 30, 0, MAROON);
    if (Done)
    {
        Done = false;
        return resuit;
    }
    return "\0";
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

float per1000(int number)
{
    return (float)number / 1000;
}

//==================================================================================================================================
// main function
void mainGraphics()
{
    LoadResources();

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetWindowMinSize(700, 400);
    SetSizeWindow();
    RenderTexture2D renderTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT); // Load nội dung màn hình như một ảnh
    while (!WindowShouldClose())
    {
        BeginTextureMode(renderTexture);
        // Cách thao tác trên đồ hoạ

        if (current_page != 0)
            ThanhQuanLy();
        switch (current_page)
        {
        case 0:
        {
            CreateHomePage();
            break;
        }
        case 1:
        {
            CreatePage_QLMB();
            break;
        }
        case 2:
        {
            CreatePage_QLCB();
            break;
        }
        case 3:
        {
            CreatePage_QLVe();
            break;
        }
        case 4:
        {
            CreatePage_QLHK();
            break;
        }
        case 5:
        {
            CreatePage_GioiThieu();
            break;
        }
        default:
        {
            current_page = 0;
        }
        }

        EndTextureMode();
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
    UnloadRenderTexture(renderTexture);
    UnloadResources();
}
