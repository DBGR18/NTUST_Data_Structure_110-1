#include <iostream>
#include <string>
using namespace std;
int main()
{
	string input = "";
	while (cin >> input)
	{
		bool swap = true;
		while (swap)
		{
			string left_side = "";
			string right_side = "";
			string _left_side = "";
			string _right_side = "";
			for (int i = 0; i < input.size(); i++)
			{
				if (input[i] == '<')
				{
					if (input[i - 1] == ']')
					{
						int _right = 0;
						for (int j = i - 2; j >= 0; j--)
						{
							if (input[j] == '[')
							{
								if (_right == 0)
								{
									int k = j - 1;
									while (isdigit(input[k])) --k;
									for (int n = k + 1; n < i; n++)
									{
										left_side.push_back(input[n]);
									}
									for (int m = 0; m < k + 1; m++)
									{
										_left_side.push_back(input[m]);
									}
									break;
								}
								else --_right;
							}
							if (input[j] == ']') ++_right;
						}
					}
					else
					{
						left_side.push_back(input[i - 1]);
						for (int j = 0; j < i - 1; j++)
						{
							_left_side.push_back(input[j]);
						}
					}
					if (!isdigit(input[i + 1]))
					{
						right_side.push_back(input[i + 1]);
						for (int j = i + 2; j < input.size(); j++)
						{
							_right_side.push_back(input[j]);
						}
					}
					else
					{
						for (int j = i + 1; j < input.size(); j++)
						{
							if (input[j] == '[')
							{
								int _left = 0;
								for (int k = j + 1; k < input.size(); k++)
								{
									if (input[k] == ']')
									{
										if (_left == 0)
										{
											for (int n = i + 1; n <= k; n++)
											{
												right_side.push_back(input[n]);
											}
											for (int m = k + 1; m < input.size(); m++)
											{
												_right_side.push_back(input[m]);
											}
											break;
										}
										else --_left;
									}
									if (input[k] == '[') ++_left;
								}
								break;
							}
						}
					}
					break;
				}
				if (i == input.size() - 1) swap = false;
			}
			if (swap)
			{
				input.clear();
				input = _left_side + right_side + left_side + _right_side;
			}
		}
		input += ".";
		bool repeat = true;
		while (repeat)
		{
			string left = "";
			string right = "";
			string mid = "";
			string mids = "";
			for (int i = 0; i < input.size(); i++)
			{
				if (input[i] == ']')
				{
					for (int j = i - 1; j >= 0; j--)
					{
						if (input[j] == '[')
						{
							int k = j - 1;
							while (isdigit(input[k]))
							{
								--k;
								if (k == -1) break;
							}
							string _times = "";
							for (int n = k + 1; n < j; n++)
							{
								_times.push_back(input[n]);
							}
							int times = stoi(_times);
							for (int m = 0; m <= k; m++)
							{
								left.push_back(input[m]);
							}
							for (int t = j + 1; t < i; t++)
							{
								mid.push_back(input[t]);
							}
							for (int t = 0; t < times; t++)
							{
								mids += mid;
							}
							break;
						}
					}
					for (int j = i + 1; j < input.size(); j++)
					{
						right.push_back(input[j]);
					}
					break;
				}
				if (input[i] == '.') repeat = false;
			}
			if (repeat)
			{
				input.clear();
				input = left + mids + right;
			}
		}
		for (int i = 0; i < input.size() - 1; i++)
		{
			cout << input[i];
		}
		cout << endl;
	}
}