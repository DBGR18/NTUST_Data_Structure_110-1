#include <iostream>
using namespace std;

bool aa, bb, cc;

class TreeNode {
private:


public:
	int data;
	TreeNode* right;
	TreeNode* left;
	TreeNode* parent;
	TreeNode* grandParent;
	bool color;		//		0:black		1:red
	TreeNode()
	{
		data = 0;
		right = NULL;
		left = NULL;
		parent = NULL;
		grandParent = NULL;
		color = 0;
	}
	TreeNode(int n)
	{
		data = n;
		right = NULL;
		left = NULL;
		parent = NULL;
		grandParent = NULL;
		color = 1;
	}
	friend class RBT;
};
class RBT {
private:
public:
	TreeNode* root;
	RBT()
	{
		root = NULL;
	}
	TreeNode* LL(TreeNode*& node)
	{
		TreeNode* b = node->left;
		TreeNode* t2 = b->right;

		b->parent = node->parent;
		b->grandParent = node->grandParent;
		b->left->grandParent = node->parent;
		node->parent = b;
		node->grandParent = b->parent;
		if (node->right != NULL) node->right->grandParent = b;

		b->right = node;	// b rotate to root 

		if (t2 != NULL) t2->parent = node;
		if (t2 != NULL) t2->grandParent = b;
		if (t2 != NULL && t2->left != NULL) t2->left->grandParent = node;
		if (t2 != NULL && t2->right != NULL) t2->right->grandParent = node;

		node->left = t2;
		b->color = 0;
		b->left->color = 1;
		b->right->color = 1;
		return b;
	}
	TreeNode* LR(TreeNode*& node)
	{
		TreeNode* b = node->left;
		TreeNode* c = b->right;
		TreeNode* t2 = c->left;
		TreeNode* t3 = c->right;

		b->parent = c;
		b->grandParent = node->parent;
		if (b->left != NULL) b->left->grandParent = c;
		if (t2 != NULL) t2->parent = b;
		if (t2 != NULL) t2->grandParent = c;
		if (t2 != NULL && t2->left != NULL) t2->left->grandParent = b;
		if (t2 != NULL && t2->right != NULL) t2->right->grandParent = b;
		c->parent = node->parent;
		c->grandParent = node->grandParent;

		c->left = b;	// c & b rotate first
		b->right = t2;
		node->left = c;

		node->grandParent = node->parent;
		node->parent = c;
		if (node->right != NULL) node->right->grandParent = c;
		if (t3 != NULL) t3->parent = node;
		if (t3 != NULL) t3->grandParent = c;
		if (t3 != NULL && t3->left != NULL) t3->left->grandParent = node;
		if (t3 != NULL && t3->right != NULL) t3->right->grandParent = node;

		c->right = node;	// then c & root rotate
		node->left = t3;
		c->color = 0;
		c->left->color = 1;
		c->right->color = 1;
		return c;
	}
	TreeNode* RL(TreeNode*& node)
	{
		TreeNode* b = node->right;
		TreeNode* c = b->left;
		TreeNode* t3 = c->right;
		TreeNode* t2 = c->left;

		b->parent = c;
		b->grandParent = node->parent;
		if (b->right != NULL) b->right->grandParent = c;
		if (t3 != NULL) t3->parent = b;
		if (t3 != NULL) t3->grandParent = c;
		if (t3 != NULL && t3->left != NULL) t3->left->grandParent = b;
		if (t3 != NULL && t3->right != NULL) t3->right->grandParent = b;
		c->parent = node->parent;
		c->grandParent = node->grandParent;

		c->right = b;	// c & b rotate first
		b->left = t3;
		node->right = c;

		node->grandParent = node->parent;
		node->parent = c;
		if (node->left != NULL) node->left->grandParent = c;
		if (t2 != NULL) t2->parent = node;
		if (t2 != NULL) t2->grandParent = c;
		if (t2 != NULL && t2->left != NULL) t2->left->grandParent = node;
		if (t2 != NULL && t2->right != NULL) t2->right->grandParent = node;

		c->left = node;		// then c & root rotate
		node->right = t2;
		c->color = 0;
		c->left->color = 1;
		c->right->color = 1;
		return c;
	}
	TreeNode* RR(TreeNode*& node)
	{
		TreeNode* b = node->right;

		b->parent = node->parent;
		b->grandParent = node->grandParent;
		b->right->grandParent = node->parent;
		node->parent = b;
		node->grandParent = b->parent;
		if (node->left != NULL) node->left->grandParent = b;

		TreeNode* t2 = b->left;

		if (t2 != NULL) t2->parent = node;
		if (t2 != NULL) t2->grandParent = b;
		if (t2 != NULL && t2->left != NULL) t2->left->grandParent = node;
		if (t2 != NULL && t2->right != NULL) t2->right->grandParent = node;

		b->left = node;		// b rotate to root
		node->right = t2;
		b->color = 0;
		b->left->color = 1;
		b->right->color = 1;
		return b;
	}
	void red_red_check(TreeNode*& node)
	{
		if (node != NULL)
		{
			if (node->left != NULL && node->left->left != NULL)
			{
				if (node->left->color == 1 && node->left->left->color == 1)			//  do LL rotation
				{
					node = LL(node);
					return;
				}
			}
			if (node->left != NULL && node->left->right != NULL)
			{
				if (node->left->color == 1 && node->left->right->color == 1)		//  do LR rotation
				{
					node = LR(node);
					return;
				}
			}
			if (node->right != NULL && node->right->left != NULL)
			{
				if (node->right->color == 1 && node->right->left->color == 1)		//  do RL rotation
				{
					node = RL(node);
					return;
				}
			}
			if (node->right != NULL && node->right->right != NULL)
			{
				if (node->right->color == 1 && node->right->right->color == 1)		//  do RR rotation
				{
					node = RR(node);
					return;
				}
			}
		}
		return;
	}
	TreeNode* _insertion(TreeNode*& node, int n, TreeNode*& p, TreeNode*& gp, TreeNode*& nn)
	{
		if (node == NULL)
		{
			TreeNode* newnode = new TreeNode(n);
			newnode->parent = p;
			newnode->grandParent = gp;
			nn = newnode;
			return newnode;
		}
		else
		{
			if (node->right != NULL && node->left != NULL)
			{
				if (node->right->color == 1 && node->left->color == 1)
				{
					node->color = 1;
					node->right->color = 0;
					node->left->color = 0;
				}
			}
			if (n <= node->data) node->left = _insertion(node->left, n, node, node->parent, nn);
			else node->right = _insertion(node->right, n, node, node->parent, nn);
		}
		return node;
	}
	void check(TreeNode* n)
	{
		TreeNode* nn = n;
		while (nn->parent != NULL && nn->grandParent != NULL)
		{
			TreeNode* nngp = nn->grandParent;
			TreeNode* x = NULL;
			bb = false;
			find_node(this->root, nngp, x);
			if (x == nngp) nn = nn->parent;
			else nn = x;

			if (nn == NULL) break;
			if (nn->parent == NULL) break;
			if (nn->grandParent == NULL) break;
		}
	}
	void find_check(TreeNode*& node, TreeNode* target)
	{
		if (node != NULL)
		{
			if (node == target)
			{
				check(node);
				aa = true;
				return;
			}
			if (target->data <= node->data) find_check(node->left, target);
			if (aa) return;
			if (target->data > node->data) find_check(node->right, target);
			//if (aa) return;
		}
		return;
	}
	void find_node(TreeNode*& node, TreeNode* target, TreeNode*& x)
	{
		if (node != NULL)
		{
			if (node == target)
			{
				red_red_check(node);
				x = node;
				bb = true;
				return;
			}
			if (target->data <= node->data) find_node(node->left, target, x);
			if (bb) return;
			if (target->data > node->data) find_node(node->right, target, x);
			//if (bb) return;
		}
		return;
	}

	void print(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << node->data << "_";
			node->color == 0 ? cout << "b" : cout << "r";
			cout << "(";
			print(node->left);
			cout << ")";
			cout << "(";
			print(node->right);
			cout << ")";
		}
	}
};

int main()
{
	RBT rbt;
	char c = ' ';
	int val = 0;
	while (cin >> c)
	{
		if (c == 'I')
		{
			cin >> val;
			TreeNode* parent = NULL;
			TreeNode* grandParent = NULL;
			TreeNode* new_node = NULL;
			rbt.root = rbt._insertion(rbt.root, val, parent, grandParent, new_node);
			aa = false;
			rbt.find_check(rbt.root, new_node);
			rbt.root->color = 0;
		}
		if (c == 'P')
		{
			rbt.print(rbt.root);
			cout << endl;
		}
	}
}