#include<iostream>
using namespace std;
int main()
{
    unsigned long long a;
    while (cin >> a)
    {
        cout << ((((a + 1) % 997) * (a % 997)) / 2) % 997 << endl;
    }
}