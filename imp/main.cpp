#include "../header/libs.h"

int main()
{
	system("chcp 65001"); // Bật UTF-8 show tiếng Việt trong terminal

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Quyết qua môn!");
	mainGraphics();
	CloseWindow();

	system("pause");
	return 0;
}
