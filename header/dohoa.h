#pragma once
#include "header.h"
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

void CreatePageBackground(); // done

void CreatePage_QLMB();
void CreateTable_QLMB();

void CreatePage_QLCB();
void CreateTable_QLCB();

void CreatePage_QLVe();
void CreateTable_QLVe();

void CreatePage_QLHK();
void CreateTable_QLHK();

void CreatePage_GioiThieu();

void ThanhQuanLy(); // done
void CreateTable(int soCot, float cellW[]);
void DrawLineTable(float pos_x, float pos_y, int soCot, float cellW[], float cellH);

float CenterDataSetter(float doDai_khung_chua, float vi_tri_khung_chua, float obj_width);                                           // done
bool CreateButton(float pos_x, float pos_y, float width, float height, bool BoTron, const char *titlle, Font font, BoMauNut BoMau); // done
bool CreateButtonWithPicture(float pos_x, float pos_y, float width, float height, bool BoTron, Texture2D Picture, BoMauNut BoMau);  // done
const char *CreateTextInputBox();
Vector2 GetVMousePosition(); // done
float per1000(int number);   // done

void mainGraphics();
