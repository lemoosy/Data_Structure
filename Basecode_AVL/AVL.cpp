#include "AVL.h"

// ------------------------------ AVLNode ------------------------------

template <typename T>
AVLNode<T>::AVLNode(T value)
{
	m_value = value;
	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_height = 0;
}

template <typename T>
AVLNode<T>::~AVLNode()
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

template <typename T>
void AVLNode<T>::SetLeft(AVLNode<T>* node)
{
	m_left = node;

	if (node)
	{
		node->m_parent = this;
	}
}

template <typename T>
void AVLNode<T>::SetRight(AVLNode<T>* node)
{
	m_right = node;

	if (node)
	{
		node->m_parent = this;
	}
}

template <typename T>
void AVLNode<T>::UpdateHeight(void)
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	m_height = max(L, R) + 1;
}

template <typename T>
int AVLNode<T>::GetBalance(void) const
{
	int L = (m_left ? m_left->m_height : -1);
	int R = (m_right ? m_right->m_height : -1);

	return (R - L);
}

template <typename T>
void AVLNode<T>::PrintRec(void) const
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

// ------------------------------ AVLTree ------------------------------

template <typename T>
void AVLTree<T>::Replace(AVLNode<T>* parent, AVLNode<T>* oldChild, AVLNode<T>* newChild)
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

template <typename T>
void AVLTree<T>::RotateLeft(AVLNode<T>* node)
{
	AVLNode<T>* parent = node->m_parent;
	AVLNode<T>* child = node->m_right;

	node->SetRight(child->m_left);
	child->SetLeft(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

template <typename T>
void AVLTree<T>::RotateRight(AVLNode<T>* node)
{
	AVLNode<T>* parent = node->m_parent;
	AVLNode<T>* child = node->m_left;

	node->SetLeft(child->m_right);
	child->SetRight(node);
	Replace(parent, node, child);

	node->UpdateHeight();
	child->UpdateHeight();
}

template <typename T>
void AVLTree<T>::Balance(AVLNode<T>* node)
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

template <typename T>
AVLTree<T>::AVLTree()
{
	m_size = 0;
	m_root = nullptr;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	delete m_root;
}

template <typename T>
bool AVLTree<T>::Find(T value, AVLNode<T>** res) const
{
	*res = nullptr;
	
	AVLNode<T>* curr = m_root;

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

template <typename T>
T* AVLTree<T>::Insert(T value)
{
	if (IsEmpty())
	{
		m_root = new AVLNode<T>(value);
	}
	else
	{
		AVLNode<T>* res = nullptr;

		if (Find(value, &res))
		{
			T* old = &(res->m_value);
			res->m_value = value;
			return old;
		}
		else
		{
			AVLNode<T>* node = new AVLNode<T>(value);

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

	return NULL;
}

template <typename T>
void AVLTree<T>::Print(void) const
{
	printf("(size=%d) : ", m_size);

	if (m_root)
	{
		m_root->PrintRec();
	}

	putchar('\n');
}
