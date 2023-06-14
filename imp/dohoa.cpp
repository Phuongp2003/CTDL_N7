#include "../header/dohoa.h"

// Global status variable
int V_MOUSE_CURSOR_IBEAM = 0;         // Trỏ văn bản
int V_MOUSE_CURSOR_POINTING_HAND = 0; // Trỏ chọn

const Vector2 StartPos{per1000(10) * SCREEN_WIDTH, per1000(40) * SCREEN_HEIGHT}; // Vector khởi đầu

Font FontArial;
Texture2D PNG_logo;

Texture2D PNG_home;

Texture2D PNG_arrowLeft;
Texture2D PNG_arrowRight;

Texture2D PNG_tick;
Texture2D PNG_circleGreen;
Texture2D PNG_circleYellow;
Texture2D PNG_circleGray;
//==================================================================================================================================

void setDataToFile(UIcontroller &control)
{
  setDataToFile(control.listCB, control.listMB, control.listHK);
}

void getDataFromFile(UIcontroller &control)
{
  setDataToFile(control.listCB, control.listMB, control.listHK);
}

// Nhận text làm giá trị ban đầu (truyền trực tiếp vào dữ liệu ô nhập)
void SetDataInputTextBox(InputTextBox &box, const char *text, int length = -1)
{
  if (!box.isGotData)
  {
    strcpy(box.name, text);
    if (length != -1)
    {
      box.letterCount = length;
    }
    else
    {
      box.letterCount = getCharSize(text);
    }
    box.isGotData = true;
  }
}

// Reset data của ô nhập nếu nếu trực tiếp từ nguồn ngoài
void ResetDataInputTextBox(InputTextBox &box)
{
  if (box.isGotData)
  {
    strcpy(box.name, "\0");
    box.letterCount = 0;
    box.isGotData = false;
  }
}

void initQLMBdata(QLMB_data &thisdata)
{
  thisdata.data = NULL;
  thisdata.current_popup = 0;
  thisdata.popup_errorMess = "";
  thisdata.time_showError = 0;

  thisdata.MaMB.mode = UpperAlphanumeric;
  thisdata.MaMB.tittle = (char *)"Nhập số hiệu máy bay";
  thisdata.MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 900, 50};
  thisdata.MaMB.size = 15;
  thisdata.LoaiMB.mode = Alphanumeric;
  thisdata.LoaiMB.tittle = (char *)"Nhập loại máy bay";
  thisdata.LoaiMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  thisdata.LoaiMB.size = 40;
  thisdata.SoDong.mode = Numeric;
  thisdata.SoDong.tittle = (char *)"Nhập số dòng của máy bay";
  thisdata.SoDong.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 500, 50};
  thisdata.SoDong.size = 2;
  thisdata.SoDay.mode = Numeric;
  thisdata.SoDay.tittle = (char *)"Nhập số dãy của máy bay";
  thisdata.SoDay.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
  thisdata.SoDay.size = 2;

  thisdata.pickdata_index = -1;
  thisdata.keyword = "";
  thisdata.searchKeyword.mode = UpperAlphanumeric;
  thisdata.searchKeyword.tittle = "Nhập mã máy bay tìm kiếm";
  thisdata.current_showPage = 1;

  resetPageSwitcher(thisdata.Sw_table_page);
}

void initQLHKdata(QLHK_data &thisdata)
{
  thisdata.data = nullptr;
  thisdata.current_popup = 0;
  thisdata.pickdata_index = -1;
  thisdata.current_page = 1;

  thisdata.i_CMND.mode = Numeric;
  thisdata.i_CMND.tittle = (char *)"Nhập số CMND/CCCD";
  thisdata.i_CMND.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  thisdata.i_CMND.size = 12;

  thisdata.i_Ho.mode = AlphaleteWithSpace;
  thisdata.i_Ho.tittle = (char *)"Nhập họ và tên đệm";
  thisdata.i_Ho.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 580, 50};
  thisdata.i_Ho.size = 26;

  thisdata.i_Ten.mode = Alphalete;
  thisdata.i_Ten.tittle = (char *)"Nhập tên";
  thisdata.i_Ten.textBox = {StartPos.x + 300 + 600, StartPos.y + 60 + 380, 300, 50};
  thisdata.i_Ten.size = 10;

  thisdata.i_Phai = -1;

  resetPageSwitcher(thisdata.Sw_table_page);
}

void initPageSwitcher(PageSwitcher &thisdata)
{
  thisdata.fast_switcher.editMode = true;
  thisdata.fast_switcher.size = 2;
  thisdata.fast_switcher.MauVien = BROWN;
  thisdata.fast_switcher.mode = Numeric;
  thisdata.fast_switcher.returnIfDone = true;
  thisdata.fast_switcher.showNKeyRemain = false;
}

void resetPageSwitcher(PageSwitcher &thisdata)
{
  thisdata.editmode = false;
  resetInputTextBox(thisdata.fast_switcher);
}

void initQLVedata(QLVe_data &thisdata)
{
  thisdata.current_page = 1;
  thisdata.position = -1;
  thisdata.data = VeMayBay();
  thisdata.inDelete = false;

  resetPageSwitcher(thisdata.Sw_table_page);
}

void initQLCBdata(QLCB_data &thisdata)
{
  thisdata.data = nullptr;
  thisdata.status = 0;
  thisdata.current_popup = 0;
  thisdata.popup_errorMess = "";
  thisdata.time_showError = 0;
  thisdata.inChooseMB = false;
  initQLVedata(thisdata.dataDSVe);

  thisdata.pickdata_index = -1;
  thisdata.current_showPage = 1;

  thisdata.inSearching = false;
  thisdata.fbDay = Date(1, 1, 0, 0, 0);
  thisdata.fbNoiDen = "";
  thisdata.inGetTicket = false;
  thisdata.gotChangeTicket = false;

  resetPageSwitcher(thisdata.Sw_table_page);

  // Input Textbox
  thisdata.MaCB.mode = UpperAlphanumeric;
  thisdata.MaCB.tittle = (char *)"Nhập mã chuyến bay";
  thisdata.MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  thisdata.MaCB.size = 15;
  thisdata.MaMB.mode = UpperAlphanumeric;
  thisdata.MaMB.tittle = (char *)"Nhập số hiệu máy bay";
  thisdata.MaMB.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 900, 50};
  thisdata.MaMB.size = 40;
  thisdata.NoiDen.mode = ASCII2;
  thisdata.NoiDen.tittle = (char *)"Nhập nơi đến";
  thisdata.NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
  thisdata.NoiDen.size = 40;
  thisdata.Ngay.mode = Day;
  thisdata.Ngay.tittle = (char *)"DD";
  thisdata.Ngay.textBox = {StartPos.x + 300, StartPos.y + 60 + 180, 60, 50};
  thisdata.Ngay.size = 2;
  thisdata.Ngay.showNKeyRemain = false;
  thisdata.Thang.mode = Month;
  thisdata.Thang.tittle = (char *)"MM";
  thisdata.Thang.textBox = {StartPos.x + 300 + 70, StartPos.y + 60 + 180, 60, 50};
  thisdata.Thang.size = 2;
  thisdata.Thang.showNKeyRemain = false;
  thisdata.Nam.mode = Year;
  thisdata.Nam.tittle = (char *)"YYYY";
  thisdata.Nam.textBox = {StartPos.x + 300 + 70 + 70, StartPos.y + 60 + 180, 120,
                          50};
  thisdata.Nam.size = 4;
  thisdata.Nam.showNKeyRemain = false;
  thisdata.Gio.mode = Hour;
  thisdata.Gio.tittle = (char *)"HH";
  thisdata.Gio.textBox = {StartPos.x + 300 + 70 + 70 + 150, StartPos.y + 60 + 180,
                          60, 50};
  thisdata.Gio.size = 2;
  thisdata.Gio.showNKeyRemain = false;
  thisdata.Phut.mode = Minute;
  thisdata.Phut.tittle = (char *)"MM";
  thisdata.Phut.textBox = {StartPos.x + 300 + 70 + 70 + 150 + 70,
                           StartPos.y + 60 + 180, 60, 50};
  thisdata.Phut.size = 2;
  thisdata.Phut.showNKeyRemain = false;

  thisdata.searchMaCB.tittle = "Mã chuyến bay";
  thisdata.searchMaCB.textBox = {StartPos.x + 60 + 300 + 250 + 165, StartPos.y + 60 + 70, 350, 45};
  thisdata.searchMaCB.size = 15;
  thisdata.searchMaCB.mode = UpperAlphanumeric;

  thisdata.searchNoiDen.tittle = "Nơi đến";
  thisdata.searchNoiDen.textBox = {StartPos.x + 60 + 150 + 30, StartPos.y + 60 + 70 + 55, 300, 45};
  thisdata.searchNoiDen.size = 20;
  thisdata.searchNoiDen.mode = ASCII2;
}

// Xử lí yêu cầu chuyển tab
bool UI_reqSwitchTab(UIcontroller &control)
{
  if (control.dataTabCB.current_popup != 0 || control.dataTabMB.current_popup != 0 || control.dataTabHK.current_popup != 0)
  {
    int check = Warning_SwitchTab();
    if (check == -1)
      return true;
    else if (check == 1)
    {
      UI_switchTab(control);
      return true;
    }
  }
  else
  {
    UI_switchTab(control);
    return true;
  }

  return false;
}

void ReloadData(UIcontroller &control)
{
  setDataToFile(control.listCB, control.listMB, control.listHK);
  getDataFromFile(control.listCB, control.listMB, control.listHK);
}

// Thực hiện chuyển tab
void UI_switchTab(UIcontroller &control)
{
  InitUIData(control);

  CreateLoadingScreen();

  if (control.current_tab != 0)
  {
    resetData_QLCB(control.dataTabCB);
    resetData_QLMB(control.dataTabMB);
    resetData_QLHK(control.dataTabHK);
  }
  control.current_tab = control.next_tab;
}

// Khởi tạo dữ liệu người dùng ban đầu
void InitUIData(UIcontroller &control)
{
  control.current_tab = 0;
  initQLMBdata(control.dataTabMB);
  initQLCBdata(control.dataTabCB);
  initQLHKdata(control.dataTabHK);
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

  resetPageSwitcher(data.Sw_table_page);
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
  data.inAdvSearch = false;
  data.fbNoiDen = "";
  data.fbAvail = false;
  data.inSearching = false;
  data.inGetTicket = false;
  data.gotChangeTicket = false;

  resetPageSwitcher(data.Sw_table_page);
}

void resetData_searchQLCB(QLCB_data &data)
{
  data.fbDay = Date(1, 1, 0, 0, 0);
  data.inAdvSearch = false;
  data.fbNoiDen = "";
  data.fbAvail = false;
  data.fbMaCB = "";
}

void resetData_QLHK(QLHK_data &data)
{
  data.data = nullptr;

  data.current_popup = 0;
  data.popup_errorMess = "";
  data.time_showError = 0;

  data.pickdata_index = -1;
  data.current_page = 1;

  resetInputTextBox(data.i_CMND);

  resetInputTextBox(data.i_Ho);

  resetInputTextBox(data.i_Ten);

  data.i_Phai = -1;

  resetPageSwitcher(data.Sw_table_page);
}

void resetData_QLVe(QLVe_data &data)
{
  data.current_page = 1;
  data.position = -1;
  data.data = VeMayBay();
  data.inDelete = false;

  resetPageSwitcher(data.Sw_table_page);
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

// Load dữ liệu từ các file ngoài
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

  // Làm trống bộ nhớ
  UnloadImage(LogoPTIT);
  UnloadImage(HomeIcon);
  UnloadImage(ArrowLeft);
  UnloadImage(Status_Tick);
  UnloadImage(Status_Green);
  UnloadImage(Status_Yellow);
  UnloadImage(Status_Gray);
}

// Làm trống bộ nhớ
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

// Hiệu chỉnh kích thước cửa sổ phù hợp với máy tính
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
    W = 800;
    H = 580;
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

void CreateLoadingScreen()
{
  TextBox Loading;
  Loading.box = {StartPos.x, StartPos.y + 60, SCREEN_WIDTH, SCREEN_HEIGHT};
  Loading.text = (char *)"LOADING";
  Loading.isCenter = true;
  Loading.fontSize = 60;

  DrawRectangleRec(Loading.box, DARKBLUE);
  CreateTextBox(Loading);
}

//---Homepage-------------------------------------------------------------------------------------------------------------
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
  char *button_tittle[4];
  button_tittle[0] = (char *)"QUẢN LÝ MÁY BAY";
  button_tittle[1] = (char *)"QUẢN LÝ CHUYẾN BAY";
  button_tittle[2] = (char *)"QUẢN LÝ HÀNH KHÁCH";
  button_tittle[3] = (char *)"GIỚI THIỆU VỀ SẢN PHẨM";

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

  CreateHomeBackground();
  DrawTexture(PNG_logo, pngScreen.x, pngScreen.y, RED);
  DrawRectangleRec(splitScreen, GRAY);
  DrawTextEx(FontArial, home_tittle, tittleHomePos, 50, 0, RED);
  DrawTextEx(FontArial, button_tille, tittleButtonPos, 40, 0, BLUE);

  DrawTextureEx(PNG_logo, pngPos, 0, 1, WHITE);

  Button button[4];
  for (int i = 0; i < 4; i++)
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
      control.next_tab = i + 1;
      UI_switchTab(control);
    }
  }
}

// ---Các trang thành phần----------------------------------------------------------------------------
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

  DrawTextEx(FontArial, "DANH SÁCH MÁY BAY",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);

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
    if (control.dataTabMB.data == NULL || control.dataTabMB.data->inUsed())
    {
      button[1].isActive = false;
      button[2].isActive = false;
    }
    else
    {
      button[1].isActive = true;
      button[2].isActive = true;
    }
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
    if (control.listMB.isFull())
    {
      if (Warning_Full())
      {
        control.dataTabMB.current_popup = 0;
      }
      return;
    }

    if (Popup_ThemMB(control))
      control.dataTabMB.current_popup = 0;
    ReloadData(control);
  }
  else if (control.dataTabMB.current_popup == 2)
  {
    if (Popup_HieuChinhMB(control))
      control.dataTabMB.current_popup = 0;
    ReloadData(control);
  }
  else if (control.dataTabMB.current_popup == 3)
  {
    if (Popup_XoaMB(control))
      control.dataTabMB.current_popup = 0;
    ReloadData(control);
  }
  else if (control.dataTabMB.current_popup == 4)
  {
    if (Popup_Thongkesoluotbay(control))
    {
      control.dataTabMB.current_popup = 0;
      // control.dataTabMB.Sw_table_page.reset();
    }
  }
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
  DrawTextEx(FontArial, "(Gồm CHỈ số, nhỏ hơn hoặc bằng 25)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  const char *newSoDong = CreateTextInputBox(control.dataTabMB.SoDong);
  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm CHỈ số, nhỏ hơn hoặc bằng 12)",
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
    if (!(newMaMB[0] >= 32 && newLoaiMayBay[0] >= 32 && newSoDay[0] >= 32 &&
          newSoDong[0] >= 32))
    {
      control.dataTabMB.popup_errorMess = "Nhập chưa đủ thông tin!";
      return false;
    }

    if (control.listMB.findPosMB(CheckMB) >= 0)
    {
      control.dataTabMB.popup_errorMess = "Máy Bay đã tồn tại!";
      return false;
    }

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

    newLoaiMayBay = trim(charToString(newLoaiMayBay)).c_str();
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

  control.dataTabMB.LoaiMB.editMode = true;
  control.dataTabMB.LoaiMB.tittle = control.dataTabMB.data->getLoaiMB();
  control.dataTabMB.SoDong.editMode = true;
  control.dataTabMB.SoDong.tittle = intToChar(control.dataTabMB.data->getSoDong(), 0);
  control.dataTabMB.SoDay.editMode = true;
  control.dataTabMB.SoDay.tittle = intToChar(control.dataTabMB.data->getSoDay(), 0);

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
    if (!(newLoaiMB[0] >= 32 && newSoDay[0] >= 32 &&
          newSoDong[0] >= 32))
    {
      control.dataTabMB.popup_errorMess = "Nhập chưa đủ thông tin!";
      return false;
    }

    if (atoi(newSoDong) < 1 || atoi(newSoDong) > 25)
    {
      control.dataTabMB.popup_errorMess = "Số dòng không hợp lệ!(1 - 25)";
      return false;
    }
    if (atoi(newSoDay) < 1 || atoi(newSoDay) > 12)
    {
      control.dataTabMB.popup_errorMess = "Số dãy không hợp lệ!(1 - 12)";
      return false;
    }
    if (atoi(newSoDong) * atoi(newSoDay) < 20)
    {
      control.dataTabMB.popup_errorMess = "Số chỗ phải lớn hơn hoặc bằng 20!";
      return false;
    }

    newLoaiMB = trim(charToString(newLoaiMB)).c_str();
    control.dataTabMB.data->setLoaiMB(newLoaiMB);
    control.dataTabMB.data->setSoDong(atoi(newSoDong));
    control.dataTabMB.data->setSoDay(atoi(newSoDay));
    ReloadData(control);

    resetInputTextBox(control.dataTabMB.LoaiMB);
    resetInputTextBox(control.dataTabMB.SoDong);
    resetInputTextBox(control.dataTabMB.SoDay);
    control.dataTabMB.popup_errorMess = "";

    return true;
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
  Box_soDong.text = intToChar(control.dataTabMB.data->getSoDong(), 0);
  CreateTextBox(Box_soDong);

  DrawTextEx(FontArial, "Số dãy",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  TextBox Box_soDay;
  Box_soDay.box = {StartPos.x + 300, StartPos.y + 60 + 480, 500, 50};
  Box_soDay.showBox = true;
  Box_soDay.text = intToChar(control.dataTabMB.data->getSoDay(), 0);
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
    ReloadData(control);

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
  DrawTextEx(FontArial, "Thống kê số lượt bay",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);
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

  Rectangle timkiem = {searchText.x + searchText.width, searchText.y, 200, 50};
  TextBox Timkiem;
  Timkiem.box = timkiem;
  Timkiem.text = "TÌM KIẾM";
  Timkiem.fontSize = 30;
  Timkiem.isCenter = true;
  Timkiem.MauNen = {175, 175, 175, 225};
  Timkiem.showBox = true;
  CreateTextBox(Timkiem);
  const char *cell_tittle[3] = {"STT", "Mã MB", "Số lượt bay"};

  float cellW[3] = {180, 450, 450};
  CreateTable({StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 3, cellW, 1080);
  Vector2 *tittle_pos = GetTittlePos(
      {StartPos.x + 60, StartPos.y + 60 + 100 + 80}, 3, cellW, cell_tittle);
  for (int i = 0; i < 3; i++)
  {
    DrawTextEx(FontArial, cell_tittle[i], tittle_pos[i], 40, 0, RED);
  }

  // control.dataTabMB.current_showPage = 1;
  int n_page = 1; // 1 + (spt/10)
  int size = control.listMB.getSize();
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
            intToChar(j + 1, 0),
            control.listMB.getMB(A[id])->getSoHieuMB(), // control.listMB.getMB()[control.listMB.sapXepThongKe()[id]]->getSoHieuMB()
            intToChar(control.listMB.getMB(A[id])->getSoLuotBay(), 0)};
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
  A = 0;
  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(control.dataTabMB.Sw_table_page, control.dataTabMB.current_showPage, n_page,
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});

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

  Rectangle timkiem = {searchText.x + searchText.width, searchText.y, 200, 50};
  TextBox Timkiem;
  Timkiem.box = timkiem;
  Timkiem.text = "TÌM KIẾM";
  Timkiem.fontSize = 30;
  Timkiem.isCenter = true;
  Timkiem.MauNen = {175, 175, 175, 225};
  Timkiem.showBox = true;
  CreateTextBox(Timkiem);
  // table
  float cellW[5] = {100, 300, 380, 150, 150};
  CreateTable_QLMB();

  // data
  int n_page = 1;
  if (control.dataTabMB.status == 1)
  {
    control.dataTabMB.current_showPage = 1 + (control.listMB.getSize() - 1) / 10;
    control.dataTabMB.pickdata_index = (control.listMB.getSize() - 1) % 10;
    control.dataTabMB.status = 0;
  }
  else if (control.dataTabMB.status == -1)
  {
    control.dataTabMB.current_showPage = 1;
    control.dataTabMB.pickdata_index = -1;
    control.dataTabMB.status = 0;
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

  int size = control.listMB.getSize();
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

            intToChar(j + 1, 0), control.listMB.getMB(id)->getSoHieuMB(),
            control.listMB.getMB(id)->getLoaiMB(),
            intToChar(control.listMB.getMB(id)->getSoDay(), 0),
            intToChar(control.listMB.getMB(id)->getSoDong(), 0)};
        for (int show_i = 4; show_i >= 0; show_i--)
        {
          show[show_i] = GetCellTextBox(start_pos, 5, cellW, show_i + 1,
                                        (j % 10) + 1, showText[show_i], 30);
        }
        for (int show_i = 4; show_i >= 0; show_i--)
        {
          CreateTextBox(show[show_i]);
        }
      }
      j++;
    }
  }
  n_page = 1 + ((j - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(control.dataTabMB.Sw_table_page, control.dataTabMB.current_showPage, n_page,
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});
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

void CreatePage_QLCB(UIcontroller &control)
{
  // Get new address of nodeCB
  if (control.dataTabCB.data != nullptr)
  {
    if (control.dataTabCB.data != control.listCB.timCB(control.dataTabCB.data->getNode().getMaCB()))
      control.dataTabCB.data = nullptr;
    control.dataTabCB.data = control.listCB.timCB(control.dataTabCB.data->getNode().getMaCB());
  }

  CreatePageBackground(5);
  DrawTextEx(FontArial, "DANH SÁCH CHUYẾN BAY",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);
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
  {
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
      if (control.dataTabCB.data->getNode().getTrangThai() == 0 || control.dataTabCB.data->getNode().getTrangThai() == 3)
      {
        button[1].isActive = false;
        button[2].isActive = false;
        if (control.dataTabCB.data->getNode().getTrangThai() == 0)
          button[3].isActive = false;
      }
      else
      {
        button[1].isActive = true;
        button[2].isActive = true;
        button[3].isActive = true;
      }
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
      resetPageSwitcher(control.dataTabCB.Sw_table_page);
      if (control.dataTabCB.fbMaCB != NULL)
        control.dataTabCB.data = nullptr;
      control.dataTabCB.current_popup = 5;
    }

    control.dataTabCB.data = XuLy_QLCB(control);
  }
  else if (control.dataTabCB.current_popup == 1)
  {
    if (control.listMB.isEmpty())
    {
      if (Warning_Empty())
      {
        control.dataTabCB.current_popup = 0;
      }
      return;
    }

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
    if (Popup_chonChuyen(control) && *control.dataTabCB.fbMaCB == 0)
    {
      resetPageSwitcher(control.dataTabCB.Sw_table_page);
      control.dataTabCB.pickdata_index = -1;
      control.dataTabCB.data = nullptr;
      control.dataTabCB.current_popup = 0;
    }
  }

  if (control.dataTabCB.gotChangeTicket)
  {
    ReloadData(control);
    control.dataTabCB.gotChangeTicket = false;
  }
}

bool Popup_TimCB(UIcontroller &control)
{
  CreatePopupBackground();
  DrawTextEx(
      FontArial, "Tìm chuyến bay",
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

  const char *newNgay = CreateTextInputBox(control.dataTabCB.Ngay);
  const char *newThang = CreateTextInputBox(control.dataTabCB.Thang);
  const char *newNam = CreateTextInputBox(control.dataTabCB.Nam);

  Date newNgayBay = Date(stoi(newNgay[0] == 0 ? "0" : newNgay),
                         stoi(newThang[0] == 0 ? "0" : newThang),
                         stoi(newNam[0] == 0 ? "0" : newNam),
                         0,
                         0);

  DrawTextEx(FontArial, "Nơi đến",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái, kí tự và số)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  control.dataTabCB.NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
  const char *newNoiDen = CreateTextInputBox(control.dataTabCB.NoiDen);

  DrawTextEx(FontArial, "Mã chuyến bay",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái và số, có thể để trống để bỏ qua)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);
  control.dataTabCB.MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 380, 900, 50};
  const char *newMaCB = CreateTextInputBox(control.dataTabCB.MaCB);

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
    if (!(newNoiDen[0] >= 32 &&
          newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32))
    {
      control.dataTabCB.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      return false;
    }

    if (!newNgayBay.checkNgay())
    {
      control.dataTabCB.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
      return false;
    }
    if (*newMaCB != 0)
    {
      control.dataTabCB.data = control.listCB.timCB(newMaCB);
      if (control.dataTabCB.data == nullptr)
      {
        control.dataTabCB.searchFail = true;
      }
    }

    control.dataTabCB.fbDay = newNgayBay;
    control.dataTabCB.fbNoiDen = newNoiDen;
    control.dataTabCB.fbMaCB = newMaCB;
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.inAdvSearch = true;
    resetInputTextBox(control.dataTabCB.MaCB);
    control.dataTabCB.MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    resetInputTextBox(control.dataTabCB.NoiDen);
    control.dataTabCB.NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
    resetInputTextBox(control.dataTabCB.Ngay);
    resetInputTextBox(control.dataTabCB.Thang);
    resetInputTextBox(control.dataTabCB.Nam);
    control.dataTabCB.popup_errorMess = "";
    control.dataTabCB.status = 2;

    return true;
  }
  if (CreateButton(Cancel))
  {
    resetInputTextBox(control.dataTabCB.MaCB);
    control.dataTabCB.MaCB.textBox = {StartPos.x + 300, StartPos.y + 60 + 280, 900, 50};
    resetInputTextBox(control.dataTabCB.NoiDen);
    control.dataTabCB.NoiDen.textBox = {StartPos.x + 300, StartPos.y + 60 + 480, 900, 50};
    resetInputTextBox(control.dataTabCB.Ngay);
    resetInputTextBox(control.dataTabCB.Thang);
    resetInputTextBox(control.dataTabCB.Nam);
    control.dataTabCB.popup_errorMess = "";
    return true;
  }
  return false;
}

void Popup_getMB(UIcontroller &control, Date gioBay, bool inEdit)
{
  MayBay *result;

  CreatePageBackground(2);
  DrawTextEx(FontArial, "Hãy chọn máy bay",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);

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

    if (inEdit == true && !control.listMB.planeMatch(control.dataTabCB.data->getNode().getMaMayBay(), control.dataTabMB.data->getSoHieuMB()))
    {
      check_mb = true;
      control.dataTabCB.popup_errorMess = "Máy bay phải có số dãy và số dòng bằng máy bay ban đầu!";
      control.dataTabCB.time_showError = 99;
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

  const char *newNgay = CreateTextInputBox(control.dataTabCB.Ngay);
  const char *newThang = CreateTextInputBox(control.dataTabCB.Thang);
  const char *newNam = CreateTextInputBox(control.dataTabCB.Nam);
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
      Popup_getMB(control, newNgayBay, false);
      return false;
    }
  }

  if (control.dataTabCB.MaMB.mouseClickOnText)
  {
    if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 && newGio[0] >= 32 && newPhut[0] >= 32))
    {
      control.dataTabCB.MaMB.mouseClickOnText = false;
      control.dataTabCB.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
    }

    if (!newNgayBay.checkNgay())
    {
      control.dataTabCB.MaMB.mouseClickOnText = false;
      control.dataTabCB.popup_errorMess = "Ngày tháng cần hợp lệ để chọn số hiệu máy bay!";
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
       newGio[0] >= 32 && newPhut[0] >= 32) &&
      newNgayBay.checkNgay())
  {
    if (CreateButton(getMB))
    {
      control.dataTabCB.inChooseMB = true;
      return false;
    }
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
    if (newMaCB[0] >= 32 && newMaMB[0] >= 32 && newNoiDen[0] >= 32 &&
        newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 &&
        newGio[0] >= 32 && newPhut[0] >= 32)
    {
      if (!newNgayBay.checkNgay())
        control.dataTabCB.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
      else if (!(newNgayBay.checkNgayNhapVoiNgayHT()))
      {
        control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";
      }
      else if (control.listMB.findPosMB(newMaMB) < 0)
      {
        control.dataTabCB.popup_errorMess = "Số hiệu máy bay không tồn tại!";
      }
      else if (!control.listCB.isAval(newMaMB, newNgayBay, newMaCB))
        control.dataTabCB.popup_errorMess = "Máy bay đang được chuyển bay khác sử dụng!";
      else if (!control.listCB.isExist(newMaCB))
      {
        ChuyenBay result = ChuyenBay(newMaCB, trim(charToString(newNoiDen)), newNgayBay, newMaMB);
        DsVeMayBay newDSVe;
        newDSVe.setDSVe(control.listMB.findMB(newMaMB));
        result.setDSVe(newDSVe);
        control.listCB.insertOrder(new NodeCB(result));
        control.listMB.findMB(newMaMB)->setUsed();
        ReloadData(control);
        control.listCB.setSize();

        NodeCB *tmp = control.listCB.getHead();
        int index = 0, page = 1;
        while (tmp->hasNext())
        {
          if (strcmp(tmp->getNode().getMaCB(), newMaCB) == 0)
          {
            control.dataTabCB.pickdata_index = index;
            control.dataTabCB.current_showPage = page;
            break;
          }
          else
          {
            index++;
            if (index == 10)
            {
              index = 0;
              page++;
            }
          }
          tmp = tmp->getNext();
        }

        setDataToFile(control.listCB, control.listMB, control.listHK);
        getDataFromFile(control.listCB, control.listMB, control.listHK);

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
      else if (control.listCB.isExist(newMaCB))
      {
        control.dataTabCB.popup_errorMess = "Mã chuyến bay đã được sử dụng!";
      }
    }
    else
    {
      control.dataTabCB.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
    }
    return false;
  }
  if (CreateButton(Cancel))
  {
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
      Popup_getMB(control, newNgayBay, true);
      return false;
    }
  }
  if (control.dataTabCB.MaMB.mouseClickOnText)
  {
    if (!(newNgay[0] >= 32 && newThang[0] >= 32 && newNam[0] >= 32 && newGio[0] >= 32 && newPhut[0] >= 32))
    {
      control.dataTabCB.MaMB.mouseClickOnText = false;
      control.dataTabCB.popup_errorMess = "Hãy nhập ngày khởi hành trước!";
    }

    if (!newNgayBay.checkNgay())
    {
      control.dataTabCB.MaMB.mouseClickOnText = false;
      control.dataTabCB.popup_errorMess = "Ngày tháng cần hợp lệ để chọn số hiệu máy bay!";
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
       newGio[0] >= 32 && newPhut[0] >= 32) &&
      newNgayBay.checkNgay())
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
    if (!(newMaMB[0] >= 32 && newNgay[0] >= 32 &&
          newThang[0] >= 32 && newNam[0] >= 32 &&
          newGio[0] >= 32 && newPhut[0] >= 32))
    {
      control.dataTabCB.popup_errorMess = "Nhập chưa đầy đủ thông tin!";
      return false;
    }

    if (!newNgayBay.checkNgay())
    {
      control.dataTabCB.popup_errorMess = "Ngày, tháng hoặc năm không hợp lệ!";
      return false;
    }
    else if (!(newNgayBay.checkNgayNhapVoiNgayHT()))
    {
      control.dataTabCB.popup_errorMess = "Chuyến bay phải được lập cách 1 ngày!";
      return false;
    }

    if (control.listMB.findPosMB(newMaMB) < 0)
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
    ReloadData(control);
    control.listCB.setSize();

    control.dataTabCB.status = 1;
    resetInputTextBox(control.dataTabCB.MaMB);
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
    resetInputTextBox(control.dataTabCB.Thang);
    resetInputTextBox(control.dataTabCB.Nam);
    resetInputTextBox(control.dataTabCB.Gio);
    resetInputTextBox(control.dataTabCB.Phut);
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
    control.listCB.writetToFile();
    ChuyenBay result = control.dataTabCB.data->getNode();
    result.setTrangThai(HuyChuyen);
    control.dataTabCB.data->setCb(result);
    ReloadData(control);

    control.listCB.setSize();
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
    string tittle = "Huỷ vé " + control.dataTabCB.data->getNode().getDSVe().getVe(control.dataTabCB.dataDSVe.position).getIDVe();
    DrawTextEx(
        FontArial, strToChar(tittle),
        {CenterDataSetter(700, StartPos.x + 400,
                          MeasureTextEx(FontArial, "Huy ve A00", 50, 0).x),
         CenterDataSetter(60, StartPos.y + 60 + 10,
                          MeasureTextEx(FontArial, "A", 50, 0).y)},
        50, 0, BLACK);
    int tmp_c = Warning_Confirm_HuyVe();
    if (tmp_c == 0)
      return false;
    else if (tmp_c == 1)
    {
      control.dataTabCB.dataDSVe.inDelete = false;

      ChuyenBay cb_t = control.dataTabCB.data->getNode();
      DsVeMayBay dsv_t = cb_t.getDSVe();
      dsv_t.deleteVe(control.dataTabCB.dataDSVe.position);
      cb_t.setDSVe(dsv_t);
      control.dataTabCB.data->setCb(cb_t);
      ReloadData(control);

      resetData_QLVe(control.dataTabCB.dataDSVe);
    }
    else if (tmp_c == -1)
    {
      control.dataTabCB.dataDSVe.inDelete = false;
      return false;
    }
  }

  CreatePageBackground(2);
  DrawTextEx(FontArial, "DANH SÁCH HÀNH KHÁCH THUỘC CHUYẾN BAY ",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50 + 10,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             40, 0, BLUE);
  DrawTextEx(FontArial, control.dataTabCB.data->getNode().getMaCB(),
             {StartPos.x + 60 + 840,
              CenterDataSetter(100, StartPos.y + 50 + 10,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             40, 0, BLUE);

  DrawTextEx(FontArial, "Ngày giờ khởi hành: ",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 50 + 10 + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNgayGio().printDateHour()),
             {StartPos.x + 60 + 250,
              CenterDataSetter(100, StartPos.y + 50 + 10 + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);

  DrawTextEx(FontArial, "Nơi đến: ",
             {StartPos.x + 60 + 500,
              CenterDataSetter(100, StartPos.y + 50 + 10 + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNoiDen()),
             {StartPos.x + 60 + 500 + 120,
              CenterDataSetter(100, StartPos.y + 50 + 10 + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
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
      {
        control.dataTabCB.dataDSVe.pickdata_index = -1;
        control.dataTabCB.dataDSVe.position = -1;
      }
    }

    if (control.dataTabCB.dataDSVe.pickdata_index == i)
      DrawRectangleRoundedLines({data_picker[i].x, data_picker[i].y,
                                 data_picker[i].w, data_picker[i].h},
                                0, 1, 2, GREEN);
  }

  // mini function
  button[0].tittle = "Quay lại";

  button[1].tittle = "Huỷ vé";
  if (control.dataTabCB.data->getNode().getTrangThai() == HoanTat || control.dataTabCB.dataDSVe.position < 0)
    button[1].isActive = false;
  else
    button[1].isActive = true;

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

  if (currCB.getDSVe().getSoVeDaDat() != 0)
  {
    int iVe = 0;
    for (int i = 0; i < currCB.getDSVe().getSoVeToiDa(); i++)
    {
      VeMayBay tmp = currCB.getDSVe().getVe(i);
      if (tmp.getHanhKhach() == "")
        continue;
      if (iVe >= (control.dataTabCB.dataDSVe.current_page - 1) * 10 && iVe < control.dataTabCB.dataDSVe.current_page * 10)
      {
        const char *showText[5];
        showText[0] = intToChar(iVe % 10 + 1, 0);
        showText[1] = strToChar(tmp.getIDVe());
        showText[2] = strToChar(tmp.getHanhKhach());
        showText[3] = strToChar(control.listHK.search(tmp.getHanhKhach())->getHK().getHo() + " " + control.listHK.search(tmp.getHanhKhach())->getHK().getTen());
        showText[4] = strToChar(control.listHK.search(tmp.getHanhKhach())->getHK().getPhai());

        if (control.dataTabCB.dataDSVe.pickdata_index == iVe % 10)
        {
          control.dataTabCB.dataDSVe.position = i;
        }

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
      iVe++;
    }
    if (control.dataTabCB.dataDSVe.pickdata_index + (control.dataTabCB.dataDSVe.current_page - 1) * 10 >= iVe)
    {
      control.dataTabCB.dataDSVe.pickdata_index = -1;
      control.dataTabCB.dataDSVe.position = -1;
    }
  }

  int swp =
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabCB.dataDSVe.current_page, n_page,
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabCB.dataDSVe.current_page != swp)
  {
    control.dataTabCB.dataDSVe.position = -1;
    control.dataTabCB.dataDSVe.pickdata_index = -1;
    control.dataTabCB.dataDSVe.current_page = swp;
  }

  if (control.dataTabCB.dataDSVe.current_page > n_page)
    control.dataTabCB.dataDSVe.current_page = 1;
  if (CreateButton(button[0]))
  {
    control.dataTabCB.dataDSVe.current_page = 1;
    control.dataTabCB.current_popup = 0;
    resetData_QLVe(control.dataTabCB.dataDSVe);
    return true;
  }

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
      control.dataTabCB.inSearching = false;
      if (*control.dataTabCB.fbMaCB == 0)
        resetData_searchQLCB(control.dataTabCB);
      else
      {
        control.dataTabCB.current_popup = 0;
      }
      return true;
    }
    return false;
  }

  DrawTextEx(FontArial, "HÃY CHỌN CHUYẾN BAY",
             {StartPos.x + 60,
              CenterDataSetter(70, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);

  control.dataTabCB.fbAvail = true;
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
  if (!control.dataTabCB.inSearching)
  {
    if (CreateButton(OK))
    {
      control.dataTabCB.inGetTicket = true;
    }
    if (CreateButton(Cancel))
    {
      control.dataTabCB.fbAvail = false;
      resetData_QLVe(control.dataTabCB.dataDSVe);
      resetData_searchQLCB(control.dataTabCB);
      return true;
    }
  }
  return false;
}

bool Popup_chonVe(UIcontroller &control)
{
  CreatePageBackground(1);
  DrawTextEx(FontArial, "Hãy chọn một vé máy bay:",
             {StartPos.x + 50,
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLUE);

  DrawTextEx(FontArial, "Ngày giờ khởi hành: ",
             {StartPos.x + 50,
              CenterDataSetter(100, StartPos.y + 50 + 20 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNgayGio().printDateHour()),
             {StartPos.x + 50 + 280,
              CenterDataSetter(100, StartPos.y + 50 + 20 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);

  DrawTextEx(FontArial, "Nơi đến: ",
             {StartPos.x + 50,
              CenterDataSetter(100, StartPos.y + 50 + 20 + 45,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNoiDen()),
             {StartPos.x + 50 + 120,
              CenterDataSetter(100, StartPos.y + 50 + 20 + 45,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             30, 0, BLACK);
  if (control.dataTabCB.inSetTicket)
  {
    if (Popup_datVe(control))
    {
      control.dataTabCB.inSetTicket = false;
      if (control.dataTabCB.gotChangeTicket)
      {
        ReloadData(control);
        control.dataTabCB.inSetTicket = false;
        return true;
      }
    }
    return false;
  }

  if (control.dataTabCB.data->getNode().getDSVe().getSoVeDaDat() != 0)
  {
    DrawRectangleRoundedLines({StartPos.x + 890, StartPos.y + 60 + 20, 230, 100}, 0, 0, 3, BLUE);
    DrawRectangleRoundedLines({StartPos.x + 930, StartPos.y + 60 + 80, 150, 40}, 0, 0, 3, RED);
    Button s_ON;
    s_ON.x = StartPos.x + 900;
    s_ON.y = StartPos.y + 60 + 20;
    s_ON.w = 100;
    s_ON.h = 50;
    s_ON.gotNothing = false;
    s_ON.gotText = true;
    s_ON.tittle = (char *)"ON";
    s_ON.font = FontArial;
    s_ON.BoMau = ArrowKey;

    Button s_OFF;
    s_OFF.x = s_ON.x + s_ON.w + 10;
    s_OFF.y = s_ON.y;
    s_OFF.w = 100;
    s_OFF.h = 50;
    s_OFF.gotNothing = false;
    s_OFF.gotText = true;
    s_OFF.tittle = (char *)"OFF";
    s_OFF.font = FontArial;
    s_OFF.BoMau = ArrowKey;

    TextBox showVeAdv;
    showVeAdv.box = {s_ON.x - 100, s_ON.y + 60, 410, 40};
    showVeAdv.isCenter = true;
    showVeAdv.mode = Auto;
    showVeAdv.text = "Hiện vé đã đặt";

    CreateTextBox(showVeAdv);

    if (control.dataTabCB.dataDSVe.showNotEmpty == true)
    {
      s_ON.isActive = false;
      s_OFF.isActive = true;
    }
    else if (control.dataTabCB.dataDSVe.showNotEmpty == false)
    {
      s_OFF.isActive = false;
      s_ON.isActive = true;
    }

    if (CreateButton(s_ON))
    {
      control.dataTabCB.dataDSVe.showNotEmpty = true;
    }
    if (CreateButton(s_OFF))
    {
      control.dataTabCB.dataDSVe.showNotEmpty = false;
    }
  }

  ChuyenBay currCB = control.dataTabCB.data->getNode();
  int n_page = 1;

  int sDay = control.listMB.findMB(currCB.getMaMayBay())->getSoDay(),
      sDong = control.listMB.findMB(currCB.getMaMayBay())->getSoDong();
  int IndexSoDongMax = sDong;
  if (sDong > 10)
    IndexSoDongMax = (control.dataTabCB.dataDSVe.current_page) * 10;
  if (IndexSoDongMax > sDong)
    IndexSoDongMax = sDong;

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
      if (!control.dataTabCB.dataDSVe.showNotEmpty && currCB.getDSVe().getVe(a * sDong + m).getHanhKhach() != "")
        continue;
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
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});
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
  DrawTextEx(FontArial, "Mã chuyến bay: ",
             {StartPos.x + 300,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, control.dataTabCB.data->getNode().getMaCB(),
             {StartPos.x + 300 + 230,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  DrawTextEx(FontArial, "Ngày giờ khởi hành: ",
             {StartPos.x + 300,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNgayGio().printDateHour()),
             {StartPos.x + 300 + 280,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  DrawTextEx(FontArial, "Nơi đến: ",
             {StartPos.x + 300 + 565,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNoiDen()),
             {StartPos.x + 300 + 560 + 150,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
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
  DrawTextEx(FontArial, "(Gồm CHỈ số, phải đủ 12 số, nếu đã có sẽ tự điền thêm thông tin)",
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
  tb_Phai.mode = Auto;
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
    DrawTextEx(FontArial, "(Gồm chữ cái và kí tự)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
               25, 0, RED);
    DrawTextEx(FontArial, "(Nhấn vào để chọn)",
               {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
               25, 0, RED);
    control.dataTabHK.i_Ho.isActive = true;
    control.dataTabHK.i_Ten.isActive = true;
    if (control.listHK.search(o_CMND) != NULL)
    {
      HKexist = true;
      HanhKhach t_hk = control.listHK.search(o_CMND)->getHK();

      if (!control.dataTabHK.i_Ho.isGotData)
        control.dataTabHK.i_Phai = t_hk.getPhai() == "Nu";
      SetDataInputTextBox(control.dataTabHK.i_Ho, strToChar(t_hk.getHo()));
      SetDataInputTextBox(control.dataTabHK.i_Ten, strToChar(t_hk.getTen()));
    }
    else
    {
      if (control.dataTabHK.i_Ho.isGotData)
        control.dataTabHK.i_Phai = -1;
      ResetDataInputTextBox(control.dataTabHK.i_Ho);
      ResetDataInputTextBox(control.dataTabHK.i_Ten);
    }
  }

  if (o_CMND != "")
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
    if (control.dataTabHK.i_Ho.letterCount < 1 || control.dataTabHK.i_Ten.letterCount < 1 || control.dataTabHK.i_Phai < 0)
    {
      control.dataTabCB.popup_errorMess = "Chưa nhập đủ thông tin!";
      return false;
    }

    if (o_CMND.length() < 12)
    {
      control.dataTabCB.popup_errorMess = "CMND/ CCCD phải đủ 12 số!";
      return false;
    }

    if (control.listCB.duocDatKhong(o_CMND, control.dataTabCB.data->getNode()) == 1)
    {
      control.dataTabCB.popup_errorMess = "Một CMND không thể đặt 2 lần trên cùng một chuyến bay!";
      return false;
    }

    if (control.listCB.duocDatKhong(o_CMND, control.dataTabCB.data->getNode()) == 2)
    {
      control.dataTabCB.popup_errorMess = "Các vé bạn đặt phải cách nhau 6 tiếng!";
      return false;
    }

    HanhKhach hk = HanhKhach(o_CMND, trim(o_Ho), trim(o_Ten), control.dataTabHK.i_Phai);
    if (!HKexist)
    {
      control.listHK.insert(hk);
    }
    else
    {
      control.listHK.search(o_CMND)->setHK(hk);
    }

    ChuyenBay m_cb = control.dataTabCB.data->getNode();
    DsVeMayBay m_dsVe = m_cb.getDSVe();
    VeMayBay m_ve = m_dsVe.getVe(control.dataTabCB.dataDSVe.position);
    m_ve.setHanhKhach(o_CMND);
    m_dsVe.setVe(m_ve, control.dataTabCB.dataDSVe.position);
    m_dsVe.setSoVeDaDat(m_dsVe.getSoVeDaDat() + 1);
    m_cb.setDSVe(m_dsVe);
    control.dataTabCB.data->setCb(m_cb);
    ReloadData(control);

    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    control.dataTabCB.popup_errorMess = "";

    resetData_QLHK(control.dataTabHK);
    resetData_QLVe(control.dataTabCB.dataDSVe);

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
    resetData_QLVe(control.dataTabCB.dataDSVe);

    return true;
  }
  return false;
}

bool Popup_OneFlightAction(UIcontroller &control)
{
  CreatePopupBackground();

  DrawTextEx(FontArial, "Mã chuyến bay: ",
             {StartPos.x + 300,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, control.dataTabCB.data->getNode().getMaCB(),
             {StartPos.x + 300 + 230,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  DrawTextEx(FontArial, "Mã máy bay: ",
             {StartPos.x + 300 + 565,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, control.dataTabCB.data->getNode().getMaMayBay(),
             {StartPos.x + 300 + 560 + 200,
              CenterDataSetter(100, StartPos.y + 60 + 100,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  DrawTextEx(FontArial, "Ngày giờ khởi hành: ",
             {StartPos.x + 300,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNgayGio().printDateHour()),
             {StartPos.x + 300 + 280,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  DrawTextEx(FontArial, "Nơi đến: ",
             {StartPos.x + 300 + 565,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);
  DrawTextEx(FontArial, strToChar(control.dataTabCB.data->getNode().getNoiDen()),
             {StartPos.x + 300 + 560 + 200,
              CenterDataSetter(100, StartPos.y + 60 + 150 + 15,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             35, 0, BLACK);

  Button button[4];
  for (int i = 0; i < 4; i++)
  {
    button[i].w = 440;
    button[i].h = 60;
    button[i].BoTron = false;
    button[i].gotNothing = false;
    button[i].gotText = true;
    button[i].font = FontArial;
    button[i].BoMau = ArrowKey;
  }

  button[0].tittle = "Hiệu chỉnh CB";
  button[0].x = StartPos.x + 300;
  button[0].y = StartPos.y + 60 + 250;

  if (CreateButton(button[0]))
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
  button[1].tittle = "Huỷ chuyến bay";
  button[1].x = StartPos.x + 750;
  button[1].y = StartPos.y + 60 + 250;
  if (CreateButton(button[1]))
  {

    control.dataTabCB.current_popup = 3;
  }

  button[2].tittle = "Xem danh sách vé";
  button[2].x = StartPos.x + 300;
  button[2].y = StartPos.y + 60 + 350;
  if (CreateButton(button[2]))
  {
    control.dataTabCB.current_popup = 4;
  }
  button[3].tittle = "Đặt vé";
  button[3].x = StartPos.x + 750;
  button[3].y = StartPos.y + 60 + 350;
  if (CreateButton(button[3]))
  {
    control.dataTabCB.current_popup = 5;
    control.dataTabCB.inGetTicket = true;
  }

  Button Cancel;
  Cancel.x = StartPos.x + 225;
  Cancel.y = StartPos.y + 60 + 625;
  Cancel.w = 300;
  Cancel.h = 50;
  Cancel.gotNothing = false;
  Cancel.gotText = true;
  Cancel.tittle = (char *)"Kết thúc tìm kiếm";
  Cancel.font = FontArial;
  Cancel.BoMau = ArrowKey;

  if (CreateButton(Cancel))
  {
    resetData_QLCB(control.dataTabCB);
    control.dataTabCB.pickdata_index = -1;
    control.dataTabCB.data = nullptr;
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

int ShowListCB(UIcontroller &control, int first, const char *textMaCB, bool inAdvSearch)
{
  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  Vector2 start_pos = {StartPos.x + 35, StartPos.y + 60 + 70 + 110};

  int size = control.listCB.getSize();

  NodeCB *tmp = control.listCB.getHead();
  int i = (control.dataTabCB.current_showPage - 1) * 10;
  int j = 0;
  for (int k = 0; k < size; k++)
  {
    bool DKTimKiem = tmp->getNode().checkMaCB(textMaCB);

    if (control.dataTabCB.inAdvSearch)
    {
      string c_NoiDen = tmp->getNode().getNoiDen(), k_NoiDen = control.dataTabCB.fbNoiDen;
      formatStr(c_NoiDen);
      formatStr(k_NoiDen);
      DKTimKiem = DKTimKiem &&
                  tmp->getNode().checkTime(control.dataTabCB.fbDay) &&
                  tmp->getNode().getTrangThai() == ConVe &&
                  isGotStr(c_NoiDen, k_NoiDen);
    }
    else if (control.dataTabCB.fbAvail)
    {
      DKTimKiem = DKTimKiem && tmp->getNode().getTrangThai() == ConVe;
    }

    if (DKTimKiem)
    {
      if (j >= i && j <= i + 9)
      {
        if (j % 10 == control.dataTabCB.pickdata_index)
          control.dataTabCB.data = tmp;

        string dsVe = intToString(tmp->getNode().getDSVe().getSoVeToiDa(), 0);
        dsVe = intToString(tmp->getNode().getDSVe().getSoVeConLai(), dsVe.length()) + '/' +
               intToString(tmp->getNode().getDSVe().getSoVeToiDa(), dsVe.length());
        TextBox show[6];
        const char *showText[6];
        showText[0] = intToChar(j + 1, 0);
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
        show[3].mode = Auto;
        show[5].mode = Auto;
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
  return ((j - 1) / 10) + 1;
}

NodeCB *XuLy_QLCB(UIcontroller &control)
{
  // Tab tìm cb nâng cao
  if (control.dataTabCB.inSearching)
  {
    if (Popup_TimCB(control))
    {
      control.dataTabCB.inSearching = false;
    }
    else
      return nullptr;
  }

  if (control.dataTabCB.searchFail && *control.dataTabCB.fbMaCB != 0)
  {
    if (Warning_searchFail())
    {
      control.dataTabCB.searchFail = false;
      control.dataTabCB.fbMaCB = "";
    }
    return nullptr;
  }

  if (*control.dataTabCB.fbMaCB != 0)
  {
    if (Popup_OneFlightAction(control))
    {
      control.dataTabCB.fbMaCB = "";
      return nullptr;
    }
    else
      return control.dataTabCB.data;
  }

  bool DKTimKiem = true;
  int numNgay = 1, numThang = 1, numNam = 1900, numGio = 0, numPhut = 0;

  float cellW[7] = {90, 230, 230, 200, 230, 100, 50};
  CreateTable_QLCB();

  int n_page = 1;

  const Vector2 search = {StartPos.x + 60, StartPos.y + 60 + 70};

  Button advSearch;
  Button data_picker[10];
  Vector2 start_pos = {StartPos.x + 35, StartPos.y + 60 + 70 + 110};

  // search
  DrawRectangleRoundedLines({search.x - 5, search.y - 5, 1090, 105}, 0, 1, 3,
                            DARKBLUE);

  if (!control.dataTabCB.inAdvSearch)
  {
    advSearch.x = search.x + 5;
    advSearch.y = search.y + 55;
    advSearch.w = 1070;
    advSearch.h = 40;
    advSearch.BoTron = false;
    advSearch.gotNothing = false;
    advSearch.gotText = true;
    advSearch.tittle = "TÌM NÂNG CAO";
    advSearch.font = FontArial;
    advSearch.BoMau = ArrowKey;
  }
  else
  {
    advSearch.x = search.x;
    advSearch.y = search.y + 55;
    advSearch.w = 30;
    advSearch.h = 40;
    advSearch.BoTron = false;
    advSearch.gotNothing = false;
    advSearch.gotText = true;
    advSearch.tittle = "X";
    advSearch.font = FontArial;
    advSearch.BoMau = ArrowKey;
  }

  DrawRectangleRoundedLines({search.x - 5, search.y - 5, 480, 52}, 0, 1, 3,
                            RED);
  DrawTextEx(FontArial, "TÌM KIẾM CHUYẾN BAY",
             {search.x + 50,
              CenterDataSetter(50, search.y,
                               MeasureTextEx(FontArial, "a", 35, 0).y)},
             35, 0, BLUE);

  DrawTextEx(
      FontArial, "Mã chuyến bay:",
      {search.x + 10 + 300 + 175,
       CenterDataSetter(50, search.y, MeasureTextEx(FontArial, "a", 35, 0).y)},
      35, 0, RED);
  int pre_nTextMaCB = control.dataTabCB.searchMaCB.letterCount;

  const char *textMaCB = CreateTextInputBox(control.dataTabCB.searchMaCB);
  if (pre_nTextMaCB != control.dataTabCB.searchMaCB.letterCount)
  {
    control.dataTabCB.status = 2;
  }
  if (control.dataTabCB.inAdvSearch)
  {
    DrawTextEx(FontArial, "Nơi đến:",
               {search.x + 50,
                CenterDataSetter(50, search.y + 55,
                                 MeasureTextEx(FontArial, "a", 35, 0).y)},
               35, 0, RED);
    TextBox tbNoiDen;
    tbNoiDen.box = control.dataTabCB.searchNoiDen.textBox;
    tbNoiDen.text = strToChar(control.dataTabCB.fbNoiDen);
    tbNoiDen.showBox = true;

    DrawTextEx(FontArial, "Ngày khởi hành:",
               {search.x + 540,
                CenterDataSetter(50, search.y + 55,
                                 MeasureTextEx(FontArial, "a", 35, 0).y)},
               35, 0, RED);

    TextBox tbNgayBay;
    tbNgayBay.box = {search.x + 600 + 170, search.y + 55, 300, 45};
    tbNgayBay.text = strToChar(control.dataTabCB.fbDay.printDate());
    tbNgayBay.showBox = true;

    CreateTextBox(tbNoiDen);
    CreateTextBox(tbNgayBay);
  }
  if (CreateButton(advSearch))
    if (!control.dataTabCB.inAdvSearch)
    {
      control.dataTabCB.inSearching = true;
    }
    else
    {
      control.dataTabCB.inAdvSearch = false;
    }

  // Pick data
  if (control.dataTabCB.status == 1)
  {
    control.dataTabCB.status = 0;
  }
  if (control.dataTabCB.status == 2)
  {
    control.dataTabCB.current_showPage = 1;
    control.dataTabCB.pickdata_index = -1;
    control.dataTabCB.data = nullptr;
    control.dataTabCB.status = 0;
  }

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
  n_page = ShowListCB(control, i, textMaCB, control.dataTabCB.inAdvSearch);
  StatusHelp_QLCB();

  n_page = 1 + ((control.listCB.getSize() - 1) / 10);

  // page and switch page
  int swp =
      SwitchPage(control.dataTabCB.Sw_table_page, control.dataTabCB.current_showPage, n_page,
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});
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

void CreateTable_QLVe()
{
  DrawTextEx(FontArial, "DANH SÁCH VÉ",
             {StartPos.x + 60,
              CenterDataSetter(100, StartPos.y + 60,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);
  float cellW[3] = {100, 200, 400};
  CreateTable({CenterDataSetter(1080, StartPos.x + 60, 700),
               StartPos.y + 60 + 100 + 80},
              3, cellW, 700);
}

void CreatePage_QLHK(UIcontroller &control)
{
  CreatePageBackground(1);
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
              CenterDataSetter(100, StartPos.y + 50,
                               MeasureTextEx(FontArial, "A", 50, 0).y)},
             50, 0, BLUE);

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

    button[0].tittle = "Sửa thông tin";
    if (CreateButton(button[0]))
    {
      control.dataTabHK.current_popup = 1;
      strcpy(control.dataTabHK.i_Ho.name, strToChar(control.dataTabHK.data->getHK().getHo()));
      control.dataTabHK.i_Ho.letterCount = control.dataTabHK.data->getHK().getHo().length();
      strcpy(control.dataTabHK.i_Ten.name, strToChar(control.dataTabHK.data->getHK().getTen()));
      control.dataTabHK.i_Ten.letterCount = control.dataTabHK.data->getHK().getTen().length();
      control.dataTabHK.i_Phai = control.dataTabHK.data->getHK().getPhai() == "Nu";
    }
    control.dataTabHK.data = XuLy_QLHK(control);
  }
  else if (control.dataTabHK.current_popup == 1)
  {
    if (Popup_HieuChinhHK(control))
      control.dataTabHK.current_popup = 0;
  }
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
  DrawTextEx(
      FontArial, "Sửa thông tin hành khách",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "Sửa thông tin hành khách", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  HanhKhach tmp = control.dataTabHK.data->getHK();

  string o_Ho, o_Ten;

  const int hFont40_25 = MeasureTextEx(FontArial, "A", 40, 0).y -
                         MeasureTextEx(FontArial, "A", 25, 0).y;
  DrawTextEx(FontArial, "CMND / CCCD",
             {StartPos.x + 300, StartPos.y + 60 + 230 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Không được chỉnh sửa!)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 230 + 10 + hFont40_25},
             25, 0, RED);
  DrawTextEx(FontArial, "Họ và tên",
             {StartPos.x + 300, StartPos.y + 60 + 330 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Gồm chữ cái và kí tự)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 330 + 10 + hFont40_25},
             25, 0, RED);

  DrawTextEx(FontArial, "Phái",
             {StartPos.x + 300, StartPos.y + 60 + 430 + 10}, 40, 0, BROWN);
  DrawTextEx(FontArial, "(Nhấn vào để chọn)",
             {StartPos.x + 300 + 300, StartPos.y + 60 + 430 + 10 + hFont40_25},
             25, 0, RED);

  TextBox s_CMND;
  s_CMND.box = control.dataTabHK.i_CMND.textBox;
  s_CMND.showBox = true;
  s_CMND.text = strToChar(tmp.getCmnd());
  CreateTextBox(s_CMND);

  o_Ho = CreateTextInputBox(control.dataTabHK.i_Ho);
  o_Ten = CreateTextInputBox(control.dataTabHK.i_Ten);

  TextBox tb_Phai;
  tb_Phai.box = {StartPos.x + 300, StartPos.y + 60 + 480, 150, 50};
  tb_Phai.showBox = true;
  tb_Phai.isCenter = true;
  tb_Phai.mode = Auto;
  tb_Phai.text = (char *)"Chưa chọn";

  if (control.dataTabHK.i_Phai == 0)
    tb_Phai.text = (char *)"Nam";
  else if (control.dataTabHK.i_Phai == 1)
    tb_Phai.text = (char *)"Nữ";
  CreateTextBox(tb_Phai);

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
    if (control.dataTabHK.i_Ho.letterCount < 1 || control.dataTabHK.i_Ten.letterCount < 1 || control.dataTabHK.i_Phai < 0)
    {
      control.dataTabCB.popup_errorMess = "Chưa nhập đủ thông tin!";
      return false;
    }

    tmp.setHo(o_Ho);
    tmp.setTen(o_Ten);
    tmp.setPhai(control.dataTabHK.i_Phai);

    control.dataTabHK.data->setHK(tmp);

    resetInputTextBox(control.dataTabHK.i_CMND);
    resetInputTextBox(control.dataTabHK.i_Ho);
    resetInputTextBox(control.dataTabHK.i_Ten);
    control.dataTabHK.i_Phai = -1;
    ReloadData(control);
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

void ShowListHK(HanhKhach hanhKhach, Vector2 start_pos, float *cellW, int &j, int order)
{
  TextBox show[5];
  const char *showText[5] = {0};
  showText[0] = intToChar(order + 1, 0);
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

  int i = (control.dataTabHK.current_page - 1) * 10;

  int j = 0;

  NodeHK *root = control.listHK.getRoot();

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
        control.dataTabHK.data = currNode;

      ShowListHK(currNode->getHK(), start_pos, cellW, j, order);
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
                 {StartPos.x + 60 + 680 + 160, StartPos.y + 60 + 100 + 80 + 450 + 5});
  if (control.dataTabHK.current_page != swp)
    control.dataTabHK.pickdata_index = -1;
  control.dataTabHK.current_page = swp;
  if (control.dataTabHK.current_page > n_page)
    control.dataTabHK.current_page = 1;
  return control.dataTabHK.data;
}

void CreatePage_GioiThieu() { CreatePageBackground(0); }

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
                      const char *cell_tittle[]) // #Didn't clean memory
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
  if (control.req_swTab)
  {
    if (UI_reqSwitchTab(control))
    {
      control.req_swTab = false;
    }
    else
      return;
  }
  const int button_width = 480;
  const int button_height = 50;

  char *button_tittle[3];
  button_tittle[0] = (char *)"QUẢN LÝ MÁY BAY",
  button_tittle[1] = (char *)"QUẢN LÝ CHUYẾN BAY",
  button_tittle[2] = (char *)"QUẢN LÝ HÀNH KHÁCH";

  Vector2 buttonPos[4] = {{StartPos.x, StartPos.y},
                          {buttonPos[0].x + 60, StartPos.y},
                          {buttonPos[1].x + button_width, StartPos.y},
                          {buttonPos[2].x + button_width, StartPos.y}};
  Button button[4];
  button[0].x = buttonPos[0].x;
  button[0].y = buttonPos[0].y;
  button[0].w = 60;
  button[0].h = button_height;
  button[0].BoTron = false;
  button[0].gotNothing = false;
  button[0].gotPic = true;
  button[0].picture = PNG_home;
  button[0].BoMau = MauThanhQuanLy;
  for (int i = 1; i < 4; i++)
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
  {
    control.next_tab = 0;
    control.req_swTab = true;
  }
  for (int i = 1; i < 4; i++)
  {
    if (control.current_tab != i)
    {
      if (CreateButton(button[i]))
      {
        control.next_tab = i;
        control.req_swTab = true;
      }
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
bool Warning_searchFail()
{
  ClearBackground(DARKBLUE);
  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400, StartPos.y + 300, 700, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "KHÔNG CÓ DỮ LIỆU!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "KHÔNG TÌM THẤY CHUYẾN BAY!", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "Không tồn tại bất kì chuyến bay nào thoả các đièu kiện trên!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);

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

int Warning_Confirm_HuyVe()
{
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

bool Warning_Full()
{
  CreatePopupBackground();
  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400 - 150, StartPos.y + 300, 1000, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "BẠN KHÔNG THỂ THÊM MÁY BAY!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "BẠN KHÔNG THỂ THÊM MÁY BAY!", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "- Danh sách máy bay đã đầy!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);

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

bool Warning_Empty()
{
  CreatePopupBackground();
  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400 - 150, StartPos.y + 300, 1000, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "CẢNH BÁO!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "CANH BAO!", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  DrawTextEx(
      FontArial, "BẠN KHÔNG THỂ THÊM CHUYẾN BAY!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "BẠN KHÔNG THỂ THÊM CHUYẾN BAY!", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "- Danh sách máy bay trống!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);

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

int Warning_SwitchTab()
{
  CreatePopupBackground();

  DrawRectangle(StartPos.x + 150, StartPos.y + 280, 1200, 330,
                {246, 250, 170, 255});
  DrawRectangle(StartPos.x + 400, StartPos.y + 300, 700, 70,
                {255, 43, 43, 255});
  DrawTextEx(
      FontArial, "CẢNH BÁO!",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "CANH BAO!", 50, 0).x),
       CenterDataSetter(60, StartPos.y + 60 + 10,
                        MeasureTextEx(FontArial, "A", 50, 0).y)},
      50, 0, BLACK);
  DrawTextEx(
      FontArial, "CHUYỂN TAB?",
      {CenterDataSetter(700, StartPos.x + 400,
                        MeasureTextEx(FontArial, "CHUYEN TAB?", 55, 0).x),
       CenterDataSetter(70, StartPos.y + 300,
                        MeasureTextEx(FontArial, "A", 55, 0).y)},
      55, 0, WHITE);
  DrawTextEx(FontArial, "Toàn bộ thao tác chỉnh sửa của bạn sẽ bị huỷ!",
             {StartPos.x + 200, StartPos.y + 375}, 55, 0, BLACK);

  Button OK;
  OK.x = StartPos.x + 225 + 750;
  OK.y = StartPos.y + 60 + 625;
  OK.w = 300;
  OK.h = 50;
  OK.gotNothing = false;
  OK.gotText = true;
  OK.tittle = (char *)"Vẫn chuyển tab";
  OK.font = FontArial;
  OK.BoMau = ArrowKey;

  Button Cancel;
  Cancel.x = StartPos.x + 225;
  Cancel.y = StartPos.y + 60 + 625;
  Cancel.w = 300;
  Cancel.h = 50;
  Cancel.gotNothing = false;
  Cancel.gotText = true;
  Cancel.tittle = (char *)"Quay lại";
  Cancel.font = FontArial;
  Cancel.BoMau = ArrowKey;

  if (CreateButton(OK))
  {
    return 1;
  }

  if (CreateButton(Cancel))
  {
    return -1;
  }
  return 0;
}

// ---Các hàm hỗ trợ ngoài vìa------------------------------------------------------------------------------------------------------

// Trả về vị trí bắt đầu của obj trên 1 khung (hình 1 chiều)
float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua,
                       float obj_width)
{
  return doDai_khung_chua / 2.0f + vi_tri_khung_chua - obj_width / 2.0f;
}

int SwitchPage(PageSwitcher &data, int current_page, int n_page, Vector2 pos)
{
  Rectangle pg1 = {pos.x + 50 + 2, pos.y, 70 - 4, 50};
  Rectangle pg2 = {pos.x + 50 + 70 + 2, pos.y, 70 - 4, 50};
  int status = 0;
  int page_n = current_page;

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

  button[1].x = pos.x + 50 + 140 + 10;
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
    DrawRectangle(pos.x + 12, pos.y + 10, 30, 30, ArrowKey.isPressed);
    DrawTexture(PNG_arrowLeft, pos.x + 10 + 2, pos.y + 10, ArrowKey.isPressed);
  }

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
    DrawRectangle(pos.x + 50 + 140 + 10, pos.y + 10, 30, 30,
                  ArrowKey.isPressed);
    DrawTexture(PNG_arrowRight, pos.x + 50 + 140 + 10, pos.y + 10,
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
  data.fast_switcher.mode = Numeric;
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
    DrawRectangleRounded(Button, 0.5f, 0, data.BoMau.isPressed);
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

  if (data.BoTron)
  {
    if (!data.gotNothing)
      DrawRectangleRounded(Button, 0.5f, 0, data.BoMau.isnotHovered);
    if (data.gotText)
      DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                 data.BoMau.text1);
    else if (data.gotPic)
      DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                    data.BoMau.isnotHovered);
    if (data.firstRounder)
      DrawRectangleRoundedLines(Button, 0.5f, 0, 2, data.BoMau.Rounder);
    MousePos = GetVMousePosition();

    if (CheckCollisionPointRec(MousePos, Button))
    {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      {
        if (!data.gotNothing)
          DrawRectangleRounded(Button, 0.5f, 0, data.BoMau.isPressed);
        if (data.gotText)
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text2);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0, 2,
                                  data.BoMau.RounderPressed);
      }
      else
      {
        if (!data.gotNothing)
          DrawRectangleRounded(Button, 0.5f, 0, data.BoMau.isHovered);
        if (data.gotText)
          DrawTextEx(data.font, data.tittle, TextPos, data.h / 2.0f, 0,
                     data.BoMau.text1);
        else if (data.gotPic)
          DrawTextureEx(data.picture, {data.x, data.y}, 0, 1,
                        data.BoMau.isnotHovered);
        DrawRectangleRoundedLines(Button, 0.5f, 0, 2,
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
        DrawRectangleRoundedLines(Button, 0.5f, 0, 2,
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
        DrawRectangleRoundedLines(Button, 0.5f, 0, 2,
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

const char *CreateTextInputBox(InputTextBox &data) // #Didn't clean memory: resuilt
{
  // Xu ly
  Rectangle showBox = data.textBox;
  char name_cpy[data.size] = "\0";
  char *result = new char[data.size];
  const int font_size = data.textBox.height * per1000(700);

  // Graphic
  Vector2 textBoxPos = {
      data.textBox.x + 10,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, data.name, font_size, 0).y)};

  // show text
  if (data.mouseClickOnText)
  {
    if (showBox.width < MeasureTextEx(FontArial, data.name, font_size, 0).x + 25)
    {
      showBox.width = MeasureTextEx(FontArial, data.name, font_size, 0).x + 25;
    }
  }

  DrawRectangleRec(showBox, data.MauNen);
  DrawRectangleRoundedLines(showBox, 0, 1, 2, data.MauVien);

  if (data.name[0] != '\0')
  {
    if (data.mouseClickOnText)
    {
      DrawTextEx(FontArial, data.name, textBoxPos, font_size, 0, data.MauChu);
    }
    else
    {
      TextBox showText;
      showText.box = data.textBox;
      showText.fontSize = font_size;
      showText.text = data.name;

      CreateTextBox(showText);
    }
  }
  else
  {
    Vector2 tPos = textBoxPos;
    tPos.x -= 5;
    DrawTextEx(FontArial, data.tittle, tPos, font_size, 0, BROWN);
  }

  // disable
  if (!data.isActive)
  {
    return "\0";
  }

  strcpy(name_cpy, data.name);
  name_cpy[data.letterCount + data.indexPoint] = '\0';

  Vector2 textBoxDot = {
      data.textBox.x + 10 + MeasureTextEx(FontArial, name_cpy, font_size, 0).x,
      CenterDataSetter(data.textBox.height, data.textBox.y,
                       MeasureTextEx(FontArial, name_cpy, font_size, 0).y) -
          per1000(50) * font_size};

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
  else if (!CheckCollisionPointRec(GetVMousePosition(), showBox) &&
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
  if (data.mode == Year)
  {
    if (data.letterCount == 4)
      data.returnIfDone = false;
    else
      data.returnIfDone = true;
  }
  if (data.mode == Day || data.mode == Month)
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
  if (box.fontSize <= 0)
    box.fontSize = (box.box.height * 2) / 3;

  Vector2 textpos = {
      box.box.x + 10,
      CenterDataSetter(box.box.height, box.box.y,
                       MeasureTextEx(FontArial, "a", box.fontSize, 0).y)};

  char showtext[40] = {0};

  if (box.showBox)
  {
    DrawRectangleRec(box.box, box.MauNen);
    DrawRectangleRoundedLines(box.box, 0, 0, 2, box.MauVien);
  }

  if (MeasureTextEx(FontArial, box.text, box.fontSize, 0).x + 20 < box.box.width)
  {
    text_w = MeasureTextEx(FontArial, box.text, box.fontSize, 0).x;
    strcpy(showtext, box.text);
  }
  else if (box.mode == AntiLeak)
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
  else if (box.mode == Auto)
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
  if (box.mode == AntiLeak && CheckCollisionPointRec(GetVMousePosition(), box.box) &&
      MeasureTextEx(FontArial, box.text, box.fontSize, 0).x + 20 >=
          box.box.width)
  {
    Rectangle fullBox = {box.box.x + 3, box.box.y + 3,
                         MeasureTextEx(FontArial, box.text, box.fontSize, 0).x +
                             20,
                         box.box.height - 6};

    DrawRectangleRec(fullBox, box.MauNen);
    DrawRectangleRoundedLines(fullBox, 0, 0, 2, box.MauVien);

    textpos.x =
        CenterDataSetter(fullBox.width, fullBox.x,
                         MeasureTextEx(FontArial, box.text, box.fontSize, 0).x);
    DrawTextEx(FontArial, box.text, textpos, box.fontSize, 0, box.MauChu);
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
  main.listCB = DsChuyenBay();
  main.listMB = DsMayBay();
  main.listHK = DsHanhKhach();
  getDataFromFile(main.listCB, main.listMB, main.listHK);

  // Settup for before run graphics
  SetExitKey(0); // Disable exit key
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(700, 400);
  SetSizeWindow();

  LoadResources();

  SetTargetFPS(20); // max framerate per second set to 20

  main.renderTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT); // Load nội dung màn hình như một ảnh
  GenTextureMipmaps(&main.renderTexture.texture);
  SetTextureFilter(main.renderTexture.texture, TEXTURE_FILTER_BILINEAR);
  int ScreenW = GetScreenWidth(), ScreenH = GetScreenHeight();

  TextBox showCurrTime;
  Date CurrTime;
  showCurrTime.box = {15, 780, 200, 40};
  CurrTime.setToNow();
  showCurrTime.text = strToChar(CurrTime.printDateHour());

  // Graphics in running
  while (!WindowShouldClose())
  {
    // Full screen
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
      int display = GetCurrentMonitor();

      if (IsWindowFullscreen())
      {
        SetWindowSize(ScreenW, ScreenH);
      }
      else
      {
        SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        GenTextureMipmaps(&main.renderTexture.texture);
        SetTextureFilter(main.renderTexture.texture, TEXTURE_FILTER_BILINEAR);
      }

      ToggleFullscreen();
    }

    if (IsWindowFullscreen() && IsKeyPressed(KEY_ESCAPE))
    {
      ToggleFullscreen();
      SetWindowSize(ScreenW, ScreenH);
    }

    // Make all texture smooth
    if (!IsWindowFullscreen())
    {
      if (ScreenW != GetScreenWidth() || ScreenH != GetScreenHeight())
      {
        GenTextureMipmaps(&main.renderTexture.texture);
        SetTextureFilter(main.renderTexture.texture, TEXTURE_FILTER_BILINEAR);
        ScreenW = GetScreenWidth();
        ScreenH = GetScreenHeight();
      }
    }
    BeginTextureMode(main.renderTexture);

    // Các thao tác trên đồ hoạ
    if (!main.req_swTab)
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
        CreatePage_QLHK(main);
        break;
      }
      case 4:
      {
        CreatePage_GioiThieu();
        break;
      }
      default:
      {
        main.current_tab = 0;
      }
      }

    if (main.current_tab != 0)
      ThanhQuanLy(main);

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
    CreateTextBox(showCurrTime);
    EndTextureMode();

    BeginDrawing();
    // xuất màn hình tĩnh theo chỉ sô động6
    DrawTexturePro(main.renderTexture.texture,
                   Rectangle{0, 0,
                             static_cast<float>(main.renderTexture.texture.width),
                             static_cast<float>(-main.renderTexture.texture.height)},
                   Rectangle{0, 0, static_cast<float>(GetScreenWidth()),
                             static_cast<float>(GetScreenHeight())},
                   Vector2{0, 0}, 0, WHITE);
    EndDrawing();

    // Update realtime
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ltm->tm_sec < 2)
    {
      if (main.listCB.update(main.listMB))
      {
        ReloadData(main);
      }
      CurrTime.setToNow();
      showCurrTime.text = strToChar(CurrTime.printDateHour());
    }
  }

  // Clear all data after run graphics
  main.listMB.deleteDsMB();
  main.listHK.deleteDs();
  main.listCB.deleteDs();
  UnloadRenderTexture(main.renderTexture);
  UnloadResources();
}
