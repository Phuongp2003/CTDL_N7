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

int ChuanHoaKey(int key, const char *str, int index_pos, int mode)
{
    char tmp = str[index_pos - 1];
    if (index_pos == 0 || (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))))
    {
        if (!((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
            return 0;
        if (key >= 'a' && key <= 'z')
        {
            key -= 32;
        }
    }
    if ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))
        if (key >= 'A' && key <= 'Z')
        {
            key += 32;
        }

    switch (mode)
    {
    case 1:
    {
        if ((key >= 32) && (key <= 125))
        {
            return key;
        }
        break;
    };
    case 2:
    {
        if ((((key >= '0') && (key <= '9')) || ((key >= 'a') && (key <= 'z')) ||
             ((key >= 'A') && (key <= 'Z'))))
        {
            return key;
        }
        break;
    }
    case 3:
    {
        if ((((key >= '0') && (key <= '9')) || ((key >= 'a') && (key <= 'z')) ||
             ((key >= 'A') && (key <= 'Z'))))
        {
            if (key >= 'a' && key <= 'z')
            {
                key -= 32;
            }
            return key;
        }
        break;
    }

    case 4:
    {
        if ((((key >= 'a') && (key <= 'z')) ||
             ((key >= 'A') && (key <= 'Z'))))
        {
            if (key >= 'a' && key <= 'z')
            {
                key -= 32;
            }
            return key;
        }
        break;
    }
    case 5:
    case 8:
    {
        if (((key >= '0') && (key <= '9')))
        {
            return key;
        }
        break;
    }
    case 6:
    {
        if (((key >= '0') && (key <= '9')))
        {
            if (index_pos == 0 && (key < '0' || key > '3'))
                return 0;
            if (index_pos == 0 && str[0] >= '2' && key == '3')
                return 0;
            if (index_pos == 0 && str[0] == '0' && key == '0')
                return 0;

            if (index_pos == 1 && str[0] == '0' && key == '0')
                return 0;
            if (index_pos == 1 && str[0] == '3' && !(key == '0' || key == '1'))
                return 0;
            return key;
        }
        break;
    }
    case 7:
    {
        if (((key >= '0') && (key <= '9')))
        {
            if (str[0] == '0' && key == '0')
                return 0;
            if (index_pos == 1 && str[0] == '1' && !(key == '0' || key == '1' || key == '2'))
                return 0;
            if (index_pos == 1 && str[0] != '0' && str[0] != '1')
                return 0;

            if (index_pos == 0 && key > '1' && str[0] != '0' && str[0] != '1' && str[0] != 0)
                return 0;
            if (index_pos == 0 && key == '1' && str[0] > '2' && str[0] != 0)
                return 0;
            if (index_pos == 0 && !(key == '1' || key == '0') && !(str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == 0))
                return 0;

            return key;
        }
        break;
    }
    case 9:
    {
        if (((key >= '0') && (key <= '9')))
        {
            if (index_pos == 1 && str[0] >= '2' && key > '3')
                return 0;
            if (index_pos == 1 && str[0] > '2')
                return 0;

            if (index_pos == 0 && key >= '2' && str[0] > '3')
                return 0;

            return key;
        }
        break;
    }
    case 10:
    {
        if (((key >= '0') && (key <= '9')))
        {
            if (index_pos == 1 && str[0] > '5')
                return 0;

            if (index_pos == 0 && key >= '6' && str[0] >= '0')
                return 0;

            return key;
        }
        break;
    }
    }

    return 0;
}

int strcmp(const char *str1, const char *str2)
{
    int max = 0;
    if (getCharSize(str1) <= getCharSize(str2))
        max = getCharSize(str2);
    else
        max = getCharSize(str1);

    for (int i = 0; i < max; i++)
    {
        if (str1[i] < str2[i])
            return -1;
        else if (str1[i] > str2[i])
            return 1;
    }

    return 0;
}