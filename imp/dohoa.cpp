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

BoMauNut ArrowKey{
    {175, 175, 175, 255},
    {100, 100, 100, 255},
    {50, 50, 50, 250},
    BLACK,
    BLACK,
    BLACK};

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

Image ArrowLeft;
Texture2D PNG_arrowLeft;
Texture2D PNG_arrowRight;

void LoadResources()
{
    FontArial = LoadFontEx("../src/font/arial.ttf", 96, 0, 9812);
    GenTextureMipmaps(&FontArial.texture);
    SetTextureFilter(FontArial.texture, TEXTURE_FILTER_TRILINEAR);

    LogoPTIT = LoadImage("../src/img/Logo_PTIT_University.png"); // load ảnh
    ImageResize(&LogoPTIT, 698, 690);                            // Chỉnh size ảnh
    PNG_logo = LoadTextureFromImage(LogoPTIT);

    HomeIcon = LoadImage("../src/img/house_icon.png");
    ImageResize(&HomeIcon, 60, 50);
    PNG_home = LoadTextureFromImage(HomeIcon);

    ArrowLeft = LoadImage("../src/img/arrow_left.png");
    ImageResize(&ArrowLeft, 30, 30);
    PNG_arrowLeft = LoadTextureFromImage(ArrowLeft);
    ImageRotateCW(&ArrowLeft);
    ImageRotateCW(&ArrowLeft);
    PNG_arrowRight = LoadTextureFromImage(ArrowLeft);
}

void UnloadResources()
{
    UnloadFont(FontArial);

    UnloadImage(LogoPTIT);
    UnloadImage(HomeIcon);
    UnloadImage(ArrowLeft);

    UnloadTexture(PNG_logo);
    UnloadTexture(PNG_home);
    UnloadTexture(PNG_arrowLeft);
    UnloadTexture(PNG_arrowRight);
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
        H = 820;
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
void CreatePage_QLMB(DSMB listMB)
{
    CreatePageBackground();

    // tittle
    DrawTextEx(FontArial, "DANH SÁCH MÁY BAY", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);

    // search
    // Rectangle searchBox = {StartPos.x + 60, StartPos.y + 60 + 100, 1080, 80};
    // DrawRectangleRec(searchBox, GRAY);
    // DrawTextEx(FontArial, "Search", {searchBox.x, searchBox.y}, 60, 0, BLUE);

    Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
    DrawRectangleRec(searchText, WHITE);
    DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
    DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);
    if (CreateButton(searchText.x + searchText.width, searchText.y, 200, 50, false, "TÌM KIẾM", FontArial, ArrowKey))
    {
        cout << "TKiem" << endl;
    }

    // table
    float cellW[5] = {100, 300, 380, 150, 150};
    CreateTable_QLMB();

    // data
    static int current_page = 1;
    int n_page = 1 + listMB.getsize() / 10;
    showList_QLMB(listMB, {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, current_page, cellW);

    // page and switch page
    current_page = SwitchPage(current_page, n_page, {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
}

void CreateTable_QLMB()
{
    const char *cell_tittle[5] = {"STT", "Mã máy bay", "Tên máy bay", "Số dòng", "Số dãy"};

    float cellW[5] = {100, 300, 380, 150, 150};
    CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, 1080);

    Vector2 *tittle_pos = GetTittlePos({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, cell_tittle);

    for (int i = 0; i < 5; i++)
    {
        DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
    }
}

void showList_QLMB(DSMB listMB, Vector2 start_pos, int current_page, float cellW[])
{
    int size = listMB.getsize();
    int i = (current_page - 1) * 10;
    int j;
    if (current_page * 10 < size)
        j = current_page * 10;
    else
        j = size;

    for (i; i < j; i++)
    {
        MayBay *MB = listMB.getMB(i);
        DrawTextEx(FontArial, intTochar(i + 1, 2), GetCellTextPos_Mid(start_pos, 5, cellW, 1, (i % 10) + 1, intTochar(i + 1, 2)), 30, 0, BLACK);
        DrawTextEx(FontArial, MB->getSoHieuMB(), GetCellTextPos_Mid(start_pos, 5, cellW, 2, (i % 10) + 1, MB->getSoHieuMB()), 30, 0, BLACK);
        DrawTextEx(FontArial, MB->getLoaiMB(), GetCellTextPos_Mid(start_pos, 5, cellW, 3, (i % 10) + 1, MB->getLoaiMB()), 30, 0, BLACK);
        DrawTextEx(FontArial, intTochar(MB->getSoDay(), 2), GetCellTextPos_Mid(start_pos, 5, cellW, 4, (i % 10) + 1, intTochar(MB->getSoDay(), 2)), 30, 0, BLACK);
        DrawTextEx(FontArial, intTochar(MB->getSoDong(), 2), GetCellTextPos_Mid(start_pos, 5, cellW, 5, (i % 10) + 1, intTochar(MB->getSoDong(), 2)), 30, 0, BLACK);
    }
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
    CreateTable_QLVe();
}

void CreateTable_QLVe()
{
    DrawTextEx(FontArial, "DANH SÁCH VÉ", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);
    float cellW[3] = {100, 200, 400};
    CreateTable({CenterDataSetter(1080, StartPos.x + 60, 700), StartPos.y + 60 + 100 + 80}, 3, cellW, 700);
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
void CreateTable(Vector2 vitriBang, int soCot, float cellW[], float total_cellW)
{
    const int empty_spaces_left = 60;
    const int empty_spaces_top = 60 + 100 + 80;
    const int firstLineH = 50;
    const int lineH = 40;

    Vector2 Point_row[2][soCot + 1];
    Point_row[0][0] = {vitriBang.x - 1, vitriBang.y};
    Point_row[1][0] = {vitriBang.x - 1, vitriBang.y + firstLineH + lineH * 10};
    DrawLineEx(Point_row[0][0], Point_row[1][0], 2, BROWN);

    for (int i = 1; i < soCot; i++)
    {
        Point_row[0][i] = {Point_row[0][i - 1].x + cellW[i - 1], Point_row[0][0].y};
        Point_row[1][i] = {Point_row[1][i - 1].x + cellW[i - 1], Point_row[1][0].y};
        DrawLineEx(Point_row[0][i], Point_row[1][i], 2, BROWN);
    }
    Point_row[0][soCot] = {Point_row[0][soCot - 1].x + cellW[soCot - 1] + 1, Point_row[0][0].y};
    Point_row[1][soCot] = {Point_row[1][soCot - 1].x + cellW[soCot - 1] + 1, Point_row[1][0].y};
    DrawLineEx(Point_row[0][soCot], Point_row[1][soCot], 2, BROWN);

    Vector2 Point_line[11][2];
    Point_line[0][0] = {vitriBang.x - 1, vitriBang.y};
    Point_line[0][1] = {vitriBang.x - 1 + total_cellW + 2, vitriBang.y};

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

    Rectangle hightlight_tittle = {vitriBang.x, vitriBang.y, total_cellW - 2, firstLineH};
    DrawRectangleRoundedLines(hightlight_tittle, 0, 0, 3, BLACK);

    Rectangle hightlight_table = {vitriBang.x, vitriBang.y, total_cellW - 2, firstLineH + 10 * lineH};
    DrawRectangleRoundedLines(hightlight_table, 0, 0, 3, BLACK);
}

Vector2 GetCellTextPos_Left(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y)
{
    Vector2 ans;
    float cellPosX[soCot];
    cellPosX[0] = vitriBang.x;
    for (int i = 1; i < soCot; i++)
    {
        cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
    }
    ans = {cellPosX[vi_tri_x - 1] + 10,
           CenterDataSetter(40, StartPos.y + 60 + 100 + 80 + (vi_tri_y - 1) * 40, MeasureTextEx(FontArial, "A", 30, 0).y)};
    return ans;
}

Vector2 GetCellTextPos_Mid(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text)
{
    Vector2 ans;
    float cellPosX[soCot];
    cellPosX[0] = vitriBang.x;
    for (int i = 1; i < soCot; i++)
    {
        cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
    }
    ans = {CenterDataSetter(cellW[vi_tri_x - 1], cellPosX[vi_tri_x - 1], MeasureTextEx(FontArial, text, 30, 0).x),
           CenterDataSetter(40, vitriBang.y + 50 + (vi_tri_y - 1) * 40, MeasureTextEx(FontArial, "A", 30, 0).y)};
    return ans;
}

Vector2 GetCellTextPos_Right(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text)
{
    Vector2 ans;
    float cellPosX[soCot];
    cellPosX[0] = vitriBang.x;
    for (int i = 1; i < soCot; i++)
    {
        cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
    }
    ans = {cellPosX[vi_tri_x - 1] + cellW[vi_tri_x - 1] - MeasureTextEx(FontArial, text, 30, 0).x - 10,
           CenterDataSetter(50, StartPos.y + 60 + 100 + 80 + (vi_tri_y - 1) * 40, MeasureTextEx(FontArial, "A", 40, 0).y)};
    return ans;
}

Vector2 *GetTittlePos(Vector2 vitriBang, int soCot, float cellW[], const char *cell_tittle[])
{
    Vector2 *ans = new Vector2[soCot];
    float cellPosX[soCot];
    cellPosX[0] = vitriBang.x;
    for (int i = 1; i < soCot; i++)
    {
        cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
    }

    float pos_y_table_title = CenterDataSetter(50, StartPos.y + 60 + 100 + 80, MeasureTextEx(FontArial, "A", 40, 0).y);
    float pos_x_table_title[5];

    for (int i = 0; i < 5; i++)
    {
        pos_x_table_title[i] = CenterDataSetter(cellW[i], cellPosX[i], MeasureTextEx(FontArial, cell_tittle[i], 40, 0).x);
        ans[i] = {pos_x_table_title[i],
                  pos_y_table_title};
    }
    return ans;
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

int SwitchPage(int current_page, int n_page, Vector2 pos)
{
    Rectangle textBox = {pos.x + 50, pos.y, 160, 50};
    Rectangle pg1 = {textBox.x + textBox.width + 2, textBox.y, 70 - 4, 50};
    Rectangle pg2 = {textBox.x + textBox.width + 70 + 2, textBox.y, 70 - 4, 50};
    int status = 0;

    // char *n1 = new char[2], *n2 = new char[2];
    char n1[3], n2[3];
    strcpy(n1, intTochar(current_page, 2));
    n1[2] = '\0';
    strcpy(n2, intTochar(n_page, 2));
    n2[2] = '\0';
    char *text = "trang";

    if (current_page > 1)
    {
        if (CreateButtonWithPicture(pos.x + 10, pos.y + 10, 30, 30, false, PNG_arrowLeft, ArrowKey))
            status = -1;
    }
    else
    {
        DrawRectangle(pos.x + 10, pos.y + 10, 30, 30, ArrowKey.isPressed);
        DrawTexture(PNG_arrowLeft, pos.x + 10, pos.y + 10, ArrowKey.isPressed);
    }

    DrawRectangleRec(textBox, ArrowKey.isnotHovered);
    DrawTextEx(FontArial,
               text,
               {CenterDataSetter(160, textBox.x, MeasureTextEx(FontArial, text, 30, 0).x), CenterDataSetter(50, textBox.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
               30,
               0,
               BLACK);

    DrawRectangleRec(pg1, WHITE);
    DrawRectangleRoundedLines(pg1, 0, 1, 2, BROWN);
    DrawRectangleRec(pg2, WHITE);
    DrawRectangleRoundedLines(pg2, 0, 1, 2, BROWN);

    DrawTextEx(FontArial,
               n1,
               {CenterDataSetter(70, pg1.x, MeasureTextEx(FontArial, n1, 30, 0).x), CenterDataSetter(50, pg1.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
               30,
               0,
               BLACK);
    DrawTextEx(FontArial,
               n2,
               {CenterDataSetter(70, pg2.x, MeasureTextEx(FontArial, n2, 30, 0).x), CenterDataSetter(50, pg2.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
               30,
               0,
               BLACK);

    if (current_page < n_page)
    {
        if (CreateButtonWithPicture(pos.x + 50 + 300 + 10, pos.y + 10, 30, 30, false, PNG_arrowRight, ArrowKey))
            status = 1;
    }
    else
    {
        DrawRectangle(pos.x + 50 + 300 + 10, pos.y + 10, 30, 30, ArrowKey.isPressed);
        DrawTexture(PNG_arrowRight, pos.x + 50 + 300 + 10, pos.y + 10, ArrowKey.isPressed);
    }
    if (status == -1)
        return current_page - 1;
    else if (status == 1)
        return current_page + 1;
    else
        return current_page;
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
        if ((IsKeyDown(KEY_BACKSPACE) && letterCount + indexPoint > 0 && (fHold_BS > 60) && (fHold_BS % 3 == 0)) ||
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
        if ((IsKeyDown(KEY_LEFT) && (letterCount + indexPoint) > 0 && (fHold_LEFT > 60) && (fHold_LEFT % 3 == 0)) ||
            (IsKeyPressed(KEY_LEFT) && (letterCount + indexPoint) > 0))
        {
            indexPoint--;
        }
        if ((IsKeyDown(KEY_RIGHT) && indexPoint < 0 && (fHold_RIGHT > 60) && (fHold_RIGHT % 3 == 0)) ||
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
    if (mouseClickOnText && ((framesCounter % 120 >= 15)))
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

char *intTochar(int value, int size)
{
    char *ans = new char[size];
    for (int i = 0; i < size; i++)
    {
        int _10 = 1;
        for (int j = i + 1; j < size; j++)
        {
            _10 *= 10;
        }
        if (value / _10 == 0)
            ans[i] = '0';
        else
            ans[i] = (value / _10) + 48;
        value = value % _10;
    }
    ans[size] = '\0';
    return ans;
}

float per1000(int number)
{
    return (float)number / 1000;
}

//==================================================================================================================================
// main function
void mainGraphics()
{
    DSMB *listMB = new DSMB();
    MayBay *MB[34];
    for (int i = 0; i < 34; i++)
    {
        MB[i] = new MayBay("MB01", "boing", i * 3, i * 5);
        listMB->Insert_MB(MB[i]);
    }

    LoadResources();

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(60); // max framerate per second set to 60
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
            CreatePage_QLMB(*listMB);
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
