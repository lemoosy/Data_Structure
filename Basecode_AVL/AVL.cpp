#include "AVL.h"

// -------------------- AVLNode --------------------

AVLNode::AVLNode(AVLData value)
{
	m_value = value;
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_height = 0;
}

AVLNode::~AVLNode()
{
	if (m_left)
	{
		delete m_left;
	}

	if (m_right)
	{
		delete m_right;
	}
}

void AVLNode::SetLeft(AVLNode* node)
{
	m_left = node;

	if (node)
	{
		node->m_parent = this;
	}
}

void AVLNode::SetRight(AVLNode* node)
{
	m_right = node;

	if (node)
	{
		node->m_parent = this;
	}
}

void AVLNode::UpdateHeight(void)
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	m_height = max(L, R) + 1;
}

int AVLNode::GetBalance(void) const
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	return (R - L);
}

void AVLNode::PrintRec(void) const
{
	if (m_left)
	{
		m_left->PrintRec();
	}

	cout << m_value << " ";

	if (m_right)
	{
		m_right->PrintRec();
	}
}

// -------------------- AVLTree --------------------

void AVLTree::Replace(AVLNode* parent, AVLNode* oldChild, AVLNode* newChild)
{
	if (parent)
	{
		if (parent->m_left == oldChild)
		{
			parent->SetLeft(newChild);
		}
		else
		{
			parent->SetRight(newChild);
		}
	}
	else
	{
		m_root = newChild;
		newChild->m_parent = nullptr;
	}
}

void AVLTree::RotateLeft(AVLNode* node)
{
	AVLNode* parent = node->m_parent;
	AVLNode* child = node->m_right;

	node->SetRight(child->m_left);
	child->SetLeft(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

void AVLTree::RotateRight(AVLNode* node)
{
	AVLNode* parent = node->m_parent;
	AVLNode* child = node->m_left;

	node->SetLeft(child->m_right);
	child->SetRight(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

void AVLTree::Balance(AVLNode* node)
{
	while (node)
	{
		node->UpdateHeight();

		int balance = node->GetBalance();

		if (balance == +2)
		{
			if (node->m_right->GetBalance() == -1)
			{
				RotateRight(node->m_right);
			}

			RotateLeft(node);
		}
		else if (balance == -2)
		{
			if (node->m_left->GetBalance() == +1)
			{
				RotateLeft(node->m_left);
			}

			RotateRight(node);
		}

		node = node->m_parent;
	}
}

AVLTree::AVLTree(void)
{
	m_size = 0;
	m_root = nullptr;
}

AVLTree::~AVLTree()
{
	delete m_root;
}

bool AVLTree::Find(AVLData value, AVLNode** res) const
{
	*res = nullptr;
	
	AVLNode* curr = m_root;

	while (curr)
	{
		if (value < curr->m_value)
		{
			*res = curr;
			curr = curr->m_left;
		}
		else if (value > curr->m_value)
		{
			*res = curr;
			curr = curr->m_right;
		}
		else
		{
			*res = curr;
			return true;
		}
	}

	return false;
}

AVLData* AVLTree::Insert(AVLData value)
{
	if (IsEmpty())
	{
		m_root = new AVLNode(value);
	}
	else
	{
		AVLNode* res = nullptr;

		if (Find(value, &res))
		{
			return false;
		}
		else
		{
			AVLNode* node = new AVLNode(value);

			if (value < res->m_value)
			{
				res->SetLeft(node);
			}
			else
			{
				res->SetRight(node);
			}

			Balance(res);
		}
	}

	m_size++;

	return true;
}

void AVLTree::Print(void)
{
	printf("(size=%d) : ", m_size);
	if (m_root) m_root->PrintRec();
	putchar('\n');
}
