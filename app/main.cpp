#include "../header/libs.h"

// using namespace std;
// using std::filesystem::current_path;
int main() {
  system("chcp 65001");
  // string test;
  // string key;

  // getline(std::cin, test);
  // getline(std::cin, key);

  // if (isGotStr(test, key))
  //      cout << "yes" << endl;
  // else
  //      cout << "no" << endl;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My PJ");
  mainGraphics();
  CloseWindow();
  return 0;
}
