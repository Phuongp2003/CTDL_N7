#include "header/libs.h"
// #include "windows.h"

using namespace std;
int main()
{
     system("chcp 65001");
     Date *date = new Date(10, 38, 14, 3, 2023);
     date->checkNgayGio();

     InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "First Screen");
     mainGraphics();
     CloseWindow();
}
// int main()
// {
//      DSMB *DanhSachMB = new DSMB();
//      MayBay **mb;
//      mb = new MayBay *[10];
//      mb[0] = new MayBay("MB01", "boing", 4, 20);
//      DanhSachMB->Insert_MB(mb[0]);
//      Date *date = new Date[10];
//      for (int i = 0; i < 10; i++)
//      {
//           date[i] = Date(8, 20, 15 + i, 3, 2023);
//      }
//      ChuyenBay **cb;
//      cb = new ChuyenBay *[10];
//      cb[0] = new ChuyenBay("MH01", "Lien Khuong", date[0], "MB01");
//      ChuyenBay *cbp = new ChuyenBay("MH2", "Ha Noi", date[0], "MB01");

//      cb[0]->setDSVeMB(DanhSachMB);
//      cb[0]->showDSVe();
//      cb[0]->ThucHienCB(DanhSachMB);
//      cbp->ThucHienCB(DanhSachMB);
//      cout << endl
//           << "SLB: " << mb[0]->getSoLuotBay() << endl;
//      // system("pause");Segmentation fault
//      InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "First Screen");
//      CreateScreen();
//      CloseWindow();
//      return 0;
// }

// int screenWidth = 1280;
// int screenHeight = 800;

// int main(void)
// {
//      InitWindow(800, 450, "raylib [shapes] example - raylib logo using shapes");

//      // This should use the flag FLAG_FULLSCREEN_MODE which results in a possible ToggleFullscreen() call later on
//      SetWindowState(FLAG_WINDOW_RESIZABLE);

//      // Request a texture to render to. The size is the screen size of the raylib example.
//      RenderTexture2D renderTexture = LoadRenderTexture(screenWidth, screenHeight);

//      while (!WindowShouldClose())
//      {
//           if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
//           {
//                // see what display we are on right now
//                int display_2 = GetCurrentMonitor();

//                if (IsWindowFullscreen())
//                {
//                     // if we are full screen, then go back to the windowed size
//                     SetWindowSize(screenWidth, screenHeight);
//                     cout << GetScreenWidth() << " " << GetScreenHeight() << endl;
//                }
//                else
//                {
//                     // if we are not full screen, set the window size to match the monitor we are on
//                     SetWindowSize(GetMonitorWidth(display_2), GetMonitorHeight(display_2));
//                     cout << GetScreenWidth() << " " << GetScreenHeight() << endl;
//                }

//                // toggle the state
//                ToggleFullscreen();
//           }
//           cout << GetScreenWidth() << " " << GetScreenHeight() << endl;

//           // Instead of using BeginDrawing() we render to the render texture. Everything else stays unchanged
//           BeginTextureMode(renderTexture);
//           ClearBackground(RAYWHITE);
//           DrawRectangle(screenWidth / 2 - 128, screenHeight / 2 - 128, 256, 256, BLACK);
//           DrawRectangle(screenWidth / 2 - 112, screenHeight / 2 - 112, 224, 224, RAYWHITE);
//           DrawText("raylib", screenWidth / 2 - 44, screenHeight / 2 + 48, 50, BLACK);
//           // We need to end the texture mode separately
//           EndTextureMode();

//           // Let's draw the texture. The source rect is the size of the texture, the destination rect is of the same size as the screen. For some reason, the texture was flipped vertically, so I had to invert the source rects "height" to flip the UV.
//           BeginDrawing();
//           DrawTexturePro(
//               renderTexture.texture,
//               Rectangle{0, 0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height)},
//               Rectangle{0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
//               Vector2{0, 0},
//               0,
//               WHITE);
//           EndDrawing();
//      }

//      // Unload the texture handle again to make a clean exit.
//      UnloadRenderTexture(renderTexture);

//      CloseWindow();

//      return 0;
// }
