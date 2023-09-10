#pragma once

#include "Settings.h"

/// @brief Classe repr�sentant un noeud dans un arbre (AVL).
template <typename AVLData>
class AVLNode
{
public:

	/// @brief Valeur du noeud.
	AVLData* m_value;

	/// @brief Pointeur vers le parent.
	AVLNode<AVLData>* m_parent;

	/// @brief Pointeur vers l'enfant de gauche.
	AVLNode<AVLData>* m_left;

	/// @brief Pointeur vers l'enfant de droite.
	AVLNode<AVLData>* m_right;

	/// @brief Hauteur du noeud.
	int m_height;

	AVLNode(AVLData* value);

	/// @brief D�truit la valeur du noeud et le noeud.
	~AVLNode();

	/// @brief D�truit le sous-arbre du noeud (m�thode r�cursive).
	void DestroyRec(void);

	/// @brief Lie un noeud � gauche du noeud.
	void SetLeft(AVLNode<AVLData>* node);

	/// @brief Lie un noeud � droite du noeud.
	void SetRight(AVLNode<AVLData>* node);

	/// @brief Met � jour la hauteur du noeud [max(L, R) + 1].
	void UpdateHeight(void);

	/// @brief Renvoie la diff�rence de hauteur entre
	/// l'enfant de gauche et l'enfant de droite.
	int GetBalance(void) const;

	/// @brief Affiche le noeud et son sous-arbre sous forme d'une liste (m�thode r�cursive).
	void PrintListRec(void) const;

	/// @brief Affiche le noeud et son sous-arbre sous forme d'un arbre (m�thode r�cursive).
	void PrintTreeRec(int level = 0) const;
};

/// @brief Classe repr�sentant un arbre (AVL).
template <typename AVLData>
class AVLTree
{
private:

	/// @brief Nombre de noeuds dans l'arbre.
	int m_size;

	/// @brief Racine de l'arbre.
	AVLNode<AVLData>* m_root;
	
	/// @brief Remplace 'oldChild' par 'newChild',
	/// 'parent' est le parent de 'oldChild'.
	void Replace(AVLNode<AVLData>* parent, AVLNode<AVLData>* oldChild, AVLNode<AVLData>* newChild);

	/// @brief Fait une rotation � gauche (ce noeud et son enfant de droite).
	void RotateLeft(AVLNode<AVLData>* node);

	/// @brief Fait une rotation � droite (ce noeud et son enfant de gauche).
	void RotateRight(AVLNode<AVLData>* node);

	/// @brief R�-�quilibre l'arbre � partir d'un noeud jusqu'� la racine.
	void Balance(AVLNode<AVLData>* node);

public:

	AVLTree();

	~AVLTree();

	/// @brief Renvoie la taille de l'arbre (nombre de noeuds).
	inline int GetSize() const
	{
		return m_size;
	}

	/// @brief V�rifie si l'arbre est vide.
	inline bool IsEmpty() const
	{
		return (m_size == 0);
	}

	/// @brief Recherche une valeur dans l'arbre en log(n).
	/// @return true si la valeur existe, false sinon.
	bool Find(AVLData* value, AVLNode<AVLData>** res) const;

	/// @brief Ins�re une valeur dans l'arbre en log(n).
	/// @return true si la valeur est ins�r�e, false sinon (existe d�j�).
	bool Insert(AVLData* value);

	/// @brief V�rifie si une valeur est dans l'arbre en log(n).
	/// @return true si la valeur se trouve dans l'arbre, false sinon.
	bool IsIn(AVLData* value) const;

	/// @brief Supprime une valeur dans l'arbre en log(n).
	/// @return true si la valeur est supprim�e, false sinon (n'existe pas).
	bool Remove(AVLData* value);

	/// @brief Affiche les donn�es sous forme d'une liste.
	void PrintList(void) const;

	/// @brief Affiche les donn�es sous forme d'un arbre.
	void PrintTree(void) const;
};

template class AVLTree<int>;
