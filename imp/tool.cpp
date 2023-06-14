#include "../header/header.h"

void deleteZeroNumberChar(char *&str)
{
  while (str[0] == '0' && str[1] != 0 && str != NULL)
  {
    int size = getCharSize(str);
    for (int i = 0; i < size; i++)
    {
      str[i] = str[i + 1];
    }
  }
}

char *intToChar(int value, int size)
{
  bool fill = true;
  if (size == 0)
  {
    size = 10;
    fill = false;
  }
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
  if (!fill)
    deleteZeroNumberChar(ans);
  return ans;
}

float per1000(int number) { return (float)number / 1000; }

bool isGotStr(string str, string keyworld)
{
  if (str.length() < keyworld.length())
    return false;
  bool status = false;
  for (int i = 0; i <= str.length() - keyworld.length(); i++)
  {
    if (str[i] == keyworld[0])
    {
      status = true;
      for (int j = i + 1; j < i + keyworld.length(); j++)
      {
        if (str[j] != keyworld[j - i])
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

int getCharSize(const char *ch)
{
  int result = 0;
  while (ch[result] >= 32 && ch[result] <= 126)
  {
    result++;
  }
  return result;
}

int chuanHoaKey(int key, const char *str, int pos, int mode)
{
  char tmp = str[pos - 1];
  if (pos == 0 ||
      (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') ||
         (tmp >= '0' && tmp <= '9'))))
  {
    if (!((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
          (key >= '0' && key <= '9')))
      return 0;
    if (key >= 'a' && key <= 'z')
    {
      key -= 32;
    }
  }
  if ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') ||
      (tmp >= '0' && tmp <= '9'))
    if (key >= 'A' && key <= 'Z')
    {
      key += 32;
    }

  switch (mode)
  {
  case ASCII2:
  {
    if ((key >= 32) && (key <= 125))
    {
      return key;
    }
    break;
  };
  case Alphanumeric:
  {
    if ((((key >= '0') && (key <= '9')) || ((key >= 'a') && (key <= 'z')) ||
         ((key >= 'A') && (key <= 'Z'))))
    {
      return key;
    }
    break;
  }
  case UpperAlphanumeric:
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

  case Alphalete:
  {
    if (((key >= 'a') && (key <= 'z')) || ((key >= 'A') && (key <= 'Z')))
    {
      return key;
    }
    break;
  }

  case AlphaleteWithSpace:
  {
    if (((key >= 'a') && (key <= 'z')) || ((key >= 'A') && (key <= 'Z')) || key == ' ')
    {
      return key;
    }
    break;
  }
  case Numeric:
  case Year:
  {
    if (((key >= '0') && (key <= '9')))
    {
      return key;
    }
    break;
  }
  case Day:
  {
    if ((key >= '0') && (key <= '9'))
    {
      if ((pos == 0 || pos == 1) && str[0] == '0' && key == '0')
      {
        return 0;
      }
      if (pos == 0 && str[0] >= '2' && key >= '3')
      {
        return 0;
      }
      if (pos == 1 && str[0] == '3' && !(key == '0' || key == '1'))
      {
        return 0;
      }
      if (pos == 1 && str[0] > '3')
      {
        return 0;
      }
      return key;
    }
    break;
  }
  case Month:
  {
    if (((key >= '0') && (key <= '9')))
    {
      if (str[0] == '0' && key == '0')
        return 0;
      if (pos == 1 && str[0] == '1' &&
          !(key == '0' || key == '1' || key == '2'))
        return 0;
      if (pos == 1 && str[0] != '0' && str[0] != '1')
        return 0;

      if (pos == 0 && key > '1' && str[0] != '0' && str[0] != '1' &&
          str[0] != 0)
        return 0;
      if (pos == 0 && key == '1' && str[0] > '2' && str[0] != 0)
        return 0;
      if (pos == 0 && !(key == '1' || key == '0') &&
          !(str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == 0))
        return 0;

      return key;
    }
    break;
  }
  case Hour:
  {
    if (((key >= '0') && (key <= '9')))
    {
      if (pos == 1 && str[0] >= '2' && key > '3')
        return 0;
      if (pos == 1 && str[0] > '2')
        return 0;

      if (pos == 0 && key >= '2' && str[0] > '3')
        return 0;

      return key;
    }
    break;
  }
  case Minute:
  {
    if (((key >= '0') && (key <= '9')))
    {
      if (pos == 1 && str[0] > '5')
        return 0;

      if (pos == 0 && key >= '6' && str[0] >= '0')
        return 0;

      return key;
    }
    break;
  }
  }

  return 0;
}

const char *strToChar(string str)
{
  char *result = new char[100];
  for (int i = 0; i < str.length(); i++)
  {
    result[i] = str[i];
  }
  result[str.length()] = 0;

  return result;
}
void Selection_Sort(int A[], int n)
{
  int min, vitrimin;
  int i, j;
  for (i = 0; i < n - 1; i++)
  {
    min = A[i];
    vitrimin = i;
    for (j = i + 1; j < n; j++)
      if (A[j] < min)
      {
        min = A[j];
        vitrimin = j;
      }
    // Doi cho 2 phan tu A[i] va A[vitrimin]
    min = A[vitrimin];
    A[vitrimin] = A[i];
    A[i] = min;
  }
}
void swap(int &a, int &b)
{
  int c = a;
  a = b;
  b = c;
}

string intToString(int num, int size)
{
  std::stringstream ss;
  ss << num;

  std::string str = ss.str();
  if (str.length() < size)
  {
    int len = str.length();
    for (int i = 0; i < size - len; i++)
    {
      str = "0" + str;
    }
  }

  str[size] = 0;

  return str;
}

string charToString(const char *ch)
{
  string str(ch);
  return str;
}

string trim(string str)
{
  const char *WhiteSpace = " \t\f\v\r\n";
  size_t start = str.find_first_not_of(WhiteSpace);
  size_t end = str.find_last_not_of(WhiteSpace);
  str = str.substr(start, end - start + 1);
  return str;
}

void formatStr(string &str)
{
  int pos = 0;
  while (pos < str.length())
  {
    if (str[pos] == ' ')
    {
      for (int i = pos; i < str.length() - 1; i++)
      {
        str[i] = str[i + 1];
      }
      str.resize(str.length() - 1);
    }
    else
    {
      str[pos] = tolower(str[pos]);
      pos++;
    }
  }
}

bool laNamNhuan(int nInput)
{
  if ((nInput % 4 == 0 && nInput % 100 != 0) || nInput % 400 == 0)
  {
    return true;
  }
  return false;
}
