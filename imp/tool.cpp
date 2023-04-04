#include "../header/header.h"

char *intTochar(int value, int size)
{
    char *ans = new char[size];
    for (int i = 0; i < size; i++)
    {
        int _10 = 1;
        for (int j = i + 1; j < size; j++)
        {
            _10 *= 10;
        }
        if (value / _10 == 0)
            ans[i] = '0';
        else
            ans[i] = (value / _10) + 48;
        value = value % _10;
    }
    ans[size] = '\0';
    return ans;
}

float per1000(int number)
{
    return (float)number / 1000;
}
bool isGotStr(string _string, string _keyword)
{
    if (_string.length() < _keyword.length())
        return false;
    bool status = false;
    for (int i = 0; i <= _string.length() - _keyword.length(); i++)
    {
        if (_string[i] == _keyword[0])
        {
            status = true;
            for (int j = i + 1; j < i + _keyword.length(); j++)
            {
                if (_string[j] != _keyword[j - i])
                {
                    status = false;
                    break;
                }
            }
        }
        if (status == true)
            return true;
    }
    return false;
}

int getCharSize(const char *_char)
{
    int result = 0;
    while (_char[result] >= 32 && _char[result] <= 126)
    {
        result++;
    }
    return result;
}