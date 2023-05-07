#include "../header/dohoa.h"

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
// int current_page = 0;

Vector2 StartPos{per1000(10) * SCREEN_WIDTH, per1000(40) * SCREEN_HEIGHT};

Font FontArial;
Texture2D PNG_logo; // Load ảnh vào biến (ram)

Texture2D PNG_home;

Texture2D PNG_arrowLeft;
Texture2D PNG_arrowRight;

Texture2D PNG_tick;
Texture2D PNG_circleGreen;
Texture2D PNG_circleYellow;
Texture2D PNG_circleGray;
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
  bool done = true;
  bool mouseClickOnText = false;
  int letterCount = 0;
  int framesCounter = 0;
  int indexPoint = 0;
};

struct TextBox
{
  const char *text;
  Rectangle box;
  bool showBox = false;
  int mode = 1;
  bool isCenter = false;
  int fontSize = 0;
};

struct QLMB_data
{
  MayBay *data = NULL;
  int status = 0;

  int current_popup = 0;
  string popup_errorMess = "";
  int time_showError = 0;
  InputTextBox MaMB, LoaiMB, SoDong, SoDay;

  int pickdata_index = -1;
  const char *keyword;
  InputTextBox searchKeyword;
  int current_showPage = 1;
};

struct QLHK_data
{
  NodeHK *data;
  int status = 0;

  int current_popup = 0;

  int pickdata_index = -1;
  int current_page = 1;

  InputTextBox i_CMND, i_Ho, i_Ten;
};

struct QLVe_data
{
  int current_page = 1;
  int position = -1;
  int pickdata_index = -1;
  VeMayBay data = VeMayBay();
};

struct QLCB_data
{
  NodeCB *data = nullptr;
  DsMayBay dsachMB;
  DsHanhKhach dsachHK;
  int status = 0;

  int current_popup = 0;
  string popup_errorMess = "";
  int time_showError = 0;
  InputTextBox MaCB, MaMB, NoiDen, Ngay, Thang, Nam, Gio, Phut;
  bool inChooseMB = false;
  QLMB_data dataMB;
  QLVe_data dataDSVe;
  QLHK_data dataDSHK;

  InputTextBox searchMaCB, searchNoiDen, searchNgay, searchThang, searchNam;
  int pickdata_index = -1;
  int current_showPage = 1;

  bool inSetTicket = false;
  bool gotNewTicket = false;
};
struct UIcontroller
{
  int current_tab = 0;
  QLMB_data dataTabMB;
  QLCB_data dataTabCB;
  QLHK_data dataTabHK;

  DsMayBay listMB;
  DsChuyenBay listCB;
  DsHanhKhach listHK;
};

void UI_switchTab(UIcontroller &control, int idTab)
{
  InitUIData(control);

  setDataToFile(control.listCB, control.listMB, control.listHK);
  getDataFromFile(control.listCB, control.listMB, control.listHK);

  if (control.current_tab != 0)
  {
    resetData_QLCB(control.dataTabCB);
    resetData_QLMB(control.dataTabMB);
    resetData_QLHK(control.dataTabHK);
  }

  if (idTab == 2)
  {
    control.dataTabCB.dsachMB = control.listMB;
    control.dataTabCB.dsachHK = control.listHK;
  }

  control.current_tab = idTab;
}
void InitUIData(UIcontroller &control)
{
  control.current_tab = 0;
  resetData_QLMB(control.dataTabMB);

  resetData_QLCB(control.dataTabCB);
  // resetData_QLVe(control.dataTabCB.dataDSVe);
  resetData_QLMB(control.dataTabCB.dataMB);
  resetData_QLHK(control.dataTabCB.dataDSHK);

  resetData_QLHK(control.dataTabHK);
}

void resetData_QLMB(QLMB_data &data)
{
  data.data = nullptr;
  data.status = 0;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;
  resetInputTextBox(data.MaMB);
  data.MaMB.mode = 3;
  data.MaMB.tittle = (char *)"Nhập số hiệu máy bay";
  data.MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
  data.MaMB.size = 15;
  resetInputTextBox(data.LoaiMB);
  data.LoaiMB.mode = 2;
  data.LoaiMB.tittle = (char *)"Nhập loại máy bay";
  data.LoaiMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  data.LoaiMB.size = 40;
  resetInputTextBox(data.SoDong);
  data.SoDong.mode = 5;
  data.SoDong.tittle = (char *)"Nhập số dòng của máy bay";
  data.SoDong.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
  data.SoDong.size = 3;
  resetInputTextBox(data.SoDay);
  data.SoDay.mode = 5;
  data.SoDay.tittle = (char *)"Nhập số dãy của máy bay";
  data.SoDay.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
  data.SoDay.size = 3;

  data.pickdata_index = -1;
  data.keyword = "";
  resetInputTextBox(data.searchKeyword);
  data.searchKeyword.mode = 3;
  data.searchKeyword.tittle = "Nhập nội dung tìm kiếm";
  data.current_showPage = 1;
}

void resetData_QLCB(QLCB_data &data)
{
  resetInputTextBox(data.MaCB);
  data.MaCB.mode = 3;
  data.MaCB.tittle = (char *)"Nhập mã chuyến bay";
  data.MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  data.MaCB.size = 15;

  resetInputTextBox(data.MaMB);
  data.MaMB.mode = 3;
  data.MaMB.tittle = (char *)"Nhập số hiệu máy bay";
  data.MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 900, 50};
  data.MaMB.size = 40;

  resetInputTextBox(data.NoiDen);
  data.NoiDen.mode = 1;
  data.NoiDen.tittle = (char *)"Nhập nơi đến";
  data.NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
  data.NoiDen.size = 40;

  resetInputTextBox(data.Ngay);
  data.Ngay.mode = 6;
  data.Ngay.tittle = (char *)"DD";
  data.Ngay.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 60, 50};
  data.Ngay.size = 2;
  data.Ngay.showNKeyRemain = false;

  resetInputTextBox(data.Thang);
  data.Thang.mode = 7;
  data.Thang.tittle = (char *)"MM";
  data.Thang.textBox = {StartPos.x + 300 + 70, StartPos.y + 60 + 180, 60, 50};
  data.Thang.size = 2;
  data.Thang.showNKeyRemain = false;

  resetInputTextBox(data.Nam);
  data.Nam.mode = 8;
  data.Nam.tittle = (char *)"YYYY";
  data.Nam.textBox = {StartPos.x + 300 + 70 + 70, StartPos.y + 60 + 180, 120,
                      50};
  data.Nam.size = 4;
  data.Nam.showNKeyRemain = false;

  resetInputTextBox(data.Gio);
  data.Gio.mode = 9;
  data.Gio.tittle = (char *)"HH";
  data.Gio.textBox = {StartPos.x + 300 + 70 + 70 + 150, StartPos.y + 60 + 180,
                      60, 50};
  data.Gio.size = 2;
  data.Gio.showNKeyRemain = false;

  resetInputTextBox(data.Phut);
  data.Phut.mode = 10;
  data.Phut.tittle = (char *)"MM";
  data.Phut.textBox = {StartPos.x + 300 + 70 + 70 + 150 + 70,
                       StartPos.y + 60 + 180, 60, 50};
  data.Phut.size = 2;
  data.Phut.showNKeyRemain = false;

  resetInputTextBox(data.searchNoiDen);
  data.searchNoiDen.tittle = "Nơi đến";
  data.searchNoiDen.size = 20;
  data.searchNoiDen.mode = 1;

  // data.searchNgay.textBox = boxNgay;
  // data.searchNgay.tittle = "DD";
  // data.searchNgay.mode = 6;
  // data.searchNgay.size = 2;
  // data.searchNgay.showNKeyRemain = false;

  // data.searchThang.textBox = boxThang;
  // data.searchThang.tittle = "MM";
  // data.searchThang.size = 2;
  // data.searchThang.mode = 7;
  // data.searchThang.showNKeyRemain = false;

  // data.searchNam.textBox = boxNam;
  // data.data.searchNam.tittle = "YYYY";
  // data.searchNam.size = 4;
  // data.searchNam.mode = 8;
  // data.searchNam.showNKeyRemain = false;

  resetInputTextBox(data.searchMaCB);
  data.searchMaCB.tittle = "Mã chuyến bay";
  data.searchMaCB.size = 15;
  data.searchMaCB.mode = 3;

  resetData_QLMB(data.dataMB);
  resetData_QLVe(data.dataDSVe);

  data.data = NULL;
  data.status = 0;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;
  data.inChooseMB = false;

  data.pickdata_index = -1;
  data.current_showPage = 1;
}

void resetData_QLHK(QLHK_data &data)
{
  data.data;
  data.status = 0;

  data.current_popup = 0;

  data.pickdata_index = -1;
  data.current_page = 1;

  resetInputTextBox(data.i_CMND);
  data.i_CMND.mode = 3;
  data.i_CMND.tittle = (char *)"Nhập số CMND/CCCD";
  data.i_CMND.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  data.i_CMND.size = 15;

  resetInputTextBox(data.i_Ho);
  data.i_Ho.mode = 3;
  data.i_Ho.tittle = (char *)"Nhập họ và tên đệm";
  data.i_Ho.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 580, 50};
  data.i_Ho.size = 40;

  resetInputTextBox(data.i_Ten);
  data.i_Ten.mode = 1;
  data.i_Ten.tittle = (char *)"Nhập tên";
  data.i_Ten.textBox = {StartPos.x + 300 + 600, StartPos.y + 60 + 380, 300, 50};
  data.i_Ten.size = 40;
}

void resetData_QLVe(QLVe_data &data)
{
  data.current_page = 1;
  data.position = -1;
  data.data = VeMayBay();
}

BoMauNut HomeButtonColor{{153, 255, 153, 255},
                         {80, 255, 80, 255},
                         {50, 50, 255, 255},
                         BLACK,
                         WHITE,
                         GREEN};

BoMauNut ArrowKey{{175, 175, 175, 255},
                  {100, 100, 100, 255},
                  {50, 50, 50, 250},
                  BLACK,
                  BLACK,
                  BLACK};

BoMauNut MauThanhQuanLy{
    {126, 100, 179, 255},
    {86, 42, 176, 255},
    {171, 249, 255, 255},
    WHITE,
    BLACK,
    {25, 25, 255, 255},

};

Vector2 operator-(const Vector2 first, const Vector2 second)
{
  return {first.x - second.x, first.y - second.y};
}

Vector2 operator+(const Vector2 first, const Vector2 second)
{
  return {first.x + second.x, first.y + second.y};
}

void LoadResources()
{
  Image LogoPTIT;
  Image HomeIcon;
  Image ArrowLeft;
  Image Status_Tick;
  Image Status_Green;
  Image Status_Yellow;
  Image Status_Gray;

  UnloadResources();
  FontArial = LoadFontEx("../src/font/arial.ttf", 72, 0, 9812);
  // FontArial = LoadFontEx("c:/Windows/Fonts/arial.ttf", 96, 0, 9812);
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

  Status_Tick = LoadImage("../src/img/status_tick.png");
  ImageResize(&Status_Tick, 34, 34);
  PNG_tick = LoadTextureFromImage(Status_Tick);

  Status_Green = LoadImage("../src/img/status_green.png");
  ImageResize(&Status_Green, 34, 34);
  PNG_circleGreen = LoadTextureFromImage(Status_Green);

  Status_Gray = LoadImage("../src/img/status_gray.png");
  ImageResize(&Status_Gray, 34, 34);
  PNG_circleGray = LoadTextureFromImage(Status_Gray);

  Status_Yellow = LoadImage("../src/img/status_yellow.png");
  ImageResize(&Status_Yellow, 34, 34);
  PNG_circleYellow = LoadTextureFromImage(Status_Yellow);

  UnloadImage(LogoPTIT);
  UnloadImage(HomeIcon);
  UnloadImage(ArrowLeft);
  UnloadImage(Status_Tick);
  UnloadImage(Status_Green);
  UnloadImage(Status_Yellow);
  UnloadImage(Status_Gray);
}

void UnloadResources()
{
  UnloadFont(FontArial);

  UnloadTexture(PNG_logo);
  UnloadTexture(PNG_home);
  UnloadTexture(PNG_arrowLeft);
  UnloadTexture(PNG_arrowRight);
  UnloadTexture(PNG_tick);
  UnloadTexture(PNG_circleGreen);
  UnloadTexture(PNG_circleYellow);
  UnloadTexture(PNG_circleGray);
}

void SetSizeWindow()
{
  int display = GetCurrentMonitor();

  int MONITOR_WIDTH = GetMonitorWidth(display),
      MONITOR_HEIGHT = GetMonitorHeight(display);
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

//---Home
// page----------------------------------------------------------------------------------------------------------------------
void CreateHomeBackground()
{
  ClearBackground(DARKBLUE);
  const int home_tittle_h = 60;
  Rectangle mainScreen = {StartPos.x, StartPos.y + home_tittle_h, SCREEN_WIDTH,
                          SCREEN_HEIGHT - home_tittle_h};
  DrawRectangleRec(mainScreen, WHITE);
}

void CreateHomePage(UIcontroller &control)
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
  Rectangle pngScreen = {StartPos.x, StartPos.y + home_tittle_h, png_screen_w,
                         SCREEN_HEIGHT - home_tittle_h};
  // Thanh chia màn hình
  Rectangle splitScreen = {pngScreen.x + png_screen_w, pngScreen.y,
                           split_screen_w, SCREEN_HEIGHT - home_tittle_h};
  // Màn hình chứa nút chọn chức năng
  Rectangle buttonScreen = {splitScreen.x + splitScreen.width, splitScreen.y,
                            button_screen_w, SCREEN_HEIGHT - home_tittle_h};

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
  Vector2 tittleHomePos = {
      CenterDataSetter(SCREEN_WIDTH, StartPos.x,
                       MeasureTextEx(FontArial, home_tittle, 50, 0).x),
      StartPos.y};
  Vector2 tittleButtonPos = {
      CenterDataSetter(button_screen_w, buttonScreen.x,
                       MeasureTextEx(FontArial, button_tille, 40, 0).x),
      buttonScreen.y + button_tittle_margin_top};

  // Vị trí ảnh
  Vector2 pngPos = {pngScreen.x, pngScreen.y};
  Vector2 buttonPos[5] = {
      {CenterDataSetter(button_screen_w, buttonScreen.x, button_width),
       tittleButtonPos.y + button_tittle_h + button_tittle_margin_bot +
           button_margin_topbot},
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
        UI_switchTab(control, i + 1);
      }
    }
  }
}

// ---Các trang thành
// phần----------------------------------------------------------------------------------------------------------
void CreatePageBackground(int SoHang)
{
  ClearBackground(DARKBLUE);
  const int home_tittle_h = 60;
  Rectangle mainScreen = {StartPos.x, StartPos.y + home_tittle_h, 1199,
                          SCREEN_HEIGHT - home_tittle_h};
  Rectangle funcScreen = {StartPos.x + 1201, StartPos.y + home_tittle_h, 299,
                          SCREEN_HEIGHT - home_tittle_h};
  Rectangle splitScreen = {mainScreen.x + 1199, mainScreen.y,
                           2, // dày 2
                           SCREEN_HEIGHT - home_tittle_h};
  DrawRectangleRec(mainScreen, WHITE);
  DrawRectangleRoundedLines(mainScreen, 0, 1, 2, RED);
  DrawRectangleRec(funcScreen, WHITE);
  DrawRectangleRoundedLines(funcScreen, 0, 1, 2, RED);

  DrawRectangleRec(splitScreen, BLACK);
  for (int i = 0; i < SoHang; i++)
  {
    DrawRectangle(funcScreen.x + 29, funcScreen.y + 105 + 75 * i, 240, 60,
                  GRAY);
    // DrawRectangle(funcScreen.x + 29, funcScreen.y + 180, 240, 60, GRAY);
    // DrawRectangle(funcScreen.x + 29, funcScreen.y + 255, 240, 60, GRAY);
  }

  if (SoHang != 0)
  {
    DrawTextEx(
        FontArial, "Chức năng",
        {CenterDataSetter(300, funcScreen.x - 1,
                          MeasureTextEx(FontArial, "Chức năng", 55, 0).x),
         CenterDataSetter(70, funcScreen.y + 10,
                          MeasureTextEx(FontArial, "Chức năng", 55, 0).y)},
        55, 0, BLUE);
  }
}

// =-MayBay
void CreatePage_QLMB(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  CreatePageBackground(4);

  // tittle
  DrawTextEx(FontArial, "DANH SÁCH MÁY BAY",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);

  if (tabMB_data.current_popup == 0)
  {
    Button button[4];
    for (int i = 0; i < 4; i++)
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
      tabMB_data.current_popup = 1;
    }
    button[1].tittle = "Hiệu chỉnh máy bay";
    if (CreateButton(button[1]))
    {

      tabMB_data.current_popup = 2;
    }
    button[2].tittle = "Xoá máy bay";
    if (CreateButton(button[2]))
    {
      tabMB_data.current_popup = 3;
    }
    button[3].tittle = "Thống kê S.lượt bay";
    if (CreateButton(button[3]))
    {
      tabMB_data.current_popup = 4;
    }
    tabMB_data.data = XuLy_QLMB(listMB, tabMB_data);
    // if (data->getSoHieuMB()[0] >= 36)
    // {
    //     preResult = data->getSoHieuMB();
    // }
  }
  else if (tabMB_data.current_popup == 1)
  {
    if (Popup_ThemMB(listMB, tabMB_data))
      tabMB_data.current_popup = 0;
  }
  else if (tabMB_data.current_popup == 2)
  {
    if (Popup_HieuChinhMB(listMB, tabMB_data))
      tabMB_data.current_popup = 0;
  }
  else if (tabMB_data.current_popup == 3)
  {
    if (Popup_XoaMB(listMB, tabMB_data))
      tabMB_data.current_popup = 0;
  }
  else if (tabMB_data.current_popup == 4)
  {
    if (Popup_Thongkesoluotbay(listMB, tabMB_data))
      tabMB_data.current_popup = 0;
  }
  // cout << data->getSoHieuMB() << endl;
}

void CreatePopupBackground()
{
  DrawRectangle(StartPos.x, StartPos.y + 60, SCREEN_WIDTH, SCREEN_HEIGHT - 60,
                {129, 150, 212, 255});
  DrawRectangle(StartPos.x + 400, StartPos.y + 60 + 10, 700, 60,
                {104, 112, 217, 255});
}

bool Popup_ThemMB(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Thêm máy bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Thêm máy bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;

  DrawTextEx(FontArial, "Mã máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaMB = CreateTextInputBox(tabMB_data.MaMB);
  DrawTextEx(FontArial, "Hãng máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  const char *newLoaiMayBay = CreateTextInputBox(tabMB_data.LoaiMB);
  DrawTextEx(FontArial, "Số dòng",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nho hon hoac bang 25)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newSoDong = CreateTextInputBox(tabMB_data.SoDong);
  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nho hon hoac bang 12)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  const char *newSoDay = CreateTextInputBox(tabMB_data.SoDay);

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
  
  DrawTextEx(
      FontArial, strToChar(tabMB_data.popup_errorMess),
      {CenterDataSetter(
           1100, StartPos.x + 200,
           MeasureTextEx(FontArial, strToChar(tabMB_data.popup_errorMess), 40, 0).x),
       CenterDataSetter(50, StartPos.y + 130,
                        MeasureTextEx(FontArial, "A", 40, 0).y)},
      40, 0, RED);

  if (CreateButton(OK))
  {
    char CheckMB[16];
    strcpy(CheckMB, newMaMB);
    if (listMB.findPosMB(CheckMB) < 0)
    {
      if (newMaMB[0] >= 32 && newLoaiMayBay[0] >= 32 && newSoDay[0] >= 32 &&
          newSoDong[0] >= 32)
      {
        if (atoi(newSoDong) < 1 || atoi(newSoDong) > 25)
        {
          tabMB_data.popup_errorMess = "So dong khong hop le!";
          return false;
        }
        if (atoi(newSoDay) < 1 || atoi(newSoDay) > 12)
        {
          tabMB_data.popup_errorMess = "So day khong hop le!";
          return false;
        }
        if (atoi(newSoDong) * atoi(newSoDay) < 20)
        {
          tabMB_data.popup_errorMess = "So cho phai lon hon hoac bang 20!";
          return false;
        }
        MayBay *result =
            new MayBay(newMaMB, newLoaiMayBay, atoi(newSoDay), atoi(newSoDong));
        listMB.insertMB(result);
        listMB.writetoFileWhenAdd();

        tabMB_data.status = 1;
        resetInputTextBox(tabMB_data.MaMB);
        resetInputTextBox(tabMB_data.LoaiMB);
        resetInputTextBox(tabMB_data.SoDong);
        resetInputTextBox(tabMB_data.SoDay);
        tabMB_data.popup_errorMess = "";

        return true;
      }
      else
      {
        tabMB_data.popup_errorMess = "Nhập chưa đủ thông tin!";
      }
    }
    else
    {
      tabMB_data.popup_errorMess = "Máy Bay đã tồn tại!";
    }
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(tabMB_data.MaMB);
    resetInputTextBox(tabMB_data.LoaiMB);
    resetInputTextBox(tabMB_data.SoDong);
    resetInputTextBox(tabMB_data.SoDay);

    tabMB_data.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_HieuChinhMB(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  CreatePopupBackground();
  DrawTextEx(FontArial, "Sửa thông tin máy bay",
             {CenterDataSetter(
                  700, StartPos.x + 400,
                  MeasureTextEx(FontArial, "Sửa thông tin máy bay", 50, 0).x),
              CenterDataSetter(60, StartPos.y + 60 + 10,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLACK);

  if (tabMB_data.data != NULL)
  {
    tabMB_data.MaMB.editMode = true;
    tabMB_data.MaMB.tittle = tabMB_data.data->getSoHieuMB();
    tabMB_data.LoaiMB.editMode = true;
    tabMB_data.LoaiMB.tittle = tabMB_data.data->getLoaiMB();
    tabMB_data.SoDong.editMode = true;
    tabMB_data.SoDong.tittle = intToChar(tabMB_data.data->getSoDong(), 3);
    tabMB_data.SoDay.editMode = true;
    tabMB_data.SoDay.tittle = intToChar(tabMB_data.data->getSoDay(), 3);

    const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                           MeasureTextEx(FontArial, "A", 25, 0).y;

    DrawTextEx(FontArial, "Mã máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
    DrawTextEx(
        FontArial, "(Gồm chữ cái IN HOA và số)",
        {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25}, 25,
        0, RED);
    const char *newMaMB = CreateTextInputBox(tabMB_data.MaMB);
    DrawTextEx(FontArial, "Hãng máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
    DrawTextEx(
        FontArial, "(Gồm chữ cái và số)",
        {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25}, 25,
        0, RED);
    const char *newLoaiMB = CreateTextInputBox(tabMB_data.LoaiMB);
    DrawTextEx(FontArial, "Số dòng",
               {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
    DrawTextEx(
        FontArial, "(Gồm CHỈ số, nho hon hoac bang 25)",
        {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25}, 25,
        0, RED);
    const char *newSoDong = CreateTextInputBox(tabMB_data.SoDong);
    DrawTextEx(FontArial, "Số dãy",
               {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
    DrawTextEx(
        FontArial, "(Gồm CHỈ số, nho hon hoac bang 12)",
        {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25}, 25,
        0, RED);
    const char *newSoDay = CreateTextInputBox(tabMB_data.SoDay);

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

    DrawTextEx(
        FontArial, strToChar(tabMB_data.popup_errorMess),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, strToChar(tabMB_data.popup_errorMess), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);

    if (CreateButton(OK))
    {
      char CheckMB[16];
      strcpy(CheckMB, newMaMB);
      if (listMB.findPosMB(CheckMB) < 0 ||
          listMB.findPosMB(CheckMB) ==
              listMB.findPosMB(tabMB_data.data->getSoHieuMB()))
      {
        if (newMaMB[0] >= 32 && newLoaiMB[0] >= 32 && newSoDay[0] >= 32 &&
            newSoDong[0] >= 32)
        {
          if (atoi(newSoDong) < 1 || atoi(newSoDong) > 25)
          {
            tabMB_data.popup_errorMess = "So dong khong hop le!";
            return false;
          }
          if (atoi(newSoDay) < 1 || atoi(newSoDay) > 12)
          {
            tabMB_data.popup_errorMess = "So day khong hop le!";
            return false;
          }
          if (atoi(newSoDong) * atoi(newSoDay) < 20)
          {
            tabMB_data.popup_errorMess = "So cho phai lon hon hoac bang 20!";
            return false;
          }
          tabMB_data.data->setSoHieuMB(newMaMB);
          tabMB_data.data->setLoaiMB(newLoaiMB);
          tabMB_data.data->setSoDong(atoi(newSoDong));
          tabMB_data.data->setSoDay(atoi(newSoDay));

          listMB.writetoFile();

          resetInputTextBox(tabMB_data.MaMB);
          resetInputTextBox(tabMB_data.LoaiMB);
          resetInputTextBox(tabMB_data.SoDong);
          resetInputTextBox(tabMB_data.SoDay);
          tabMB_data.popup_errorMess = "";

          return true;
        }
        else
        {
          tabMB_data.popup_errorMess = "Nhập chưa đủ thông tin!";
        }
      }
      else
      {
        tabMB_data.popup_errorMess = "Mã máy bay đã tồn tại!";
      }
    }

    if (CreateButton(Cancel))
    {
      resetInputTextBox(tabMB_data.MaMB);
      resetInputTextBox(tabMB_data.LoaiMB);
      resetInputTextBox(tabMB_data.SoDong);
      resetInputTextBox(tabMB_data.SoDay);
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

bool Popup_XoaMB(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Xoá máy bay?",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Xoá máy bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  DrawTextEx(
      FontArial, "Máy bay có các thông tin như sau: ",
      {CenterDataSetter(
           1100, StartPos.x + 200,
           MeasureTextEx(FontArial, "Máy bay có các thông tin như sau: ", 40, 0)
               .x),
       CenterDataSetter(50, StartPos.y + 130,
                        MeasureTextEx(FontArial, "A", 40, 0).y)},
      40, 0, RED);

  if (tabMB_data.data != NULL)
  {
    DrawTextEx(FontArial, "Mã máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
    TextBox Box_maMB;
    Box_maMB.box = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
    Box_maMB.showBox = true;
    Box_maMB.text = tabMB_data.data->getSoHieuMB();
    CreateTextBox(Box_maMB);

    DrawTextEx(FontArial, "Hãng máy bay",
               {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
    TextBox Box_loaiMB;
    Box_loaiMB.box = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    Box_loaiMB.showBox = true;
    Box_loaiMB.text = tabMB_data.data->getLoaiMB();
    CreateTextBox(Box_loaiMB);

    DrawTextEx(FontArial, "Số dòng",
               {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
    TextBox Box_soDong;
    Box_soDong.box = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
    Box_soDong.showBox = true;
    Box_soDong.text = intToChar(tabMB_data.data->getSoDong(), 2);
    CreateTextBox(Box_soDong);

    DrawTextEx(FontArial, "Số dãy",
               {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
    TextBox Box_soDay;
    Box_soDay.box = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
    Box_soDay.showBox = true;
    Box_soDay.text = intToChar(tabMB_data.data->getSoDay(), 2);
    CreateTextBox(Box_soDay);

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
      strcpy(CheckMB, tabMB_data.data->getSoHieuMB());
      listMB.deleteMB(listMB.findPosMB(CheckMB));

      listMB.writetoFile();

      tabMB_data.status = -1;

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

bool Popup_Thongkesoluotbay(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  CreatePageBackground(1);
  Button button;
  button.x = StartPos.x + 1201 + 29;
  button.y = StartPos.y + 60 + 20 + 70 + 15;
  button.w = 240;
  button.h = 60;
  button.gotNothing = false;
  button.gotText = true;
  button.font = FontArial;
  button.BoMau = ArrowKey;

  button.tittle = "Quay lại";

  // search
  Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
  DrawRectangleRec(searchText, WHITE);
  DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
  tabMB_data.searchKeyword.textBox = searchText;

  DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

  tabMB_data.keyword = CreateTextInputBox(tabMB_data.searchKeyword);

  Button button1;

  button1.x = searchText.x + searchText.width;
  button1.y = searchText.y;
  button1.w = 200;
  button1.h = 50;
  button1.gotNothing = false;
  button1.gotText = true;
  button1.tittle = "TÌM KIẾM";
  button1.font = FontArial;
  button1.BoMau = ArrowKey;

  if (CreateButton(button1))
  {
    cout << "Tim kiem" << endl;
  }

  DrawTextEx(
      FontArial, "Thống kê số lượt bay",
      {CenterDataSetter(1200, StartPos.x,
                        MeasureTextEx(FontArial, "Thống kê số lượt bay", 60, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10 + 40,
                        MeasureTextEx(FontArial, "A", 60, 0).y)},
      60, 0, BLACK);
  const char *cell_tittle[3] = {"STT", "Mã MB", "Số lượt bay"};

  float cellW[3] = {180, 450, 450};
  CreateTable({StartPos.x + 35, StartPos.y + 60 + 100 + 80}, 3, cellW, 1080);
  Vector2 *tittle_pos = GetTittlePos(
      {StartPos.x + 35, StartPos.y + 60 + 100 + 80}, 3, cellW, cell_tittle);
  for (int i = 0; i < 3; i++)
  {
    DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
  }
  static int current_page = 1;
  int n_page = 1; // 1 + (spt/10)
  int size = listMB.getSize();
  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;
  int i = (current_page - 1) * 10;
  int j = 0;
  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 110 + 70 + 60};
  int *A = listMB.sapXepThongKe();
  MayBay **dsMB = listMB.getMB();
  for (int id = 0; id < size; id++)
  {
    if (isGotStr(dsMB[id]->getSoHieuMB(), tabMB_data.keyword))
    {
      if (j >= i && j <= i + 9)
      {

        TextBox show[3];
        const char *showText[3] = {
            intToChar(j + 1, n_char),
            dsMB[A[id]]->getSoHieuMB(), // listMB.getMB()[listMB.sapXepThongKe()[id]]->getSoHieuMB()
            intToChar(dsMB[A[id]]->getSoLuotBay(), 3)};
        for (int show_i = 2; show_i >= 0; show_i--)
        {
          show[show_i] = GetCellTextBox(start_pos, 3, cellW, show_i + 1,
                                        (j % 10) + 1, showText[show_i], 30);
        }
        for (int show_i = 2; show_i >= 0; show_i--)
        {
          CreateTextBox(show[show_i]);
        }

        // delete[] showText;
      }
      j++;
    }
  }
  delete[] A;
  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});

  current_page = swp;
  if (current_page > n_page)
    current_page = 1;

  if (CreateButton(button))
  {
    current_page = 1;
    resetInputTextBox(tabMB_data.searchKeyword);
    // tabMB_data.current_popup =0;
    return true;
  }
  return false;
}

MayBay *XuLy_QLMB(DsMayBay &listMB, QLMB_data &tabMB_data)
{
  // search
  Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
  DrawRectangleRec(searchText, WHITE);
  DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
  tabMB_data.searchKeyword.textBox = searchText;

  DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

  tabMB_data.keyword = CreateTextInputBox(tabMB_data.searchKeyword);

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
  int n_page = 1; // 1 + (spt/10)
  // if (status == 1)
  // {
  //     current_page = 1 + (listMB.getsize() - 1) / 10;
  //     index = (listMB.getsize() - 1) % 10;
  //     status = 0;
  // }
  // else if (status == -1)
  // {
  //     current_page = 1;
  //     index = -1;
  //     status = 0;
  // }

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
      if (tabMB_data.pickdata_index != i)
      {

        tabMB_data.pickdata_index = i;
      }
      else
        tabMB_data.pickdata_index = -1;
    }
    if (tabMB_data.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  // if (tabMB_data.pickdata_index >= 0)
  // {
  //     result = listMB.getMB(tabMB_data.pickdata_index);
  // }
  // else
  //     result = new MayBay();

  int size = listMB.getSize();
  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;
  int i = (tabMB_data.current_showPage - 1) * 10;
  int j = 0;
  // if (current_page * 10 < size)
  //     j = current_page * 10;
  // else
  // {
  //     j = size;
  // }

  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 60 + 70 + 110};
  MayBay **temp = listMB.getMB();
  for (int id = 0; id < size; id++)
  {
    if (isGotStr(temp[id]->getSoHieuMB(), tabMB_data.keyword))
    {
      if (j >= i && j <= i + 9)
      {
        if (j % 10 == tabMB_data.pickdata_index)
          tabMB_data.data = temp[id];
        TextBox show[5];
        const char *showText[5] = {

            intToChar(j + 1, n_char), temp[id]->getSoHieuMB(),
            temp[id]->getLoaiMB(),
            intToChar(temp[id]->getSoDay(), 3),
            intToChar(temp[id]->getSoDong(), 3)};
        for (int show_i = 4; show_i >= 0; show_i--)
        {
          show[show_i] = GetCellTextBox(start_pos, 5, cellW, show_i + 1,
                                        (j % 10) + 1, showText[show_i], 30);
        }
        for (int show_i = 4; show_i >= 0; show_i--)
        {
          CreateTextBox(show[show_i]);
        }

        // delete[] showText;
      }
      j++;
    }
  }
  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(tabMB_data.current_showPage, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (tabMB_data.current_showPage != swp)
  {
    tabMB_data.pickdata_index = -1;
    tabMB_data.data = nullptr;
  }
  tabMB_data.current_showPage = swp;
  if (tabMB_data.current_showPage > n_page)
    tabMB_data.current_showPage = 1;
  if (tabMB_data.pickdata_index == -1)
    tabMB_data.data = nullptr;
  return tabMB_data.data;
}

void CreateTable_QLMB()
{
  const char *cell_tittle[5] = {"STT", "Mã máy bay", "Tên máy bay",
                                "Số dãy", "Số dòng"};

  float cellW[5] = {100, 300, 380, 150, 150};
  CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, 1080);

  Vector2 *tittle_pos = GetTittlePos(
      {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, cell_tittle);

  for (int i = 0; i < 5; i++)
  {
    DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
  }
}

// =-ChuyenBay

void CreatePage_QLCB(DsChuyenBay &listCB, QLCB_data &tabCB_data)
{
  CreatePageBackground(5);

  if (tabCB_data.current_popup == 0)
  { // tittle
    DrawTextEx(FontArial, "DANH SÁCH CHUYẾN BAY",
               {StartPos.x + 60,
                CenterDataSetter(70, StartPos.y + 60,
                                 MeasureTextEx(FontArial, "A", 50, 0).y)},
               50, 0, BLUE);

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
      tabCB_data.current_popup = 1;
    }
    button[1].tittle = "Hiệu chỉnh CB";
    if (CreateButton(button[1]))
    {
      tabCB_data.current_popup = 2;
    }
    button[2].tittle = "Xóa chuyến bay";
    if (CreateButton(button[2]))
    {
      tabCB_data.current_popup = 3;
    }
    button[3].tittle = "Xem danh sach vé";
    if (CreateButton(button[3]))
    {
      tabCB_data.current_popup = 4;
    }
    button[4].tittle = "Đặt vé";
    if (CreateButton(button[4]))
    {
      tabCB_data.current_popup = 5;
    }
    tabCB_data.data = XuLy_QLCB(listCB, tabCB_data);
  }
  else if (tabCB_data.current_popup == 1)
  {
    if (Popup_ThemCB(listCB, tabCB_data))
    {
      tabCB_data.current_popup = 0;
    }
  }
  else if (tabCB_data.current_popup == 2)
  {
    if (Popup_HieuChinhCB(listCB, tabCB_data))
    {
      tabCB_data.current_popup = 0;
    }
  }
  else if (tabCB_data.current_popup == 3)
  {
    if (Popup_XoaCB(listCB, tabCB_data))
    {
      tabCB_data.current_popup = 0;
    }
  }
  else if (tabCB_data.current_popup == 4)
  {
    if (Popup_showListHK(tabCB_data))
    {
      tabCB_data.current_popup = 0;
    }
  }
  else if (tabCB_data.current_popup == 5)
  {
    if (Popup_chonVe(tabCB_data))
    {
      tabCB_data.current_popup = 0;
    }
  }

  if (listCB.update() || tabCB_data.gotNewTicket)
  {
    setDataToFile(listCB, tabCB_data.dsachMB, tabCB_data.dsachHK);
    getDataFromFile(listCB, tabCB_data.dsachMB, tabCB_data.dsachHK);
    tabCB_data.gotNewTicket = false;
  }
}

void Popup_getMB(DsChuyenBay listCB, QLCB_data &tabCB_data, Date gioBay)
{
  MayBay *result;

  CreatePageBackground(2);
  TextBox tittle;
  tittle.box = {StartPos.x + 60, StartPos.y + 60, 400, 50};
  tittle.mode = 2;
  tittle.text = (char *)"Hãy chọn máy bay!";

  CreateTextBox(tittle);
  result = XuLy_QLMB(tabCB_data.dsachMB, tabCB_data.dataMB);

  Button OK;

  OK.x = StartPos.x + 1201 + 29;
  OK.y = StartPos.y + 60 + 20 + 70 + 15;
  OK.w = 240;
  OK.h = 60;
  OK.BoTron = false;
  OK.gotNothing = false;
  OK.gotText = true;
  OK.font = FontArial;
  OK.BoMau = ArrowKey;

  Button Cancel;

  Cancel.x = StartPos.x + 1201 + 29;
  Cancel.y = StartPos.y + 60 + 20 + 70 + 15 + 75;
  Cancel.w = 240;
  Cancel.h = 60;
  Cancel.BoTron = false;
  Cancel.gotNothing = false;
  Cancel.gotText = true;
  Cancel.font = FontArial;
  Cancel.BoMau = ArrowKey;

  if (tabCB_data.dataMB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, tabCB_data.dataMB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, tabCB_data.dataMB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    tabCB_data.dataMB.time_showError++;
  }
  else
  {
    tabCB_data.dataMB.popup_errorMess = "";
    tabCB_data.dataMB.time_showError = 0;
  }

  // mini function
  OK.tittle = (char *)"Thêm máy bay";
  Cancel.tittle = (char *)"Huỷ bỏ";
  bool check_mb = false;
  const char *maCB_t;
  if (tabCB_data.data == NULL)
    maCB_t = "";
  else
    maCB_t = tabCB_data.data->getNode().getMaCB();
  if (tabCB_data.dataMB.data != NULL && !listCB.isAval(tabCB_data.dataMB.data->getSoHieuMB(), gioBay, maCB_t))
  {
    check_mb = true;
    tabCB_data.dataMB.popup_errorMess = "Máy bay đang bận!";
    tabCB_data.dataMB.time_showError = 98;
    // return;
  }

  if (CreateButton(OK))
  {
    if (tabCB_data.dataMB.data == NULL)
    {
      tabCB_data.dataMB.popup_errorMess = "Chưa chọn máy bay nào!";
      return;
    }
    else if (check_mb)
      return;
    tabCB_data.inChooseMB = false;
    strcpy(tabCB_data.MaMB.name, tabCB_data.dataMB.data->getSoHieuMB());
    tabCB_data.MaMB.letterCount = getCharSize(tabCB_data.dataMB.data->getSoHieuMB());
    if (tabCB_data.MaCB.editMode)
      tabCB_data.MaMB.tittle = tabCB_data.dataMB.data->getSoHieuMB();
    resetData_QLMB(tabCB_data.dataMB);
  }
  if (CreateButton(Cancel))
  {
    tabCB_data.inChooseMB = false;
    resetData_QLMB(tabCB_data.dataMB);
  }
}

bool Popup_ThemCB(DsChuyenBay &listCB, QLCB_data &tabCB_data)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Thêm chuyến bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Thêm máy bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;

  DrawTextEx(FontArial, "Thời gian bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, sai tự xoá dữ liệu của ô)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25},
             25, 0, RED);

  Date check = Date(1, 1, 1901, 00, 00);
  const char *newNgay = CreateTextInputBox(tabCB_data.Ngay);
  const char *newThang = CreateTextInputBox(tabCB_data.Thang);
  const char *newNam = CreateTextInputBox(tabCB_data.Nam);

  check = Date(stoi(newNgay[0] == 0 ? "1" : newNgay),
               stoi(newThang[0] == 0 ? "1" : newThang),
               stoi(newNam[0] == 0 ? "2000" : newNam), 00, 00);
  if (strcmp(newThang, "00") == 0 || !check.checkNgay())
  {
    int tmp = stoi(newNam[0] == 0 ? "2000" : newNam);
    if (Date(29, 2, tmp, 0, 0).checkNgay())
    {
      tabCB_data.popup_errorMess = "Tháng không hợp lệ!";
      resetInputTextBox(tabCB_data.Thang);
      newThang = "";
    }
    else
    {
      tabCB_data.popup_errorMess = "Năm không hợp lệ!";
      resetInputTextBox(tabCB_data.Nam);
      newNam = "";
    }
  }
  const char *newGio = CreateTextInputBox(tabCB_data.Gio);
  const char *newPhut = CreateTextInputBox(tabCB_data.Phut);

  Date newNgayBay = Date(stoi(newNgay[0] == 0 ? "0" : newNgay),
                         stoi(newThang[0] == 0 ? "0" : newThang),
                         stoi(newNam[0] == 0 ? "0" : newNam),
                         stoi(newGio[0] == 0 ? "25" : newGio),
                         stoi(newPhut[0] == 0 ? "25" : newPhut));

  DrawTextEx(FontArial, "Mã mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaCB = CreateTextInputBox(tabCB_data.MaCB);

  DrawTextEx(FontArial, "Số hiệu máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaMB = CreateTextInputBox(tabCB_data.MaMB);
  if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32) &&
      tabCB_data.MaMB.mouseClickOnText)
  {
    tabCB_data.MaMB.mouseClickOnText = false;
    tabCB_data.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
  }
  else
  {
    if (tabCB_data.inChooseMB)
    {
      Popup_getMB(listCB, tabCB_data, newNgayBay);
      return false;
    }
  }

  Button getMB;
  getMB.x = StartPos.x + 300 + 900;
  getMB.y = StartPos.y + 60 + 380 + 2;
  getMB.w = 200;
  getMB.h = 46;
  getMB.gotNothing = false;
  getMB.gotText = true;
  getMB.tittle = (char *)"Chọn máy bay";
  getMB.font = FontArial;
  getMB.BoMau = ArrowKey;

  if ((newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
       newGio[0] >= 32 && newPhut[0] >= 32))
    if (CreateButton(getMB))
    {
      tabCB_data.inChooseMB = true;
      return false;
    }

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái, kí tự và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  const char *newNoiDen = CreateTextInputBox(tabCB_data.NoiDen);

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

  // Hiện lỗi trong 5s
  if (tabCB_data.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, tabCB_data.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, tabCB_data.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    tabCB_data.time_showError++;
  }
  else
  {
    tabCB_data.popup_errorMess = "";
    tabCB_data.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    if (!newNgayBay.checkNgay())
      tabCB_data.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
    else if (tabCB_data.dsachMB.findPosMB(newMaMB) < 0)
      tabCB_data.popup_errorMess = "Mã máy bay không tồn tại!";
    else if (!listCB.isAval(newMaMB, newNgayBay, newMaCB))
      tabCB_data.popup_errorMess = "Máy bay đang được chuyển bay khác sử dụng!";
    else if (!listCB.isExist(newMaCB) || (tabCB_data.data != NULL && strcmp(newMaCB, tabCB_data.data->getNode().getMaCB()) == 0))
    {
      if (newMaCB[0] >= 32 && newMaMB[0] >= 32 && newNoiDen[0] >= 32 &&
          newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
          newGio[0] >= 32 && newPhut[0] >= 32)
      {
        ChuyenBay result = ChuyenBay(newMaCB, newNoiDen, newNgayBay, newMaMB);
        DsVeMayBay newDSVe;
        newDSVe.setDSVe(tabCB_data.dsachMB.findMB(newMaMB));
        result.setDSVe(newDSVe);
        listCB.insertOrder(new NodeCB(result));
        listCB.writetToFile();
        listCB.setSize();

        tabCB_data.status = 1;
        resetInputTextBox(tabCB_data.MaCB);
        resetInputTextBox(tabCB_data.MaMB);
        resetInputTextBox(tabCB_data.NoiDen);
        resetInputTextBox(tabCB_data.Ngay);
        resetInputTextBox(tabCB_data.Thang);
        resetInputTextBox(tabCB_data.Nam);
        resetInputTextBox(tabCB_data.Gio);
        resetInputTextBox(tabCB_data.Phut);
        tabCB_data.popup_errorMess = "";

        return true;
      }
      else
      {
        tabCB_data.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      }
    }
    else
    {
      tabCB_data.popup_errorMess = "Mã chuyến bay đã được sử dụng!";
    }
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(tabCB_data.MaCB);
    resetInputTextBox(tabCB_data.MaMB);
    resetInputTextBox(tabCB_data.NoiDen);
    resetInputTextBox(tabCB_data.Ngay);
    tabCB_data.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_HieuChinhCB(DsChuyenBay &listCB, QLCB_data &tabCB_data)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Hiệu chỉnh chuyến bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Thêm chuyến bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  if (tabCB_data.data == NULL)
  {
    if (Warning_NoData())
      return true;
    return false;
  }

  tabCB_data.MaCB.editMode = true;
  tabCB_data.MaCB.tittle = tabCB_data.data->getNode().getMaCB();
  tabCB_data.MaMB.editMode = true;
  tabCB_data.MaMB.tittle = tabCB_data.data->getNode().getMaMayBay();
  tabCB_data.NoiDen.editMode = true;
  tabCB_data.NoiDen.tittle = strToChar(tabCB_data.data->getNode().getNoiDen());
  tabCB_data.Ngay.editMode = true;
  tabCB_data.Ngay.tittle = intToChar(tabCB_data.data->getNode().getNgayGio().getNgay(), 2);
  tabCB_data.Thang.editMode = true;
  tabCB_data.Thang.tittle = intToChar(tabCB_data.data->getNode().getNgayGio().getThang(), 2);
  tabCB_data.Nam.editMode = true;
  tabCB_data.Nam.tittle = intToChar(tabCB_data.data->getNode().getNgayGio().getNam(), 4);
  tabCB_data.Gio.editMode = true;
  tabCB_data.Gio.tittle = intToChar(tabCB_data.data->getNode().getNgayGio().getGio(), 2);
  tabCB_data.Phut.editMode = true;
  tabCB_data.Phut.tittle = intToChar(tabCB_data.data->getNode().getNgayGio().getPhut(), 2);

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;

  DrawTextEx(FontArial, "Thời gian bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, sai tự xoá dữ liệu của ô)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25},
             25, 0, RED);

  Date check = Date(1, 1, 1901, 00, 00);
  const char *newNgay = CreateTextInputBox(tabCB_data.Ngay);
  const char *newThang = CreateTextInputBox(tabCB_data.Thang);
  const char *newNam = CreateTextInputBox(tabCB_data.Nam);

  check = Date(stoi(newNgay[0] == 0 ? "1" : newNgay),
               stoi(newThang[0] == 0 ? "1" : newThang),
               stoi(newNam[0] == 0 ? "2000" : newNam), 00, 00);
  if (strcmp(newThang, "00") == 0 || !check.checkNgay())
  {
    int tmp = stoi(newNam[0] == 0 ? "2000" : newNam);
    if (Date(29, 2, tmp, 0, 0).checkNgay())
    {
      tabCB_data.popup_errorMess = "Tháng không hợp lệ!";
      resetInputTextBox(tabCB_data.Thang);
      newThang = "";
    }
    else
    {
      tabCB_data.popup_errorMess = "Năm không hợp lệ!";
      resetInputTextBox(tabCB_data.Nam);
      newNam = "";
    }
  }
  const char *newGio = CreateTextInputBox(tabCB_data.Gio);
  const char *newPhut = CreateTextInputBox(tabCB_data.Phut);

  Date newNgayBay = Date(stoi(newNgay[0] == 0 ? "0" : newNgay),
                         stoi(newThang[0] == 0 ? "0" : newThang),
                         stoi(newNam[0] == 0 ? "0" : newNam),
                         stoi(newGio[0] == 0 ? "25" : newGio),
                         stoi(newPhut[0] == 0 ? "25" : newPhut));

  DrawTextEx(FontArial, "Mã mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaCB = CreateTextInputBox(tabCB_data.MaCB);

  DrawTextEx(FontArial, "Số hiệu máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaMB = CreateTextInputBox(tabCB_data.MaMB);
  if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32) &&
      tabCB_data.MaMB.mouseClickOnText)
  {
    tabCB_data.MaMB.mouseClickOnText = false;
    tabCB_data.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
  }
  else
  {
    if (tabCB_data.inChooseMB)
    {
      Popup_getMB(listCB, tabCB_data, newNgayBay);
      return false;
    }
  }

  Button getMB;
  getMB.x = StartPos.x + 300 + 900;
  getMB.y = StartPos.y + 60 + 380 + 2;
  getMB.w = 200;
  getMB.h = 46;
  getMB.gotNothing = false;
  getMB.gotText = true;
  getMB.tittle = (char *)"Chọn máy bay";
  getMB.font = FontArial;
  getMB.BoMau = ArrowKey;

  if ((newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
       newGio[0] >= 32 && newPhut[0] >= 32))
    if (CreateButton(getMB))
    {
      tabCB_data.inChooseMB = true;
      return false;
    }

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái, kí tự và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  const char *newNoiDen = CreateTextInputBox(tabCB_data.NoiDen);

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

  // Hiện lỗi trong 5s
  if (tabCB_data.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, tabCB_data.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, tabCB_data.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    tabCB_data.time_showError++;
  }
  else
  {
    tabCB_data.popup_errorMess = "";
    tabCB_data.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    if (!newNgayBay.checkNgay())
      tabCB_data.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
    else if (tabCB_data.dsachMB.findPosMB(newMaMB) < 0)
      tabCB_data.popup_errorMess = "Mã máy bay không tồn tại!";
    else if (!listCB.isAval(newMaMB, newNgayBay, newMaCB))
      tabCB_data.popup_errorMess = "Máy bay đang được chuyển bay khác sử dụng!";
    else if (!listCB.isExist(newMaCB) || (tabCB_data.data != NULL && strcmp(newMaCB, tabCB_data.data->getNode().getMaCB()) == 0))
    {
      if (newMaCB[0] >= 32 && newMaMB[0] >= 32 && newNoiDen[0] >= 32 &&
          newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
          newGio[0] >= 32 && newPhut[0] >= 32)
      {
        ChuyenBay result = tabCB_data.data->getNode();
        result.setNgayGio(newNgayBay);
        tabCB_data.data->setCb(result);
        listCB.writetToFile();
        listCB.setSize();

        tabCB_data.status = 1;
        resetInputTextBox(tabCB_data.MaCB);
        resetInputTextBox(tabCB_data.MaMB);
        resetInputTextBox(tabCB_data.NoiDen);
        resetInputTextBox(tabCB_data.Ngay);
        resetInputTextBox(tabCB_data.Thang);
        resetInputTextBox(tabCB_data.Nam);
        resetInputTextBox(tabCB_data.Gio);
        resetInputTextBox(tabCB_data.Phut);
        tabCB_data.popup_errorMess = "";

        return true;
      }
      else
      {
        tabCB_data.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      }
    }
    else
    {
      tabCB_data.popup_errorMess = "Mã chuyến bay đã được sử dụng!";
    }
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(tabCB_data.MaCB);
    resetInputTextBox(tabCB_data.MaMB);
    resetInputTextBox(tabCB_data.NoiDen);
    resetInputTextBox(tabCB_data.Ngay);
    tabCB_data.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_XoaCB(DsChuyenBay &listCB, QLCB_data &tabCB_data)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Xoá chuyến bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Thêm chuyến bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  if (tabCB_data.data == NULL)
  {
    if (Warning_NoData())
      return true;
    return false;
  }
  TextBox Box_maCB;
  Box_maCB.box = tabCB_data.MaCB.textBox;
  Box_maCB.showBox = true;
  Box_maCB.text = tabCB_data.data->getNode().getMaCB();
  CreateTextBox(Box_maCB);

  TextBox Box_maMB;
  Box_maMB.box = tabCB_data.MaMB.textBox;
  Box_maMB.showBox = true;
  Box_maMB.text = tabCB_data.data->getNode().getMaMayBay();
  CreateTextBox(Box_maMB);

  TextBox Box_noiDen;
  Box_noiDen.box = tabCB_data.NoiDen.textBox;
  Box_noiDen.showBox = true;
  Box_noiDen.text = strToChar(tabCB_data.data->getNode().getNoiDen());
  CreateTextBox(Box_noiDen);

  TextBox Box_ngayBay;
  Box_ngayBay.box = tabCB_data.Ngay.textBox;
  Box_ngayBay.box.width += 300;
  Box_ngayBay.showBox = true;
  Box_ngayBay.text = strToChar(tabCB_data.data->getNode().getNgayGio().printDateHour());
  CreateTextBox(Box_ngayBay);

  DrawTextEx(FontArial, "Thời gian bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);

  DrawTextEx(FontArial, "Mã mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);

  DrawTextEx(FontArial, "Số hiệu máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);

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

  // Hiện lỗi trong 5s
  if (tabCB_data.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, tabCB_data.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, tabCB_data.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    tabCB_data.time_showError++;
  }
  else
  {
    tabCB_data.popup_errorMess = "";
    tabCB_data.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    listCB.pop(tabCB_data.data);
    listCB.writetToFile();
    listCB.setSize();

    tabCB_data.status = 1;
    resetInputTextBox(tabCB_data.MaCB);
    resetInputTextBox(tabCB_data.MaMB);
    resetInputTextBox(tabCB_data.NoiDen);
    resetInputTextBox(tabCB_data.Ngay);
    resetInputTextBox(tabCB_data.Thang);
    resetInputTextBox(tabCB_data.Nam);
    resetInputTextBox(tabCB_data.Gio);
    resetInputTextBox(tabCB_data.Phut);
    tabCB_data.popup_errorMess = "";

    return true;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(tabCB_data.MaCB);
    resetInputTextBox(tabCB_data.MaMB);
    resetInputTextBox(tabCB_data.NoiDen);
    resetInputTextBox(tabCB_data.Ngay);
    tabCB_data.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_showListHK(QLCB_data &tabCB_data)
{
  CreatePageBackground(2);
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
      if (tabCB_data.dataDSVe.pickdata_index != i)
      {

        tabCB_data.dataDSVe.pickdata_index = i;
      }
      else
        tabCB_data.dataDSVe.pickdata_index = -1;
    }
    if (tabCB_data.dataDSVe.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);

    // mini function
    button[0].tittle = "Quay lại";

    button[1].tittle = "Huỷ vé";

    ChuyenBay currCB = tabCB_data.data->getNode();
    int n_page = 1 + (currCB.getDSVe().getSoVeDaDat() - 1) / 10;

    float cellW[6] = {100, 180, 300, 400, 100};
    const char *cell_tittle[5] = {"STT", "Mã vé", "Số CMND", "Họ và tên", "Phái"};
    Vector2 start_pos = {CenterDataSetter(1200, StartPos.x, 1080), StartPos.y + 60 + 80 + 100};
    CreateTable(start_pos, 5, cellW, 1080);
    Vector2 *tittle_pos = GetTittlePos(start_pos, 5, cellW, cell_tittle);
    for (int i = 0; i < 5; i++)
    {
      DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
    }

    int n_char;
    if (currCB.getDSVe().getSoVeDaDat() <= 99)
      n_char = 2;
    else if (currCB.getDSVe().getSoVeDaDat() >= 100)
      n_char = 3;

    if (currCB.getDSVe().getSoVeDaDat() == 0)
    {
    }
    else
    {
      int iVe = 0;
      for (int i = 0; i < currCB.getDSVe().getSoVeToiDa(); i++)
      {

        VeMayBay tmp = currCB.getDSVe().getVe(i);
        if (tmp.getHanhKhach() == "")
          continue;
        const char *showText[5];
        showText[0] = intToChar(iVe % 10 + 1, n_char);
        showText[1] = strToChar(tmp.getIDVe());
        showText[2] = strToChar(tmp.getHanhKhach());
        showText[3] = strToChar(tabCB_data.dsachHK.search(tmp.getHanhKhach())->getHK().getHo() + " " + tabCB_data.dsachHK.search(tmp.getHanhKhach())->getHK().getTen());
        showText[4] = strToChar(tabCB_data.dsachHK.search(tmp.getHanhKhach())->getHK().getPhai());

        TextBox show[5];
        for (int j = 0; j < 5; j++)
        {
          show[j] = GetCellTextBox(start_pos, 5, cellW, j + 1, (iVe % 10) + 1, showText[j], 30);
        }
        for (int j = 4; j >= 0; j--)
        {
          CreateTextBox(show[j]);
        }
      }
    }

    int swp =
        SwitchPage(tabCB_data.dataDSVe.current_page, n_page,
                   {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
    if (tabCB_data.dataDSVe.current_page != swp)
    {
      tabCB_data.dataDSVe.position = -1;
      tabCB_data.dataDSVe.current_page = swp;
    }

    if (tabCB_data.dataDSVe.current_page > n_page)
      tabCB_data.dataDSVe.current_page = 1;
    if (CreateButton(button[0]))
    {
      tabCB_data.dataDSVe.current_page = 1;
      tabCB_data.current_popup = 0;
      return true;
    }
    // if (tabMB_data.data != NULL)
    // {
    // if (CreateButton(button[1]))
    // {
    //   // hàm lấy index data
    // }
    // int tmp_c = Warning_Confirm();
    // if (tmp_c == 1)
    // {
    //   tabCB_data.current_popup = 4;
    // }
    // else if (tmp_c == 2)
    // {
    //   tabCB_data.current_popup = 4;
    // }
  }
  return false;
}

bool Popup_chonVe(QLCB_data &tabCB_data)
{
  if (tabCB_data.inSetTicket)
  {
    if (Popup_datVe(tabCB_data))
    {
      tabCB_data.inSetTicket = false;
      if (!tabCB_data.gotNewTicket)
        return false;
      return true;
    }
    return false;
  }

  ChuyenBay currCB = tabCB_data.data->getNode();
  int n_page = 1;
  // int size = dsve.getSoVeToiDa();
  int sDay = tabCB_data.dsachMB.findMB(currCB.getMaMayBay())->getSoDay(),
      sDong = tabCB_data.dsachMB.findMB(currCB.getMaMayBay())->getSoDong();
  int IndexSoDongMax = sDong;
  if (sDong > 10)
    IndexSoDongMax = (tabCB_data.dataDSVe.current_page) * 10;
  if (IndexSoDongMax > sDong)
    IndexSoDongMax = sDong;
  // if (current_page * 10 < size)
  //     j = current_page * 100;
  // else
  //     j = size;
  Rectangle r;
  r = {0,
       CenterDataSetter(12 * 40, StartPos.y + 60 + 70 + 80, sDay * 40),
       70, 30};
  if (sDong > 10)
    r.x = CenterDataSetter(1200, StartPos.x, 10 * 100);
  else
    r.x = CenterDataSetter(1200, StartPos.x, (sDong)*100);

  DrawTextPro(FontArial,
              "Dãy",
              // {StartPos.x + 20, CenterDataSetter(12 * 40, StartPos.y + 60 + 70 + 80, 40)},
              // {StartPos.x + 20, CenterDataSetter(12 * 40, StartPos.y + 60 + 70 + 80, 40)},
              {r.x - MeasureTextEx(FontArial, "Day", 40, 0).y,
               CenterDataSetter(12 * 40, StartPos.y + 60 + 70 + 80, MeasureTextEx(FontArial, "Day", 40, 0).x) +
                   MeasureTextEx(FontArial, "Day", 40, 0).x},
              {0, 0},
              -90, 40, 0, RED);

  DrawTextEx(FontArial,
             "Dòng",
             {CenterDataSetter(1200, StartPos.x, MeasureTextEx(FontArial, "Dong", 40, 0).x), r.y - MeasureTextEx(FontArial, "A", 40, 0).y - 5},
             40, 0, RED);
  Button button;
  for (int a = 0; a < sDay; a++)
  {
    for (int m = (tabCB_data.dataDSVe.current_page - 1) * 10; m < IndexSoDongMax; m++)
    {
      button.x = r.x + (m % 10) * 100 + 15;
      button.y = r.y + a * 40;
      button.w = r.width;
      button.h = r.height;
      button.gotNothing = false;
      button.gotText = true;
      button.tittle =
          strToChar(currCB.getDSVe().getVe(a * sDong + m).getIDVe());
      button.font = FontArial;
      button.BoMau = ArrowKey;
      if (CreateButton(button))
      {
        tabCB_data.dataDSVe.position = a * (sDong) + m;
        cout << tabCB_data.dataDSVe.position << endl;
      };
    }
  }

  n_page = 1 + ((sDong - 1) / 10);

  int swp =
      SwitchPage(tabCB_data.dataDSVe.current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (tabCB_data.dataDSVe.current_page != swp)
  {
    tabCB_data.dataDSVe.position = -1;
    tabCB_data.dataDSVe.current_page = swp;
  }

  if (tabCB_data.dataDSVe.current_page > n_page)
    tabCB_data.dataDSVe.current_page = 1;

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

  if (CreateButton(OK))
  {
    tabCB_data.inSetTicket = true;
  }

  return false;
}

bool Popup_datVe(QLCB_data &tabCB_data)
{
  CreatePopupBackground();

  string o_CMND, o_Ho, o_Ten;
  o_CMND = CreateTextInputBox(tabCB_data.dataDSHK.i_CMND);
  o_Ho = CreateTextInputBox(tabCB_data.dataDSHK.i_Ho);
  o_Ten = CreateTextInputBox(tabCB_data.dataDSHK.i_Ten);

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

  if (CreateButton(OK))
  {
    HanhKhach hk = HanhKhach(o_CMND, o_Ho, o_Ten, 0);
    tabCB_data.dsachHK.insert(hk);

    ChuyenBay m_cb = tabCB_data.data->getNode();
    DsVeMayBay m_dsVe = m_cb.getDSVe();
    VeMayBay m_ve = m_dsVe.getVe(tabCB_data.dataDSVe.position);
    m_ve.setHanhKhach(o_CMND);
    m_dsVe.setVe(m_ve, tabCB_data.dataDSVe.position);
    m_dsVe.setSoVeDaDat(m_dsVe.getSoVeDaDat() + 1);
    m_cb.setDSVe(m_dsVe);
    tabCB_data.data->setCb(m_cb);

    resetInputTextBox(tabCB_data.dataDSHK.i_CMND);
    resetInputTextBox(tabCB_data.dataDSHK.i_Ho);
    resetInputTextBox(tabCB_data.dataDSHK.i_Ten);
    tabCB_data.popup_errorMess = "";

    resetData_QLHK(tabCB_data.dataDSHK);

    tabCB_data.gotNewTicket = true;
    return true;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(tabCB_data.dataDSHK.i_CMND);
    resetInputTextBox(tabCB_data.dataDSHK.i_Ho);
    resetInputTextBox(tabCB_data.dataDSHK.i_Ten);
    tabCB_data.popup_errorMess = "";

    resetData_QLHK(tabCB_data.dataDSHK);

    return true;
  }
  return false;
}

void CreateTable_QLCB()
{
  const char *cell_tittle[7] = {"STT", "Mã CB", "Số hiệu MB", "Ngày giờ",
                                "Nơi đến", "SL Vé", "TT"};

  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  CreateTable({StartPos.x + 35, StartPos.y + 60 + 100 + 80}, 7, cellW, 1130);
  Vector2 *tittle_pos = GetTittlePos(
      {StartPos.x + 35, StartPos.y + 60 + 100 + 80}, 7, cellW, cell_tittle);
  for (int i = 0; i < 7; i++)
  {
    DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
  }
}

void StatusHelp_QLCB()
{
  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  Vector2 cell = GetCellPos({StartPos.x + 35, StartPos.y + 60 + 100 + 80}, 7,
                            cellW, 7, 1) -
                 (Vector2){0, 50};

  if (CheckCollisionPointRec(GetVMousePosition(),
                             (Rectangle){cell.x, cell.y, cellW[6], 50}))
  {
    Rectangle box = {cell.x, cell.y, 300, 400};
    // 10 50 40 60 60 60 60 20
    DrawRectangleRounded(box, 0.125, 0, {255, 255, 255, 210});
    DrawRectangleRoundedLines(box, 0.125, 0, 2, BROWN);

    DrawRectangleRoundedLines({box.x + 20, box.y + 10, 150, 50}, 0, 0, 2, RED);

    TextBox tittle;
    tittle.text = (char *)"Ghi chú";
    tittle.isCenter = true;
    tittle.box = {box.x + 20, box.y + 10, 150, 50};

    TextBox Aval;
    Aval.text = (char *)"Còn vé";
    Aval.box = {box.x + 50, box.y + 100 - 5, 200, 50};

    TextBox notAval;
    notAval.text = (char *)"Hết vé";
    notAval.box = {box.x + 50, box.y + 100 + 60 - 5, 200, 50};

    TextBox complt;
    complt.text = (char *)"Hoàn thành";
    complt.box = {box.x + 50, box.y + 100 + 120 - 5, 200, 50};

    TextBox disb;
    disb.text = (char *)"Huỷ chuyến";
    disb.box = {box.x + 50, box.y + 100 + 180 - 5, 200, 50};

    CreateTextBox(tittle);
    DrawTextureEx(PNG_circleGreen, {box.x + 13, box.y + 100 + 16}, 0, 1, WHITE);
    CreateTextBox(Aval);
    DrawTextureEx(PNG_circleYellow, {box.x + 13, box.y + 100 + 60 + 16}, 0, 1,
                  WHITE);
    CreateTextBox(notAval);
    DrawTextureEx(PNG_tick, {box.x + 13, box.y + 100 + 120 + 16}, 0, 1, WHITE);
    CreateTextBox(complt);
    DrawTextureEx(PNG_circleGray, {box.x + 13, box.y + 100 + 180 + 16}, 0, 1,
                  WHITE);
    CreateTextBox(disb);
  }
}

// test
NodeCB *XuLy_QLCB(DsChuyenBay &listCB, QLCB_data &tabCB_data)
{
  bool DKTimKiem = true;
  int numNgay = 1, numThang = 1, numNam = 1900, numGio = 0, numPhut = 0;

  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  CreateTable_QLCB();

  int n_page = 1;

  const Vector2 search = {StartPos.x + 60, StartPos.y + 60 + 70};

  // VỊ trị box
  Rectangle boxMaCB = {search.x + 300 + 250, search.y, 350, 45};
  Rectangle boxNoiDen = {search.x + 80 + 150 + 20, search.y + 55, 350, 45};

  Button dayFilter;
  Button data_picker[10];
  Vector2 start_pos = {StartPos.x + 35, StartPos.y + 60 + 70 + 110};
  NodeCB *tmp = listCB.getHead();

  // Cài đặt các ô nhập
  tabCB_data.searchNoiDen.textBox = boxNoiDen;
  tabCB_data.searchMaCB.textBox = boxMaCB;

  // if (first_run)
  // {
  //   strcpy(searchNgay.name, intToChar(numNgay, 2));
  //   searchNgay.letterCount = 2;
  //   strcpy(searchThang.name, intToChar(numThang, 2));
  //   searchThang.letterCount = 2;
  //   strcpy(searchNam.name, intToChar(numNam, 4));
  //   searchNam.letterCount = 4;
  // }

  // search

  DrawRectangleRoundedLines({search.x - 5, search.y - 5, 1090, 105}, 0, 1, 3,
                            DARKBLUE);

  // if (!findByDay)
  // {
  // dayFilter.x = search.x + 5;
  // dayFilter.y = search.y + 5 + 55;
  // dayFilter.w = 470;
  // dayFilter.h = 40;
  // dayFilter.BoTron = false;
  // dayFilter.gotNothing = false;
  // dayFilter.gotText = true;
  // dayFilter.tittle = "LỌC THEO NGÀY";
  // dayFilter.font = FontArial;
  // dayFilter.BoMau = ArrowKey;
  // }
  // else
  // {
  dayFilter.x = search.x + 5;
  dayFilter.y = search.y + 5 + 55;
  dayFilter.w = 30;
  dayFilter.h = 40;
  dayFilter.BoTron = false;
  dayFilter.gotNothing = false;
  dayFilter.gotText = true;
  dayFilter.tittle = "X";
  dayFilter.font = FontArial;
  dayFilter.BoMau = ArrowKey;
  // }

  DrawTextEx(
      FontArial, "Mã chuyến bay:",
      {search.x + 10 + 300,
       CenterDataSetter(50, search.y, MeasureTextEx(FontArial, "a", 35, 0).y)},
      35, 0, RED);
  const char *textMaCB = CreateTextInputBox(tabCB_data.searchMaCB);
  DrawTextEx(FontArial, "Nơi đến:",
             {search.x + 20,
              CenterDataSetter(50, search.y + 55,
                               MeasureTextEx(FontArial, "a", 35, 0).y)},
             35, 0, RED);
  const char *textNoiDen = CreateTextInputBox(tabCB_data.searchNoiDen);
  // if (!findByDay)
  // {
  if (CreateButton(dayFilter))
    cout << "hi;";
  // }
  // else
  // {
  //   if (CreateButton(dayFilter))
  //     findByDay = false;

  //   DrawTextEx(FontArial, "Ngày khởi hành:",
  //              {search.x + 10 + 30,
  //               CenterDataSetter(50, search.y + 55,
  //                                MeasureTextEx(FontArial, "a", 35, 0).y)},
  //              35, 0, RED);
  //   const char *textNgay = CreateTextInputBox(searchNgay);
  //   const char *textThang = CreateTextInputBox(searchThang);
  //   const char *textNam = CreateTextInputBox(searchNam);
  //   if (textNgay[0] != 0)
  //     numNgay = stoi(textNgay);

  //   if (textThang[0] != 0)
  //     numThang = stoi(textThang);

  //   if (textNam[0] != 0)
  //     numNam = stoi(textNam);
  // }

  // table

  // data
  // if (status == 1)
  // {
  //     current_page = 1 + (listCB.getSize() - 1) / 10;
  //     index = (listCB.getSize() - 1) % 10;
  //     status = 0;
  // }
  // else if (status == -1)
  // {
  //     current_page = 1;
  //     index = -1;
  //     status = 0;
  // }

  // Pick data

  for (int i = 0; i < 10; i++)
  {
    data_picker[i].x = StartPos.x + 35;
    data_picker[i].y = StartPos.y + 60 + 100 + 80 + 50 + i * 40;
    data_picker[i].w = 1130;
    data_picker[i].h = 40;
    data_picker[i].firstRounder = false;
    data_picker[i].RounderChangeColor = true;
    data_picker[i].BoMau.RounderHovered = YELLOW;
    data_picker[i].BoMau.RounderPressed = RED;
    if (CreateButton(data_picker[i]))
    {
      if (tabCB_data.pickdata_index != i)
      {

        tabCB_data.pickdata_index = i;
      }
      else
        tabCB_data.pickdata_index = -1;
    }
    if (tabCB_data.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  tabCB_data.data = NULL;

  // show list
  int size = listCB.getSize();

  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;

  int i = (tabCB_data.current_showPage - 1) * 10;

  int j = 0;

  for (int k = 0; k < size; k++)
  {
    // if (findByDay)
    //   DKTimKiem = tmp->getNode().checkMaCB(textMaCB) &&
    //               tmp->getNode().checkTime(numNgay, numThang, numNam, numGio,
    //                                        numPhut) &&
    //               tmp->getNode().checkNoiDen(textNoiDen);
    if (tmp->getNode().checkMaCB(textMaCB) &&
        tmp->getNode().checkNoiDen(textNoiDen))
    {
      if (j >= i && j <= i + 9)
      {
        if (j % 10 == tabCB_data.pickdata_index)
          tabCB_data.data = tmp;

        string dsVe = "";
        dsVe = intToString(tmp->getNode().getDSVe().getSoVeConLai(), 3) + '/' +
               intToString(tmp->getNode().getDSVe().getSoVeToiDa(), 3);
        TextBox show[6];
        const char *showText[6];
        showText[0] = intToChar(j % 10 + 1, n_char);
        showText[1] = tmp->getNode().getMaCB();
        showText[2] = tmp->getNode().getMaMayBay();
        showText[3] = strToChar(tmp->getNode().getNgayGio().printDateHour());
        showText[4] = strToChar(tmp->getNode().getNoiDen());
        showText[5] = strToChar(dsVe);
        for (int show_i = 5; show_i >= 0; show_i--)
        {
          show[show_i] = GetCellTextBox(start_pos, 7, cellW, show_i + 1,
                                        (j % 10) + 1, showText[show_i], 30);
        }
        show[3].mode = 2;
        show[5].mode = 2;
        switch (tmp->getNode().getTrangThai())
        {
        case 0:
        {

          DrawTextureEx(PNG_circleGray,
                        GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1) +
                            (Vector2){8, 3},
                        0, 1, WHITE);
          break;
        }
        case 1:
        {
          DrawTextureEx(PNG_circleGreen,
                        GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1) +
                            (Vector2){8, 3},
                        0, 1, WHITE);
          // cout << (GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1)).x << "/"
          // << (GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1)).y << endl;
          break;
        }
        case 2:
        {
          DrawTextureEx(PNG_circleYellow,
                        GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1) +
                            (Vector2){8, 3},
                        0, 1, WHITE);
          break;
        }
        case 3:
        {
          DrawTextureEx(PNG_tick,
                        GetCellPos(start_pos, 7, cellW, 7, j % 10 + 1) +
                            (Vector2){8, 3},
                        0, 1, WHITE);
          break;
        }
        }
        for (int show_i = 5; show_i >= 0; show_i--)
        {
          CreateTextBox(show[show_i]);
        }
      }
      j++;
    }
    tmp = tmp->getNext();
  }

  StatusHelp_QLCB();

  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(tabCB_data.current_showPage, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (tabCB_data.current_showPage != swp)
  {
    tabCB_data.pickdata_index = -1;
    tabCB_data.data = NULL;
  }
  tabCB_data.current_showPage = swp;
  if (tabCB_data.current_showPage > n_page)
    tabCB_data.current_showPage = 1;

  // if (first_run)
  //   first_run = false;
  return tabCB_data.data;
}

void CreatePage_QLVe()
{
  CreatePageBackground(3);
  // CreateTable_QLVe();

  ChuyenBay *cb = new ChuyenBay("CB01", "Da Lat", {25, 4, 2023, 10, 0}, "MB1");
  // XuLy_QLVe(*cb);
}

void CreateTable_QLVe()
{
  DrawTextEx(FontArial, "DANH SÁCH VÉ",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);
  float cellW[3] = {100, 200, 400};
  CreateTable({CenterDataSetter(1080, StartPos.x + 60, 700),
               StartPos.y + 60 + 100 + 80},
              3, cellW, 700);
}

void CreatePage_QLHK(DsHanhKhach &listHK, QLHK_data &tabHK_data)
{
  CreatePageBackground(2);

  static NodeHK *data;
  static char *preResult = (char *)"\0";
  static int status = 0;
  static int current_popup = 0; // 0-k hien/ 1-them/ 2-sua/ 3-xoa

  DrawTextEx(FontArial, "DANH SÁCH HÀNH KHÁCH",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);

  if (current_popup == 0)
  { // mini function
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
      current_popup = 1;
    }
    button[1].tittle = "Huỷ vé";
    if (CreateButton(button[1]))
    {
      current_popup = 2;
    }
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15,
    // 240, 60, false, "Quản lý vé", FontArial, ArrowKey))
    // {
    //     cout << "quan ly ve" << endl;
    // }
    // if (CreateButton(StartPos.x + 1201 + 29, StartPos.y + 60 + 20 + 70 + 15 +
    // 75, 240, 60, false, "Huỷ vé", FontArial, ArrowKey))
    // {
    //     cout << "huy ve" << endl;
    // }

    CreateTable_QLHK();
  }
  else if (current_popup = 1)
  {
  }
  else if (current_popup = 2)
  {
  }
  data = XuLy_QLHK(listHK, tabHK_data);
  if (data != NULL)
    cout << data->getHK().getCmnd() << endl;
}

void CreateTable_QLHK()
{
  const char *cell_tittle[5] = {"STT", "CMND", "Họ", "Tên", "Phái"};

  float cellW[5] = {100, 300, 380, 200, 100};
  CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, 1080);

  Vector2 *tittle_pos = GetTittlePos(
      {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 5, cellW, cell_tittle);

  for (int i = 0; i < 5; i++)
  {
    DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
  }
}

void showHanhKhach(HanhKhach hanhKhach, int n_char, Vector2 start_pos, float *cellW, int &j, int order)
{
  TextBox show[5];
  const char *showText[5] = {0};
  showText[0] = intToChar(order + 1, n_char);
  showText[1] = strToChar(hanhKhach.getCmnd());
  showText[2] = strToChar(hanhKhach.getHo());
  showText[3] = strToChar(hanhKhach.getTen());
  showText[4] = strToChar(hanhKhach.getPhai());
  for (int show_i = 4; show_i >= 0; show_i--)
  {
    show[show_i] = GetCellTextBox(start_pos, 5, cellW, show_i + 1,
                                  (j % 10) + 1, showText[show_i], 30);
    show[show_i].isCenter = false;
  }
  for (int show_i = 4; show_i >= 0; show_i--)
  {
    CreateTextBox(show[show_i]);
  }
}

NodeHK *XuLy_QLHK(DsHanhKhach &listHK, QLHK_data &tabHK_data)
{
  static NodeHK *result;
  static int index = -1;
  const Vector2 search = {StartPos.x + 60, StartPos.y + 60 + 70};

  // table
  float cellW[5] = {100, 300, 380, 200, 100};
  CreateTable_QLHK();

  // data
  static int current_page = 1;
  int n_page = 1;
  if (tabHK_data.status == 1)
  {
    // current_page = 1 + (listHK.getSize() - 1) / 10;
    // index = (listHK.getSize() - 1) % 10;
    tabHK_data.status = 0;
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
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  result = NULL;

  // show list
  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 60 + 70 + 110};
  int size = listHK.getSize();

  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;

  int i = (current_page - 1) * 10;

  int j = 0;

  NodeHK *root = listHK.getRoot();
  // Queue queue = Queue(size);
  // listHK.levelOrderTraversal(queue);
  // NodeHK *tmp;
  // int k = 0;

  // while (!queue.isEmpty())
  // {
  //   if (j >= i && j <= i + 9)
  //   {
  //     if (j % 10 == index)
  //       result = root;

  //     TextBox show[5];
  //     tmp = queue.getFront();
  //     const char *showText[5] = {0};
  //     showText[0] = intToChar(k + 1, n_char);
  //     showText[1] = strToChar(tmp->getHK().getCmnd());
  //     showText[2] = strToChar(tmp->getHK().getHo());
  //     showText[3] = strToChar(tmp->getHK().getTen());
  //     showText[4] = strToChar(tmp->getHK().getPhai());
  //     for (int show_i = 4; show_i >= 0; show_i--)
  //     {
  //       show[show_i] = GetCellTextBox(start_pos, 5, cellW, show_i + 1,
  //                                     (j % 10) + 1, showText[show_i], 30);
  //       show[show_i].isCenter = false;
  //     }
  //     for (int show_i = 4; show_i >= 0; show_i--)
  //     {
  //       CreateTextBox(show[show_i]);
  //     }
  //   }
  //   j++;
  //   k++;
  //   // }
  //   queue.pop();
  // }

  Queue queue = Queue();
  NodeHK *currNode;
  int order = 0;
  if (root != NULL)
  {
    queue.push(root);
  }

  while (!queue.isEmpty())
  {
    currNode = queue.getFront();
    queue.pop();
    if (j >= i && j <= i + 9)
    {
      if (j % 10 == index)
        result = root;

      showHanhKhach(currNode->getHK(), n_char, start_pos, cellW, j, order);
    }

    if (currNode->getLeft() != NULL)
    {
      queue.push(currNode->getLeft());
    }
    if (currNode->getRight() != NULL)
    {
      queue.push(currNode->getRight());
    }
    j++;
    order++;
  }

  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (current_page != swp)
    index = -1;
  current_page = swp;
  if (current_page > n_page)
    current_page = 1;
  return result;
}

void CreatePage_GioiThieu() { CreatePageBackground(0); }

/**
 * @brief Create a Table object
 *
 * @param cellW tổng các phần tử phải bằng 1080
 *
 * @note Số hàng luôn bằng 10, chiều cao ô luôn là 40, ô tiêu đề là 50
 */
void CreateTable(Vector2 vitriBang, int soCot, float cellW[],
                 float total_cellW)
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

  Rectangle hightlight_tittle = {vitriBang.x, vitriBang.y, total_cellW - 2,
                                 firstLineH};
  DrawRectangleRoundedLines(hightlight_tittle, 0, 0, 3, BLACK);

  Rectangle hightlight_table = {vitriBang.x, vitriBang.y, total_cellW - 2,
                                firstLineH + 10 * lineH};
  DrawRectangleRoundedLines(hightlight_table, 0, 0, 3, BLACK);
}

TextBox GetCellTextBox(Vector2 vitriBang, int soCot, float cellW[],
                       int vi_tri_x, int vi_tri_y, const char *text,
                       float fontSize)
{
  Vector2 ans;
  float cellPosX[soCot];
  cellPosX[0] = vitriBang.x;
  for (int i = 1; i < soCot; i++)
  {
    cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
  }
  TextBox res;
  res.box = {
      cellPosX[vi_tri_x - 1],
      vitriBang.y + 50 + (vi_tri_y - 1) * 40,
      cellW[vi_tri_x - 1],
      40,
  };
  res.fontSize = fontSize;
  res.isCenter = true;
  res.text = (char *)text;

  return res;
}

Vector2 GetCellPos(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x,
                   int vi_tri_y)
{
  Vector2 ans;
  float cellPosX[soCot];
  cellPosX[0] = vitriBang.x;
  for (int i = 1; i < soCot; i++)
  {
    cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
  }
  ans = {cellPosX[vi_tri_x - 1], vitriBang.y + 50 + (vi_tri_y - 1) * 40};
  return ans;
}

Vector2 *GetTittlePos(Vector2 vitriBang, int soCot, float cellW[],
                      const char *cell_tittle[])
{
  Vector2 *ans = new Vector2[soCot];
  float cellPosX[soCot];
  cellPosX[0] = vitriBang.x;
  for (int i = 1; i < soCot; i++)
  {
    cellPosX[i] = cellPosX[i - 1] + cellW[i - 1];
  }

  float pos_y_table_title = CenterDataSetter(
      50, vitriBang.y, MeasureTextEx(FontArial, "A", 40, 0).y);
  float pos_x_table_title[5];

  for (int i = 0; i < soCot; i++) //
  {
    pos_x_table_title[i] =
        CenterDataSetter(cellW[i], cellPosX[i],
                         MeasureTextEx(FontArial, cell_tittle[i], 40, 0).x);
    ans[i] = {pos_x_table_title[i], pos_y_table_title};
  }
  return ans;
}

void ThanhQuanLy(UIcontroller &control)
{
  const int button_width = 360;
  const int button_height = 50;

  char *button_tittle[4];
  button_tittle[0] = (char *)"QUẢN LÝ MÁY BAY",
  button_tittle[1] = (char *)"QUẢN LÝ CHUYẾN BAY",
  button_tittle[2] = (char *)"ĐẶT VÉ",
  button_tittle[3] = (char *)"QUẢN LÝ HÀNH KHÁCH";

  Vector2 buttonPos[5] = {{StartPos.x, StartPos.y},
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
    UI_switchTab(control, 0);
  for (int i = 1; i < 5; i++)
  {
    if (control.current_tab != i)
    {
      if (CreateButton(button[i]))
        UI_switchTab(control, i);
    }
    else
    {
      DrawRectangleRec(
          {buttonPos[i].x, buttonPos[i].y, button_width, button_height},
          MauThanhQuanLy.isPressed);
      DrawTextEx(
          FontArial, button_tittle[i - 1],
          {CenterDataSetter(button_width, buttonPos[i].x,
                            MeasureTextEx(FontArial, button_tittle[i - 1],
                                          button_height / 2.0f, 0)
                                .x),
           button_height / 5.0f + buttonPos[i].y},
          button_height / 2.0f, 0, MauThanhQuanLy.text2);
    };
  }
}

bool Warning_NoData()
{
  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400, StartPos.y + 300, 700, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "KHÔNG CÓ DỮ LIỆU!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "KHÔNG CÓ DỮ LIỆU!", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "- Có vẻ bạn chưa chọn dữ liệu hoặc dữ liệu trống!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);
  DrawTextEx(FontArial, "-> Hãy click vào 1 dòng trong bảng để lấy dữ liệu!",
             {StartPos.x + 200, StartPos.y + 445}, 55, 0, BLACK);

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

int Warning_Confirm()
{
  CreatePopupBackground();
  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400, StartPos.y + 300, 700, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "XÁC NHẬN!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "XÁC NHẬN!", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "Bạn có muốn huỷ vé không!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);
  // DrawTextEx(FontArial, "-> Hãy click vào 1 dòng trong bảng để lấy dữ liệu!",
  //            {StartPos.x + 200, StartPos.y + 445}, 55, 0, BLACK);

  Button OK;
  OK.x = StartPos.x + 225 + 750;
  OK.y = StartPos.y + 60 + 625;
  OK.w = 100;
  OK.h = 50;
  OK.gotNothing = false;
  OK.gotText = true;
  OK.tittle = (char *)"OK";
  OK.font = FontArial;
  OK.BoMau = ArrowKey;

  Button CANCEL;
  CANCEL.x = StartPos.x + 225;
  CANCEL.y = StartPos.y + 60 + 625;
  CANCEL.w = 100;
  CANCEL.h = 50;
  CANCEL.gotNothing = false;
  CANCEL.gotText = true;
  CANCEL.tittle = (char *)"CANCEL";
  CANCEL.font = FontArial;
  CANCEL.BoMau = ArrowKey;

  if (CreateButton(OK))
  {
    return 1;
  }

  if (CreateButton(CANCEL))
  {
    return 2;
  }
  return 0;
}

// ---Các hàm hỗ trợ ngoài
// vìa------------------------------------------------------------------------------------------------------

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua,
                       float obj_width)
{
  return doDai_khung_chua / 2.0f + vi_tri_khung_chua - obj_width / 2.0f;
}

int SwitchPage(int current_page, int n_page, Vector2 pos)
{
  static bool editmode = false;
  Rectangle textBox = {pos.x + 50, pos.y, 160, 50};
  Rectangle pg1 = {textBox.x + textBox.width + 2, textBox.y, 70 - 4, 50};
  Rectangle pg2 = {textBox.x + textBox.width + 70 + 2, textBox.y, 70 - 4, 50};
  int status = 0;
  int page_n = current_page;

  // char *n1 = new char[2], *n2 = new char[2];
  char n1[3], n2[3];
  strcpy(n1, intToChar(current_page, 2));
  n1[2] = '\0';
  strcpy(n2, intToChar(n_page, 2));
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
  DrawTextEx(
      FontArial, text,
      {CenterDataSetter(160, textBox.x,
                        MeasureTextEx(FontArial, text, 30, 0).x),
       CenterDataSetter(50, textBox.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
      30, 0, BLACK);

  DrawRectangleRec(pg1, WHITE);
  DrawRectangleRoundedLines(pg1, 0, 1, 2, BROWN);

  DrawRectangleRec(pg2, WHITE);
  DrawRectangleRoundedLines(pg2, 0, 1, 2, BROWN);

  DrawTextEx(
      FontArial, n1,
      {CenterDataSetter(70, pg1.x, MeasureTextEx(FontArial, n1, 30, 0).x),
       CenterDataSetter(50, pg1.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
      30, 0, BLACK);
  DrawTextEx(
      FontArial, n2,
      {CenterDataSetter(70, pg2.x, MeasureTextEx(FontArial, n2, 30, 0).x),
       CenterDataSetter(50, pg2.y, MeasureTextEx(FontArial, "A", 30, 0).y)},
      30, 0, BLACK);

  if (current_page < n_page)
  {
    if (CreateButton(button[1]))
      status = 1;
  }
  else
  {
    DrawRectangle(pos.x + 50 + 300 + 10, pos.y + 10, 30, 30,
                  ArrowKey.isPressed);
    DrawTexture(PNG_arrowRight, pos.x + 50 + 300 + 10, pos.y + 10,
                ArrowKey.isPressed);
  }

  if (CheckCollisionPointRec(GetVMousePosition(), pg1) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    editmode = true;
  static InputTextBox fast_switcher;
  fast_switcher.textBox = pg1;
  fast_switcher.editMode = true;
  fast_switcher.tittle = intToChar(current_page, 2);
  fast_switcher.size = 2;
  fast_switcher.MauVien = BROWN;
  fast_switcher.mode = 5;
  fast_switcher.returnIfDone = true;
  fast_switcher.showNKeyRemain = false;
  if (editmode)
  {
    const char *page_t = CreateTextInputBox(fast_switcher);
    if (page_t[0] == 0)
      page_n = current_page;
    else
      page_n = stoi(page_t);
    if (!(page_n > 0 && page_n <= n_page))
    {
      page_n = current_page;
      resetInputTextBox(fast_switcher);
    }
  }

  if (page_n != current_page)
  {
    resetInputTextBox(fast_switcher);
    editmode = false;
    return page_n;
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
  Vector2 TextPos = {
      CenterDataSetter(
          data.w, data.x,
          MeasureTextEx(data.font, data.tittle, data.h / 2.0f, 0).x),
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
      DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                 data.BoMau.text1);
    else if (data.gotPic)
      DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                    data.BoMau.isnotHovered);
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
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text2);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2,
                                  data.BoMau.RounderPressed);
      }
      else
      {
        if (!data.gotNothing)
          DrawRectangleRounded(Button, 0.5f, 0.5f, data.BoMau.isHovered);
        if (data.gotText)
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text1);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2,
                                  data.BoMau.RounderHovered);
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
      DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                 data.BoMau.text1);
    else if (data.gotPic)
      DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                    data.BoMau.isnotHovered);
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
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text2);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2,
                                  data.BoMau.RounderPressed);
      }
      else
      {
        if (!data.gotNothing)
          DrawRectangleRec(Button, data.BoMau.isHovered);
        if (data.gotText)
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text2);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0.5f, 2,
                                  data.BoMau.RounderHovered);
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

  Vector2 textBoxPos = {
      data.textBox.x + 5,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, data.name, font_size, 0).y)};
  Vector2 MousePos = {0.0f, 0.0f};
  strcpy(name_cpy, data.name);
  name_cpy[data.letterCount + data.indexPoint] = '\0';

  Vector2 textBoxDot = {
      data.textBox.x + MeasureTextEx(FontArial, name_cpy, font_size, 0).x,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, name_cpy, font_size, 0).y)};

  if (data.editMode && data.done)
  {
    strcpy(data.name, data.tittle);
    data.letterCount = getCharSize(data.name);
  }

  MousePos = GetVMousePosition();
  if (CheckCollisionPointRec(MousePos, data.textBox) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
  else if (!CheckCollisionPointRec(MousePos, data.textBox) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
      key = chuanHoaKey(key, data.name, data.letterCount + data.indexPoint,
                        data.mode);
      if ((key >= 32) && (key <= 127) && (data.letterCount < data.size))
      {
        for (int i = data.letterCount; i > data.letterCount + data.indexPoint;
             i--)
        {
          data.name[i] = data.name[i - 1];
        }
        data.name[data.letterCount + data.indexPoint] = char(key);
        data.name[data.letterCount + 1] = '\0';
        data.letterCount++;
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
    if ((IsKeyDown(KEY_BACKSPACE) && data.letterCount + data.indexPoint > 0 &&
         (data.fHold_BS > 10) && (data.fHold_BS % 1 == 0)) ||
        IsKeyPressed(KEY_BACKSPACE) && data.letterCount + data.indexPoint > 0)
    {
      for (int i = data.letterCount + data.indexPoint - 1; i < data.letterCount;
           i++)
      {
        data.name[i] = data.name[i + 1];
      }
      data.letterCount--;
      if (data.letterCount < 0)
        data.letterCount = 0;
      data.name[data.letterCount] = '\0';
    }
    if ((IsKeyDown(KEY_LEFT) && (data.letterCount + data.indexPoint) > 0 &&
         (data.fHold_LEFT > 20) && (data.fHold_LEFT % 1 == 0)) ||
        (IsKeyPressed(KEY_LEFT) && (data.letterCount + data.indexPoint) > 0))
    {
      data.indexPoint--;
    }
    if ((IsKeyDown(KEY_RIGHT) && data.indexPoint < 0 &&
         (data.fHold_RIGHT > 20) && (data.fHold_RIGHT % 1 == 0)) ||
        (IsKeyPressed(KEY_RIGHT) && data.indexPoint < 0))
    {
      data.indexPoint++;
    }
  }
  else
    data.framesCounter = 0;

  // Lấy đủ 4 kí tự
  if (data.mode == 8)
  {
    if (data.letterCount == 4)
      data.returnIfDone = false;
    else
      data.returnIfDone = true;
  }
  if (data.mode == 6 || data.mode == 7)
  {
    if (data.letterCount == 1 && data.name[0] == '0')
    {
      data.returnIfDone = true;
      data.done = false;
    }
    else
      data.returnIfDone = false;
  }
  strcpy(result, data.name);

  DrawRectangleRec(data.textBox, data.MauNen);
  DrawRectangleRoundedLines(data.textBox, 0, 1, 2, data.MauVien);
  if (data.showNKeyRemain)
  {
    DrawTextEx(FontArial, intToChar(data.size - data.letterCount, 2),
               {data.textBox.x + data.textBox.width - data.textBox.height,
                data.textBox.y + data.textBox.height / 3},
               data.textBox.height * per1000(400), 0, DARKGREEN);
  }
  if (data.name[0] != '\0')
    DrawTextEx(FontArial, data.name, textBoxPos, font_size, 0, data.MauChu);
  else
    DrawTextEx(FontArial, data.tittle, textBoxPos, font_size, 0, BROWN);
  if (data.mouseClickOnText && ((data.framesCounter % 40 >= 5)))
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

void CreateTextBox(TextBox box)
{
  float text_w = 0.0f;
  box.fontSize = (box.box.height * 2) / 3;

  Vector2 textpos = {
      box.box.x + 10,
      CenterDataSetter(box.box.height, box.box.y,
                       MeasureTextEx(FontArial, "a", box.fontSize, 0).y)};

  char showtext[40] = {0};

  if (box.showBox)
  {
    DrawRectangleRec(box.box, WHITE);
    DrawRectangleRoundedLines(box.box, 0, 0, 2, BLACK);
  }

  if (MeasureTextEx(FontArial, box.text, box.fontSize, 0).x + 20 <
      box.box.width)
  {
    text_w = MeasureTextEx(FontArial, box.text, box.fontSize, 0).x;
    strcpy(showtext, box.text);
  }
  else if (box.mode == 1)
  {
    int i = 0;
    float charW = 0;
    while (MeasureTextEx(FontArial, showtext, box.fontSize, 0).x + charW <
           box.box.width)
    {
      showtext[i] = box.text[i];
      showtext[i + 1] = 0;

      char c[2] = {0};
      c[0] = box.text[i + 1];
      c[1] = 0;
      charW = MeasureTextEx(FontArial, c, box.fontSize, 0).x;
      if (charW == 0)
        break;

      i++;
    }
    text_w = MeasureTextEx(FontArial, showtext, box.fontSize, 0).x;
  }
  else if (box.mode == 2)
  {
    while (MeasureTextEx(FontArial, box.text, box.fontSize, 0).x + 20 >=
           box.box.width)
    {
      if (box.text[0] == 0)
      {
        text_w = 0;
        break;
      }
      box.fontSize -= 2;
    }
    text_w = MeasureTextEx(FontArial, box.text, box.fontSize, 0).x;
    strcpy(showtext, box.text);
  }
  if (box.isCenter)
  {
    textpos.x = CenterDataSetter(box.box.width, box.box.x, text_w);
    textpos.y =
        CenterDataSetter(box.box.height, box.box.y,
                         MeasureTextEx(FontArial, "a", box.fontSize, 0).y);
  }

  DrawTextEx(FontArial, showtext, textpos, box.fontSize, 0, BLACK);
  if (box.mode == 1 && CheckCollisionPointRec(GetVMousePosition(), box.box) &&
      MeasureTextEx(FontArial, box.text, box.fontSize, 0).x + 20 >=
          box.box.width)
  {
    Rectangle fullBox = {box.box.x + 3, box.box.y + 3,
                         MeasureTextEx(FontArial, box.text, box.fontSize, 0).x +
                             20,
                         box.box.height - 6};

    DrawRectangleRec(fullBox, WHITE);
    DrawRectangleRoundedLines(fullBox, 0, 0, 2, BLACK);

    textpos.x =
        CenterDataSetter(fullBox.width, fullBox.x,
                         MeasureTextEx(FontArial, box.text, box.fontSize, 0).x);
    DrawTextEx(FontArial, box.text, textpos, box.fontSize, 0, BLACK);
  }
}

Vector2 GetVMousePosition()
{
  float scaleW = (float)GetScreenWidth() / WINDOW_WIDTH,
        scaleH = (float)GetScreenHeight() / WINDOW_HEIGHT;

  Vector2 mouse = GetMousePosition();

  Vector2 virtualMouse = {0};
  virtualMouse.x =
      (mouse.x - (GetScreenWidth() - (WINDOW_WIDTH * scaleW)) * 0.5f) / scaleW;
  virtualMouse.y =
      (mouse.y - (GetScreenHeight() - (WINDOW_HEIGHT * scaleH)) * 0.5f) /
      scaleH;
  virtualMouse =
      Vector2Clamp(virtualMouse, (Vector2){0, 0},
                   (Vector2){(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT});
  return virtualMouse;
}

//==================================================================================================================================
// main function
void mainGraphics()
{
  UIcontroller main;
  InitUIData(main);
  // Settup data
  getDataFromFile(main.listCB, main.listMB, main.listHK);

  // Settup for before run graphics

  SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  SetWindowMinSize(700, 400);
  LoadResources();
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetTargetFPS(20); // max framerate per second set to 20
  SetSizeWindow();
  RenderTexture2D renderTexture = LoadRenderTexture(
      WINDOW_WIDTH, WINDOW_HEIGHT); // Load nội dung màn hình như một ảnh
  GenTextureMipmaps(&renderTexture.texture);
  SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_TRILINEAR);

  // Graphics in running
  while (!WindowShouldClose())
  {
    BeginTextureMode(renderTexture);
    // Cách thao tác trên đồ hoạ

    if (main.current_tab != 0)
      ThanhQuanLy(main);
    switch (main.current_tab)
    {
    case 0:
    {
      CreateHomePage(main);
      break;
    }
    case 1:
    {
      CreatePage_QLMB(main.listMB, main.dataTabMB);
      break;
    }
    case 2:
    {
      CreatePage_QLCB(main.listCB, main.dataTabCB);
      break;
    }
    case 3:
    {
      CreatePage_QLVe();
      break;
    }
    case 4:
    {
      CreatePage_QLHK(main.listHK, main.dataTabHK);
      break;
    }
    case 5:
    {
      CreatePage_GioiThieu();
      break;
    }
    default:
    {
      main.current_tab = 0;
    }
    }

    EndTextureMode();
    BeginDrawing();
    // xuất màn hình tĩnh theo chỉ sô động6
    DrawTexturePro(renderTexture.texture,
                   Rectangle{0, 0,
                             static_cast<float>(renderTexture.texture.width),
                             static_cast<float>(-renderTexture.texture.height)},
                   Rectangle{0, 0, static_cast<float>(GetScreenWidth()),
                             static_cast<float>(GetScreenHeight())},
                   Vector2{0, 0}, 0, WHITE);
    EndDrawing();
  }

  // Clear all data after run graphics
  UnloadRenderTexture(renderTexture);
  UnloadResources();
}
