#include "libs/libs.h"
// #include <windows.h>

using namespace std;

int main()
{
    std::cout << "Hello, world!" << std::endl;

    HanhKhach hk;

    string IDV = "";
    IDV = InputXau(IDV);

    std::cout << "X: " << IDV;
    VeMayBay *veBay = new VeMayBay("A12", hk);

    return 0;
}