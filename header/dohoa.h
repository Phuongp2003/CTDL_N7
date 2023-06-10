#pragma once

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "queue.h"
#include "vemaybay.h"
#include <list>

struct BoMauNut;
/**
 * @brief chứa câu trúc nút
 *
 *
 * @param BoTron bo tròn các góc (mặc định false)
 * @param gotNothing chỉ vẽ phần viền (mặc định true)
 * @param gotText hiện chũ (mạc định false)
 * @param gotPic hiện ảnh (mặc định false)
 *
 * @note text: tittle, font
 * @note pic: picture
 * @note default: x, y, w, h, BoMau
 *
 * @warning ba biến gotNothing, gotText, gotPic chỉ có 1 biến nhận true;
 * @warning Độ ưu tiên: (trống thông tin > có ảnh > có chữ)
 *
 */
struct Button;

/**
 * @brief tạo ô nhập kí tự
 *
 * @warning chữ luôn in hoa
 * @warning editMode yêu cầu tittle phải là kí tự không dấu
 *
 * @param not_default textBox, tittle, mode(1)
 * @param size mặc định là 27
 * @param showNKeyRemain hiện số kí tự còn có thể nhập (mặc định true)
 * @param editMode nhận giá trị từ tittle và chỉnh sửa (mặc định false)
 * @param showPreResult giữ kết quả đã nhập sau khi thoát box (mặc định true)
 * @param returnIfDone chỉ return kết quả khi nhấn enter (mặc định false)
 * @param MauNen mặc định: trắng
 * @param MauChu mặc định: đen
 * @param MauVien mặc định: đen
 * @param mode (1 - chữ, số và kí tự) (2 - chỉ chữ và số) (3 - chỉ chữ IN HOA và
 * số) (4 - chỉ chữ) (5 - chỉ số) (6-7-8-9-10 dd-mm-yyyy-hh-mm)
 *
 */
struct InputTextBox;
/**
 * @brief tạo ô hiện kí tự, chống tràn chữ
 *
 * @param text The text to show
 * @param box ô chứa
 * @param showBox hiện ô chứa (mặc định false)
 * @param mode chế độ hiển thị (1<mặc định> - Chống tràn, 2 - Tự căn)
 * @param isCenter căn giữa (mặc định không)
 * @param fontsize cỡ chữ (mặc định bằng 2/3 độ cao ô)
 */
struct TextBox;
struct UIcontroller;
struct QLMB_data;
struct QLCB_data;
struct QLHK_data;
struct QLVe_data;
struct PageSwitcher;

struct BoMauNut
{
    Color isnotHovered;   // Trạng thái bth
    Color isHovered;      // Được trỏ vào
    Color isPressed;      // Được nhấn vào
    Color text1;          // Màu chữ 1 (màu bth)
    Color text2;          // Màu chữ 2 (có thao tác tác động lên)
    Color Rounder;        // Màu viền
    Color RounderHovered; // Màu viền khi được trỏ vào
    Color RounderPressed; // Màu viền khi nhấn vào
};

struct Button
{
    bool isActive = true; // Chỉ in ra nếu bị disable

    float x;
    float y;
    float w;
    float h;
    bool BoTron = false;             // Vễ bo tròn
    bool gotNothing = true;          // Nút trống (chỉ có viền và màu)
    bool gotText = false;            // Chứa chữ, y/c gotNothing = false
    const char *tittle = "";         // Tiều đề nút
    Font font;                       // Font chữ cho nút
    bool gotPic = false;             // Chứa hình, y/c gotNothing = false
    Texture2D picture;               // Hình trong nút
    bool RounderChangeColor = false; // Màu viền thay đổi khi được thao tác
    bool firstRounder = true;        // In viền
    BoMauNut BoMau;
};

struct InputTextBox
{
    bool isActive = true;   // Chỉ in nội dung nếu bị disable
    bool isGotData = false; // Đang chứa dữ liệu được truyền trực tiếp (tiền xử lý)

    Rectangle textBox;
    const char *tittle = "";    // Tiêu đề ô nhập
    int size = 27;              // Số kí tự được nhập tối đa
    bool showNKeyRemain = true; // Hiện số kí tự được nhập còn lại
    bool editMode = false;      // Nhận tiêu đề để chỉnh sửa
    bool showPreResult = true;  // Hiện kết quả đã nhập trước đó
    bool returnIfDone = false;  // Chỉ nhận giá trị khi nhấn enter
    Color MauNen = WHITE;
    Color MauVien = BLACK;
    Color MauChu = BLACK;
    int mode = ASCII2; // Chi tiết xem hàm chuanHoaKey (tool.cpp)

    // xử lý
    char name[120] = "\0";                             // xâu được xử lý
    int fHold_BS = 0, fHold_RIGHT = 0, fHold_LEFT = 0; // Thời gian giữ nút (đơn vị là 1/20 giây, với max FPS = 20)
    bool done = true;                                  // Đã nhận nút enter
    bool mouseClickOnText = false;                     // Đang được thao tác
    int letterCount = 0;                               // số kí tự đã nhập
    int framesCounter = 0;                             // số frames đã được in ra (chi tiết tìm hiểu về FPS)
    int indexPoint = 0;                                // vị trí con trỏ so với kí tự cuối cùng
};

struct TextBox
{
    const char *text;      // Xâu xuất
    Rectangle box;         // Giá trị ô xuát
    bool showBox = false;  // Hiện ô xuất
    int mode = ASCII2;          // Hiện thêm ô (1) / Thu nhỏ chữ (2)
    bool isCenter = false; // Căn giữa
    int fontSize = 0;      // Cỡ chữ
};

struct PageSwitcher
{
    bool editmode = false;      // Trạng thái chế độ ô nhập
    InputTextBox fast_switcher; // Ô nhập để chuyển trạng thái nhanh
};

struct QLMB_data
{
    MayBay *data = nullptr; // Giá trị của MB được chọn (qua index)
    int status = 0;         // Trạng thái index (1 - sau khi thêm, -1 - sau khi xoá)

    int current_popup = 0;                    // popup được mở
    string popup_errorMess = "";              // lỗi ở các popup đang chờ được xâu
    int time_showError = 0;                   // thời gian đã hiện lỗi (tối đa đến 99)
    InputTextBox MaMB, LoaiMB, SoDong, SoDay; // các ô nhập ở các popup

    int pickdata_index = -1;    // Vị trí của index
    const char *keyword;        // Từ khoá (tìm kiếm)
    InputTextBox searchKeyword; // Ô nhập của tìm kiếm
    int current_showPage = 1;   // Trang hiến tại (ds máy bay)

    PageSwitcher Sw_table_page; // Chuyển trang
};

struct QLHK_data
{
    NodeHK *data = nullptr; // Địa chỉ của node hành khách được trở vào

    int current_popup = 0;       // Popup được mở
    string popup_errorMess = ""; // Lỗi ở các popup
    int time_showError = 0;      // Thời gian hiện lỗi (tối đa 99)

    int pickdata_index = -1; // Vị trí của index
    int current_page = 1;    // Trang hiện tại (ds hành khách)

    InputTextBox i_CMND, i_Ho, i_Ten; // Ô nhập thông tin
    int i_Phai = -1;                  // Thông tin phái

    PageSwitcher Sw_table_page; // Chuyển trang
};

struct QLVe_data
{
    int current_page = 1;       // Trang hiện tại
    int position = -1;          // Vị trí vé đã chọn trong ds vé
    int pickdata_index = -1;    // Vị trí vé (DSve đã đặt của cbay)
    VeMayBay data = VeMayBay(); // Vé được pick

    bool showNotEmpty = false; // Hiện vé đã đặt
    bool inDelete = false;     // Có thao tác huỷ vé được kích hoạt

    PageSwitcher Sw_table_page; // Chuyển trang
};

struct QLCB_data
{
    NodeCB *data = nullptr; // Địa chỉ của node chuyến bay được chọn
    int status = 0;         // Trạng thái index (1 - sau khi thêm)

    int current_popup = 0;                                        // Popup đang mở
    string popup_errorMess = "";                                  // Lỗi ở các Popup
    int time_showError = 0;                                       // Thời gian hiên lỗi (tối đa 99)
    InputTextBox MaCB, MaMB, NoiDen, Ngay, Thang, Nam, Gio, Phut; // Ô nhập dữ liệu
    bool inChooseMB = false;                                      // Bảng chọn máy bay trong thêm/hiệu chỉnh CBay được kích hoạt
    QLVe_data dataDSVe;                                           // Dữ liệu của các thao tác trên vé

    InputTextBox searchMaCB, searchNoiDen; // Ô nhập dữ liệu tìm kiếm
    int pickdata_index = -1;               // Vị trí index
    int current_showPage = 1;              // Trang hiện tại

    bool inSearching = false;         // Popup nhập dữ liệu tìm kiếm
    bool inAdvSearch = false;         // Dữ liệu được lọc theo giá trị tìm kiếm
    Date fbDay = Date(1, 1, 0, 0, 0); // Tìm theo ngày
    string fbNoiDen = "";             // Tìm theo nơi đến
    bool fbAvail = false;             // Lọc chuyến bay không khả dụng
    bool inGetTicket = false;         // Popup chọn vé
    bool inSetTicket = false;         // Popup đặt vé
    bool gotChangeTicket = false;     // Có thao tác trên vé

    PageSwitcher Sw_table_page; // Chuyển trang
};

struct UIcontroller
{
    RenderTexture2D renderTexture; // Dữ liệu của cảnh được in

    int current_tab = 0; // Tab hiện tại (Home / MayBay / ChuyenBay / HanhKhach)
    int next_tab = 0;    // Tab sắp chuyển dến
    QLMB_data dataTabMB; // Dữ liệu tab Máy bay và các dữ liệu được thao tác trên MB
    QLCB_data dataTabCB;
    QLHK_data dataTabHK;

    DsMayBay listMB; // Danh sách máy bay
    DsChuyenBay listCB;
    DsHanhKhach listHK;

    bool req_swTab = false; // Có yêu cầu chuyển tab
};
void setDataToFile(UIcontroller &control);
void getDataFromFile(UIcontroller &control);

void CreateLoadingScreen();

void SetDataInputTextBox(InputTextBox &box, const char *text, int length);
void ResetDataInputTextBox(InputTextBox &box);
void resetPageSwitcher(PageSwitcher &thisdata);
void initPageSwitcher(PageSwitcher &thisdata);
void initQLMBdata(QLMB_data &thisdata);
void initQLHKdata(QLHK_data &thisdata);
void initQLVedata(QLVe_data &thisdata);
void initQLCBdata(QLCB_data &thisdata);

bool UI_reqSwitchTab(UIcontroller &control, int idTab);
void UI_switchTab(UIcontroller &control);
void InitUIData(UIcontroller &control);

void LoadResources();
void UnloadResources();
void SetSizeWindow(); // done

void CreateHomeBackground();                // done
void CreateHomePage(UIcontroller &control); // done

void CreatePageBackground(int SoHang); // done

void resetData_QLMB(QLMB_data &data);
void CreatePage_QLMB(UIcontroller &control);
MayBay *XuLy_QLMB(UIcontroller &control);
void CreateTable_QLMB();

void resetData_QLCB(QLCB_data &data);
void CreatePage_QLCB(UIcontroller &control);
int ShowListCB(UIcontroller &control, int first, const char *textMaCB, bool inFill);
NodeCB *XuLy_QLCB(UIcontroller &control);
void CreateTable_QLCB();
void StatusHelp_QLCB();

void resetData_QLVe(QLVe_data &data);
void CreatePage_QLVe();
void CreateTable_QLVe();

void resetData_QLHK(QLHK_data &data);
void CreatePage_QLHK(UIcontroller &control);
void CreateTable_QLHK();
NodeHK *XuLy_QLHK(UIcontroller &control);

void CreatePage_GioiThieu();

void CreatePopupBackground();
//-
bool Popup_ThemMB(UIcontroller &control);
bool Popup_HieuChinhMB(UIcontroller &control);
bool Popup_XoaMB(UIcontroller &control);
bool Popup_Thongkesoluotbay(UIcontroller &control);
//-
bool Popup_TimCB(UIcontroller &control);
bool Popup_ThemCB(UIcontroller &control);
bool Popup_HieuChinhCB(UIcontroller &control);
bool Popup_HuyCB(UIcontroller &control);
bool Popup_chonChuyen(UIcontroller &control);
bool Popup_chonVe(UIcontroller &control);
bool Popup_showListHK(UIcontroller &control);
void Popup_getMB(UIcontroller &control, Date gioBay, bool inEdit);
bool Popup_datVe(UIcontroller &control);
//-
bool Popup_QLVe(UIcontroller &control);
bool Popup_HieuChinhHK(UIcontroller &control);

void ThanhQuanLy(UIcontroller &control); // done
bool Warning_NoData();
int Warning_Confirm_HuyVe(); //
bool Warning_Full();
bool Warning_Empty();
int Warning_SwitchTab();
void CreateTable(Vector2 viriBang, int soCot, float cellW[], float total_cellW);
void DrawLineTable(float pos_x, float pos_y, int soCot, float cellW[],
                   float cellH);
Vector2 *GetTittlePos(Vector2 vitriBang, int soCot, float cellW[],
                      const char *cell_tittle[]);
TextBox GetCellTextBox(Vector2 vitriBang, int soCot, float cellW[],
                       int vi_tri_x, int vi_tri_y, const char *text,
                       float fontSize);
Vector2 GetCellPos(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x,
                   int vi_tri_y);

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua,
                       float obj_width); // done
int SwitchPage(PageSwitcher &data, int current_page, int n_page, Vector2 pos);
bool CreateButton(Button data);
const char *CreateTextInputBox(InputTextBox &data);
void resetInputTextBox(InputTextBox &box);
void CreateTextBox(TextBox box);

Vector2 GetVMousePosition(); // done
void mainGraphics();
