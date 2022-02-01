#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

bool node_in_list(int n, list<pair<int, int> >lt)
{
	for (auto a : lt)
	{
		if (a.first == n) return true;
	}
	return false;
}

int smallest_node(vector<int>labelled, list<pair<int, int> >shortest)
{
	int index = -1;
	int smallest = -1;
	int temp = -1;
	for (int i = 1; i < labelled.size(); i++)
	{
		if (labelled[i] >= 0 && !node_in_list(i,shortest))
		{
			if (temp == -1)
			{
				smallest = labelled[i];
				index = i;
			}
			temp = labelled[i];
			if (temp < smallest)
			{
				smallest = temp;
				index = i;
			}
		}
	}
	return index;
}

int minimum(int a, int b)
{
	if (a > b) return b;
	else return a;
}

bool mysort(pair<int, int>a, pair<int, int>b)
{
	if (a.second < b.second) return true;
	else return false;
}

int main()
{
	int nodes = 0;
	int edges = 0;
	while (cin >> nodes >> edges)
	{
		int n1 = 0;
		int n2 = 0;
		int w = 0;
		int outset = 0;
		vector<list<pair<int, int> > >adjacency_list(nodes + 1);
		for (int i = 0; i < edges; i++)
		{
			cin >> n1 >> n2 >> w;
			adjacency_list[n1].push_back(make_pair(n2, w));
		}
		cin >> outset;
		list<pair<int, int> > shortest_distance;
		vector<int>labelled_nodes(nodes + 1, -1);
		shortest_distance.push_back(make_pair(outset, 0));
		labelled_nodes[outset] = 0;
		bool finish = false;
		while (!finish)
		{
			for (auto a : adjacency_list[shortest_distance.back().first])
			{
				int temp = labelled_nodes[a.first];
				if (temp == -1) labelled_nodes[a.first] = labelled_nodes[shortest_distance.back().first] + a.second;
				else labelled_nodes[a.first] = minimum(labelled_nodes[a.first], labelled_nodes[shortest_distance.back().first] + a.second);
			}
			int s = smallest_node(labelled_nodes, shortest_distance);
			if (s != -1) shortest_distance.push_back(make_pair(s, labelled_nodes[s]));
			else finish = true;
		}
		//sort(shortest_distance.begin(), shortest_distance.end(), mysort);
		for (auto a : shortest_distance)
		{
			cout << a.first << " " << a.second << endl;
		}
	}
}