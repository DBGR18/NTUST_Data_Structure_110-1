#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        if (b % 2 == 1)
        {
            if (a <= (b + 1) / 2)
            {
                cout << (b - 1) / 2 << endl;
            }
            else cout << b - a << endl;
        }
        else
        {
            if (a <= b / 2)
            {
                cout << b / 2 - 1 << endl;
            }
            else cout << b - a << endl;
        }
    }
}