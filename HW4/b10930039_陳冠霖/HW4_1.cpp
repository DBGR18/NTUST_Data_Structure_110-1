#include <iostream>
using namespace std;
int loc;
void partition(int arr[], int begin, int end, int& loc)
{
	int l = begin, r = end;
	loc = begin;
	bool flag = true;
	while (flag)
	{
		while (arr[loc] <= arr[r] && loc != r) r--;
		if (loc == r) flag = false;
		else if (arr[loc] > arr[r])
		{
			int temp = arr[loc];
			arr[loc] = arr[r];
			arr[r] = temp;
			loc = r;
		}
		if (flag)
		{
			while (arr[loc] >= arr[l] && loc != l) l++;
			if (loc == l) flag = false;
			else if (arr[loc] < arr[l])
			{
				int temp = arr[loc];
				arr[loc] = arr[l];
				arr[l] = temp;
				loc = l;
			}
		}
	}
}

void quick_sort(int arr[], int begin, int end)
{
	if (begin < end)
	{
		partition(arr, begin, end, loc);
		quick_sort(arr, begin, loc - 1);
		quick_sort(arr, loc + 1, end);
	}
}


//void insertion_sort(int arr[], int n)
//{
//	for (int i = 1; i < n; i++)
//	{
//		int temp = arr[i];
//		int j = i - 1;
//		while (temp < arr[j])
//		{
//			arr[j + 1] = arr[j];
//			--j;
//			if (j == -1) break;
//		}
//		arr[j + 1] = temp;
//	}
//}

bool ascending(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] > arr[i + 1]) return false;
	}
	return true;
}
bool descending(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] < arr[i + 1]) return false;
	}
	return true;
}

int main()
{
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		int* arr = new int[m];
		//int arr[100000] = { 0 };
		for (int j = 0; j < m; j++)
		{
			cin >> arr[j];
		}
		if (ascending(arr, m))
		{
			for (int j = 0; j < m; j++)
			{
				if (j == m - 1) cout << arr[j] << endl;
				else cout << arr[j] << " ";
			}
			//cout << endl;
		}
		else if (descending(arr, m))
		{
			for (int j = m - 1; j >= 0; j--)
			{
				if (j == 0) cout << arr[j] << endl;
				else cout << arr[j] << " ";
			}
			//cout << endl;
		}
		else
		{
			loc = m / 2;
			quick_sort(arr, 0, m - 1);
			for (int j = 0; j < m; j++)
			{
				if (j == m - 1) cout << arr[j] << endl;
				else cout << arr[j] << " ";
			}
			//cout << endl;
		}
		delete arr;
	}
}