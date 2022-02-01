#include <iostream>
using namespace std;
class TreeNode {
private:
	int data;
	TreeNode* right;
	TreeNode* left;
	int height;
public:
	TreeNode()
	{
		data = 0;
		right = NULL;
		left = NULL;
		height = 0;
	}
	TreeNode(int n)
	{
		data = n;
		right = NULL;
		left = NULL;
		height = 1;
	}
	
	friend class AVL;
};

class AVL {
private:
public:
	TreeNode* root;
	AVL()
	{
		root = NULL;
	}
	int _height(TreeNode* node)
	{
		if (node == NULL) return 0;
		else return node->height;
	}
	int get_height(TreeNode* node)
	{
		if (node == NULL) return 0;
		else if (_height(node->left) > _height(node->right)) return _height(node->left) + 1;
		else return _height(node->right) + 1;
	}
	int get_balance(TreeNode* node)
	{
		if (node == NULL) return 0;
		return get_height(node->left) - get_height(node->right);
		//return node->left->height - node->right->height;
	}
	TreeNode* insertion(TreeNode*& node, int n)		// always return root node
	{
		//if (node == NULL) node = new TreeNode(n);
		if (node == NULL)
		{
			TreeNode* newnode = new TreeNode(n);
			return newnode;
		}
		else
		{
			if (n <= node->data) node->left = insertion(node->left, n);
			else node->right = insertion(node->right, n);
		}
		node->height = get_height(node);
		int balance_factor = get_balance(node);
		//	LL rotation
		if (balance_factor > 1 && n <= node->left->data)
		{
			TreeNode* b = node->left;
			TreeNode* t2 = b->right;
			b->right = node;	// b rotate to root 
			node->left = t2;
			node->height = get_height(node);	// ***child's height calculus first***
			b->height = get_height(b);
			return b;
		}
		//	RR rotation
		else if (balance_factor < -1 && n > node->right->data)
		{
			TreeNode* b = node->right;
			TreeNode* t2 = b->left;
			b->left = node;
			node->right = t2;
			node->height = get_height(node);	// ***child's height calculus first***
			b->height = get_height(b);
			return b;
		}
		//	LR rotation
		else if (balance_factor > 1 && n > node->left->data)
		{
			TreeNode* b = node->left;
			TreeNode* c = b->right;
			TreeNode* t2 = c->left;
			c->left = b;	// c & b rotate first
			b->right = t2;
			b->height = get_height(b);	// ***child's height calculus first***
			c->height = get_height(c);
			node->left = c;

			TreeNode* t3 = c->right;
			c->right = node;	// then c & root rotate
			node->left = t3;
			node->height = get_height(node);
			c->height = get_height(c);
			return c;
		}
		//	RL rotation
		else if (balance_factor < -1 && n <= node->right->data)
		{
			TreeNode* b = node->right;
			TreeNode* c = b->left;
			TreeNode* t3 = c->right;
			c->right = b;	// c & b rotate first
			b->left = t3;
			b->height = get_height(b);	// ***child's height calculus first***
			c->height = get_height(c);
			node->right = c;

			TreeNode* t2 = c->left;
			c->left = node;		// then c & root rotate
			node->right = t2;
			node->height = get_height(node);
			c->height = get_height(c);
			return c;
		}
		return node;
	}
	TreeNode* deletion(TreeNode*& node, int n)		// always return root node
	{
		if (n > node->data) node->right = deletion(node->right, n);
		else if (n < node->data) node->left = deletion(node->left, n);
		else if (node->left != NULL && node->right != NULL)
		{
			//TreeNode* temp = find_max(node->left);
			int temp = 0;
			find_max(node->left, temp);
			node->data = temp;
			node->left = deletion(node->left, temp);
		}
		else
		{
			TreeNode* temp = node;
			if (node->left == NULL && node->right == NULL) node = NULL;
			else if (node->left != NULL) node = temp->left;
			else node = temp->right;
			temp = NULL;
		}
		if (node == NULL) return node;		// if the node is leaf then return 
		node->height = get_height(node);
		int balance_factor = get_balance(node);
		//	LL rotation
		if (balance_factor > 1 && get_balance(node->left) > -1)
		{
			TreeNode* b = node->left;
			TreeNode* t2 = b->right;
			b->right = node;	// b rotate to root 
			node->left = t2;
			node->height = get_height(node);
			b->height = get_height(b);
			return b;
		}
		//	RR rotation
		if (balance_factor < -1 && get_balance(node->right) < 1)
		{
			TreeNode* b = node->right;
			TreeNode* t2 = b->left;
			b->left = node;
			node->right = t2;
			node->height = get_height(node);
			b->height = get_height(b);
			return b;
		}
		//	LR rotation
		if (balance_factor > 1 && get_balance(node->left) == -1)
		{
			TreeNode* b = node->left;
			TreeNode* c = b->right;
			TreeNode* t2 = c->left;
			c->left = b;	// c & b rotate first
			b->right = t2;
			b->height = get_height(b);
			c->height = get_height(c);
			node->left = c;

			TreeNode* t3 = c->right;
			c->right = node;	// then c & root rotate
			node->left = t3;
			node->height = get_height(node);
			c->height = get_height(c);
			return c;
		}
		//	RL rotation
		if (balance_factor < -1 && get_balance(node->right) == 1)
		{
			TreeNode* b = node->right;
			TreeNode* c = b->left;
			TreeNode* t3 = c->right;
			c->right = b;	// c & b rotate first
			b->left = t3;
			b->height = get_height(b);
			c->height = get_height(c);
			node->right = c;

			TreeNode* t2 = c->left;
			c->left = node;		// then c & root rotate
			node->right = t2;
			node->height = get_height(node);
			c->height = get_height(c);
			return c;
		}
		return node;
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
	void inorder(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << "(";
			inorder(node->left);
			cout << ")";
			cout << node->data;
			cout << "(";
			inorder(node->right);
			cout << ")";
		}
	}
	void preorder(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << node->data;
			cout << "(";
			preorder(node->left);
			cout << ")";
			cout << "(";
			preorder(node->right);
			cout << ")";
		}
	}
	void postorder(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << "(";
			postorder(node->left);
			cout << ")";
			cout << "(";
			postorder(node->right);
			cout << ")";
			cout << node->data;
		}
	}
};

int main()
{
	AVL avl;
	TreeNode* node = avl.root;
	int n = 0, val = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		node = avl.insertion(node, val);
	}
	char c = ' ';
	while (cin >> c)
	{
		if (c == 'I')
		{
			cin >> val;
			node = avl.insertion(node, val);
		}
		else if (c == 'D')
		{
			cin >> val;
			node = avl.deletion(node, val);
		}
		else if (c == 'P')
		{
			cin >> c;
			if (c == '1')
			{
				avl.preorder(node);
				cout << endl;
			}
			else if (c == '2')
			{
				avl.inorder(node);
				cout << endl;
			}
			else
			{
				avl.postorder(node);
				cout << endl;
			}
		}
		else continue;
	}
	return 0;
}