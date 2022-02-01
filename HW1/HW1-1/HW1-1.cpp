#include<iostream>
using namespace std;

char _map[100][100];
int step[100][100];

void find_step(int x, int y, char  _map[][100], int  step[][100])
{
	if (_map[x - 1][y] == '*' || _map[x - 1][y] == '@')
	{
		if (_map[x - 1][y] == '@')
		{
			step[x - 1][y] = step[x][y] + 1;
			return;
		}
		else if (step[x - 1][y] == -1 || step[x][y] < step[x - 1][y])
		{
			step[x - 1][y] = step[x][y] + 1;
			find_step(x - 1, y, _map, step);
		}
	}
	if (_map[x][y + 1] == '*' || _map[x][y + 1] == '@')
	{
		if (_map[x][y + 1] == '@')
		{
			step[x][y + 1] = step[x][y] + 1;
			return;
		}
		else if (step[x][y + 1] == -1 || step[x][y] < step[x][y + 1])
		{
			step[x][y + 1] = step[x][y] + 1;
			find_step(x, y + 1, _map, step);
		}
	}
	if (_map[x + 1][y] == '*' || _map[x + 1][y] == '@')
	{
		if (_map[x + 1][y] == '@')
		{
			step[x + 1][y] = step[x][y] + 1;
			return;
		}
		else if (step[x + 1][y] == -1 || step[x][y] < step[x + 1][y])
		{
			step[x + 1][y] = step[x][y] + 1;
			find_step(x + 1, y, _map, step);
		}
	}
	if (_map[x][y - 1] == '*' || _map[x][y - 1] == '@')
	{
		if (_map[x][y - 1] == '@')
		{
			step[x][y - 1] = step[x][y] + 1;
			return;
		}
		else if (step[x][y - 1] == -1 || step[x][y] < step[x][y - 1])
		{
			step[x][y - 1] = step[x][y] + 1;
			find_step(x, y - 1, _map, step);
		}
	}
	return;
}

int main()
{
	int n = 0, m = 0;
	while (cin >> n >> m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> _map[i][j];
				step[i][j] = -1;
			}
		}
		int x = 0, y = 0;
		int _x = 0, _y = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (_map[i][j] == '.')
				{
					x = i;
					y = j;
					step[i][j] = 0;
				}
				if (_map[i][j] == '@')
				{
					_x = i;
					_y = j;
				}
			}
		}

		find_step(x, y, _map, step);
		cout << step[_x][_y] << endl;
	}
}