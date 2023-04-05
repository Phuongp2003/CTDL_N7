#pragma once

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"
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
 * @param editMode nhận giá trị từ tittle và chỉnh sửa (mặc định false)
 * @param showPreResult giữ kết quả đã nhập sau khi thoát box (mặc định true)
 * @param returnIfDone chỉ return kết quả khi nhấn enter (mặc định false)
 * @param MauNen mặc định: trắng
 * @param MauChu mặc định: đen
 * @param MauVien mặc định: đen
 * @param not_default textBox, tittle, mode
 * @param mode (1 - chữ, số và kí tự) (2 - chỉ chữ và số) (3 - chỉ chữ IN HOA và số) (4 - chỉ chữ) (5 - chỉ số)
 *
 */
struct InputTextBox;

void LoadResources();
void UnloadResources();
void SetSizeWindow(); // done

void CreateHomeBackground(); // done
void CreateHomePage();       // done

void CreatePageBackground(int SoHang); // done

void CreatePage_QLMB(DSMB *listMB);
MayBay *XuLy_QLMB(DSMB *listMB, int &status);
void CreateTable_QLMB();
MayBay **showList_QLMB(DSMB *listMB, Vector2 start_pos, int current_page, float cellW[]);
bool Popup_ThemMB(DSMB *listMB, int &status);
bool Popup_HieuChinhMB(DSMB *listMB, MayBay *mb);
bool Popup_XoaMB(DSMB *listMB, MayBay *mb, int &status);

void CreatePopupBackground();

void CreatePage_QLCB();
void CreateTable_QLCB();

void CreatePage_QLVe();
void CreateTable_QLVe();

void CreatePage_QLHK();
void CreateTable_QLHK();

void CreatePage_GioiThieu();

void ThanhQuanLy(); // done
bool Warning_NoData();
void CreateTable(Vector2 viriBang, int soCot, float cellW[], float total_cellW);
void DrawLineTable(float pos_x, float pos_y, int soCot, float cellW[], float cellH);
Vector2 *GetTittlePos(Vector2 vitriBang, int soCot, float cellW[], const char *cell_tittle[]);
Vector2 GetCellTextPos_Left(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y);
Vector2 GetCellTextPos_Mid(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text);
Vector2 GetCellTextPos_Right(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text);

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua, float obj_width); // done
int SwitchPage(int current_page, int n_page, Vector2 pos);
// bool CreateButton(float pos_x, float pos_y, float width, float height, bool BoTron, const char *titlle, Font font, BoMauNut BoMau); // done
// bool CreateButtonWithPicture(float pos_x, float pos_y, float width, float height, bool BoTron, Texture2D Picture, BoMauNut BoMau);  // done
bool CreateButton(Button data);
const char *CreateTextInputBox(InputTextBox &data);
void resetInputTextBox(InputTextBox &box);

Vector2 GetVMousePosition(); // done
void mainGraphics();