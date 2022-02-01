#include <iostream>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	bool* oasis = new bool[n];
	bool** table = new bool* [n];
	bool* checked = new bool[n];
	bool* path = new bool[n];
	for (int i = 0; i < n; i++)
	{
		cin >> oasis[i];
		table[i] = new bool[n];
		checked[i] = false;
		path[i] = false;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			table[i][j] = false;
		}
	}
	for (int i = 0; i < n; i++) table[i][i] = true;
	for (int i = 0; i < k; i++)
	{
		int a, b;
		cin >> a >> b;
		table[a][b] = true;
		table[b][a] = true;
	}
	int c, d;
	while (cin >> c >> d)
	{
		bool finish = false;
		bool flag = true;
		bool withered = false;
		if (!oasis[c]) withered = true;
		while (!finish)
		{
			for (int i = 0; i < n; i++)
			{
				if (table[c][i])
				{
					if (withered && !oasis[i] && i != c)
					{
						checked[c] = true;
						continue;
					}
					if (i == d)
					{
						finish = true;
						for (int k = 0; k < n; k++) checked[k] = false;
						for (int k = 0; k < n; k++) path[k] = false;
						break;
					}
					path[i] = true;
				}
				checked[c] = true;
			}
			if (finish) break;
			for (int k = 0; k < n; k++)
			{
				if (path[k] && !checked[k])
				{
					c = k;
					if (!oasis[c]) withered = true;
					else withered = false;
					break;
				}
				if (k == n - 1)
				{
					finish = true;
					flag = false;
					for (int j = 0; j < n; j++) checked[j] = false;
					for (int j = 0; j < n; j++) path[j] = false;
				}
			}
		}
		if (flag) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}