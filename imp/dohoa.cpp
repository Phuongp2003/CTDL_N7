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

// Global status variable
int V_MOUSE_CURSOR_IBEAM = 0;
int V_MOUSE_CURSOR_POINTING_HAND = 0;

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
  bool isActive = true;

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
  bool isActive = true;

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

struct PageSwitcher
{
  bool editmode = false;
  InputTextBox fast_switcher;
  PageSwitcher()
  {
    fast_switcher.editMode = true;
    fast_switcher.size = 2;
    fast_switcher.MauVien = BROWN;
    fast_switcher.mode = 5;
    fast_switcher.returnIfDone = true;
    fast_switcher.showNKeyRemain = false;
  }
  void reset()
  {
    editmode = false;
    resetInputTextBox(fast_switcher);
  }
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

  PageSwitcher Sw_table_page;

  QLMB_data()
  {
    data = NULL;
    current_popup = 0;
    popup_errorMess = "";
    time_showError = 0;

    MaMB.mode = 3;
    MaMB.tittle = (char *)"Nhập số hiệu máy bay";
    MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
    MaMB.size = 15;
    LoaiMB.mode = 2;
    LoaiMB.tittle = (char *)"Nhập loại máy bay";
    LoaiMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    LoaiMB.size = 40;
    SoDong.mode = 5;
    SoDong.tittle = (char *)"Nhập số dòng của máy bay";
    SoDong.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
    SoDong.size = 3;
    SoDay.mode = 5;
    SoDay.tittle = (char *)"Nhập số dãy của máy bay";
    SoDay.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
    SoDay.size = 3;

    pickdata_index = -1;
    keyword = "";
    searchKeyword.mode = 3;
    searchKeyword.tittle = "Nhập nội dung tìm kiếm";
    current_showPage = 1;

    Sw_table_page = PageSwitcher();
  }
};

struct QLHK_data
{
  NodeHK *data = nullptr;
  int status = 0;

  int current_popup = 0;
  string popup_errorMess = "";
  int time_showError = 0;

  int pickdata_index = -1;
  int current_page = 1;

  InputTextBox i_CMND, i_Ho, i_Ten;
  int i_Phai = -1;

  PageSwitcher Sw_table_page;

  QLHK_data()
  {
    data = nullptr;
    status = 0;
    current_popup = 0;
    pickdata_index = -1;
    current_page = 1;

    i_CMND.mode = 5;
    i_CMND.tittle = (char *)"Nhập số CMND/CCCD";
    i_CMND.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    i_CMND.size = 15;

    i_Ho.mode = 1;
    i_Ho.tittle = (char *)"Nhập họ và tên đệm";
    i_Ho.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 580, 50};
    i_Ho.size = 40;

    i_Ten.mode = 1;
    i_Ten.tittle = (char *)"Nhập tên";
    i_Ten.textBox = {StartPos.x + 300 + 600, StartPos.y + 60 + 380, 300, 50};
    i_Ten.size = 40;

    i_Phai = -1;

    Sw_table_page = PageSwitcher();
  }
};

struct QLVe_data
{
  int current_page = 1;
  int position = -1;
  int pickdata_index = -1;
  VeMayBay data = VeMayBay();

  bool inDelete = false;

  PageSwitcher Sw_table_page;

  QLVe_data()
  {
    current_page = 1;
    position = -1;
    data = VeMayBay();
    inDelete = false;

    Sw_table_page = PageSwitcher();
  }
};

struct QLCB_data
{
  NodeCB *data = nullptr;
  int status = 0;

  int current_popup = 0;
  string popup_errorMess = "";
  int time_showError = 0;
  InputTextBox MaCB, MaMB, NoiDen, Ngay, Thang, Nam, Gio, Phut;
  bool inChooseMB = false;
  QLVe_data dataDSVe;

  InputTextBox searchMaCB, searchNoiDen, searchNgay, searchThang, searchNam;
  int pickdata_index = -1;
  int current_showPage = 1;

  Date fbDay = Date(1, 1, 0, 0, 0);
  bool inShowFightAvail = false;
  bool inGetTicket = false;
  bool inSetTicket = false;
  bool gotNewTicket = false;

  PageSwitcher Sw_table_page;

  QLCB_data()
  {
    data = nullptr;
    status = 0;
    current_popup = 0;
    popup_errorMess = "";
    time_showError = 0;
    inChooseMB = false;
    dataDSVe = QLVe_data();

    MaCB.mode = 3;
    MaCB.tittle = (char *)"Nhập mã chuyến bay";
    MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    MaCB.size = 15;
    MaMB.mode = 3;
    MaMB.tittle = (char *)"Nhập số hiệu máy bay";
    MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 900, 50};
    MaMB.size = 40;
    NoiDen.mode = 1;
    NoiDen.tittle = (char *)"Nhập nơi đến";
    NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
    NoiDen.size = 40;
    Ngay.mode = 6;
    Ngay.tittle = (char *)"DD";
    Ngay.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 60, 50};
    Ngay.size = 2;
    Ngay.showNKeyRemain = false;
    Thang.mode = 7;
    Thang.tittle = (char *)"MM";
    Thang.textBox = {StartPos.x + 300 + 70, StartPos.y + 60 + 180, 60, 50};
    Thang.size = 2;
    Thang.showNKeyRemain = false;
    Nam.mode = 8;
    Nam.tittle = (char *)"YYYY";
    Nam.textBox = {StartPos.x + 300 + 70 + 70, StartPos.y + 60 + 180, 120,
                   50};
    Nam.size = 4;
    Nam.showNKeyRemain = false;
    Gio.mode = 9;
    Gio.tittle = (char *)"HH";
    Gio.textBox = {StartPos.x + 300 + 70 + 70 + 150, StartPos.y + 60 + 180,
                   60, 50};
    Gio.size = 2;
    Gio.showNKeyRemain = false;
    Phut.mode = 10;
    Phut.tittle = (char *)"MM";
    Phut.textBox = {StartPos.x + 300 + 70 + 70 + 150 + 70,
                    StartPos.y + 60 + 180, 60, 50};
    Phut.size = 2;
    Phut.showNKeyRemain = false;

    searchMaCB.tittle = "Mã chuyến bay";
    searchMaCB.size = 15;
    searchMaCB.mode = 3;
    searchNoiDen.tittle = "Nơi đến";
    searchNoiDen.size = 20;
    searchNoiDen.mode = 1;

    pickdata_index = -1;
    current_showPage = 1;

    fbDay = Date(1, 1, 0, 0, 0);
    inShowFightAvail = false;
    inGetTicket = false;
    gotNewTicket = false;

    Sw_table_page = PageSwitcher();
  }
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

  control.current_tab = idTab;
}
void InitUIData(UIcontroller &control)
{
  control.current_tab = 0;
  control.dataTabMB = QLMB_data();
  control.dataTabCB = QLCB_data();
  control.dataTabHK = QLHK_data();
}

void resetData_QLMB(QLMB_data &data)
{
  data.data = nullptr;
  data.status = 0;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;
  resetInputTextBox(data.MaMB);
  data.MaMB.tittle = (char *)"Nhập số hiệu máy bay";
  resetInputTextBox(data.LoaiMB);
  data.LoaiMB.tittle = (char *)"Nhập loại máy bay";
  resetInputTextBox(data.SoDong);
  data.SoDong.tittle = (char *)"Nhập số dòng của máy bay";
  resetInputTextBox(data.SoDay);
  data.SoDay.tittle = (char *)"Nhập số dãy của máy bay";

  data.pickdata_index = -1;
  data.keyword = "";
  resetInputTextBox(data.searchKeyword);
  data.searchKeyword.tittle = "Nhập nội dung tìm kiếm";
  data.current_showPage = 1;

  data.Sw_table_page.reset();
}

void resetData_QLCB(QLCB_data &data)
{
  resetInputTextBox(data.MaCB);
  data.MaCB.tittle = (char *)"Nhập mã chuyến bay";

  resetInputTextBox(data.MaMB);
  data.MaMB.tittle = (char *)"Nhập số hiệu máy bay";

  resetInputTextBox(data.NoiDen);
  data.NoiDen.tittle = (char *)"Nhập nơi đến";

  resetInputTextBox(data.Ngay);
  data.Ngay.tittle = (char *)"DD";

  resetInputTextBox(data.Thang);
  data.Thang.tittle = (char *)"MM";

  resetInputTextBox(data.Nam);
  data.Nam.tittle = (char *)"YYYY";

  resetInputTextBox(data.Gio);
  data.Gio.tittle = (char *)"HH";

  resetInputTextBox(data.Phut);
  data.Phut.tittle = (char *)"MM";

  resetInputTextBox(data.searchNoiDen);
  data.searchNoiDen.tittle = "Nơi đến";

  resetInputTextBox(data.searchMaCB);
  data.searchMaCB.tittle = "Mã chuyến bay";

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

  resetData_QLVe(data.dataDSVe);

  data.data = NULL;
  data.status = 0;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;
  data.inChooseMB = false;

  data.pickdata_index = -1;
  data.current_showPage = 1;

  data.fbDay = Date(1, 1, 0, 0, 0);
  data.inShowFightAvail = false;
  data.inGetTicket = false;
  data.gotNewTicket = false;

  data.Sw_table_page.reset();
}

void resetData_QLHK(QLHK_data &data)
{
  data.data = nullptr;
  data.status = 0;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;

  data.pickdata_index = -1;
  data.current_page = 1;

  resetInputTextBox(data.i_CMND);

  resetInputTextBox(data.i_Ho);

  resetInputTextBox(data.i_Ten);

  data.i_Phai = -1;

  data.Sw_table_page.reset();
}

void resetData_QLVe(QLVe_data &data)
{
  data.current_page = 1;
  data.position = -1;
  data.data = VeMayBay();
  data.inDelete = false;

  data.Sw_table_page.reset();
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
void CreatePage_QLMB(UIcontroller &control)
{
  CreatePageBackground(4);
  if (control.dataTabMB.data == NULL && !(control.dataTabMB.current_popup == 0 || control.dataTabMB.current_popup == 1 || control.dataTabMB.current_popup == 4))
  {
    CreatePopupBackground();
    if (Warning_NoData())
      control.dataTabMB.current_popup = 0;
    return;
  }

  // tittle
  DrawTextEx(FontArial, "DANH SÁCH MÁY BAY",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);

  if (control.dataTabMB.current_popup == 0)
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

    // disable button if no data
    if (control.dataTabMB.data == NULL)
    {
      button[1].isActive = false;
      button[2].isActive = false;
    }
    else
    {
      button[1].isActive = true;
      button[2].isActive = true;
    }
    // if(control.dataTabMB.data)

    // mini function
    button[0].tittle = "Thêm máy bay";
    if (CreateButton(button[0]))
    {
      control.dataTabMB.current_popup = 1;
    }
    button[1].tittle = "Hiệu chỉnh máy bay";
    if (CreateButton(button[1]))
    {

      control.dataTabMB.current_popup = 2;
    }
    button[2].tittle = "Xoá máy bay";
    if (CreateButton(button[2]))
    {
      control.dataTabMB.current_popup = 3;
    }
    button[3].tittle = "Thống kê S.lượt bay";
    if (CreateButton(button[3]))
    {
      control.dataTabMB.current_popup = 4;
      // control.dataTabMB.Sw_table_page.reset();
    }
    control.dataTabMB.data = XuLy_QLMB(control);
    // if (data->getSoHieuMB()[0] >= 36)
    // {
    //     preResult = data->getSoHieuMB();
    // }
  }
  else if (control.dataTabMB.current_popup == 1)
  {
    if (Popup_ThemMB(control))
      control.dataTabMB.current_popup = 0;
  }
  else if (control.dataTabMB.current_popup == 2)
  {
    if (Popup_HieuChinhMB(control))
      control.dataTabMB.current_popup = 0;
  }
  else if (control.dataTabMB.current_popup == 3)
  {
    if (Popup_XoaMB(control))
      control.dataTabMB.current_popup = 0;
  }
  else if (control.dataTabMB.current_popup == 4)
  {
    if (Popup_Thongkesoluotbay(control))
    {
      control.dataTabMB.current_popup = 0;
      // control.dataTabMB.Sw_table_page.reset();
    }
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

bool Popup_ThemMB(UIcontroller &control)
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
  const char *newMaMB = CreateTextInputBox(control.dataTabMB.MaMB);
  DrawTextEx(FontArial, "Hãng máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  const char *newLoaiMayBay = CreateTextInputBox(control.dataTabMB.LoaiMB);
  DrawTextEx(FontArial, "Số dòng",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nho hon hoac bang 25)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newSoDong = CreateTextInputBox(control.dataTabMB.SoDong);
  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nho hon hoac bang 12)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  const char *newSoDay = CreateTextInputBox(control.dataTabMB.SoDay);

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
      FontArial, strToChar(control.dataTabMB.popup_errorMess),
      {CenterDataSetter(
           1100, StartPos.x + 200,
           MeasureTextEx(FontArial, strToChar(control.dataTabMB.popup_errorMess), 40, 0).x),
       CenterDataSetter(50, StartPos.y + 130,
                        MeasureTextEx(FontArial, "A", 40, 0).y)},
      40, 0, RED);

  if (CreateButton(OK))
  {
    char CheckMB[16];
    strcpy(CheckMB, newMaMB);
    if (control.listMB.findPosMB(CheckMB) < 0)
    {
      if (newMaMB[0] >= 32 && newLoaiMayBay[0] >= 32 && newSoDay[0] >= 32 &&
          newSoDong[0] >= 32)
      {
        if (atoi(newSoDong) < 1 || atoi(newSoDong) > 25)
        {
          control.dataTabMB.popup_errorMess = "So dong khong hop le!";
          return false;
        }
        if (atoi(newSoDay) < 1 || atoi(newSoDay) > 12)
        {
          control.dataTabMB.popup_errorMess = "So day khong hop le!";
          return false;
        }
        if (atoi(newSoDong) * atoi(newSoDay) < 20)
        {
          control.dataTabMB.popup_errorMess = "So cho phai lon hon hoac bang 20!";
          return false;
        }
        MayBay *result =
            new MayBay(newMaMB, newLoaiMayBay, atoi(newSoDay), atoi(newSoDong));
        control.listMB.insertMB(result);
        control.listMB.writetoFileWhenAdd();

        control.dataTabMB.status = 1;
        resetInputTextBox(control.dataTabMB.MaMB);
        resetInputTextBox(control.dataTabMB.LoaiMB);
        resetInputTextBox(control.dataTabMB.SoDong);
        resetInputTextBox(control.dataTabMB.SoDay);
        control.dataTabMB.popup_errorMess = "";

        return true;
      }
      else
      {
        control.dataTabMB.popup_errorMess = "Nhập chưa đủ thông tin!";
      }
    }
    else
    {
      control.dataTabMB.popup_errorMess = "Máy Bay đã tồn tại!";
    }
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabMB.MaMB);
    resetInputTextBox(control.dataTabMB.LoaiMB);
    resetInputTextBox(control.dataTabMB.SoDong);
    resetInputTextBox(control.dataTabMB.SoDay);

    control.dataTabMB.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_HieuChinhMB(UIcontroller &control)
{
  CreatePopupBackground();
  DrawTextEx(FontArial, "Sửa thông tin máy bay",
             {CenterDataSetter(
                  700, StartPos.x + 400,
                  MeasureTextEx(FontArial, "Sửa thông tin máy bay", 50, 0).x),
              CenterDataSetter(60, StartPos.y + 60 + 10,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLACK);

  TextBox Box_maMB;
  Box_maMB.box = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
  Box_maMB.showBox = true;
  Box_maMB.text = control.dataTabMB.data->getSoHieuMB();
  CreateTextBox(Box_maMB);

  // control.dataTabMB.MaMB.editMode = true;
  // control.dataTabMB.MaMB.tittle = control.dataTabMB.data->getSoHieuMB();
  control.dataTabMB.LoaiMB.editMode = true;
  control.dataTabMB.LoaiMB.tittle = control.dataTabMB.data->getLoaiMB();
  control.dataTabMB.SoDong.editMode = true;
  control.dataTabMB.SoDong.tittle = intToChar(control.dataTabMB.data->getSoDong(), 3);
  control.dataTabMB.SoDay.editMode = true;
  control.dataTabMB.SoDay.tittle = intToChar(control.dataTabMB.data->getSoDay(), 3);

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;

  DrawTextEx(FontArial, "Mã máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  DrawTextEx(
      FontArial, "(Gồm chữ cái IN HOA và số)",
      {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25}, 25,
      0, RED);
  // const char *newMaMB = CreateTextInputBox(control.dataTabMB.MaMB);
  DrawTextEx(FontArial, "Hãng máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(
      FontArial, "(Gồm chữ cái và số)",
      {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25}, 25,
      0, RED);
  const char *newLoaiMB = CreateTextInputBox(control.dataTabMB.LoaiMB);
  DrawTextEx(FontArial, "Số dòng",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(
      FontArial, "(Gồm CHỈ số, nhỏ hơn hoặc bằng 25)",
      {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25}, 25,
      0, RED);
  const char *newSoDong = CreateTextInputBox(control.dataTabMB.SoDong);
  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(
      FontArial, "(Gồm CHỈ số, nhỏ hơn hoặc bằng 12)",
      {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25}, 25,
      0, RED);
  const char *newSoDay = CreateTextInputBox(control.dataTabMB.SoDay);

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
      FontArial, strToChar(control.dataTabMB.popup_errorMess),
      {CenterDataSetter(1100, StartPos.x + 200,
                        MeasureTextEx(FontArial, strToChar(control.dataTabMB.popup_errorMess), 40, 0).x),
       CenterDataSetter(50, StartPos.y + 130,
                        MeasureTextEx(FontArial, "A", 40, 0).y)},
      40, 0, RED);

  if (CreateButton(OK))
  {
    // char CheckMB[16];
    // strcpy(CheckMB, newMaMB);
    // if (control.listMB.findPosMB(CheckMB) < 0 ||
    //     control.listMB.findPosMB(CheckMB) ==
    //         control.listMB.findPosMB(control.dataTabMB.data->getSoHieuMB()))
    // {
    if (newLoaiMB[0] >= 32 && newSoDay[0] >= 32 &&
        newSoDong[0] >= 32)
    {
      if (atoi(newSoDong) < 1 || atoi(newSoDong) > 25)
      {
        control.dataTabMB.popup_errorMess = "So dong khong hop le!";
        return false;
      }
      if (atoi(newSoDay) < 1 || atoi(newSoDay) > 12)
      {
        control.dataTabMB.popup_errorMess = "So day khong hop le!";
        return false;
      }
      if (atoi(newSoDong) * atoi(newSoDay) < 20)
      {
        control.dataTabMB.popup_errorMess = "So cho phai lon hon hoac bang 20!";
        return false;
      }
      // control.dataTabMB.data->setSoHieuMB(newMaMB);
      control.dataTabMB.data->setLoaiMB(newLoaiMB);
      control.dataTabMB.data->setSoDong(atoi(newSoDong));
      control.dataTabMB.data->setSoDay(atoi(newSoDay));

      control.listMB.writetoFile();

      // resetInputTextBox(control.dataTabMB.MaMB);
      resetInputTextBox(control.dataTabMB.LoaiMB);
      resetInputTextBox(control.dataTabMB.SoDong);
      resetInputTextBox(control.dataTabMB.SoDay);
      control.dataTabMB.popup_errorMess = "";

      return true;
    }
    else
    {
      control.dataTabMB.popup_errorMess = "Nhập chưa đủ thông tin!";
    }
    // }
    // else
    // {
    //   control.dataTabMB.popup_errorMess = "Mã máy bay đã tồn tại!";
    // }
  }

  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabMB.MaMB);
    resetInputTextBox(control.dataTabMB.LoaiMB);
    resetInputTextBox(control.dataTabMB.SoDong);
    resetInputTextBox(control.dataTabMB.SoDay);
    return true;
  }

  return false;
}

bool Popup_XoaMB(UIcontroller &control)
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

  DrawTextEx(FontArial, "Mã máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  TextBox Box_maMB;
  Box_maMB.box = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
  Box_maMB.showBox = true;
  Box_maMB.text = control.dataTabMB.data->getSoHieuMB();
  CreateTextBox(Box_maMB);

  DrawTextEx(FontArial, "Hãng máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  TextBox Box_loaiMB;
  Box_loaiMB.box = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  Box_loaiMB.showBox = true;
  Box_loaiMB.text = control.dataTabMB.data->getLoaiMB();
  CreateTextBox(Box_loaiMB);

  DrawTextEx(FontArial, "Số dòng",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  TextBox Box_soDong;
  Box_soDong.box = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
  Box_soDong.showBox = true;
  Box_soDong.text = intToChar(control.dataTabMB.data->getSoDong(), 2);
  CreateTextBox(Box_soDong);

  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  TextBox Box_soDay;
  Box_soDay.box = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
  Box_soDay.showBox = true;
  Box_soDay.text = intToChar(control.dataTabMB.data->getSoDay(), 2);
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
    strcpy(CheckMB, control.dataTabMB.data->getSoHieuMB());
    control.listMB.deleteMB(control.listMB.findPosMB(CheckMB));

    control.listMB.writetoFile();

    control.dataTabMB.status = -1;

    return true;
  }
  if (CreateButton(Cancel))
  {
    return true;
  }

  return false;
}

bool Popup_Thongkesoluotbay(UIcontroller &control)
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
  control.dataTabMB.searchKeyword.textBox = searchText;

  DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

  control.dataTabMB.keyword = CreateTextInputBox(control.dataTabMB.searchKeyword);

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

  // control.dataTabMB.current_showPage = 1;
  int n_page = 1; // 1 + (spt/10)
  int size = control.listMB.getSize();
  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;
  int i = (control.dataTabMB.current_showPage - 1) * 10;
  int j = 0;
  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 110 + 70 + 60};
  int *A = control.listMB.sapXepThongKe();
  for (int id = 0; id < size; id++)
  {
    if (isGotStr(control.listMB.getMB(id)->getSoHieuMB(), control.dataTabMB.keyword))
    {
      if (j >= i && j <= i + 9)
      {

        TextBox show[3];
        const char *showText[3] = {
            intToChar(j + 1, n_char),
            control.listMB.getMB(A[id])->getSoHieuMB(), // control.listMB.getMB()[control.listMB.sapXepThongKe()[id]]->getSoHieuMB()
            intToChar(control.listMB.getMB(A[id])->getSoLuotBay(), 3)};
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
      SwitchPage(control.dataTabMB.Sw_table_page, control.dataTabMB.current_showPage, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});

  control.dataTabMB.current_showPage = swp;
  if (control.dataTabMB.current_showPage > n_page)
    control.dataTabMB.current_showPage = 1;

  if (CreateButton(button))
  {
    control.dataTabMB.current_showPage = 1;
    resetInputTextBox(control.dataTabMB.searchKeyword);
    // control.dataTabMB.current_popup =0;
    return true;
  }
  return false;
}

MayBay *XuLy_QLMB(UIcontroller &control)
{
  // search
  Rectangle searchText = {StartPos.x + 60, StartPos.y + 60 + 100 + 15, 880, 50};
  DrawRectangleRec(searchText, WHITE);
  DrawRectangleRoundedLines(searchText, 0, 1, 3, BLACK);
  control.dataTabMB.searchKeyword.textBox = searchText;

  DrawTextEx(FontArial, "Search", {searchText.x, searchText.y}, 40, 0, BLUE);

  control.dataTabMB.keyword = CreateTextInputBox(control.dataTabMB.searchKeyword);

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
  //     current_page = 1 + (control.listMB.getsize() - 1) / 10;
  //     index = (control.listMB.getsize() - 1) % 10;
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
      if (control.dataTabMB.pickdata_index != i)
      {

        control.dataTabMB.pickdata_index = i;
      }
      else
        control.dataTabMB.pickdata_index = -1;
    }
    if (control.dataTabMB.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  // if (control.dataTabMB.pickdata_index >= 0)
  // {
  //     result = control.listMB.getMB(control.dataTabMB.pickdata_index);
  // }
  // else
  //     result = new MayBay();

  int size = control.listMB.getSize();
  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;
  int i = (control.dataTabMB.current_showPage - 1) * 10;
  int j = 0;
  // if (current_page * 10 < size)
  //     j = current_page * 10;
  // else
  // {
  //     j = size;
  // }

  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 60 + 70 + 110};
  for (int id = 0; id < size; id++)
  {
    if (isGotStr(control.listMB.getMB(id)->getSoHieuMB(), control.dataTabMB.keyword))
    {
      if (j >= i && j <= i + 9)
      {
        if (j % 10 == control.dataTabMB.pickdata_index)
          control.dataTabMB.data = control.listMB.getMB(id);
        TextBox show[5];
        const char *showText[5] = {

            intToChar(j + 1, n_char), control.listMB.getMB(id)->getSoHieuMB(),
            control.listMB.getMB(id)->getLoaiMB(),
            intToChar(control.listMB.getMB(id)->getSoDay(), 3),
            intToChar(control.listMB.getMB(id)->getSoDong(), 3)};
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
      SwitchPage(control.dataTabMB.Sw_table_page, control.dataTabMB.current_showPage, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabMB.current_showPage != swp)
  {
    control.dataTabMB.pickdata_index = -1;
    control.dataTabMB.data = nullptr;
  }
  control.dataTabMB.current_showPage = swp;
  if (control.dataTabMB.current_showPage > n_page)
    control.dataTabMB.current_showPage = 1;
  if (control.dataTabMB.pickdata_index == -1)
    control.dataTabMB.data = nullptr;
  return control.dataTabMB.data;
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

void CreatePage_QLCB(UIcontroller &control)
{
  CreatePageBackground(5);
  DrawTextEx(FontArial, "DANH SÁCH CHUYẾN BAY",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);
  if (control.dataTabCB.data == NULL && !(control.dataTabCB.current_popup == 0 || control.dataTabCB.current_popup == 1 || control.dataTabCB.current_popup == 5))
  {
    CreatePopupBackground();
    DrawTextEx(
        FontArial, "Lỗi",
        {CenterDataSetter(700, StartPos.x + 400,
                          MeasureTextEx(FontArial, "Loi", 50, 0).x),
         CenterDataSetter(60, StartPos.y + 60 + 10,
                          MeasureTextEx(FontArial, "A", 50, 0).y)},
        50, 0, BLACK);
    if (Warning_NoData())
      control.dataTabCB.current_popup = 0;
    return;
  }

  if (control.dataTabCB.current_popup == 0)
  { // tittle

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
    // disable button if no data
    if (control.dataTabCB.data == NULL)
    {
      button[1].isActive = false;
      button[2].isActive = false;
      button[3].isActive = false;
    }
    else
    {
      button[1].isActive = true;
      button[2].isActive = true;
      button[3].isActive = true;
    }

    button[0].tittle = "Thêm chuyến bay";
    if (CreateButton(button[0]))
    {
      control.dataTabCB.current_popup = 1;
    }

    button[1].tittle = "Hiệu chỉnh CB";
    if (CreateButton(button[1]))
    {
      // Pre-run
      strcpy(control.dataTabCB.MaMB.name, control.dataTabCB.data->getNode().getMaMayBay());
      control.dataTabCB.MaMB.letterCount = getCharSize(control.dataTabCB.data->getNode().getMaMayBay());
      strcpy(control.dataTabCB.Ngay.name, intToChar(control.dataTabCB.data->getNode().getNgayGio().getNgay(), 2));
      control.dataTabCB.Ngay.letterCount = 2;
      strcpy(control.dataTabCB.Thang.name, intToChar(control.dataTabCB.data->getNode().getNgayGio().getThang(), 2));
      control.dataTabCB.Thang.letterCount = 2;
      strcpy(control.dataTabCB.Nam.name, intToChar(control.dataTabCB.data->getNode().getNgayGio().getNam(), 4));
      control.dataTabCB.Nam.letterCount = 4;
      strcpy(control.dataTabCB.Gio.name, intToChar(control.dataTabCB.data->getNode().getNgayGio().getGio(), 2));
      control.dataTabCB.Gio.letterCount = 2;
      strcpy(control.dataTabCB.Phut.name, intToChar(control.dataTabCB.data->getNode().getNgayGio().getPhut(), 2));
      control.dataTabCB.Phut.letterCount = 2;

      control.dataTabCB.current_popup = 2;
    }
    button[2].tittle = "Huỷ chuyến bay";
    if (CreateButton(button[2]))
    {

      control.dataTabCB.current_popup = 3;
    }

    button[3].tittle = "Xem danh sách vé";
    if (CreateButton(button[3]))
    {
      control.dataTabCB.current_popup = 4;
    }
    button[4].tittle = "Đặt vé";
    if (CreateButton(button[4]))
    {
      control.dataTabCB.pickdata_index = -1;
      control.dataTabCB.Sw_table_page.reset();
      control.dataTabCB.data == nullptr;
      control.dataTabCB.current_popup = 5;
    }

    control.dataTabCB.data = XuLy_QLCB(control);
    cout << control.dataTabCB.MaMB.tittle << endl;
  }
  else if (control.dataTabCB.current_popup == 1)
  {

    if (Popup_ThemCB(control))
    {
      control.dataTabCB.current_popup = 0;
    }
  }
  else if (control.dataTabCB.current_popup == 2)
  {
    // if(!(control.dataTabCB.data->getNode().getTrangThai()==HoanTat))
    // {
    if (Popup_HieuChinhCB(control))
    {
      control.dataTabCB.current_popup = 0;
    }
  }
  else if (control.dataTabCB.current_popup == 3)
  {
    // if(!(control.dataTabCB.data->getNode().getTrangThai()==HoanTat))
    // {
    cout << control.dataTabCB.data->getNode().getTrangThai() << endl;
    if (Popup_HuyCB(control))
    {
      control.dataTabCB.current_popup = 0;
    }
  }
  else if (control.dataTabCB.current_popup == 4)
  {
    if (Popup_showListHK(control))
    {
      control.dataTabCB.current_popup = 0;
    }
  }
  else if (control.dataTabCB.current_popup == 5)
  {
    if (Popup_chonChuyen(control))
    {
      control.dataTabCB.Sw_table_page.reset();
      control.dataTabCB.pickdata_index = -1;
      control.dataTabCB.data == nullptr;
      control.dataTabCB.current_popup = 0;
    }
  }

  if (control.listCB.update() || control.dataTabCB.gotNewTicket)
  {
    setDataToFile(control.listCB, control.listMB, control.listHK);
    getDataFromFile(control.listCB, control.listMB, control.listHK);
    control.dataTabCB.gotNewTicket = false;
  }
}

void Popup_getMB(UIcontroller &control, Date gioBay)
{
  MayBay *result;

  CreatePageBackground(2);
  TextBox tittle;
  tittle.box = {StartPos.x + 60, StartPos.y + 60, 400, 50};
  tittle.mode = 2;
  tittle.text = (char *)"Hãy chọn máy bay!";

  CreateTextBox(tittle);
  result = XuLy_QLMB(control);

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

  if (control.dataTabCB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, control.dataTabCB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, control.dataTabCB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    control.dataTabCB.time_showError++;
  }
  else
  {
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.time_showError = 0;
  }

  // mini function
  OK.tittle = (char *)"Thêm máy bay";
  Cancel.tittle = (char *)"Huỷ bỏ";
  bool check_mb = false;
  const char *maCB_t;
  if (control.dataTabCB.data == NULL)
    maCB_t = "";
  else
    maCB_t = control.dataTabCB.data->getNode().getMaCB();

  if (control.dataTabMB.data != NULL)
  {
    if (!control.listMB.planeMatch(control.dataTabCB.data->getNode().getMaMayBay(), control.dataTabMB.data->getSoHieuMB()))
    {
      check_mb = true;
      control.dataTabCB.popup_errorMess = "Máy bay phải có số dãy và số dòng bằng máy bay ban đầu!";
      control.dataTabCB.time_showError = 98;
    }
    else if (!control.listCB.isAval(control.dataTabMB.data->getSoHieuMB(), gioBay, maCB_t))
    {
      check_mb = true;
      control.dataTabCB.popup_errorMess = "Máy bay đang bận!";
      control.dataTabCB.time_showError = 98;
    }
  }

  if (CreateButton(OK))
  {
    if (control.dataTabMB.data == NULL)
    {
      control.dataTabCB.popup_errorMess = "Chưa chọn máy bay nào!";
      return;
    }
    else if (check_mb)
      return;
    control.dataTabCB.inChooseMB = false;
    strcpy(control.dataTabCB.MaMB.name, control.dataTabMB.data->getSoHieuMB());
    control.dataTabCB.MaMB.letterCount = getCharSize(control.dataTabMB.data->getSoHieuMB());
    if (control.dataTabCB.MaMB.editMode)
    {
      control.dataTabCB.MaMB.tittle = control.dataTabMB.data->getSoHieuMB();
      // cout << control.dataTabCB.MaMB.tittle << "     " << control.dataTabMB.data->getSoHieuMB() << endl;
    }
    resetData_QLMB(control.dataTabMB);
  }
  if (CreateButton(Cancel))
  {
    control.dataTabCB.inChooseMB = false;
    resetData_QLMB(control.dataTabMB);
  }
}

bool Popup_ThemCB(UIcontroller &control)
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
  const char *newNgay = CreateTextInputBox(control.dataTabCB.Ngay);
  const char *newThang = CreateTextInputBox(control.dataTabCB.Thang);
  const char *newNam = CreateTextInputBox(control.dataTabCB.Nam);

  check = Date(stoi(newNgay[0] == 0 ? "1" : newNgay),
               stoi(newThang[0] == 0 ? "1" : newThang),
               stoi(newNam[0] == 0 ? "2000" : newNam), 00, 00);
  if (strcmp(newThang, "00") == 0 || !check.checkNgay())
  {
    int tmp = stoi(newNam[0] == 0 ? "2000" : newNam);
    if (Date(29, 2, tmp, 0, 0).checkNgay())
    {
      control.dataTabCB.popup_errorMess = "Tháng không hợp lệ!";
      resetInputTextBox(control.dataTabCB.Thang);
      newThang = "";
    }
    else
    {
      control.dataTabCB.popup_errorMess = "Năm không hợp lệ!";
      resetInputTextBox(control.dataTabCB.Nam);
      newNam = "";
    }
  }
  const char *newGio = CreateTextInputBox(control.dataTabCB.Gio);
  const char *newPhut = CreateTextInputBox(control.dataTabCB.Phut);

  Date newNgayBay = Date(stoi(newNgay[0] == 0 ? "0" : newNgay),
                         stoi(newThang[0] == 0 ? "0" : newThang),
                         stoi(newNam[0] == 0 ? "0" : newNam),
                         stoi(newGio[0] == 0 ? "25" : newGio),
                         stoi(newPhut[0] == 0 ? "25" : newPhut));

  DrawTextEx(FontArial, "Mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaCB = CreateTextInputBox(control.dataTabCB.MaCB);

  DrawTextEx(FontArial, "Số hiệu máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaMB = CreateTextInputBox(control.dataTabCB.MaMB);
  if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32) &&
      control.dataTabCB.MaMB.mouseClickOnText)
  {
    control.dataTabCB.MaMB.mouseClickOnText = false;
    control.dataTabCB.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
  }
  else
  {
    if (control.dataTabCB.inChooseMB)
    {
      Popup_getMB(control, newNgayBay);
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
      control.dataTabCB.inChooseMB = true;
      return false;
    }

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái, kí tự và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  const char *newNoiDen = CreateTextInputBox(control.dataTabCB.NoiDen);

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
  if (control.dataTabCB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, control.dataTabCB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, control.dataTabCB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    control.dataTabCB.time_showError++;
  }
  else
  {
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    if (!newNgayBay.checkNgay())
      control.dataTabCB.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
    else if (!(newNgayBay.checkNgayNhapVoiNgayHT()))
    {
      cout << "ngay" << newNgayBay.checkNgayNhapVoiNgayHT() << endl;
      control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";
    }
    // else if (newNgayBay.checkNgayNhapVoiNgayHT() && !(newNgayBay.checkGioNhapVoiGioHT()))
    // {
    //   control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";
    //   cout<<"gio"<<newNgayBay.checkGioNhapVoiGioHT()<<endl;
    // }
    else if (control.listMB.findPosMB(newMaMB) < 0)
    {
      control.dataTabCB.popup_errorMess = "Mã máy bay không tồn tại!";
      cout << "vitri" << control.listMB.findPosMB(newMaMB) << endl;
    }
    else if (!control.listCB.isAval(newMaMB, newNgayBay, newMaCB))
      control.dataTabCB.popup_errorMess = "Máy bay đang được chuyển bay khác sử dụng!";
    else if (!control.listCB.isExist(newMaCB) || (control.dataTabCB.data != NULL && strcmp(newMaCB, control.dataTabCB.data->getNode().getMaCB()) == 0))
    {
      if (newMaCB[0] >= 32 && newMaMB[0] >= 32 && newNoiDen[0] >= 32 &&
          newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
          newGio[0] >= 32 && newPhut[0] >= 32)
      {
        ChuyenBay result = ChuyenBay(newMaCB, newNoiDen, newNgayBay, newMaMB);
        DsVeMayBay newDSVe;
        newDSVe.setDSVe(control.listMB.findMB(newMaMB));
        result.setDSVe(newDSVe);
        control.listCB.insertOrder(new NodeCB(result));
        control.listCB.writetToFile();
        control.listCB.setSize();

        control.dataTabCB.status = 1;
        resetInputTextBox(control.dataTabCB.MaCB);
        resetInputTextBox(control.dataTabCB.MaMB);
        resetInputTextBox(control.dataTabCB.NoiDen);
        resetInputTextBox(control.dataTabCB.Ngay);
        resetInputTextBox(control.dataTabCB.Thang);
        resetInputTextBox(control.dataTabCB.Nam);
        resetInputTextBox(control.dataTabCB.Gio);
        resetInputTextBox(control.dataTabCB.Phut);
        control.dataTabCB.popup_errorMess = "";
        cout << "dax xong0" << endl;
        return true;
      }
      else
      {
        control.dataTabCB.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      }
    }
    else
    {
      control.dataTabCB.popup_errorMess = "Mã chuyến bay đã được sử dụng!";
    }
    return false;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabCB.MaCB);
    resetInputTextBox(control.dataTabCB.MaMB);
    resetInputTextBox(control.dataTabCB.NoiDen);
    resetInputTextBox(control.dataTabCB.Ngay);
    control.dataTabCB.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_HieuChinhCB(UIcontroller &control)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Hiệu chỉnh chuyến bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Hiệu chỉnh chuyến bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  TextBox Box_maCB;
  Box_maCB.box = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  Box_maCB.showBox = true;
  Box_maCB.text = control.dataTabCB.data->getNode().getMaCB();
  CreateTextBox(Box_maCB);
  TextBox Box_noiDen;
  Box_noiDen.box = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
  Box_noiDen.showBox = true;
  Box_noiDen.text = control.dataTabCB.data->getNode().getNoiDen().data();
  CreateTextBox(Box_noiDen);

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;

  DrawTextEx(FontArial, "Thời gian bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, sai tự xoá dữ liệu của ô)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 130 + 10 + hFont40_25},
             25, 0, RED);

  Date check = Date(1, 1, 2000, 00, 00);
  const char *newNgay = CreateTextInputBox(control.dataTabCB.Ngay);
  const char *newThang = CreateTextInputBox(control.dataTabCB.Thang);
  const char *newNam = CreateTextInputBox(control.dataTabCB.Nam);

  check = Date(stoi(newNgay[0] == 0 ? "1" : newNgay),
               stoi(newThang[0] == 0 ? "1" : newThang),
               stoi(newNam[0] == 0 ? "2000" : newNam), 00, 00);
  if (strcmp(newThang, "00") == 0 || !check.checkNgay())
  {
    int tmp = stoi(newNam[0] == 0 ? "2000" : newNam);
    if (Date(29, 2, tmp, 0, 0).checkNgay())
    {
      control.dataTabCB.popup_errorMess = "Tháng không hợp lệ!";
      resetInputTextBox(control.dataTabCB.Thang);
      newThang = "";
    }
    else
    {
      control.dataTabCB.popup_errorMess = "Năm không hợp lệ!";
      resetInputTextBox(control.dataTabCB.Nam);
      newNam = "";
    }
  }
  const char *newGio = CreateTextInputBox(control.dataTabCB.Gio);
  const char *newPhut = CreateTextInputBox(control.dataTabCB.Phut);

  Date newNgayBay = Date(stoi(newNgay[0] == 0 ? "0" : newNgay),
                         stoi(newThang[0] == 0 ? "0" : newThang),
                         stoi(newNam[0] == 0 ? "0" : newNam),
                         stoi(newGio[0] == 0 ? "25" : newGio),
                         stoi(newPhut[0] == 0 ? "25" : newPhut));

  DrawTextEx(FontArial, "Mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Không được hiệu chỉnh!)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  // const char *newMaCB = CreateTextInputBox(control.dataTabCB.MaCB);

  DrawTextEx(FontArial, "Số hiệu máy bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái IN HOA và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newMaMB = CreateTextInputBox(control.dataTabCB.MaMB);
  if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32) &&
      control.dataTabCB.MaMB.mouseClickOnText)
  {
    control.dataTabCB.MaMB.mouseClickOnText = false;
    control.dataTabCB.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
  }
  else
  {
    if (control.dataTabCB.inChooseMB)
    {
      Popup_getMB(control, newNgayBay);
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
      control.dataTabCB.inChooseMB = true;
      return false;
    }

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Không được hiệu chỉnh!)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);
  // const char *newNoiDen = CreateTextInputBox(control.dataTabCB.NoiDen);

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
  if (control.dataTabCB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, control.dataTabCB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, control.dataTabCB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    control.dataTabCB.time_showError++;
  }
  else
  {
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    // else //if (!control.listCB.isExist(newMaCB) || (control.dataTabCB.data != NULL && strcmp(newMaCB, control.dataTabCB.data->getNode().getMaCB()) == 0))
    // {
    if (newMaMB[0] >= 32 && newNgay[0] >= 32 &&
        newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32)
    {
      if (!newNgayBay.checkNgay())
      {
        control.dataTabCB.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
        return false;
      }
      else if (!(newNgayBay.checkNgayNhapVoiNgayHT()))
      {
        cout << "ngay" << newNgayBay.checkNgayNhapVoiNgayHT() << endl;
        control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";
        return false;
      }
      // else if (newNgayBay.checkNgayNhapVoiNgayHT() && !(newNgayBay.checkGioNhapVoiGioHT()))
      // {
      //   control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";

      // }
      else if (control.listMB.findPosMB(newMaMB) < 0)
      {
        control.dataTabCB.popup_errorMess = "Mã máy bay không tồn tại!";
        return false;
      }
      else if (!control.listCB.isAval(newMaMB, newNgayBay, control.dataTabCB.data->getNode().getMaCB()))
      {
        control.dataTabCB.popup_errorMess = "Máy bay đang được chuyển bay khác sử dụng!";
        return false;
      }
      ChuyenBay result = control.dataTabCB.data->getNode();
      result.setNgayGio(newNgayBay);
      result.setidMayBay(newMaMB);
      control.dataTabCB.data->setCb(result);
      control.listCB.writetToFile();
      control.listCB.setSize();

      control.dataTabCB.status = 1;
      // resetInputTextBox(control.dataTabCB.MaCB);
      // resetInputTextBox(control.dataTabCB.NoiDen);
      resetInputTextBox(control.dataTabCB.MaMB);
      resetInputTextBox(control.dataTabCB.Ngay);
      resetInputTextBox(control.dataTabCB.Thang);
      resetInputTextBox(control.dataTabCB.Nam);
      resetInputTextBox(control.dataTabCB.Gio);
      resetInputTextBox(control.dataTabCB.Phut);
      control.dataTabCB.popup_errorMess = "";

      return true;
    }
    else
    {
      control.dataTabCB.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      return false;
    }
  }
  // else
  // {
  //   control.dataTabCB.popup_errorMess = "Mã chuyến bay đã được sử dụng!";
  // }

  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabCB.MaCB);
    resetInputTextBox(control.dataTabCB.MaMB);
    resetInputTextBox(control.dataTabCB.NoiDen);
    resetInputTextBox(control.dataTabCB.Ngay);
    control.dataTabCB.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_HuyCB(UIcontroller &control)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Huỷ chuyến bay",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Huỷ chuyến bay", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  TextBox Box_maCB;
  Box_maCB.box = control.dataTabCB.MaCB.textBox;
  Box_maCB.showBox = true;
  Box_maCB.text = control.dataTabCB.data->getNode().getMaCB();
  CreateTextBox(Box_maCB);

  TextBox Box_maMB;
  Box_maMB.box = control.dataTabCB.MaMB.textBox;
  Box_maMB.showBox = true;
  Box_maMB.text = control.dataTabCB.data->getNode().getMaMayBay();
  CreateTextBox(Box_maMB);

  TextBox Box_noiDen;
  Box_noiDen.box = control.dataTabCB.NoiDen.textBox;
  Box_noiDen.showBox = true;
  Box_noiDen.text = strToChar(control.dataTabCB.data->getNode().getNoiDen());
  CreateTextBox(Box_noiDen);

  TextBox Box_ngayBay;
  Box_ngayBay.box = control.dataTabCB.Ngay.textBox;
  Box_ngayBay.box.width += 300;
  Box_ngayBay.showBox = true;
  Box_ngayBay.text = strToChar(control.dataTabCB.data->getNode().getNgayGio().printDateHour());
  CreateTextBox(Box_ngayBay);

  DrawTextEx(FontArial, "Thời gian bay",
             {StartPos.x + 300, StartPos.y + 60 + 130 + 10}, 40, 0, BROWN);

  DrawTextEx(FontArial, "Mã chuyến bay",
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
  if (control.dataTabCB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, control.dataTabCB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, control.dataTabCB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    control.dataTabCB.time_showError++;
  } //
  else
  {
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    control.dataTabCB.data->getNode().setTrangThai(HuyChuyen);
    cout << control.dataTabCB.data->getNode().getTrangThai() << endl;
    control.listCB.writetToFile();
    // control.listCB.setSize();
    ChuyenBay result = control.dataTabCB.data->getNode();
    result.setTrangThai(HuyChuyen);
    control.dataTabCB.data->setCb(result);
    control.listCB.writetToFile();
    control.listCB.setSize();
    control.dataTabCB.status = 1;
    resetInputTextBox(control.dataTabCB.MaCB);
    resetInputTextBox(control.dataTabCB.MaMB);
    resetInputTextBox(control.dataTabCB.NoiDen);
    resetInputTextBox(control.dataTabCB.Ngay);
    resetInputTextBox(control.dataTabCB.Thang);
    resetInputTextBox(control.dataTabCB.Nam);
    resetInputTextBox(control.dataTabCB.Gio);
    resetInputTextBox(control.dataTabCB.Phut);
    control.dataTabCB.popup_errorMess = "";

    return true;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabCB.MaCB);
    resetInputTextBox(control.dataTabCB.MaMB);
    resetInputTextBox(control.dataTabCB.NoiDen);
    resetInputTextBox(control.dataTabCB.Ngay);
    control.dataTabCB.popup_errorMess = "";
    return true;
  }
  return false;
}

bool Popup_showListHK(UIcontroller &control)
{
  if (control.dataTabCB.dataDSVe.inDelete)
  {
    CreatePopupBackground();
    int tmp_c = Warning_Confirm();
    if (tmp_c == 0)
      return false;
    else if (tmp_c == 1)
    {
      control.dataTabCB.dataDSVe.inDelete = false;
      control.dataTabCB.data->getNode().getDSVe().deleteVe(control.dataTabCB.dataDSVe.position);
    }
  }

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
      if (control.dataTabCB.dataDSVe.pickdata_index != i)
      {

        control.dataTabCB.dataDSVe.pickdata_index = i;
      }
      else
        control.dataTabCB.dataDSVe.pickdata_index = -1;
    }
    if (control.dataTabCB.dataDSVe.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }

  // mini function
  button[0].tittle = "Quay lại";

  button[1].tittle = "Huỷ vé";

  ChuyenBay currCB = control.dataTabCB.data->getNode();
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
      showText[3] = strToChar(control.listHK.search(tmp.getHanhKhach())->getHK().getHo() + " " + control.listHK.search(tmp.getHanhKhach())->getHK().getTen());
      showText[4] = strToChar(control.listHK.search(tmp.getHanhKhach())->getHK().getPhai());

      TextBox show[5];
      for (int j = 0; j < 5; j++)
      {
        if (control.dataTabCB.dataDSVe.pickdata_index == j)
          control.dataTabCB.dataDSVe.position = i;
        show[j] = GetCellTextBox(start_pos, 5, cellW, j + 1, (iVe % 10) + 1, showText[j], 30);
      }
      for (int j = 4; j >= 0; j--)
      {
        CreateTextBox(show[j]);
      }
      iVe++;
    }
  }

  int swp =
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabCB.dataDSVe.current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabCB.dataDSVe.current_page != swp)
  {
    control.dataTabCB.dataDSVe.position = -1;
    control.dataTabCB.dataDSVe.current_page = swp;
  }

  if (control.dataTabCB.dataDSVe.current_page > n_page)
    control.dataTabCB.dataDSVe.current_page = 1;
  if (CreateButton(button[0]))
  {
    control.dataTabCB.dataDSVe.current_page = 1;
    control.dataTabCB.current_popup = 0;
    return true;
  }
  // if (control.dataTabMB.data != NULL)
  // {
  if (CreateButton(button[1]))
  {
    control.dataTabCB.dataDSVe.inDelete = true;
  }

  return false;
}

bool Popup_chonChuyen(UIcontroller &control)
{
  CreatePageBackground(2);
  if (control.dataTabCB.inGetTicket)
  {
    if (Popup_chonVe(control))
    {
      control.dataTabCB.inShowFightAvail = false;
      return true;
    }
    return false;
  }

  control.dataTabCB.inShowFightAvail = true;

  DrawTextEx(FontArial, "HÃY CHỌN CHUYẾN BAY",
             {StartPos.x + 60,
              CenterDataSetter(70, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);

  control.dataTabCB.data = XuLy_QLCB(control);

  Button OK;

  if (control.dataTabCB.data == NULL)
  {
    OK.isActive = false;
  }
  else
  {
    OK.isActive = true;
  }
  OK.x = StartPos.x + 1201 + 29;
  OK.y = StartPos.y + 60 + 20 + 70 + 15;
  OK.w = 240;
  OK.h = 60;
  OK.BoTron = false;
  OK.gotNothing = false;
  OK.gotText = true;
  OK.tittle = "Chọn chuyến này!";
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
  Cancel.tittle = "Quay lại";
  Cancel.font = FontArial;
  Cancel.BoMau = ArrowKey;
  if (CreateButton(OK))
  {
    control.dataTabCB.inGetTicket = true;
  }
  if (CreateButton(Cancel))
  {
    control.dataTabCB.inShowFightAvail = false;
    return true;
  }
  return false;
}

bool Popup_chonVe(UIcontroller &control)
{
  CreatePageBackground(1);
  DrawTextEx(FontArial, "Hãy chọn một vé máy bay:",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);

  if (control.dataTabCB.inSetTicket)
  {
    if (Popup_datVe(control))
    {
      control.dataTabCB.inSetTicket = false;
      if (control.dataTabCB.gotNewTicket)
      {
        control.dataTabCB.inGetTicket = false;
        control.dataTabCB.inSetTicket = false;
        return true;
      }
    }
    return false;
  }

  ChuyenBay currCB = control.dataTabCB.data->getNode();
  int n_page = 1;
  // int size = dsve.getSoVeToiDa();
  int sDay = control.listMB.findMB(currCB.getMaMayBay())->getSoDay(),
      sDong = control.listMB.findMB(currCB.getMaMayBay())->getSoDong();
  int IndexSoDongMax = sDong;
  if (sDong > 10)
    IndexSoDongMax = (control.dataTabCB.dataDSVe.current_page) * 10;
  if (IndexSoDongMax > sDong)
    IndexSoDongMax = sDong;
  // if (current_page * 10 < size)
  //     j = current_page * 100;
  // else
  //     j = size;
  Rectangle r;
  r = {0,
       StartPos.y + 60 + 70 + 80,
       70, 30};
  if (sDong > 10)
    r.x = CenterDataSetter(1200, StartPos.x, 10 * 100);
  else
    r.x = CenterDataSetter(1200, StartPos.x, (sDong)*100);

  DrawTextPro(FontArial,
              "Dãy",
              {r.x - MeasureTextEx(FontArial, "Day", 40, 0).y,
               CenterDataSetter(sDay * 40, StartPos.y + 60 + 70 + 80, MeasureTextEx(FontArial, "Day", 40, 0).x) +
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
    for (int m = (control.dataTabCB.dataDSVe.current_page - 1) * 10; m < IndexSoDongMax; m++)
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
      if (currCB.getDSVe().getVe(a * sDong + m).getHanhKhach() != "")
        button.isActive = false;
      else
        button.isActive = true;
      if (CreateButton(button))
      {
        control.dataTabCB.dataDSVe.position = a * (sDong) + m;
        control.dataTabCB.inSetTicket = true;
      };
    }
  }

  n_page = 1 + ((sDong - 1) / 10);

  int swp =
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabCB.dataDSVe.current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabCB.dataDSVe.current_page != swp)
  {
    control.dataTabCB.dataDSVe.position = -1;
    control.dataTabCB.dataDSVe.current_page = swp;
  }

  if (control.dataTabCB.dataDSVe.current_page > n_page)
    control.dataTabCB.dataDSVe.current_page = 1;

  Button Cancel;
  Cancel.x = StartPos.x + 1201 + 29;
  Cancel.y = StartPos.y + 60 + 20 + 70 + 15;
  Cancel.w = 240;
  Cancel.h = 60;
  Cancel.gotNothing = false;
  Cancel.gotText = true;
  Cancel.tittle = (char *)"Huỷ";
  Cancel.font = FontArial;
  Cancel.BoMau = ArrowKey;

  if (CreateButton(Cancel))
  {
    control.dataTabCB.inGetTicket = false;
    return true;
  }

  return false;
}

bool Popup_datVe(UIcontroller &control)
{
  bool HKexist = false;

  CreatePopupBackground();
  string tittle = "Đặt vé " + control.dataTabCB.data->getNode().getDSVe().getVe(control.dataTabCB.dataDSVe.position).getIDVe();
  DrawTextEx(
      FontArial, strToChar(tittle),
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, strToChar(tittle), 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);

  string o_CMND, o_Ho, o_Ten;

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;
  DrawTextEx(FontArial, "CMND / CCCD",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nếu đã có sẽ tự điền thêm thông tin)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);

  DrawTextEx(FontArial, "Họ và tên",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);

  DrawTextEx(FontArial, "Phái",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);

  o_CMND = CreateTextInputBox(control.dataTabHK.i_CMND);
  o_Ho = CreateTextInputBox(control.dataTabHK.i_Ho);
  o_Ten = CreateTextInputBox(control.dataTabHK.i_Ten);

  TextBox tb_Phai;
  tb_Phai.box = {StartPos.x + 300, StartPos.y + 60 + 480, 150, 50};
  tb_Phai.showBox = true;
  tb_Phai.isCenter = true;
  tb_Phai.mode = 2;
  tb_Phai.text = (char *)"Chưa chọn";

  if (o_CMND == "")
  {
    control.dataTabHK.i_Ho.isActive = false;
    control.dataTabHK.i_Ten.isActive = false;
    control.dataTabHK.i_Phai = -1;

    DrawTextEx(FontArial, "(Nhập CMND/CCCD trước!)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
               25, 0, RED);
    DrawTextEx(FontArial, "(Nhập CMND/CCCD trước!)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
               25, 0, RED);
  }
  else
  {
    if (control.listHK.search(o_CMND) != NULL)
    {
      HKexist = true;
      DrawTextEx(FontArial, "(Đẫ tự động điền, không thể chỉnh sửa!)",
                 {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
                 25, 0, RED);
      DrawTextEx(FontArial, "(Đẫ tự động điền, không thể chỉnh sửa!)",
                 {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
                 25, 0, RED);

      HanhKhach t_hk = control.listHK.search(o_CMND)->getHK();

      control.dataTabHK.i_Ho.isActive = false;
      control.dataTabHK.i_Ten.isActive = false;
      control.dataTabHK.i_Phai = -1;

      TextBox tb_Ho;
      tb_Ho.box = control.dataTabHK.i_Ho.textBox;
      tb_Ho.showBox = true;
      tb_Ho.text = strToChar(t_hk.getHo());

      TextBox tb_Ten;
      tb_Ten.box = control.dataTabHK.i_Ten.textBox;
      tb_Ten.showBox = true;
      tb_Ten.text = strToChar(t_hk.getTen());

      CreateTextBox(tb_Ho);
      CreateTextBox(tb_Ten);

      if (t_hk.getPhai() == "Nam")
        tb_Phai.text = (char *)"Nam";
      else if (t_hk.getPhai() == "Nu")
        tb_Phai.text = (char *)"Nữ";
    }
    else
    {
      control.dataTabHK.i_Ho.isActive = true;
      control.dataTabHK.i_Ten.isActive = true;
      DrawTextEx(FontArial, "(Gồm chữ cái và kí tự)",
                 {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
                 25, 0, RED);
      DrawTextEx(FontArial, "(Nhấn vào để chọn)",
                 {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
                 25, 0, RED);
    }
  }

  if (!HKexist && o_CMND != "")
  {
    if (control.dataTabHK.i_Phai == 0)
      tb_Phai.text = (char *)"Nam";
    else if (control.dataTabHK.i_Phai == 1)
      tb_Phai.text = (char *)"Nữ";

    Button s_Nam;
    s_Nam.x = tb_Phai.box.x + tb_Phai.box.width + 20;
    s_Nam.y = tb_Phai.box.y;
    s_Nam.w = 100;
    s_Nam.h = 50;
    s_Nam.gotNothing = false;
    s_Nam.gotText = true;
    s_Nam.tittle = (char *)"Nam";
    s_Nam.font = FontArial;
    s_Nam.BoMau = ArrowKey;

    Button s_Nu;
    s_Nu.x = s_Nam.x + s_Nam.w + 10;
    s_Nu.y = s_Nam.y;
    s_Nu.w = 100;
    s_Nu.h = 50;
    s_Nu.gotNothing = false;
    s_Nu.gotText = true;
    s_Nu.tittle = (char *)"Nữ";
    s_Nu.font = FontArial;
    s_Nu.BoMau = ArrowKey;

    if (control.dataTabHK.i_Phai == 0)
    {
      s_Nam.isActive = false;
      s_Nu.isActive = true;
    }
    else if (control.dataTabHK.i_Phai == 1)
    {
      s_Nu.isActive = false;
      s_Nam.isActive = true;
    }

    if (CreateButton(s_Nam))
    {
      control.dataTabHK.i_Phai = 0;
    }
    if (CreateButton(s_Nu))
    {
      control.dataTabHK.i_Phai = 1;
    }
  }
  CreateTextBox(tb_Phai);

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
  if (control.dataTabCB.time_showError <= 100)
  {
    DrawTextEx(
        FontArial, control.dataTabCB.popup_errorMess.data(),
        {CenterDataSetter(1100, StartPos.x + 200,
                          MeasureTextEx(FontArial, control.dataTabCB.popup_errorMess.data(), 40, 0).x),
         CenterDataSetter(50, StartPos.y + 130,
                          MeasureTextEx(FontArial, "A", 40, 0).y)},
        40, 0, RED);
    control.dataTabCB.time_showError++;
  }
  else
  {
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.time_showError = 0;
  }
  if (CreateButton(OK))
  {
    if (!HKexist)
    {
      trim(o_Ho);
      trim(o_Ten);
      HanhKhach hk = HanhKhach(o_CMND, o_Ho, o_Ten, control.dataTabHK.i_Phai);
      control.listHK.insert(hk);
    }

    if(!control.listCB.duocDatKhong(o_CMND,control.dataTabCB.data->getNode()))
    {
      control.dataTabCB.popup_errorMess = "Bạn không được đặt vé trên chuyến bay này!";
      resetData_QLHK(control.dataTabHK);
      return false;
    }
    ChuyenBay m_cb = control.dataTabCB.data->getNode();
    DsVeMayBay m_dsVe = m_cb.getDSVe();
    VeMayBay m_ve = m_dsVe.getVe(control.dataTabCB.dataDSVe.position);
    m_ve.setHanhKhach(o_CMND);
    m_dsVe.setVe(m_ve, control.dataTabCB.dataDSVe.position);
    m_dsVe.setSoVeDaDat(m_dsVe.getSoVeDaDat() + 1);
    m_cb.setDSVe(m_dsVe);
    control.dataTabCB.data->setCb(m_cb);

    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    control.dataTabCB.popup_errorMess = "";

    resetData_QLHK(control.dataTabHK);

    control.dataTabCB.gotNewTicket = true;
    return true;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    control.dataTabCB.popup_errorMess = "";

    resetData_QLHK(control.dataTabHK);

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

void ShowListCB(UIcontroller &control, int first, const char *textMaCB, const char *textNoiDen, bool showAvail, Date ngayBay)
{
  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  Vector2 start_pos = {StartPos.x + 35, StartPos.y + 60 + 70 + 110};

  int size = control.listCB.getSize();

  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;

  NodeCB *tmp = control.listCB.getHead();
  int i = (control.dataTabCB.current_showPage - 1) * 10;
  int j = 0;
  for (int k = 0; k < size; k++)
  {
    bool DKTimKiem = tmp->getNode().checkMaCB(textMaCB) &&
                     tmp->getNode().checkNoiDen(textNoiDen);

    if (!(ngayBay == Date(1, 1, 0, 0, 0)))
      DKTimKiem = DKTimKiem &&
                  tmp->getNode().checkTime(ngayBay);
    if (showAvail)
      DKTimKiem = DKTimKiem &&
                  tmp->getNode().getTrangThai() == ConVe;

    if (DKTimKiem)
    {
      if (j >= i && j <= i + 9)
      {
        if (j % 10 == control.dataTabCB.pickdata_index)
          control.dataTabCB.data = tmp;

        string dsVe = "";
        dsVe = intToString(tmp->getNode().getDSVe().getSoVeConLai(), 3) + '/' +
               intToString(tmp->getNode().getDSVe().getSoVeToiDa(), 3);
        TextBox show[6];
        const char *showText[6];
        showText[0] = intToChar(j + 1, n_char);
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
}

NodeCB *XuLy_QLCB(UIcontroller &control)
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

  // Cài đặt các ô nhập
  control.dataTabCB.searchNoiDen.textBox = boxNoiDen;
  control.dataTabCB.searchMaCB.textBox = boxMaCB;

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
  const char *textMaCB = CreateTextInputBox(control.dataTabCB.searchMaCB);
  DrawTextEx(FontArial, "Nơi đến:",
             {search.x + 20,
              CenterDataSetter(50, search.y + 55,
                               MeasureTextEx(FontArial, "a", 35, 0).y)},
             35, 0, RED);
  const char *textNoiDen = CreateTextInputBox(control.dataTabCB.searchNoiDen);
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
  //     current_page = 1 + (control.listCB.getSize() - 1) / 10;
  //     index = (control.listCB.getSize() - 1) % 10;
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
      if (control.dataTabCB.pickdata_index != i)
      {

        control.dataTabCB.pickdata_index = i;
      }
      else
        control.dataTabCB.pickdata_index = -1;
    }
    if (control.dataTabCB.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  control.dataTabCB.data = NULL;

  int i = (control.dataTabCB.current_showPage - 1) * 10;
  ShowListCB(control, i, textMaCB, textNoiDen, control.dataTabCB.inShowFightAvail, control.dataTabCB.fbDay);
  StatusHelp_QLCB();

  n_page = 1 + ((control.listCB.getSize() - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabCB.current_showPage, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabCB.current_showPage != swp)
  {
    control.dataTabCB.pickdata_index = -1;
    control.dataTabCB.data = NULL;
  }
  control.dataTabCB.current_showPage = swp;
  if (control.dataTabCB.current_showPage > n_page)
    control.dataTabCB.current_showPage = 1;

  return control.dataTabCB.data;
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

void CreatePage_QLHK(UIcontroller &control)
{
  CreatePageBackground(2);
  if (control.dataTabHK.data == NULL && control.dataTabHK.current_popup != 0)
  {
    CreatePopupBackground();
    DrawTextEx(
        FontArial, "Lỗi",
        {CenterDataSetter(700, StartPos.x + 400,
                          MeasureTextEx(FontArial, "Loi", 50, 0).x),
         CenterDataSetter(60, StartPos.y + 60 + 10,
                          MeasureTextEx(FontArial, "A", 50, 0).y)},
        50, 0, BLACK);
    if (Warning_NoData())
      control.dataTabHK.current_popup = 0;
    return;
  }

  DrawTextEx(FontArial, "DANH SÁCH HÀNH KHÁCH",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 60, 0).y)},
             60, 0, BLUE);

  if (control.dataTabHK.current_popup == 0)
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
    // disable button if no data
    if (control.dataTabHK.data == NULL)
    {
      button[0].isActive = false;
    }
    else
    {
      button[0].isActive = true;
    }

    button[0].tittle = "Quản lý vé";
    if (CreateButton(button[0]))
    {
      control.dataTabHK.current_popup = 1;
    }
    button[1].tittle = "Huỷ vé";
    if (CreateButton(button[1]))
    {
      control.dataTabHK.current_popup = 2;
    }
  }
  else if (control.dataTabHK.current_popup == 1)
  {
    if (Popup_QLVe(control))
      control.dataTabHK.current_popup = 0;
  }
  else if (control.dataTabHK.current_popup == 2)
  {
    if (Popup_HieuChinhHK(control))
      control.dataTabHK.current_popup = 0;
  }
  control.dataTabHK.data = XuLy_QLHK(control);
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

bool Popup_QLVe(UIcontroller &control)
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
  return true;
}

bool Popup_HieuChinhHK(UIcontroller &control)
{
  CreatePopupBackground();
  HanhKhach tmp = control.dataTabHK.data->getHK();

  string o_Ho, o_Ten;
  TextBox s_CMND;
  s_CMND.box = control.dataTabHK.i_Ten.textBox;
  s_CMND.showBox = true;
  s_CMND.text = strToChar(tmp.getCmnd());
  CreateTextBox(s_CMND);

  o_Ho = CreateTextInputBox(control.dataTabHK.i_Ho);
  o_Ten = CreateTextInputBox(control.dataTabHK.i_Ten);

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
    tmp.setHo(o_Ho);
    tmp.setTen(o_Ten);

    control.dataTabHK.data->setHK(tmp);

    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    return true;
  }

  if (CreateButton(Cancel))
  {

    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    return true;
  }
  return false;
}

void ShowListHK(HanhKhach hanhKhach, int n_char, Vector2 start_pos, float *cellW, int &j, int order)
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

NodeHK *XuLy_QLHK(UIcontroller &control)
{
  const Vector2 search = {StartPos.x + 60, StartPos.y + 60 + 70};

  // table
  float cellW[5] = {100, 300, 380, 200, 100};
  CreateTable_QLHK();

  // data
  int n_page = 1;
  if (control.dataTabHK.status == 1)
  {
    // current_page = 1 + (listHK.getSize() - 1) / 10;
    // index = (listHK.getSize() - 1) % 10;
    control.dataTabHK.status = 0;
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
      if (control.dataTabHK.pickdata_index != i)
      {

        control.dataTabHK.pickdata_index = i;
      }
      else
        control.dataTabHK.pickdata_index = -1;
    }
    if (control.dataTabHK.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }
  control.dataTabHK.data = NULL;

  // show list
  Vector2 start_pos = {StartPos.x + 60, StartPos.y + 60 + 70 + 110};
  int size = control.listHK.getSize();

  int n_char;
  if (size <= 99)
    n_char = 2;
  else if (size >= 100 && size <= 999)
    n_char = 3;
  else
    n_char = 4;

  int i = (control.dataTabHK.current_page - 1) * 10;

  int j = 0;

  NodeHK *root = control.listHK.getRoot();
  // Queue queue = Queue(size);
  // listHK.levelOrderTraversal(queue);
  // NodeHK *tmp;
  // int k = 0;

  // while (!queue.isEmpty())
  // {
  //   if (j >= i && j <= i + 9)
  //   {
  //     if (j % 10 == control.dataTabHK.pickdata_index)
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
      if (j % 10 == control.dataTabHK.pickdata_index)
        control.dataTabHK.data = root;

      ShowListHK(currNode->getHK(), n_char, start_pos, cellW, j, order);
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
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabHK.current_page, n_page,
                 {StartPos.x + 60 + 680, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabHK.current_page != swp)
    control.dataTabHK.pickdata_index = -1;
  control.dataTabHK.current_page = swp;
  if (control.dataTabHK.current_page > n_page)
    control.dataTabHK.current_page = 1;
  return control.dataTabHK.data;
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
    return -1;
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

int SwitchPage(PageSwitcher &data, int current_page, int n_page, Vector2 pos)
{
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
    data.editmode = true;

  data.fast_switcher.textBox = pg1;
  data.fast_switcher.editMode = true;
  data.fast_switcher.tittle = intToChar(current_page, 2);
  data.fast_switcher.size = 2;
  data.fast_switcher.MauVien = BROWN;
  data.fast_switcher.mode = 5;
  data.fast_switcher.returnIfDone = true;
  data.fast_switcher.showNKeyRemain = false;
  if (data.editmode)
  {
    const char *page_t = CreateTextInputBox(data.fast_switcher);
    if (page_t[0] == 0)
      page_n = current_page;
    else
      page_n = stoi(page_t);
    if (!(page_n > 0 && page_n <= n_page))
    {
      page_n = current_page;
      resetInputTextBox(data.fast_switcher);
    }
  }

  if (page_n != current_page)
  {
    resetInputTextBox(data.fast_switcher);
    data.editmode = false;
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

  if (!data.isActive)
  {
    DrawRectangleRounded(Button, 0.5f, 0.5f, data.BoMau.isPressed);
    DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
               data.BoMau.text2);

    return false;
  }

  if (CheckCollisionPointRec(GetVMousePosition(), Button))
  {
    V_MOUSE_CURSOR_POINTING_HAND++;
  }

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
  // Xu ly
  char name_cpy[data.size] = "\0";
  char *result = new char[data.size];
  const int font_size = data.textBox.height * per1000(700);

  // Graphic
  Vector2 textBoxPos = {
      data.textBox.x + 5,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, data.name, font_size, 0).y)};

  // show text
  DrawRectangleRec(data.textBox, data.MauNen);
  DrawRectangleRoundedLines(data.textBox, 0, 1, 2, data.MauVien);
  if (data.name[0] != '\0')
    DrawTextEx(FontArial, data.name, textBoxPos, font_size, 0, data.MauChu);
  else
    DrawTextEx(FontArial, data.tittle, textBoxPos, font_size, 0, BROWN);

  // disable
  if (!data.isActive)
  {
    return "\0";
  }

  Vector2 MousePos = {0.0f, 0.0f};
  strcpy(name_cpy, data.name);
  name_cpy[data.letterCount + data.indexPoint] = '\0';

  Vector2 textBoxDot = {
      data.textBox.x + MeasureTextEx(FontArial, name_cpy, font_size, 0).x,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, name_cpy, font_size, 0).y)};

  // edit from pre-work
  if (data.editMode && data.done)
  {
    strcpy(data.name, data.tittle);
    data.letterCount = getCharSize(data.name);
  }

  // Action - active
  if (CheckCollisionPointRec(GetVMousePosition(), data.textBox) &&
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
  else if (!CheckCollisionPointRec(GetVMousePosition(), data.textBox) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    data.mouseClickOnText = false;

  if (CheckCollisionPointRec(GetVMousePosition(), data.textBox))
  {
    V_MOUSE_CURSOR_IBEAM++;
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
  // get result
  strcpy(result, data.name);

  if (data.showNKeyRemain)
  {
    DrawTextEx(FontArial, intToChar(data.size - data.letterCount, 2),
               {data.textBox.x + data.textBox.width - data.textBox.height,
                data.textBox.y + data.textBox.height / 3},
               data.textBox.height * per1000(400), 0, DARKGREEN);
  }

  // show index point
  if (data.mouseClickOnText && ((data.framesCounter % 40 >= 5)))
    DrawTextEx(FontArial, "|", textBoxDot, font_size, 0, MAROON);

  // return
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
  box.isActive = true;
  box.editMode = false;
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
    // Các thao tác trên đồ hoạ
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
      CreatePage_QLMB(main);
      break;
    }
    case 2:
    {
      CreatePage_QLCB(main);
      break;
    }
    case 3:
    {
      CreatePage_QLVe();
      break;
    }
    case 4:
    {
      CreatePage_QLHK(main);
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

    // Windows variable status
    // -Mouse cursor
    if (V_MOUSE_CURSOR_IBEAM > 0)
    {
      SetMouseCursor(MOUSE_CURSOR_IBEAM);
      V_MOUSE_CURSOR_IBEAM = 0;
    }
    else if (V_MOUSE_CURSOR_POINTING_HAND)
    {
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
      V_MOUSE_CURSOR_POINTING_HAND = 0;
    }
    else
    {
      V_MOUSE_CURSOR_IBEAM = 0;
      V_MOUSE_CURSOR_POINTING_HAND = 0;
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
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
