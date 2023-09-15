#pragma once

#include "Settings.h"

/// @brief Structure représentant un noeud dans une liste doublement chaînée.
template <typename DListData>
class DListNode
{
public:

	/// @brief Valeur du noeud.
	DListData* m_value;

	/// @brief Pointeur vers le noeud précédent.
	DListNode* m_prev;

	/// @brief Pointeur vers le noeud suivant.
	DListNode* m_next;

	DListNode(
		DListData* value = nullptr,
		DListNode<DListData>* prev = nullptr,
		DListNode<DListData>* next = nullptr
	);

	~DListNode();

	/// @brief Insère le noeud dans une liste.
	void Insert(void);

	/// @brief Supprime le noeud dans une liste.
	void Remove(void);
};

template <typename DListData>
DListNode<DListData>::DListNode(DListData* value, DListNode<DListData>* prev, DListNode<DListData>* next)
{
	m_value = value;
	m_prev = prev;
	m_next = next;
}

template<typename DListData>
DListNode<DListData>::~DListNode()
{
	if (m_value)
	{
		delete m_value;
	}
}

template<typename DListData>
void DListNode<DListData>::Insert(void)
{
	m_next->m_prev = this;
	m_prev->m_next = this;
}

template <typename DListData>
void DListNode<DListData>::Remove(void)
{
	assert(m_next != this);

	m_next->m_prev = m_prev;
	m_prev->m_next = m_next;

	m_prev = nullptr;
	m_next = nullptr;
}

/// @brief Structure représentant une liste doublement chaînée.
template <typename DListData>
class DList
{
private:

	/// @brief Taille de la liste.
	int m_size;

	/// @brief Sentinelle.
	DListNode<DListData>* m_sentinel;

public:

	DList();

	~DList();

	/// @brief Retourne la taille de la liste.
	inline int GetSize() const
	{
		return m_size;
	}

	/// @brief Vérifie si la liste est vide.
	inline bool IsEmpty() const
	{
		return (m_size == 0);
	}

	/// @brief Insère une valeur en premier dans la liste.
	void InsertFirst(DListData* value);

	/// @brief Insère une valeur en dernier dans la liste.
	void InsertLast(DListData* value);

	/// @brief Insère une valeur de manière ordonnée dans la liste.
	void InsertSorted(DListData* value);

	/// @brief Retire et retourne la première valeur de la liste.
	DListData* PopFirst();

	/// @brief Retire et retourne la dernière valeur de la liste.
	DListData* PopLast();

	/// @brief Supprime une valeur dans la liste.
	DListData* RemoveAt(int index);

	/// @brief Afiche la liste.
	void Print() const;

	/// @brief Renvoie un noeud dans la liste.
	DListNode* GetNode(int index) const;

	/// @brief Renvoie une valeur dans la liste.
	DListData* GetValue(int index) const;

	/// @brief Vérifie si deux listes sont égales.
	bool IsEqual(DList const& list) const;
};

template <typename DListData>
DList<DListData>::DList()
{
	m_size = 0;
	m_sentinel = new DListNode<DListData>;
	m_sentinel->m_prev = m_sentinel;
	m_sentinel->m_next = m_sentinel;
}

template<typename DListData>
inline DList<DListData>::~DList()
{
	while (!IsEmpty())
	{
		DListData* res = PopFirst();
		delete res;
	}

	delete m_sentinel;
}

template <typename DListData>
void DList<DListData>::InsertFirst(DListData* value)
{
	DListNode<DListData>* node = new DListNode<DListData>(
		value,
		m_sentinel,
		m_sentinel->m_next
	);

	node->Insert();

	m_size++;
}

template <typename DListData>
void DList<DListData>::InsertLast(DListData* value)
{
	DListNode<DListData>* node = new DListNode<DListData>(
		value,
		m_sentinel->m_prev,
		m_sentinel
	);

	node->Insert();

	m_size++;
}

template <typename DListData>
void DList<DListData>::InsertSorted(DListData* value)
{
	DListNode<DListData>* curr = m_sentinel->m_next;

	while ((curr != m_sentinel) && (curr->m_value < value))
	{
		curr = curr->m_next;
	}

	DListNode<DListData>* node = new DListNode<DListData>(
		value,
		curr->m_prev,
		curr
	);

	node->Insert();

	m_size++;
}

template <typename DListData>
DListData* DList<DListData>::PopFirst()
{
	assert(m_size > 0);

	DListNode<DListData>* node = m_sentinel->m_next;

	node->Remove();

	DListData* res = node->m_value;

	delete node;

	m_size--;

	return res;
}

template <typename DListData>
DListData* DList<DListData>::PopLast()
{
	assert(m_size > 0);

	DListNode<DListData>* node = m_sentinel->m_prev;

	node->Remove();

	DListData* res = node->m_value;

	delete node;

	m_size--;

	return res;
}

template <typename DListData>
void DList<DListData>::Print() const
{
	printf("(size=%d) : ", m_size);

	DListNode<DListData>* curr = m_sentinel->m_next;

	while (curr != m_sentinel)
	{
		cout << curr->m_value << " ";
		curr = curr->m_next;
	}

	putchar('\n');
}

template <typename DListData>
DListNode<DListData>* DList<DListData>::GetNode(int index) const
{
	if (index < 0)
	{
		assert(-m_size <= index);

		DListNode<DListData>* curr = m_sentinel;

		while (index < 0)
		{
			index++;
			curr = curr->m_prev;
		}

		return curr;
	}
	else
	{
		assert(index < m_size);

		DListNode<DListData>* curr = m_sentinel->m_next;

		while (index > 0)
		{
			index--;
			curr = curr->m_next;
		}

		return curr;
	}
}

template <typename DListData>
DListData* DList<DListData>::GetValue(int index) const
{
	return GetNode(index)->m_value;
}

template <typename DListData>
DListData* DList<DListData>::RemoveAt(int index)
{
	DListNode<DListData>* node = GetNode(index);

	node->Remove();

	DListData* res = node->m_value;

	m_size--;

	return res;
}

template <typename DListData>
bool DList<DListData>::IsEqual(DList const& list) const
{
	if (GetSize() != list.GetSize()) return false;

	DListNode<DListData>* curr0 = m_sentinel->m_next;
	DListNode<DListData>* curr1 = list.m_sentinel->m_next;

	while (curr0 != m_sentinel)
	{
		if (curr0->m_value != curr1->m_value)
		{
			return false;
		}

		curr0 = curr0->m_next;
		curr1 = curr1->m_next;
	}

	return true;
}

template <typename DListData>
bool operator==(DList<DListData> const& l1, DList<DListData> const& l2)
{
	return l1.IsEqual(l2);
}

template <typename DListData>
ostream& operator<<(ostream& flux, DList<DListData> const& list)
{
	list.Print();

	return flux;
}
