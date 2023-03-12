#include "libs/libs.h"
#include "raylib.h"
// #include "windows.h"

using namespace std;
void CreateScreen()
{
    Font ARIAL_font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 40, 0, 250);

    char name[120] = "\0";
    char name_cpy[120] = "\0";
    bool mouseOnText = false;
    int letterCount = 0;
    int framesCounter = 0;
    int indexPoint = 0;
    Rectangle textBox = {300, 300, 700, 56};
    Vector2 textBoxPos = {textBox.x + 5, textBox.y + 8};
    Vector2 textBoxPos2 = {textBox.x + 5, textBox.y + 8 + 50};
    while (!WindowShouldClose())
    {
        strcpy(name_cpy, name);
        name_cpy[letterCount + indexPoint] = '\0';
        Vector2 textBoxDot = {textBox.x + MeasureTextEx(ARIAL_font, name_cpy, 40, 0).x, textBox.y + 8};
        if (CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            mouseOnText = true;
        else if (IsKeyPressed(KEY_ENTER))
            mouseOnText = false;

        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (mouseOnText)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 27))
                {
                    for (int i = letterCount; i > letterCount + indexPoint; i--)
                    {
                        name[i] = name[i - 1];
                    }
                    name[letterCount + indexPoint] = char(key);
                    name[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                for (int i = letterCount + indexPoint - 1; i < letterCount; i++)
                {
                    name[i] = name[i + 1];
                }
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                name[letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_LEFT) && (letterCount + indexPoint) > 0)
            {
                indexPoint--;
            }
            if (IsKeyPressed(KEY_RIGHT) && indexPoint < 0)
            {
                indexPoint++;
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 80, 1280, 680, DARKBLUE);
        DrawRectangleRec(textBox, GRAY);
        DrawTextEx(ARIAL_font, name, textBoxPos, 40, 0, BLACK);
        cout << "index: " << indexPoint << endl;
        if (mouseOnText && (((framesCounter / 20) % 2) == 0))
            DrawTextEx(ARIAL_font, "|", textBoxDot, 40, 0, MAROON);

        EndDrawing();
    }
}
// void CreateScreen()
// {
//     Font ARIAL_font = LoadFontEx("C:/Windows/Fonts/arial.ttf", 40, 0, 250);

//     int letterCount = 0;
//     char name[12];
//     Vector2 box = {300, 100};
//     Vector2 boxPos = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
//     Rectangle textBox = {300, 300, 300, 56};
//     bool mouseOnText = false;
//     int framesCounter = 0;
//     while (!WindowShouldClose())
//     {
//         if (CheckCollisionPointRec(GetMousePosition(), textBox))
//             mouseOnText = true;
//         else
//             mouseOnText = false;

//         if (mouseOnText)
//         {
//             SetMouseCursor(MOUSE_CURSOR_IBEAM);
//             int key = GetCharPressed();
//             while (key > 0)
//             {
//                 if ((key >= 32) && (key <= 125) && (letterCount < 9))
//                 {
//                     name[letterCount] = char(key);
//                     name[letterCount + 1] = '\0';
//                     letterCount++;
//                 }

//                 key = GetCharPressed();
//             }
//             if (IsKeyPressed(KEY_BACKSPACE))
//             {
//                 letterCount--;
//                 if (letterCount < 0)
//                     letterCount = 0;
//                 name[letterCount] = '\0';
//             }
//         }
//         else
//             SetMouseCursor(MOUSE_CURSOR_DEFAULT);
//         if (mouseOnText)
//             framesCounter++;
//         else
//             framesCounter = 0;
//         if (IsKeyDown(KEY_UP) && boxPos.y >= 0)
//             boxPos.y -= 2.0f;
//         if (IsKeyDown(KEY_DOWN) && boxPos.y + box.y <= GetScreenHeight())
//             boxPos.y += 2.0f;
//         if (IsKeyDown(KEY_RIGHT) && boxPos.x + box.x <= GetScreenWidth())
//             boxPos.x += 2.0f;
//         if (IsKeyDown(KEY_LEFT) && boxPos.x >= 0)
//             boxPos.x -= 2.0f;

//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         DrawRectangle(0, 80, 1280, 680, DARKBLUE);
//         DrawRectangleRec(textBox, GRAY);
//         DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
//         if (mouseOnText)
//         {
//             if (letterCount < 9)
//             {
//                 if (((framesCounter / 20) % 2) == 0)
//                     DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
//             }
//         }
//         DrawRectangleV(boxPos, box, BLUE);
//         DrawTextEx(ARIAL_font, name, boxPos, 40, 0, DARKGREEN);
//         EndDrawing();
//     }
// }
// int GetCharPressed(void)
// {
//     int value = 0;

//     if (CORE.Input.Keyboard.charPressedQueueCount > 0)
//     {
//         // Get character from the queue head
//         value = CORE.Input.Keyboard.charPressedQueue[0];

//         // Shift elements 1 step toward the head.
//         for (int i = 0; i < (CORE.Input.Keyboard.charPressedQueueCount - 1); i++)
//             CORE.Input.Keyboard.charPressedQueue[i] = CORE.Input.Keyboard.charPressedQueue[i + 1];

//         // Reset last character in the queue
//         CORE.Input.Keyboard.charPressedQueue[CORE.Input.Keyboard.charPressedQueueCount - 1] = 0;
//         CORE.Input.Keyboard.charPressedQueueCount--;
//     }

//     return value;
// }
int main()
{
     // MayBay **mb;
     // mb = new MayBay *[10];
     // for (int i = 0; i < 10; i++)
     // {
     //      mb[i] = new MayBay("MB" + i, "boing" + i, 4 + i, 20 - i);
     // }
     // Date *date = new Date[10];
     // for (int i = 0; i < 10; i++)
     // {
     //      date[i] = Date(8, 20, 15 + i, 3, 2023);
     // }
     // ChuyenBay **cb;
     // cb = new ChuyenBay *[10];
     // for (int i = 0; i < 10; i++)
     // {
     //      cb[i] = new ChuyenBay("MB" + i, "Lien Khuong", date[i], mb[i]);
     // }
     // ChuyenBay *cbp = new ChuyenBay("MH2", "Ha Noi", date[0], mb[0]);

     // cb[0]->setDSVeMB();
     // cb[0]->showDSVe();
     // cb[0]->ThucHienCB();
     // cbp->ThucHienCB();
     // cout << endl
     //      << "SLB: " << mb[0]->getSoLuotBay() << endl;
     // system("pause");
     MayBay MB("MOT","MOT",1,2);
     MayBay MB1("HAI","HAI",2,3);
     DSMB DS;
     DS.Insert_MB(DS,MB);
     DS.Insert_MB(DS,MB1);
     char* SH="HAI";
     if(DS.Find_MB(DS,SH)==-1) cout<<"khong tim thay mb"<<endl;
     else cout<<DS.getMB(DS.Find_MB(DS,SH))<<endl;
     cout<<"/////////////////";
     cout<<"Size  "<<DS.getsize()<<endl;
    for(int i=0;i<DS.getsize();i++){
         cout<<DS.getMB(i)<<endl;
    }
    DS.getDSMB();
    
    
    
    
    //  InitWindow(1280, 800 , "First Screen");

    //  CreateScreen();
    //  GetCharPressed();
    //  CloseWindow();
     

     return 0;
}