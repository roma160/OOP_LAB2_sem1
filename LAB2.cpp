#include <iostream>
#include "longint.h"

int main()
{
    int i = 0;
    char sign;
    longint a, b;
    while (true)
    {
        cout << ++i << ") ";
        cin >> a >> sign >> b;
        if(sign == '-')
			cout << " = " << a - b << "\n";
        else if(sign == '+')
            cout << " = " << a + b << "\n";
        else if(sign == '*')
            cout << " = " << a * b << "\n";
    	else if (sign == '/')
            cout << " = " << a / b << "\n";
    }
}