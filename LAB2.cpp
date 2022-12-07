#include <iostream>

#include "division.h"
#include "longint.h"
#include "primality.h"
#include "algorithms/multiplication.h"
#include <map>
#include <string>

//map<string>

int main()
{
    /*int i = 0;
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
            cout << " = " << multiplication::shengage(a, b) << "\n";
        else if (sign == '/') {
            tuple<longint, longint> res = division::toom(a, b);
            cout << " = " << get<0>(res) << " " << get<1>(res) << "\n";
        }
    }*/

    cout << primality::strassen(18, 100);
}