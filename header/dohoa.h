#pragma once

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"
#include "queue.h"
#include <list>

// Kích thước cửa sổ mặc định
#define WINDOW_WIDTH 1530
#define WINDOW_HEIGHT 820

// kích thước màn hình làm việc mặc định
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 750

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

void UI_switchTab(UIcontroller &control);
void InitUIData(UIcontroller &control);

void LoadResources();
void UnloadResources();
void SetSizeWindow(); // done

void CreateHomeBackground();                // done
void CreateHomePage(UIcontroller &control); // done

void CreatePageBackground(int SoHang); // done

void resetData_QLMB(QLMB_data &data);
void CreatePage_QLMB(DsMayBay &listMB, QLMB_data &tabMB_data);
MayBay *XuLy_QLMB(DsMayBay &listMB, QLMB_data &tabMB_data);
void CreateTable_QLMB();

void resetData_QLCB(QLCB_data &data);
void CreatePage_QLCB(DsChuyenBay &listCB, QLCB_data &tabCB_data);
NodeCB *XuLy_QLCB(DsChuyenBay &listCB, QLCB_data &tabCB_data);
void CreateTable_QLCB();
void StatusHelp_QLCB();

void resetData_QLDSVe(QLVe_data &data);
void CreatePage_QLVe();
void CreateTable_QLVe();
void XuLy_QLVe(QLCB_data &tabCB_data);

void resetData_QLHK(QLHK_data &data);
void CreatePage_QLHK(DsHanhKhach &listHK, QLHK_data &tabHK_data);
void CreateTable_QLHK();
NodeHK *XuLy_QLHK(DsHanhKhach &listHK, QLHK_data &tabHK_data);

void CreatePage_GioiThieu();

void CreatePopupBackground();
bool Popup_ThemMB(DsMayBay &listMB, QLMB_data &tabMB_data);
bool Popup_HieuChinhMB(DsMayBay &listMB, QLMB_data &tabMB_data);
bool Popup_XoaMB(DsMayBay &listMB, QLMB_data &tabMB_data);
bool Popup_Thongkesoluotbay(DsMayBay &listMB, QLMB_data &tabMB_data);
bool Popup_ThemHK(DsHanhKhach &listHK);
bool Popup_ThemCB(DsChuyenBay &listCB, QLCB_data &tabCB_data);
bool Popup_HieuChinhCB(DsChuyenBay &listCB, QLCB_data &tabCB_data);
bool Popup_XoaCB(DsChuyenBay &listCB, QLCB_data &tabCB_data);
void Popup_getMB(DsChuyenBay listCB, QLCB_data &tabCB_data, Date gioBay);

void ThanhQuanLy(UIcontroller &control); // done
bool Warning_NoData();
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
int SwitchPage(int current_page, int n_page, Vector2 pos);
bool CreateButton(Button data);
const char *CreateTextInputBox(InputTextBox &data);
void resetInputTextBox(InputTextBox &box);
void CreateTextBox(TextBox box);

Vector2 GetVMousePosition(); // done
void mainGraphics();
