#pragma once

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"

// Kích thước cửa sổ mặc định
#define WINDOW_WIDTH 1530
#define WINDOW_HEIGHT 820

// kích thước màn hình làm việc mặc định
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 750

struct BoMauNut;

void LoadResources();
void UnloadResources();
void SetSizeWindow(); // done

void CreateHomeBackground(); // done
void CreateHomePage();       // done

void CreatePageBackground(int SoCot); // done

void CreatePage_QLMB(DSMB listMB);
void XuLy_QLMB(DSMB listMB);
void CreateTable_QLMB();
void showList_QLMB(DSMB listMB, Vector2 start_pos, int current_page, float cellW[]);

void CreatePage_QLCB();
void CreateTable_QLCB();

void CreatePage_QLVe();
void CreateTable_QLVe();

void CreatePage_QLHK();
void XuLy_QLHK(DSMB listHK);
void CreateTable_QLHK();

void CreatePage_GioiThieu();

void ThanhQuanLy(); // done
void CreateTable(Vector2 viriBang, int soCot, float cellW[], float total_cellW);
void DrawLineTable(float pos_x, float pos_y, int soCot, float cellW[], float cellH);
Vector2 *GetTittlePos(Vector2 vitriBang, int soCot, float cellW[], const char *cell_tittle[]);
Vector2 GetCellTextPos_Left(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y);
Vector2 GetCellTextPos_Mid(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text);
Vector2 GetCellTextPos_Right(Vector2 vitriBang, int soCot, float cellW[], int vi_tri_x, int vi_tri_y, const char *text);

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua, float obj_width); // done
int SwitchPage(int current_page, int n_page, Vector2 pos);
bool CreateButton(float pos_x, float pos_y, float width, float height, bool BoTron, const char *titlle, Font font, BoMauNut BoMau); // done
bool CreateButtonWithPicture(float pos_x, float pos_y, float width, float height, bool BoTron, Texture2D Picture, BoMauNut BoMau);  // done
const char *CreateTextInputBox(Vector2 pos, float width,
                               float height, const char *tittle,
                               bool showPreResult, bool returnIfDone,
                               Color MauSac, Color MauVien, Color MauChu);
// const char *CreateTextInputBox(Vector2 pos, float width, float height, const char *tittle, bool showPreResult, Color MauSac, Color MauVien, Color MauChu);

Vector2 GetVMousePosition();          // done
char *intTochar(int value, int size); // done
float per1000(int number);            // done

void mainGraphics();
