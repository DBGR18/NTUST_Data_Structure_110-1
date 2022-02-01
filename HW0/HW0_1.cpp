#include <iostream>
using namespace std;
unsigned int GCD(unsigned int a, unsigned int b)
{
	if (b == 0)
	{
		return a;
	}
	return GCD(b, a % b);
}
int main()
{
	unsigned int a, b, gcd;
	while (cin >> a >> b)
	{
		gcd = GCD(a, b);
		cout << gcd << endl;
	}
}