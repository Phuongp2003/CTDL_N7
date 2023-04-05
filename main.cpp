#include "header/libs.h"

using namespace std;
// using std::filesystem::current_path;
int main(int argc, const char *argv[])
{
     // string test;
     // string key;

     // getline(std::cin, test);
     // getline(std::cin, key);

     // if (isGotStr(test, key))
     //      cout << "yes" << endl;
     // else
     //      cout << "no" << endl;
     char tmp[256];
     getcwd(tmp, 256);
     cout << "Current working directory: " << argv[1] << endl;

     InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "First Screen");
     mainGraphics();
     CloseWindow();
     return 0;
}
