// longnum.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
const int N = 1024;
class longint {
private:
    char *m;//m[N] масив символів цифр в оберн. порядку
    int sign;
public:
    longint() { m = new char[N]; };
    longint(const longint& l);
    longint(char* s);
    longint& operator=(const longint& l);
    friend longint operator+(longint& l1, longint& l2);
    friend ostream& operator<<(ostream& out, const longint& l);
    friend istream& operator>>(istream& in, longint& l);
    ~longint() { delete[] m; m = nullptr; }
};

int main()
{
    longint a, b,c;
    cout << ">";
    cin >> a >> b;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    c = a + b;
    cout << "c=a+b=" << c << endl;
    system("pause");
    return 0;
}

longint::longint(const longint& l)
{
    m = new char[N];
    strcpy_s(m,N,l.m);
}

longint::longint(char* s)
{
    int l = strlen(s);
    m = new char[N];
    for (int i = l - 1; i >= 0; i--) {
        m[l - i - 1] = s[i];
    }
    m[l] = '\0';
}

longint& longint::operator=(const longint& l)
{
    strcpy_s(m, N, l.m);
    return *this;
}

longint operator+(longint& l1, longint& l2)
{
    longint t;
    int len1 = strlen(l1.m);
    int len2 = strlen(l2.m);
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++)
            l2.m[len2 + i] = '0';
        len2 = len1;
        l2.m[len2] = '\0';
    }else
        if (len2 > len1) {
            for (int i = 0; i < len2 - len1; i++)
                l1.m[len1 + i] = '0';
            len1 = len2;
            l1.m[len1] = '\0';
        }

    int r = 0,i;
    for (int i = 0; i < len1; i++) {
        t.m[i] = (l1.m[i] - '0') + (l2.m[i] - '0') + r;
        r = t.m[i] / 10;
        t.m[i] = t.m[i] % 10;
        t.m[i] += '0';
    }
    if (r > 0) {
        t.m[len1] = r + '0';
        t.m[len1 + 1] = '\0';
    }
    else
        t.m[len1] = '\0';
    return t;
}

ostream& operator<<(ostream& out, const longint& l)
{
    int len = strlen(l.m);
    if (l.sign < 0)
        out << "-";
    for (int i = 0; i < len; i++)
        out << l.m[len - i - 1];
    return out;
}

istream& operator>>(istream& in, longint& l)
{
    char buf[2048];
    in >> buf;
    int len = strlen(buf);
    strcpy_s(l.m, N, buf);
    for (int i = 0; i < len; i++)
        l.m[i] = buf[len - i - 1];
    return in;
}
