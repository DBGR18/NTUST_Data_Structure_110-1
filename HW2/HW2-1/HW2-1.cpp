#include <iostream>
using namespace std;
class TreeNode {
private:
	int data;
	TreeNode* right;
	TreeNode* left;
public:
	int rchild_count;
	int rchild_sum;
	int lchild_count;
	int lchild_sum;
	TreeNode()
	{
		data = 0;
		right = NULL;
		left = NULL;
		rchild_count = 0;
		rchild_sum = 0;
		lchild_count = 0;
		lchild_sum = 0;
	}
	TreeNode(int n)
	{
		data = n;
		right = NULL;
		left = NULL;
		rchild_count = 0;
		rchild_sum = 0;
		lchild_count = 0;
		lchild_sum = 0;
	}
	friend class BST;
};
class BST {
private:
	
public:
	TreeNode* root;
	//int sorted_value[50000];
	int index;
	int total;
	int _total;
	BST()
	{
		root = NULL;
		index = 0;
		total = 0;
	}
	void insertion(TreeNode*& node, int n)
	{
		if (node == NULL) node = new TreeNode(n);
		else
		{
			if (n <= node->data)
			{
				node->lchild_count++;
				node->lchild_sum += n;
				insertion(node->left, n);
			}
			else
			{
				node->rchild_count++;
				node->rchild_sum += n;
				insertion(node->right, n);
			}
		}
	}
	void deletion(TreeNode*& node, int n)
	{
		if (n > node->data)
		{
			node->rchild_count--;
			node->rchild_sum -= n;
			deletion(node->right, n);
		}
		else if (n < node->data)
		{
			node->lchild_count--;
			node->lchild_sum -= n;
			deletion(node->left, n);
		}
		else if (node->left != NULL && node->right != NULL)
		{
			//TreeNode* temp = find_max(node->left);
			int temp = 0;
			find_max(node->left, temp);
			node->data = temp;
			node->lchild_count--;
			node->lchild_sum -= temp;
			deletion(node->left, temp);
		}
		else
		{
			TreeNode* temp = node;
			if (node->left == NULL && node->right == NULL) node = NULL;
			else if (node->left != NULL) node = temp->left;
			else node = temp->right;
			temp = NULL;
		}
	}
	void print_pre(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << node->data;
			cout << "(";
			print_pre(node->left);
			cout << ")";
			cout << "(";
			print_pre(node->right);
			cout << ")";
		}
	}
	/*int v_max(TreeNode* node, int n)
	{
		int count = 0;
		index = 0;
		total = 0;
		sort_value(node);
		while (total > n)
		{
			--index;
			total -= sorted_value[index];
			++count;
		}
		return count;
	}
	int v_min(TreeNode* node, int n)
	{
		int count = 0;
		index = 0;
		total = 0;
		sort_value(node);
		while (total >= n)
		{
			total -= sorted_value[count];
			++count;
		}
		return --count;
	}*/
	void _v_max(TreeNode* node, int n, int& count)
	{
		if (node != NULL)
		{
			if (_total - node->rchild_sum > n)
			{
				_total -= node->rchild_sum;
				count += node->rchild_count;
				_total -= node->data;
				++count;
				if (_total <= n) return;
				else _v_max(node->left, n, count);
			}
			else _v_max(node->right, n, count);
		}
	}
	void _v_min(TreeNode* node, int n, int& count)
	{
		if(node != NULL)
		{
			if (_total - node->lchild_sum >= n)
			{
				_total -= node->lchild_sum;
				count += node->lchild_count;
				_total -= node->data;
				++count;
				if (_total < n) return;
				else _v_min(node->right, n, count);
			}
			else _v_min(node->left, n, count);
		}
	}
	void find_max(TreeNode* node, int& max)
	{
		if (node->right == NULL)
		{
			max = node->data;
			return;
		}
		find_max(node->right, max);
	}
	/*void sort_value(TreeNode* node)
	{
		if (node != NULL)
		{
			sort_value(node->left);
			sorted_value[index] = node->data;
			++index;
			total += node->data;
			sort_value(node->right);
		}
	}*/
};
int main()
{
	BST bst;
	TreeNode* node = bst.root;
	int n = 0, val = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		bst.total += val;
		bst.insertion(node, val);
	}
	char c = ' ';
	while (cin >> c)
	{
		if (c == 'I')
		{
			cin >> val;
			bst.total += val;
			bst.insertion(node, val);
		}
		else if (c == 'D')
		{
			cin >> val;
			bst.total -= val;
			bst.deletion(node, val);
		}
		else if (c == 'P')
		{
			bst.print_pre(node);
			cout << endl;
		}
		else if (c == 'L')
		{
			cin >> val;
			int count = 0;
			bst._total = bst.total;
			//cout << bst.v_max(node, val) << endl;
			bst._v_max(node, val, count);
			cout << count << endl;
		}
		else if (c == 'M')
		{
			cin >> val;
			int count = 0;
			bst._total = bst.total;
			//cout << bst.v_min(node, val) << endl;
			bst._v_min(node, val, count);
			cout << count - 1 << endl;
		}
		else continue;
	}
	return 0;
}