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
    Color RounderHovered;
    Color RounderPressed;
};
struct Button
{
    float x;
    float y;
    float w;
    float h;
    bool BoTron = false;
    bool gotNothing = true;
    bool gotText = false;
    const char *tittle = "";
    Font font;
    bool gotPic = false;
    Texture2D picture;
    bool RounderChangeColor = false;
    bool firstRounder = true;
    BoMauNut BoMau;
};

struct InputTextBox
{
    Rectangle textBox;
    const char *tittle = "";
    int size = 27;
    bool showNKeyRemain = true;
    bool editMode = false;
    bool showPreResult = true;
    bool returnIfDone = false;
    Color MauNen = WHITE;
    Color MauVien = BLACK;
    Color MauChu = BLACK;
    int mode = 1;

    // xử lý
    char name[120] = "\0";
    int fHold_BS = 0, fHold_RIGHT = 0, fHold_LEFT = 0;
    bool done;
    bool mouseClickOnText = false;
    int letterCount = 0;
    int framesCounter = 0;
    int indexPoint = 0;
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
    // FontArial = LoadFontEx("../src/font/arial.ttf", 96, 0, 9812);
    FontArial = LoadFontEx("c:/Windows/Fonts/arial.ttf", 96, 0, 9812);
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
    const int button_tittle_h = 80;
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
               *button_tille = "CÁC CHỨC NĂNG";
    char *button_tittle[5];
    button_tittle[0] = (char *)"QUẢN LÝ MÁY BAY";
    button_tittle[1] = (char *)"QUẢN LÝ CHUYẾN BAY";
    button_tittle[2] = (char *)"QUẢN LÝ VÉ";
    button_tittle[3] = (char *)"QUẢN LÝ HÀNH KHÁCH";
    button_tittle[4] = (char *)"GIỚI THIỆU VỀ SẢN PHẨM";

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
             tittleButtonPos.y + button_tittle_h + button_tittle_margin_bot + button_margin_topbot},
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

        Button button[5];
        for (int i = 0; i < 5; i++)
        {
            button[i].x = buttonPos[i].x;
            button[i].y = buttonPos[i].y;
            button[i].w = button_width;
            button[i].h = button_height;
            button[i].BoTron = true;
            button[i].gotNothing = false;
            button[i].gotText = true;
            button[i].tittle = button_tittle[i];
            button[i].font = FontArial;
            button[i].BoMau = HomeButtonColor;
            if (CreateButton(button[i]))
            {
                current_page = i + 1;
            }
        }
    }
}

// ---Các trang thành phần----------------------------------------------------------------------------------------------------------
void CreatePageBackground(int SoHang)
{
    ClearBackground(DARKBLUE);
    const int home_tittle_h = 60;
    Rectangle mainScreen = {StartPos.x,
                            StartPos.y + home_tittle_h,
                            1199,
                            SCREEN_HEIGHT - home_tittle_h};
    Rectangle funcScreen = {StartPos.x + 1201,
                            StartPos.y + home_tittle_h,
                            299,
                            SCREEN_HEIGHT - home_tittle_h};
    Rectangle splitScreen = {mainScreen.x + 1199,
                             mainScreen.y,
                             2, // dày 2
                             SCREEN_HEIGHT - home_tittle_h};
    DrawRectangleRec(mainScreen, WHITE);
    DrawRectangleRoundedLines(mainScreen, 0, 1, 2, RED);
    DrawRectangleRec(funcScreen, WHITE);
    DrawRectangleRoundedLines(funcScreen, 0, 1, 2, RED);

    DrawRectangleRec(splitScreen, BLACK);
    for (int i = 0; i < SoHang; i++)
    {
        DrawRectangle(funcScreen.x + 29, funcScreen.y + 105 + 75 * i, 240, 60, GRAY);
        // DrawRectangle(funcScreen.x + 29, funcScreen.y + 180, 240, 60, GRAY);
        // DrawRectangle(funcScreen.x + 29, funcScreen.y + 255, 240, 60, GRAY);
    }

    if (SoHang != 0)
    {
        DrawTextEx(FontArial,
                   "Chức năng",
                   {CenterDataSetter(300, funcScreen.x - 1, MeasureTextEx(FontArial, "Chức năng", 55, 0).x),
                    CenterDataSetter(70, funcScreen.y + 10, MeasureTextEx(FontArial, "Chức năng", 55, 0).y)},
                   55,
                   0,
                   BLUE);
    }
}

// =-MayBay
void CreatePage_QLMB(DSMB *listMB)
{
    CreatePageBackground(3);
    static MayBay *data = new MayBay();
    static char *preResult = (char *)"\0";
    static int status = 0;
    static int current_popup = 0; // 0-k hien/ 1-them/ 2-sua/ 3-xoa

    // tittle
    DrawTextEx(FontArial, "DANH SÁCH MÁY BAY", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);

    if (current_popup == 0)
    {
        Button button[3];
        for (int i = 0; i < 3; i++)
        {
            button[i].x = StartPos.x + 1201 + 29;
            button[i].y = StartPos.y + 60 + 20 + 70 + 15 + 75 * i;
            button[i].w = 240;
            button[i].h = 60;
            button[i].BoTron = false;
            button[i].gotNothing = false;
            button[i].gotText = true;
            button[i].font = FontArial;
            button[i].BoMau = ArrowKey;
        }

        // mini function
        button[0].tittle = "Thêm máy bay";
        if (CreateButton(button[0]))
        {
            current_popup = 1;
        }
        button[1].tittle = "Hiệu chỉnh máy bay";
        if (CreateButton(button[1]))
        {

            current_popup = 2;
        }
        button[2].tittle = "Xoá máy bay";
        if (CreateButton(button[2]))
        {
            current_popup = 3;
        }
        data = XuLy_QLMB(listMB, status);
        // if (data->getSoHieuMB()[0] >= 36)
        // {
        //     preResult = data->getSoHieuMB();
        // }
    }
    else if (current_popup == 1)
    {
        if (Popup_ThemMB(listMB, status))
            current_popup = 0;
    }
    else if (current_popup == 2)
    {
        if (Popup_HieuChinhMB(listMB, data))
            current_popup = 0;
    }
    else if (current_popup == 3)
    {
        if (Popup_XoaMB(listMB, data, status))
            current_popup = 0;
    }
    // cout << data->getSoHieuMB() << endl;
}

void CreatePopupBackground()
{
    DrawRectangle(StartPos.x, StartPos.y + 60, SCREEN_WIDTH, SCREEN_HEIGHT - 60, {129, 150, 212, 255});
    DrawRectangle(StartPos.x + 400, StartPos.y + 60 + 10, 700, 60, {104, 112, 217, 255});
}

bool Popup_ThemMB(DSMB *listMB, int &status)
{
    CreatePopupBackground();
    static int error = 0;
    DrawTextEx(FontArial, "Thêm máy bay",
               {CenterDataSetter(700, StartPos.x + 400, MeasureTextEx(FontArial, "Thêm máy bay", 50, 0).x),
                CenterDataSetter(60, StartPos.y + 60 + 10, MeasureTextEx(FontArial, "A", 50, 0).y)},
               50, 0, BLACK);

    static InputTextBox MaMB;
    MaMB.mode = 3;
    MaMB.tittle = (char *)"Nhập số hiệu máy bay";
    MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
    MaMB.size = 15;
    static InputTextBox LoaiMayBay;
    LoaiMayBay.mode = 2;
    LoaiMayBay.tittle = (char *)"Nhập loại máy bay";
    LoaiMayBay.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    LoaiMayBay.size = 40;
    static InputTextBox SoDong;
    SoDong.mode = 5;
    SoDong.tittle = (char *)"Nhập số dòng của máy bay";
    SoDong.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
    SoDong.size = 3;
    static InputTextBox SoDay;
    SoDay.mode = 5;
    SoDay.tittle = (char *)"Nhập số dãy của máy bay";
    SoDay.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
    SoDay.size = 3;

    const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y - MeasureTextEx(FontArial, "A", 25, 0).y;

    DrawTextEx(FontArial, "Mã máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
    DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25}, 25, 0, RED);
    const char *newMaMB = CreateTextInputBox(MaMB);
    DrawTextEx(FontArial, "Hãng máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
    DrawTextEx(FontArial, "(Gồm chữ cái và số)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25}, 25, 0, RED);
    const char *newLoaiMayBay = CreateTextInputBox(LoaiMayBay);
    DrawTextEx(FontArial, "Số dòng",
               {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
    DrawTextEx(FontArial, "(Gồm CHỈ số)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25}, 25, 0, RED);
    const char *newSoDong = CreateTextInputBox(SoDong);
    DrawTextEx(FontArial, "Số dãy",
               {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
    DrawTextEx(FontArial, "(Gồm CHỈ số)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25}, 25, 0, RED);
    const char *newSoDay = CreateTextInputBox(SoDay);

    Button OK;
    OK.x = StartPos.x + 225 + 750;
    OK.y = StartPos.y + 60 + 625;
    OK.w = 300;
    OK.h = 50;
    OK.gotNothing = false;
    OK.gotText = true;
    OK.tittle = (char *)"Hoàn tất";
    OK.font = FontArial;
    OK.BoMau = ArrowKey;

    Button Cancel;
    Cancel.x = StartPos.x + 225;
    Cancel.y = StartPos.y + 60 + 625;
    Cancel.w = 300;
    Cancel.h = 50;
    Cancel.gotNothing = false;
    Cancel.gotText = true;
    Cancel.tittle = (char *)"Huỷ";
    Cancel.font = FontArial;
    Cancel.BoMau = ArrowKey;
    if (error == 1)
        DrawTextEx(FontArial, "Máy Bay đã tồn tại!",
                   {CenterDataSetter(1100, StartPos.x + 200, MeasureTextEx(FontArial, "Máy Bay đã tồn tại!", 40, 0).x),
                    CenterDataSetter(50, StartPos.y + 130, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, RED);
    else if (error == 2)
        DrawTextEx(FontArial, "Nhập chưa đủ thông tin!",
                   {CenterDataSetter(1100, StartPos.x + 200, MeasureTextEx(FontArial, "Nhập chưa đủ thông tin!", 40, 0).x),
                    CenterDataSetter(50, StartPos.y + 130, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, RED);
    if (CreateButton(OK))
    {
        char CheckMB[16];
        strcpy(CheckMB, newMaMB);
        if (listMB->Find_MB(CheckMB) < 0)
        {
            if (newMaMB[0] >= 32 && newLoaiMayBay[0] >= 32 && newSoDay[0] >= 32 && newSoDong[0] >= 32)
            {
                MayBay *result = new MayBay(newMaMB, newLoaiMayBay, atoi(newSoDay), atoi(newSoDong));
                listMB->Insert_MB(result);
                ofstream fileWrite("../data/dataMB.txt", ios::out | ios::trunc);
                listMB->WritetoFile(fileWrite);
                fileWrite.close();
                ifstream fileRead("../data/dataMB.txt", ios::in);
                listMB->ReadFromFile(fileRead);
                fileRead.close();
                status = 1;
                resetInputTextBox(MaMB);
                resetInputTextBox(LoaiMayBay);
                resetInputTextBox(SoDong);
                resetInputTextBox(SoDay);
                error = 0;

                return true;
            }
            else
            {
                error = 2;
            }
        }
        else
        {
            error = 1;
        }
    }
    if (CreateButton(Cancel))
    {
        resetInputTextBox(MaMB);
        resetInputTextBox(LoaiMayBay);
        resetInputTextBox(SoDong);
        resetInputTextBox(SoDay);
        error = 0;
        return true;
    }
    return false;
}

bool Popup_HieuChinhMB(DSMB *listMB, MayBay *mb)
{
    CreatePopupBackground();
    static int error = 0;
    DrawTextEx(FontArial, "Sửa thông tin máy bay",
               {CenterDataSetter(700, StartPos.x + 400, MeasureTextEx(FontArial, "Sửa thông tin máy bay", 50, 0).x),
                CenterDataSetter(60, StartPos.y + 60 + 10, MeasureTextEx(FontArial, "A", 50, 0).y)},
               50, 0, BLACK);

    if (mb->getSoHieuMB()[0] != 0)
    {
        static InputTextBox MaMB;
        MaMB.mode = 3;
        MaMB.editMode = true;
        MaMB.tittle = mb->getSoHieuMB();
        MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
        MaMB.size = 15;
        static InputTextBox LoaiMayBay;
        LoaiMayBay.mode = 2;
        LoaiMayBay.editMode = true;
        LoaiMayBay.tittle = mb->getLoaiMB();
        LoaiMayBay.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
        LoaiMayBay.size = 40;
        static InputTextBox SoDong;
        SoDong.mode = 5;
        SoDong.editMode = true;
        SoDong.tittle = intTochar(mb->getSoDong(), 3);
        SoDong.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
        SoDong.size = 3;
        static InputTextBox SoDay;
        SoDay.mode = 5;
        SoDay.editMode = true;
        SoDay.tittle = intTochar(mb->getSoDay(), 3);
        SoDay.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
        SoDay.size = 3;

        const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y - MeasureTextEx(FontArial, "A", 25, 0).y;

        DrawTextEx(FontArial, "Mã máy bay",
                   {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
        DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
                   {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25}, 25, 0, RED);
        const char *newMaMB = CreateTextInputBox(MaMB);
        DrawTextEx(FontArial, "Hãng máy bay",
                   {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
        DrawTextEx(FontArial, "(Gồm chữ cái và số)",
                   {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25}, 25, 0, RED);
        const char *newLoaiMayBay = CreateTextInputBox(LoaiMayBay);
        DrawTextEx(FontArial, "Số dòng",
                   {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
        DrawTextEx(FontArial, "(Gồm CHỈ số)",
                   {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25}, 25, 0, RED);
        const char *newSoDong = CreateTextInputBox(SoDong);
        DrawTextEx(FontArial, "Số dãy",
                   {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
        DrawTextEx(FontArial, "(Gồm CHỈ số)",
                   {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25}, 25, 0, RED);
        const char *newSoDay = CreateTextInputBox(SoDay);

        Button OK;
        OK.x = StartPos.x + 225 + 750;
        OK.y = StartPos.y + 60 + 625;
        OK.w = 300;
        OK.h = 50;
        OK.gotNothing = false;
        OK.gotText = true;
        OK.tittle = (char *)"Hoàn tất";
        OK.font = FontArial;
        OK.BoMau = ArrowKey;

        Button Cancel;
        Cancel.x = StartPos.x + 225;
        Cancel.y = StartPos.y + 60 + 625;
        Cancel.w = 300;
        Cancel.h = 50;
        Cancel.gotNothing = false;
        Cancel.gotText = true;
        Cancel.tittle = (char *)"Huỷ";
        Cancel.font = FontArial;
        Cancel.BoMau = ArrowKey;

        if (error == 1)
            DrawTextEx(FontArial, "Máy Bay đã tồn tại!",
                       {CenterDataSetter(1100, StartPos.x + 200, MeasureTextEx(FontArial, "Máy Bay đã tồn tại!", 40, 0).x),
                        CenterDataSetter(50, StartPos.y + 130, MeasureTextEx(FontArial, "A", 40, 0).y)},
                       40, 0, RED);
        else if (error == 2)
            DrawTextEx(FontArial, "Nhập chưa đủ thông tin!",
                       {CenterDataSetter(1100, StartPos.x + 200, MeasureTextEx(FontArial, "Nhập chưa đủ thông tin!", 40, 0).x),
                        CenterDataSetter(50, StartPos.y + 130, MeasureTextEx(FontArial, "A", 40, 0).y)},
                       40, 0, RED);
        if (CreateButton(OK))
        {
            char CheckMB[16];
            strcpy(CheckMB, newMaMB);
            if (listMB->Find_MB(CheckMB) < 0 || listMB->Find_MB(CheckMB) == listMB->Find_MB(mb->getSoHieuMB()))
            {
                if (newMaMB[0] >= 32 && newLoaiMayBay[0] >= 32 && newSoDay[0] >= 32 && newSoDong[0] >= 32)
                {
                    mb->setSoHieuMB(newMaMB);
                    mb->setLoaiMB(newLoaiMayBay);
                    mb->setSoDong(atoi(newSoDong));
                    mb->setSoDay(atoi(newSoDay));

                    ofstream fileWrite("../data/dataMB.txt", ios::out | ios::trunc);
                    listMB->WritetoFile(fileWrite);
                    fileWrite.close();
                    ifstream fileRead("../data/dataMB.txt", ios::in);
                    listMB->ReadFromFile(fileRead);
                    fileRead.close();
                    resetInputTextBox(MaMB);
                    resetInputTextBox(LoaiMayBay);
                    resetInputTextBox(SoDong);
                    resetInputTextBox(SoDay);
                    error = 0;

                    return true;
                }
                else
                {
                    error = 2;
                }
            }
            else
            {
                error = 1;
            }
        }

        if (CreateButton(Cancel))
        {
            resetInputTextBox(MaMB);
            resetInputTextBox(LoaiMayBay);
            resetInputTextBox(SoDong);
            resetInputTextBox(SoDay);
            return true;
        }
    }
    else
    {
        if (Warning_NoData())
            return true;
    }
    return false;
}

bool Popup_XoaMB(DSMB *listMB, MayBay *mb, int &status)
{
    CreatePopupBackground();
    DrawTextEx(FontArial, "Xoá máy bay?",
               {CenterDataSetter(700, StartPos.x + 400, MeasureTextEx(FontArial, "Xoá máy bay", 50, 0).x),
                CenterDataSetter(60, StartPos.y + 60 + 10, MeasureTextEx(FontArial, "A", 50, 0).y)},
               50, 0, BLACK);
    DrawTextEx(FontArial, "Máy bay có các thông tin như sau: ",
               {CenterDataSetter(1100, StartPos.x + 200, MeasureTextEx(FontArial, "Máy bay có các thông tin như sau: ", 40, 0).x),
                CenterDataSetter(50, StartPos.y + 130, MeasureTextEx(FontArial, "A", 40, 0).y)},
               40, 0, RED);

    if (mb->getSoHieuMB()[0] != 0)
    {
        DrawTextEx(FontArial, "Mã máy bay",
                   {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
        DrawRectangleRec({StartPos.x + 300, StartPos.y + 60 + 180, 900, 50}, WHITE);
        DrawRectangleRoundedLines({StartPos.x + 300, StartPos.y + 60 + 180, 900, 50}, 0, 1, 2, BLACK);
        DrawTextEx(FontArial, mb->getSoHieuMB(),
                   {StartPos.x + 300 + 5,
                    CenterDataSetter(60, StartPos.y + 60 + 180, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, BLACK);

        DrawTextEx(FontArial, "Hãng máy bay",
                   {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
        DrawRectangleRec({StartPos.x + 300, StartPos.y + 60 + 280, 900, 50}, WHITE);
        DrawRectangleRoundedLines({StartPos.x + 300, StartPos.y + 60 + 280, 900, 50}, 0, 1, 2, BLACK);
        DrawTextEx(FontArial, mb->getLoaiMB(),
                   {StartPos.x + 300 + 5,
                    CenterDataSetter(60, StartPos.y + 60 + 280, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, BLACK);

        DrawTextEx(FontArial, "Số dòng",
                   {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
        DrawRectangleRec({StartPos.x + 300, StartPos.y + 60 + 380, 500, 50}, WHITE);
        DrawRectangleRoundedLines({StartPos.x + 300, StartPos.y + 60 + 380, 500, 50}, 0, 1, 2, BLACK);
        DrawTextEx(FontArial, intTochar(mb->getSoDong(), 2),
                   {StartPos.x + 300 + 5,
                    CenterDataSetter(60, StartPos.y + 60 + 380, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, BLACK);

        DrawTextEx(FontArial, "Số dãy",
                   {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
        DrawRectangleRec({StartPos.x + 300, StartPos.y + 60 + 480, 500, 50}, WHITE);
        DrawRectangleRoundedLines({StartPos.x + 300, StartPos.y + 60 + 380, 500, 50}, 0, 1, 2, BLACK);
        DrawTextEx(FontArial, intTochar(mb->getSoDay(), 2),
                   {StartPos.x + 300 + 5,
                    CenterDataSetter(60, StartPos.y + 60 + 480, MeasureTextEx(FontArial, "A", 40, 0).y)},
                   40, 0, BLACK);

        Button OK;
        OK.x = StartPos.x + 225 + 750;
        OK.y = StartPos.y + 60 + 625;
        OK.w = 300;
        OK.h = 50;
        OK.gotNothing = false;
        OK.gotText = true;
        OK.tittle = (char *)"Đồng ý!";
        OK.font = FontArial;
        OK.BoMau = ArrowKey;

        Button Cancel;
        Cancel.x = StartPos.x + 225;
        Cancel.y = StartPos.y + 60 + 625;
        Cancel.w = 300;
        Cancel.h = 50;
        Cancel.gotNothing = false;
        Cancel.gotText = true;
        Cancel.tittle = (char *)"Huỷ";
        Cancel.font = FontArial;
        Cancel.BoMau = ArrowKey;

        if (CreateButton(OK))
        {
            char CheckMB[16];
            strcpy(CheckMB, mb->getSoHieuMB());
            listMB->Delete_MB(listMB->Find_MB(CheckMB));

            ofstream fileWrite("../data/dataMB.txt", ios::out | ios::trunc);
            listMB->WritetoFile(fileWrite);
            fileWrite.close();
            ifstream fileRead("../data/dataMB.txt", ios::in);
            listMB->ReadFromFile(fileRead);
            fileRead.close();

            status = -1;

            return true;
        }
        if (CreateButton(Cancel))
        {
            return true;
        }
    }
    else
    {
        if (Warning_NoData())
            return true;
    }
    return false;
}

MayBay *XuLy_QLMB(DSMB *listMB, int &status)
{
    static bool isSearch = false;
    static DSMB *searchResult = new DSMB();
    static MayBay *result;
    static MayBay **data;
    static int index = -1;

    // search
    Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
    DrawRectangleRec(searchText, WHITE);
    DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
    static InputTextBox searchTextBox;
    searchTextBox.textBox = searchText;
    searchTextBox.tittle = "Nhập nội dung tìm kiếm";

    DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

    static char *prev_key_word = new char[259];
    const char *key_word =
        CreateTextInputBox(searchTextBox);
    if (strcmp(prev_key_word, key_word) != 0)
    {

        strcpy(prev_key_word, key_word);
        if (key_word[0] != 0)
        {
            *searchResult = listMB->Find_DSMB(key_word);
            isSearch = true;
        }
        else
            isSearch = false;
    }
    Button button;

    button.x = searchText.x + searchText.width;
    button.y = searchText.y;
    button.w = 200;
    button.h = 50;
    button.BoTron = false;
    button.gotNothing = false;
    button.gotText = true;
    button.tittle = "TÌM KIẾM";
    button.font = FontArial;
    button.BoMau = ArrowKey;

    if (CreateButton(button))
    {
        cout << "Tim kiem" << endl;
    }

    // table
    float cellW[5] = {100, 300, 380, 150, 150};
    CreateTable_QLMB();

    // data
    static int current_page = 1;
    int n_page; // 1 + (spt/10)
    if (status == 1)
    {
        current_page = 1 + (listMB->getsize() - 1) / 10;
        isSearch = false;
        index = (listMB->getsize() - 1) % 10;
        status = 0;
    }
    else if (status == -1)
    {
        current_page = 1;
        isSearch = false;
        index = -1;
        status = 0;
    }
    if (!isSearch)
    {
        n_page = 1 + (listMB->getsize() - 1) / 10;
        data = showList_QLMB(listMB, {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, current_page, cellW);
    }
    else
    {
        n_page = 1 + (searchResult->getsize() - 1) / 10;
        data = showList_QLMB(searchResult, {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, current_page, cellW);
    }

    // Pick data
    Button data_picker[10];

    for (int i = 0; i < 10; i++)
    {
        data_picker[i].x = StartPos.x + 60;
        data_picker[i].y = StartPos.y + 60 + 100 + 80 + 50 + i * 40;
        data_picker[i].w = 1080;
        data_picker[i].h = 40;
        data_picker[i].firstRounder = false;
        data_picker[i].RounderChangeColor = true;
        data_picker[i].BoMau.RounderHovered = YELLOW;
        data_picker[i].BoMau.RounderPressed = RED;
        if (CreateButton(data_picker[i]))
        {
            if (index != i)
            {

                index = i;
            }
            else
                index = -1;
        }
        if (index == i)
            DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y, data_picker[i].w, data_picker[i].h}, 0, 1, 2, GREEN);
    }
    if (index >= 0)
    {
        result = data[index];
    }
    else
        result = new MayBay();

    // page and switch page
    int swp = SwitchPage(current_page, n_page, {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
    if (current_page != swp)
        index = -1;
    current_page = swp;
    if (current_page > n_page)
        current_page = 1;
    return result;
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

MayBay **showList_QLMB(DSMB *listMB, Vector2 start_pos, int current_page, float cellW[])
{
    typedef MayBay *MayBay_ptr;
    MayBay_ptr *result = new MayBay_ptr[10];
    for (int i = 0; i < 10; i++)
    {
        result[i] = new MayBay();
    }
    int size = listMB->getsize();
    int n_char;
    if (size <= 99)
        n_char = 2;
    else if (size >= 100 && size <= 999)
        n_char = 3;
    else
        n_char = 4;
    int i = (current_page - 1) * 10;
    int j;
    if (current_page * 10 < size)
        j = current_page * 10;
    else
    {
        j = size;
        for (int i = size % 10; i < 10; i++)
        {
            result[i] = new MayBay();
        }
    }

    for (i; i < j; i++)
    {
        MayBay *MB = listMB->getMB(i);
        result[i % 10] = MB;
        DrawTextEx(FontArial, intTochar(i + 1, n_char), GetCellTextPos_Mid(start_pos, 5, cellW, 1, (i % 10) + 1, intTochar(i + 1, n_char), 30), 30, 0, BLACK);
        DrawTextEx(FontArial, MB->getSoHieuMB(), GetCellTextPos_Mid(start_pos, 5, cellW, 2, (i % 10) + 1, MB->getSoHieuMB(), 30), 30, 0, BLACK);
        DrawTextEx(FontArial, MB->getLoaiMB(), GetCellTextPos_Mid(start_pos, 5, cellW, 3, (i % 10) + 1, MB->getLoaiMB(), 30), 30, 0, BLACK);
        DrawTextEx(FontArial, intTochar(MB->getSoDay(), 3), GetCellTextPos_Mid(start_pos, 5, cellW, 4, (i % 10) + 1, intTochar(MB->getSoDay(), 3), 30), 30, 0, BLACK);
        DrawTextEx(FontArial, intTochar(MB->getSoDong(), 3), GetCellTextPos_Mid(start_pos, 5, cellW, 5, (i % 10) + 1, intTochar(MB->getSoDong(), 3), 30), 30, 0, BLACK);
    }

    return result;
}

// =-ChuyenBay

void CreatePage_QLCB(DanhSachCB *listCB)
{
    CreatePageBackground(5);
    static ChuyenBay *data = new ChuyenBay();
    static char *preResult = (char *)"\0";
    static int status = 0;
    static int current_popup = 0; // 0-k hien/ 1-them/ 2-sua/ 3-xoa

    // tittle
    DrawTextEx(FontArial, "DANH SÁCH CHUYẾN BAY", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);

    // mini function
    Button button[5];
    for (int i = 0; i < 5; i++)
    {
        button[i].x = StartPos.x + 1201 + 29;
        button[i].y = StartPos.y + 60 + 20 + 70 + 15 + 75 * i;
        button[i].w = 240;
        button[i].h = 60;
        button[i].BoTron = false;
        button[i].gotNothing = false;
        button[i].gotText = true;
        button[i].font = FontArial;
        button[i].BoMau = ArrowKey;
    }
    button[0].tittle = "Thêm chuyến bay";
    if (CreateButton(button[0]))
    {
        cout << "Them" << endl;
    }
    button[1].tittle = "Hiệu chỉnh CB";
    if (CreateButton(button[1]))
    {
        cout << "Sua" << endl;
    }
    button[2].tittle = "Xóa chuyến bay";
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15 + 75 + 75, 240, 60, false, , FontArial, ArrowKey))
    if (CreateButton(button[2]))
    {
        cout << "Xoa" << endl;
    }
    button[3].tittle = "Xem danh sach vé";
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15 + 75 + 75, 240, 60, false, , FontArial, ArrowKey))
    if (CreateButton(button[3]))
    {
        cout << "XemDSVe" << endl;
    }
    button[4].tittle = "Đặt vé";
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15 + 75 + 75, 240, 60, false, , FontArial, ArrowKey))
    if (CreateButton(button[4]))
    {
        cout << "Dat ve" << endl;
    }
    data = XuLy_QLCB(listCB, status);
    // CreateTable_QLCB();
}

void CreateTable_QLCB()
{
    const char *cell_tittle[6] = {"STT", "Mã CB", "Số hiệu MB", "Ngày giờ", "Nơi đến", "TT"};

    float cellW[6] = {90, 230, 230, 200, 180, 150};
    CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 6, cellW, 1080);
    Vector2 *tittle_pos = GetTittlePos({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 6, cellW, cell_tittle);

    for (int i = 0; i < 6; i++)
    {
        DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
    }
}

ChuyenBay *XuLy_QLCB(DanhSachCB *listCB, int &status)
{
    static bool isSearch = false;
    static DanhSachCB *searchResult = new DanhSachCB();
    static ChuyenBay *result;
    static ChuyenBay **data;
    static int index = -1;

    // search
    Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
    DrawRectangleRec(searchText, WHITE);
    DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
    static InputTextBox searchTextBox;
    searchTextBox.textBox = searchText;
    searchTextBox.tittle = "Nhập nội dung tìm kiếm";

    DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

    static char *prev_key_word = new char[259];
    const char *key_word =
        CreateTextInputBox(searchTextBox);
    if (strcmp(prev_key_word, key_word) != 0)
    {

        strcpy(prev_key_word, key_word);
        if (key_word[0] != 0)
        {
            // *searchResult = listCB->LocDSCB(key_word);
            isSearch = true;
        }
        else
            isSearch = false;
    }
    Button button;

    button.x = searchText.x + searchText.width;
    button.y = searchText.y;
    button.w = 200;
    button.h = 50;
    button.BoTron = false;
    button.gotNothing = false;
    button.gotText = true;
    button.tittle = "TÌM KIẾM";
    button.font = FontArial;
    button.BoMau = ArrowKey;

    if (CreateButton(button))
    {
        cout << "Tim kiem" << endl;
    }

    // table
    float cellW[6] = {90, 230, 230, 200, 180, 150};
    CreateTable_QLCB();

    // data
    static int current_page = 1;
    int n_page; // 1 + (spt/10)
    if (status == 1)
    {
        current_page = 1 + (listCB->getSize() - 1) / 10;
        isSearch = false;
        index = (listCB->getSize() - 1) % 10;
        status = 0;
    }
    else if (status == -1)
    {
        current_page = 1;
        isSearch = false;
        index = -1;
        status = 0;
    }
    if (!isSearch)
    {
        n_page = 1 + (listCB->getSize() - 1) / 10;
        data = showList_QLCB(listCB, {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, current_page, cellW);
    }
    else
    {
        n_page = 1 + (searchResult->getSize() - 1) / 10;
        data = showList_QLCB(searchResult, {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, current_page, cellW);
    }

    // Pick data
    Button data_picker[10];

    for (int i = 0; i < 10; i++)
    {
        data_picker[i].x = StartPos.x + 60;
        data_picker[i].y = StartPos.y + 60 + 100 + 80 + 50 + i * 40;
        data_picker[i].w = 1080;
        data_picker[i].h = 40;
        data_picker[i].firstRounder = false;
        data_picker[i].RounderChangeColor = true;
        data_picker[i].BoMau.RounderHovered = YELLOW;
        data_picker[i].BoMau.RounderPressed = RED;
        if (CreateButton(data_picker[i]))
        {
            if (index != i)
            {

                index = i;
            }
            else
                index = -1;
        }
        if (index == i)
            DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y, data_picker[i].w, data_picker[i].h}, 0, 1, 2, GREEN);
    }
    if (index >= 0)
    {
        result = data[index];
    }
    else
        result = new ChuyenBay();

    // page and switch page
    int swp = SwitchPage(current_page, n_page, {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
    if (current_page != swp)
        index = -1;
    current_page = swp;
    if (current_page > n_page)
        current_page = 1;
    return result;
}

ChuyenBay **showList_QLCB(DanhSachCB *listCB, Vector2 start_pos, int current_page, float cellW[])
{
    typedef ChuyenBay *ChuyenBay_ptr;
    ChuyenBay_ptr *result = new ChuyenBay_ptr[10];
    for (int i = 0; i < 10; i++)
    {
        result[i] = new ChuyenBay();
    }
    int size = listCB->getSize();

    int n_char;
    if (size <= 99)
        n_char = 2;
    else if (size >= 100 && size <= 999)
        n_char = 3;
    else
        n_char = 4;
    int i = (current_page - 1) * 10;
    int j;
    if (current_page * 10 < size)
        j = current_page * 10;
    else
    {
        j = size;
        for (int i = size % 10; i < 10; i++)
        {
            result[i] = new ChuyenBay();
        }
    }
    NodeCB *tmp = listCB->getHead();
    for (int k = 0; k < j; k++)
    {
        if (k >= i)
        {
            ChuyenBay *CB = tmp->getNode();

            result[i % 10] = CB;
            DrawTextEx(FontArial, intTochar(k + 1, n_char), GetCellTextPos_Mid(start_pos, 6, cellW, 1, (k % 10) + 1, intTochar(k + 1, n_char), 30), 30, 0, BLACK);
            DrawTextEx(FontArial, CB->getMaCB(), GetCellTextPos_Mid(start_pos, 6, cellW, 2, (k % 10) + 1, CB->getMaCB(), 30), 30, 0, BLACK);
            DrawTextEx(FontArial, CB->getMaMayBay(), GetCellTextPos_Mid(start_pos, 6, cellW, 3, (k % 10) + 1, CB->getMaMayBay(), 30), 30, 0, BLACK);
            DrawTextEx(FontArial, "dd/mm/yyyy hh:mm", GetCellTextPos_Mid(start_pos, 6, cellW, 4, (k % 10) + 1, "dd/mm/yyyy hh:mm", 20), 20, 0, BLACK);
            DrawTextEx(FontArial, CB->getNoiDen().data(), GetCellTextPos_Mid(start_pos, 6, cellW, 5, (k % 10) + 1, CB->getNoiDen().data(), 30), 30, 0, BLACK);
            DrawTextEx(FontArial, intTochar(CB->getTrangThai(), 1), GetCellTextPos_Mid(start_pos, 6, cellW, 6, (k % 10) + 1, intTochar(CB->getTrangThai(), 1), 30), 30, 0, BLACK);
        }
        tmp = tmp->getNext();
    }

    return result;
}

void CreatePage_QLVe()
{
    CreatePageBackground(3);
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
    CreatePageBackground(2);
    DrawTextEx(FontArial, "DANH SÁCH HÀNH KHÁCH", {StartPos.x + 60, CenterDataSetter(100, StartPos.y + 60, MeasureTextEx(FontArial, "A", 60, 0).y)}, 60, 0, BLUE);

    // mini function
    Button button[2];
    for (int i = 0; i < 2; i++)
    {
        button[i].x = StartPos.x + 1201 + 29;
        button[i].y = StartPos.y + 60 + 20 + 70 + 15 + 75 * i;
        button[i].w = 240;
        button[i].h = 60;
        button[i].BoTron = false;
        button[i].gotNothing = false;
        button[i].gotText = true;
        button[i].font = FontArial;
        button[i].BoMau = ArrowKey;
    }
    button[0].tittle = "Quản lý vé";
    if (CreateButton(button[0]))
    {
        cout << "ql ve" << endl;
    }
    button[1].tittle = "Huỷ vé";
    if (CreateButton(button[1]))
    {
        cout << "huy ve" << endl;
    }
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15, 240, 60, false, "Quản lý vé", FontArial, ArrowKey))
    // {
    //     cout << "quan ly ve" << endl;
    // }
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15 + 75, 240, 60, false, "Huỷ vé", FontArial, ArrowKey))
    // {
    //     cout << "huy ve" << endl;
    // }

    CreateTable_QLHK();
    // CreateTable();
}

void CreateTable_QLHK()
{
    const char *cell_tittle[5] = {"STT", "CMND", "Họ", "Tên", "Phái"};

    float cellW[5] = {100, 300, 380, 200, 100};
    CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, 1080);

    Vector2 *tittle_pos = GetTittlePos({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, cell_tittle);

    for (int i = 0; i < 5; i++)
    {
        DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
    }
}

void CreatePage_GioiThieu()
{
    CreatePageBackground(0);
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

    for (int i = 1; i <= soCot; i++)
    {
        Point_row[0][i] = {Point_row[0][i - 1].x + cellW[i - 1], Point_row[0][0].y};
        Point_row[1][i] = {Point_row[1][i - 1].x + cellW[i - 1], Point_row[1][0].y};
        DrawLineEx(Point_row[0][i], Point_row[1][i], 2, BROWN);
    }

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

Vector2 GetCellTextPos_Mid(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text, float fontSize)
{
    Vector2 ans;
    float cellPosX[soCot];
    cellPosX[0] = vitriBang.x;
    for (int i = 1; i < soCot; i++)
    {
        cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
    }
    ans = {CenterDataSetter(cellW[vi_tri_x - 1], cellPosX[vi_tri_x - 1], MeasureTextEx(FontArial, text, fontSize, 0).x),
           CenterDataSetter(40, vitriBang.y + 50 + (vi_tri_y - 1) * 40, MeasureTextEx(FontArial, text, fontSize, 0).y)};
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

    for (int i = 0; i < soCot; i++) //
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

    char *button_tittle[4];
    button_tittle[0] = (char *)"QUẢN LÝ MÁY BAY",
    button_tittle[1] = (char *)"QUẢN LÝ CHUYẾN BAY",
    button_tittle[2] = (char *)"QUẢN LÝ VÉ",
    button_tittle[3] = (char *)"QUẢN LÝ HÀNH KHÁCH";

    Vector2 buttonPos[5] =
        {
            {StartPos.x, StartPos.y},
            {buttonPos[0].x + 60, StartPos.y},
            {buttonPos[1].x + button_width, StartPos.y},
            {buttonPos[2].x + button_width, StartPos.y},
            {buttonPos[3].x + button_width, StartPos.y}};
    Button button[5];
    button[0].x = buttonPos[0].x;
    button[0].y = buttonPos[0].y;
    button[0].w = 60;
    button[0].h = button_height;
    button[0].BoTron = false;
    button[0].gotNothing = false;
    button[0].gotPic = true;
    button[0].picture = PNG_home;
    button[0].BoMau = MauThanhQuanLy;
    for (int i = 1; i < 5; i++)
    {
        button[i].x = buttonPos[i].x;
        button[i].y = buttonPos[i].y;
        button[i].w = button_width;
        button[i].h = button_height;
        button[i].BoTron = false;
        button[i].gotNothing = false;
        button[i].gotText = true;
        button[i].tittle = button_tittle[i - 1];
        button[i].font = FontArial;
        button[i].BoMau = MauThanhQuanLy;
    }
    if (CreateButton(button[0]))
        current_page = 0;
    for (int i = 1; i < 5; i++)
    {
        if (current_page != i)
        {
            if (CreateButton(button[i]))
                current_page = i;
        }
        else
        {
            DrawRectangleRec({buttonPos[i].x, buttonPos[i].y, button_width, button_height}, MauThanhQuanLy.isPressed);
            DrawTextEx(FontArial,
                       button_tittle[i - 1],
                       {CenterDataSetter(button_width, buttonPos[i].x, MeasureTextEx(FontArial, button_tittle[i - 1], button_height / 2.0f, 0).x),
                        button_height / 5.0f + buttonPos[i].y},
                       button_height / 2.0f, 0, MauThanhQuanLy.text2);
        };
    }
}

bool Warning_NoData()
{
    DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330, GRAY);
    DrawRectangle(StartPos.x + 400, StartPos.y + 300, 700, 70, DARKBLUE);
    DrawTextEx(FontArial, "KHÔNG CÓ DỮ LIỆU!",
               {CenterDataSetter(700, StartPos.x + 400, MeasureTextEx(FontArial, "KHÔNG CÓ DỮ LIỆU!", 55, 0).x),
                CenterDataSetter(70, StartPos.y + 300, MeasureTextEx(FontArial, "A", 55, 0).y)},
               55, 0, RED);
    DrawTextEx(FontArial, "- Có vẻ bạn chưa chọn dữ liệu hoặc dữ liệu trống!", {StartPos.x + 200, StartPos.y + 375}, 55, 0, RED);
    DrawTextEx(FontArial, "-> Hãy click vào 1 dòng trong bảng để lấy dữ liệu!", {StartPos.x + 200, StartPos.y + 445}, 55, 0, DARKGREEN);

    Button OK;
    OK.x = StartPos.x + 700;
    OK.y = StartPos.y + 530;
    OK.w = 100;
    OK.h = 50;
    OK.gotNothing = false;
    OK.gotText = true;
    OK.tittle = (char *)"OK";
    OK.font = FontArial;
    OK.BoMau = ArrowKey;

    if (CreateButton(OK))
    {
        return true;
    }
    return false;
}

// ---Các hàm hỗ trợ ngoài vìa------------------------------------------------------------------------------------------------------

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua, float obj_width)
{
    return doDai_khung_chua / 2.0f + vi_tri_khung_chua - obj_width / 2.0f;
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
    char *text = (char *)"trang";

    Button button[2];
    button[0].x = pos.x + 10;
    button[0].y = pos.y + 10;
    button[0].w = 30;
    button[0].h = 30;
    button[0].BoTron = false;
    button[0].gotNothing = false;
    button[0].gotPic = true;
    button[0].BoMau = ArrowKey;
    button[0].picture = PNG_arrowLeft;

    button[1].x = pos.x + 50 + 300 + 10;
    button[1].y = pos.y + 10;
    button[1].w = 30;
    button[1].h = 30;
    button[1].BoTron = false;
    button[1].gotNothing = false;
    button[1].gotPic = true;
    button[1].BoMau = ArrowKey;
    button[1].picture = PNG_arrowRight;
    if (current_page > 1)
    {
        if (CreateButton(button[0]))
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
        if (CreateButton(button[1]))
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
bool CreateButton(Button data)
{
    Rectangle Button = {data.x, data.y, data.w, data.h};
    Vector2 MousePos = {0.0f, 0.0f};
    Vector2 TextPos = {CenterDataSetter(data.w, data.x, MeasureTextEx(data.font, data.tittle, data.h / 2.0f, 0).x),
                       data.h / 5.0f + data.y};
    if (!data.RounderChangeColor)
    {
        data.BoMau.RounderHovered = data.BoMau.Rounder;
        data.BoMau.RounderPressed = data.BoMau.Rounder;
    }
    // DrawRectangleRec(Button, BoMau.isnotHovered);
    if (data.BoTron)
    {
        if (!data.gotNothing)
            DrawRectangleRounded(Button, 0.5f, 0.5f, data.BoMau.isnotHovered);
        if (data.gotText)
            DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text1);
        else if (data.gotPic)
            DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
        if (data.firstRounder)
            DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, data.BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                if (!data.gotNothing)
                    DrawRectangleRounded(Button, 0.5f, 0.5f, data.BoMau.isPressed);
                if (data.gotText)
                    DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text2);
                else if (data.gotPic)
                    DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
                DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, data.BoMau.RounderPressed);
            }
            else
            {
                if (!data.gotNothing)
                    DrawRectangleRounded(Button, 0.5f, 0.5f, data.BoMau.isHovered);
                if (data.gotText)
                    DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text1);
                else if (data.gotPic)
                    DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
                DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, data.BoMau.RounderHovered);
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    else
    {
        if (!data.gotNothing)
            DrawRectangleRec(Button, data.BoMau.isnotHovered);
        if (data.gotText)
            DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text1);
        else if (data.gotPic)
            DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
        if (data.firstRounder)
            DrawRectangleRoundedLines(Button, 0, 0, 2, data.BoMau.Rounder);
        MousePos = GetVMousePosition();

        if (CheckCollisionPointRec(MousePos, Button))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                if (!data.gotNothing)
                    DrawRectangleRec(Button, data.BoMau.isPressed);
                if (data.gotText)
                    DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text2);
                else if (data.gotPic)
                    DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
                DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, data.BoMau.RounderPressed);
            }
            else
            {
                if (!data.gotNothing)
                    DrawRectangleRec(Button, data.BoMau.isHovered);
                if (data.gotText)
                    DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0, data.BoMau.text2);
                else if (data.gotPic)
                    DrawTextureEx(data.picture, {data.x, data.y}, 0, 1, data.BoMau.isnotHovered);
                DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2, data.BoMau.RounderHovered);
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
            else
                return false;
        }
    }
    return false;
}

const char *CreateTextInputBox(InputTextBox &data)
{
    char name_cpy[data.size] = "\0";
    char *result = new char[data.size];
    const int font_size = data.textBox.height * per1000(700);

    Vector2 textBoxPos = {data.textBox.x + 5, CenterDataSetter(data.textBox.height, data.textBox.y, MeasureTextEx(FontArial, data.name, font_size, 0).y)};
    Vector2 MousePos = {0.0f, 0.0f};
    strcpy(name_cpy, data.name);
    name_cpy[data.letterCount + data.indexPoint] = '\0';

    Vector2 textBoxDot = {data.textBox.x + MeasureTextEx(FontArial, name_cpy, font_size, 0).x, CenterDataSetter(data.textBox.height, data.textBox.y, MeasureTextEx(FontArial, name_cpy, font_size, 0).y)};
    strcpy(result, data.name);

    if (data.editMode && data.name[0] == 0)
    {
        strcpy(data.name, data.tittle);
        data.letterCount = getCharSize(data.name);
    }

    MousePos = GetVMousePosition();
    if (CheckCollisionPointRec(MousePos, data.textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        data.mouseClickOnText = true;
        data.done = false;
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        data.mouseClickOnText = false;
        if (!data.showPreResult)
        {
            data.name[0] = '\0';
            data.indexPoint = 0;
            data.letterCount = 0;
        }
        data.done = true;
    }
    else if (!CheckCollisionPointRec(MousePos, data.textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        data.mouseClickOnText = false;

    if (CheckCollisionPointRec(MousePos, data.textBox))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    }
    else
    {
        SetMouseCursor(1);
    }

    if (data.mouseClickOnText)
    {
        data.framesCounter++;
        int key = GetCharPressed();
        while (key > 0)
        {
            switch (data.mode)
            {
            case 1:
            {
                if ((key >= 32) && (key <= 125) && (data.letterCount < data.size))
                {
                    if (((key >= 'a') && (key <= 'z')))
                        key -= 32;
                    for (int i = data.letterCount; i > data.letterCount + data.indexPoint; i--)
                    {
                        data.name[i] = data.name[i - 1];
                    }
                    data.name[data.letterCount + data.indexPoint] = char(key);
                    data.name[data.letterCount + 1] = '\0';
                    data.letterCount++;
                }
                break;
            };
            case 2:
            {
                if ((((key >= '0') && (key <= '9')) || ((key >= 'a') && (key <= 'z')) ||
                     ((key >= 'A') && (key <= 'Z'))) &&
                    (data.letterCount < data.size))
                {
                    for (int i = data.letterCount; i > data.letterCount + data.indexPoint; i--)
                    {
                        data.name[i] = data.name[i - 1];
                    }
                    data.name[data.letterCount + data.indexPoint] = char(key);
                    data.name[data.letterCount + 1] = '\0';
                    data.letterCount++;
                }
                break;
            }
            case 3:
            {
                if ((((key >= '0') && (key <= '9')) || ((key >= 'a') && (key <= 'z')) ||
                     ((key >= 'A') && (key <= 'Z'))) &&
                    (data.letterCount < data.size))
                {
                    if ((key >= 'a') && (key <= 'z'))
                        key -= 32;
                    for (int i = data.letterCount; i > data.letterCount + data.indexPoint; i--)
                    {
                        data.name[i] = data.name[i - 1];
                    }
                    data.name[data.letterCount + data.indexPoint] = char(key);
                    data.name[data.letterCount + 1] = '\0';
                    data.letterCount++;
                }
                break;
            }

            case 4:
            {
                if ((((key >= 'a') && (key <= 'z')) ||
                     ((key >= 'A') && (key <= 'Z'))) &&
                    (data.letterCount < data.size))
                {
                    if (((key >= 'a') && (key <= 'z')))
                        key -= 32;
                    for (int i = data.letterCount; i > data.letterCount + data.indexPoint; i--)
                    {
                        data.name[i] = data.name[i - 1];
                    }
                    data.name[data.letterCount + data.indexPoint] = char(key);
                    data.name[data.letterCount + 1] = '\0';
                    data.letterCount++;
                }
                break;
            }
            case 5:
            {
                if (((key >= '0') && (key <= '9')) &&
                    (data.letterCount < data.size))
                {
                    for (int i = data.letterCount; i > data.letterCount + data.indexPoint; i--)
                    {
                        data.name[i] = data.name[i - 1];
                    }
                    data.name[data.letterCount + data.indexPoint] = char(key);
                    data.name[data.letterCount + 1] = '\0';
                    data.letterCount++;
                }
                break;
            }
            }

            key = GetCharPressed();
        }
        if (IsKeyDown(KEY_BACKSPACE))
            data.fHold_BS++;
        else
            data.fHold_BS = 0;
        if (IsKeyDown(KEY_RIGHT))
            data.fHold_RIGHT++;
        else
            data.fHold_RIGHT = 0;
        if (IsKeyDown(KEY_LEFT))
            data.fHold_LEFT++;
        else
            data.fHold_LEFT = 0;
        if ((IsKeyDown(KEY_BACKSPACE) &&
             data.letterCount + data.indexPoint > 0 &&
             (data.fHold_BS > 60) && (data.fHold_BS % 3 == 0)) ||
            IsKeyPressed(KEY_BACKSPACE) && data.letterCount + data.indexPoint > 0)
        {
            for (int i = data.letterCount + data.indexPoint - 1; i < data.letterCount; i++)
            {
                data.name[i] = data.name[i + 1];
            }
            data.letterCount--;
            if (data.letterCount < 0)
                data.letterCount = 0;
            data.name[data.letterCount] = '\0';
        }
        if ((IsKeyDown(KEY_LEFT) &&
             (data.letterCount + data.indexPoint) > 0 &&
             (data.fHold_LEFT > 60) && (data.fHold_LEFT % 3 == 0)) ||
            (IsKeyPressed(KEY_LEFT) && (data.letterCount + data.indexPoint) > 0))
        {
            data.indexPoint--;
        }
        if ((IsKeyDown(KEY_RIGHT) &&
             data.indexPoint < 0 &&
             (data.fHold_RIGHT > 60) &&
             (data.fHold_RIGHT % 3 == 0)) ||
            (IsKeyPressed(KEY_RIGHT) && data.indexPoint < 0))
        {
            data.indexPoint++;
        }
    }
    else
        data.framesCounter = 0;
    DrawRectangleRec(data.textBox, data.MauNen);
    DrawRectangleRoundedLines(data.textBox, 0, 1, 2, data.MauVien);
    if (data.showNKeyRemain)
    {
        DrawTextEx(FontArial, intTochar(data.size - data.letterCount, 2),
                   {data.textBox.x + data.textBox.width - data.textBox.height, data.textBox.y + data.textBox.height / 2},
                   data.textBox.height * per1000(400), 0, DARKGREEN);
    }
    if (data.name[0] != '\0')
        DrawTextEx(FontArial, data.name, textBoxPos, font_size, 0, data.MauChu);
    else
        DrawTextEx(FontArial, data.tittle, textBoxPos, font_size, 0, data.MauChu);
    // cout << "index: " << indexPoint << endl;
    if (data.mouseClickOnText && ((data.framesCounter % 120 >= 15)))
        DrawTextEx(FontArial, "|", textBoxDot, font_size, 0, MAROON);
    if (!data.returnIfDone)
        return result;
    else
    {
        if (data.done)
            return result;
        else
            return "\0";
    };
    return "\0";
}
void resetInputTextBox(InputTextBox &box)
{
    box.name[0] = 0;
    box.fHold_BS = 0;
    box.fHold_RIGHT = 0;
    box.fHold_LEFT = 0;
    box.done = true;
    box.mouseClickOnText = false;
    box.letterCount = 0;
    box.framesCounter = 0;
    box.indexPoint = 0;
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

//==================================================================================================================================
// main function
void mainGraphics()
{
    ifstream DataMB("../data/dataMB.txt", ios::in);
    DSMB *listMB = new DSMB();
    listMB->ReadFromFile(DataMB);
    DataMB.close();

    ifstream DataCB("../data/dataCB.txt", ios::in);
    DanhSachCB *listCB = new DanhSachCB();
    listCB->ReadFromFile(DataCB);
    DataCB.close();

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
            CreatePage_QLMB(listMB);
            break;
        }
        case 2:
        {
            CreatePage_QLCB(listCB);
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