#include "AVL.h"

// ------------------------------ AVLNode ------------------------------

template <typename AVLData>
AVLNode<AVLData>::AVLNode(AVLData* value)
{
	m_value = value;
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_height = 0;
}

template<typename AVLData>
AVLNode<AVLData>::~AVLNode()
{
	delete m_value;
}

template<typename AVLData>
void AVLNode<AVLData>::DestroyRec(void)
{
	if (m_left)
	{
		m_left->DestroyRec();
		delete m_left;
		m_left = nullptr;
	}

	if (m_right)
	{
		m_right->DestroyRec();
		delete m_right;
		m_right = nullptr;
	}
}

template <typename AVLData>
void AVLNode<AVLData>::SetLeft(AVLNode<AVLData>* node)
{
	m_left = node;

	if (node)
	{
		node->m_parent = this;
	}
}

template <typename AVLData>
void AVLNode<AVLData>::SetRight(AVLNode<AVLData>* node)
{
	m_right = node;

	if (node)
	{
		node->m_parent = this;
	}
}

template <typename AVLData>
void AVLNode<AVLData>::UpdateHeight(void)
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	m_height = max(L, R) + 1;
}

template <typename AVLData>
int AVLNode<AVLData>::GetBalance(void) const
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	return (R - L);
}

template <typename AVLData>
void AVLNode<AVLData>::PrintListRec(void) const
{
	if (m_left)
	{
		m_left->PrintListRec();
	}

	cout << *m_value << " ";

	if (m_right)
	{
		m_right->PrintListRec();
	}
}

template<typename AVLData>
void AVLNode<AVLData>::PrintTreeRec(int level) const
{
}

// ------------------------------ AVLTree ------------------------------

template <typename AVLData>
void AVLTree<AVLData>::Replace(AVLNode<AVLData>* parent, AVLNode<AVLData>* oldChild, AVLNode<AVLData>* newChild)
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
		if (newChild)
		{
			newChild->m_parent = nullptr;
		}

		m_root = newChild;
	}
}

template <typename AVLData>
void AVLTree<AVLData>::RotateLeft(AVLNode<AVLData>* node)
{
	AVLNode<AVLData>* parent = node->m_parent;
	AVLNode<AVLData>* child = node->m_right;

	node->SetRight(child->m_left);
	child->SetLeft(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

template <typename AVLData>
void AVLTree<AVLData>::RotateRight(AVLNode<AVLData>* node)
{
	AVLNode<AVLData>* parent = node->m_parent;
	AVLNode<AVLData>* child = node->m_left;

	node->SetLeft(child->m_right);
	child->SetRight(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

template <typename AVLData>
void AVLTree<AVLData>::Balance(AVLNode<AVLData>* node)
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

template <typename AVLData>
AVLTree<AVLData>::AVLTree()
{
	m_size = 0;
	m_root = nullptr;
}

template <typename AVLData>
AVLTree<AVLData>::~AVLTree()
{
	if (m_root)
	{
		m_root->DestroyRec();
		delete m_root;
	}
}

template <typename AVLData>
bool AVLTree<AVLData>::Find(AVLData* value, AVLNode<AVLData>** res) const
{
	if (m_root == nullptr)
	{
		*res = nullptr;
		return false;
	}

	AVLNode<AVLData>* curr = m_root;

	while (true)
	{
		if (*value < *(curr->m_value))
		{
			if (curr->m_left == nullptr)
			{
				*res = curr;
				return false;
			}

			curr = curr->m_left;
		}
		else if (*value > *(curr->m_value))
		{
			if (curr->m_right == nullptr)
			{
				*res = curr;
				return false;
			}

			curr = curr->m_right;
		}
		else
		{
			*res = curr;
			return true;
		}
	}
}

template <typename AVLData>
AVLData* AVLTree<AVLData>::Insert(AVLData* value)
{
	if (IsEmpty())
	{
		m_root = new AVLNode<AVLData>(value);
	}
	else
	{
		AVLNode<AVLData>* res = nullptr;

		if (Find(value, &res))
		{
			AVLData* old = res->m_value;
			res->m_value = value;
			return old;
		}
		else
		{
			AVLNode<AVLData>* node = new AVLNode<AVLData>(value);

			if (*value < *(res->m_value))
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

	return NULL;
}

template<typename AVLData>
bool AVLTree<AVLData>::IsIn(AVLData* value)
{
	AVLNode<AVLData>* res = nullptr;

	return Find(value, &res);
}

template<typename AVLData>
bool AVLTree<AVLData>::Remove(AVLData* value)
{
	AVLNode<AVLData>* res = nullptr;

	if (IsEmpty() || !Find(value, &res))
	{
		return false;
	}

	AVLNode<AVLData>* start = nullptr;

	if (res->m_left == nullptr)
	{
		Replace(res->m_parent, res, res->m_right);
		start = res->m_parent;
		delete res;
	}
	else if (res->m_right == nullptr)
	{
		Replace(res->m_parent, res, res->m_left);
		start = res->m_parent;
		delete res;
	}
	else
	{
		AVLNode<AVLData>* curr = res->m_left;

		while (curr->m_right)
		{
			curr = curr->m_right;
		}

		res->m_value = curr->m_value;
		Replace(curr->m_parent, curr, curr->m_left);
		start = curr->m_parent;
		delete curr;
	}

	Balance(start);

	m_size--;

	return true;
}

template <typename AVLData>
void AVLTree<AVLData>::PrintList(void) const
{
	printf("(size=%d) : ", m_size);

	if (m_root)
	{
		m_root->PrintListRec();
	}

	putchar('\n');
}

template<typename AVLData>
void AVLTree<AVLData>::PrintTree(void) const
{
}
