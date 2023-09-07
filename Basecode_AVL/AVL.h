#pragma once

#include "Settings.h"

/// @brief Classe représentant un noeud dans un arbre (AVL).
template <typename T>
class AVLNode
{
public:
	
	/// @brief Valeur du noeud.
	T m_value;

	/// @brief Pointeur vers le parent.
	AVLNode<T>* m_parent;

	/// @brief Pointeur vers l'enfant de gauche.
	AVLNode<T>* m_left;

	/// @brief Pointeur vers l'enfant de droite.
	AVLNode<T>* m_right;

	/// @brief Hauteur du noeud.
	int m_height;

	AVLNode(T value);

	~AVLNode();

	/// @brief Lie un noeud à gauche du noeud.
	void SetLeft(AVLNode<T>* node);

	/// @brief Lie un noeud à droite du noeud.
	void SetRight(AVLNode<T>* node);

	/// @brief Met à jour la hauteur du noeud [max(L, R) + 1].
	void UpdateHeight(void);

	/// @brief Renvoie la différence de hauteur entre
	/// l'enfant de gauche et l'enfant de droite.
	int GetBalance(void) const;

	/// @brief Affiche le noeud et son sous-arbre (méthode récursive).
	void PrintRec(void) const;
};

/// @brief Classe représentant un arbre (AVL).
template <typename T>
class AVLTree
{
private:

	/// @brief Nombre de noeuds dans l'arbre.
	int m_size;

	/// @brief Racine de l'arbre.
	AVLNode<T>* m_root;
	
	/// @brief Remplace 'oldChild' par 'newChild',
	/// 'parent' est le parent de 'oldChild'.
	void Replace(AVLNode<T>* parent, AVLNode<T>* oldChild, AVLNode<T>* newChild);

	/// @brief Fait une rotation à gauche (ce noeud et son enfant de droite).
	void RotateLeft(AVLNode<T>* node);

	/// @brief Fait une rotation à droite (ce noeud et son enfant de gauche).
	void RotateRight(AVLNode<T>* node);

	/// @brief Ré-équilibre l'arbre.
	void Balance(AVLNode<T>* node);

public:

	AVLTree();

	~AVLTree();

	/// @brief Renvoie la taille de l'arbre (nombre de noeuds).
	inline int GetSize() const
	{
		return m_size;
	}

	/// @brief Vérifie si l'arbre est vide.
	inline bool IsEmpty() const
	{
		return (m_size == 0);
	}

	/// @brief Recherche une valeur dans l'arbre en log(n).
	/// @return true si la valeur existe, false sinon.
	bool Find(T value, AVLNode<T>** res) const;

	/// @brief Insère une valeur dans l'arbre en log(n).
	/// @return NULL si la valeur est ajoutée,
	/// sinon renvoie le pointeur de la valeur précédente.
	T* Insert(T value);
	
	/// @brief Affiche l'arbre.
	void Print(void) const;
};

template class AVLTree<int>;
template class AVLTree<float>;
template class AVLTree<char>;
