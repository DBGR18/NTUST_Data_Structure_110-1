#include <iostream>
using namespace std;

int binary_search(int data[], int lower, int upper, int val)
{
	int index = -1;
	int mid = -1;
	while (lower <= upper)
	{
		mid = (lower + upper) / 2;
		if (data[mid] == val) return mid;
		else if (data[mid] > val) upper = mid - 1;
		else lower = mid + 1;
	}
	if (index == -1) return -1;
}
int main()
{
	int data[500000];
	int n = 0;
	int val = 0;
	cin >> n;
	cin >> val;
	int ll = 0, lu = n, ul = -1, uu = n;
	data[0] = val;
	for (int i = 1; i < n; i++)
	{
		cin >> val;
		data[i] = val;
		if (data[i] < data[i - 1])
		{
			lu = i - 1;
			ul = i;
		}
	}
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val; 
		if (val >= data[0]) cout << binary_search(data, ll, lu, val) << endl;
		else cout << binary_search(data, ul, uu, val) << endl;
	}
}
