#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

bool node_in_list(int n, list<pair<int, pair<int, int> > >mini)
{
	for (auto a : mini)
	{
		if (a.second.first == n) return true;
		if (a.second.second == n) return true;
	}
	return false;
}

pair<int, pair<int, int> > smallest_edge(list<pair<int, pair<int, int> > >mini, vector<pair<int, pair<int, int> > >labelled)
{
	int smallest = -1;
	int edge1 = -1;
	int edge2 = -1;
	int temp = -1;
	for (int i = 0; i < labelled.size(); i++)
	{
		if (!node_in_list(labelled[i].second.first, mini) || !node_in_list(labelled[i].second.second, mini))
		{
			if (temp == -1)
			{
				smallest = labelled[i].first;
				edge1 = labelled[i].second.first;
				edge2 = labelled[i].second.second;
			}
			temp = labelled[i].first;
			if (temp < smallest)
			{
				smallest = temp;
				edge1 = labelled[i].second.first;
				edge2 = labelled[i].second.second;
			}
			else if (temp == smallest)
			{
				if (edge1 > labelled[i].second.first)
				{
					smallest = temp;
					edge1 = labelled[i].second.first;
					edge2 = labelled[i].second.second;
				}
				else if (edge1 == labelled[i].second.first)
				{
					if (edge2 > labelled[i].second.second)
					{
						smallest = temp;
						edge1 = labelled[i].second.first;
						edge2 = labelled[i].second.second;
					}
				}
			}
		}
	}
	return make_pair(smallest, make_pair(edge1,edge2));
}

bool sort_edge(pair<int, pair<int, int> >a, pair<int, pair<int, int> >b)
{
	if (a.first < b.first) return true;
	if (a.first > b.first) return false;
	if (a.second.first < b.second.first) return true;
	if (a.second.first > b.second.first) return false;
	if (a.second.second < b.second.second) return true;
	if (a.second.second > b.second.second) return false;
	return true;
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
		int outset = 1;
		vector<list<pair<int, int> > >adjacency_list(nodes + 1);
		for (int i = 0; i < edges; i++)
		{
			cin >> n1 >> n2 >> w;
			adjacency_list[n1].push_back(make_pair(n2, w));
			adjacency_list[n2].push_back(make_pair(n1, w));
		}
		list<pair<int, pair<int, int> > >mini_edges;
		vector<pair<int, pair<int, int> > >labelled_edges;
		for (auto a : adjacency_list[outset])
		{
			labelled_edges.push_back(make_pair(a.second, make_pair(outset, a.first)));
		}
		mini_edges.push_back(smallest_edge(mini_edges, labelled_edges));

		bool finish = false;
		while (!finish)
		{
			for (auto a : adjacency_list[mini_edges.back().second.second])
			{
				labelled_edges.push_back(make_pair(a.second, make_pair(mini_edges.back().second.second, a.first)));
			}
			if(smallest_edge(mini_edges, labelled_edges).first == -1) finish = true;
			else mini_edges.push_back(smallest_edge(mini_edges, labelled_edges));
		}
		for (int i = 0; i < mini_edges.size(); i++)
		{
			pair<int, pair<int, int> > p = mini_edges.front();
			if (p.second.first > p.second.second)
			{
				int t = p.second.first;
				p.second.first = p.second.second;
				p.second.second = t;
			}
			mini_edges.pop_front();
			mini_edges.push_back(p);
		}
		mini_edges.sort(sort_edge);
		for (auto a : mini_edges)
		{
			cout << a.second.first << " " << a.second.second << " " << a.first << endl;
		}
	}
}