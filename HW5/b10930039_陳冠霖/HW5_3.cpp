#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
	int n = 0;
	int m = 0;
	cin >> n;
	vector<int>nums;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		nums.push_back(m);
	}
	int k = 0;
	while (cin >> k)
	{
		unordered_map<int, int> hash_table;
		for (int i = 0; i < nums.size(); i++)
		{
			int sub = k - nums[i];
			if (hash_table.find(sub) != hash_table.end())
			{
				cout << sub << " " << nums[i] << endl;
				break;
			}
			else hash_table[nums[i]] = i;
		}
	}
}