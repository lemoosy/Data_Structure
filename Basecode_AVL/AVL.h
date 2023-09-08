#pragma once

#include "Settings.h"

/// @brief Classe représentant un noeud dans un arbre (AVL).
template <typename AVLData>
class AVLNode
{
public:
	
	/// @brief Valeur du noeud.
	AVLData m_value;

	/// @brief Pointeur vers le parent.
	AVLNode<AVLData>* m_parent;

	/// @brief Pointeur vers l'enfant de gauche.
	AVLNode<AVLData>* m_left;

	/// @brief Pointeur vers l'enfant de droite.
	AVLNode<AVLData>* m_right;

	/// @brief Hauteur du noeud.
	int m_height;

	AVLNode(AVLData value);

	/// @brief Supprimer le noeud et son sous-arbre (méthode récursive).
	void DestroyRec(void);

	/// @brief Lie un noeud à gauche du noeud.
	void SetLeft(AVLNode<AVLData>* node);

	/// @brief Lie un noeud à droite du noeud.
	void SetRight(AVLNode<AVLData>* node);

	/// @brief Met à jour la hauteur du noeud [max(L, R) + 1].
	void UpdateHeight(void);

	/// @brief Renvoie la différence de hauteur entre
	/// l'enfant de gauche et l'enfant de droite.
	int GetBalance(void) const;

	/// @brief Affiche le noeud et son sous-arbre (méthode récursive).
	void PrintListRec(void) const;


	void PrintTreeRec(char ch = '*', int level = 0) const;
};

/// @brief Classe représentant un arbre (AVL).
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

	/// @brief Fait une rotation à gauche (ce noeud et son enfant de droite).
	void RotateLeft(AVLNode<AVLData>* node);

	/// @brief Fait une rotation à droite (ce noeud et son enfant de gauche).
	void RotateRight(AVLNode<AVLData>* node);

	/// @brief Ré-équilibre l'arbre.
	void Balance(AVLNode<AVLData>* node);

	/// @brief Affiche les données sous forme d'un arbre (méthode récurcive).
	void PrintTreeRec(int level = 0) const;

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
	/// @return true si la valeur existe, sinon false.
	bool Find(AVLData value, AVLNode<AVLData>** res) const;

	/// @brief Insère une valeur dans l'arbre en log(n).
	/// @return NULL si la valeur est ajoutée,
	/// sinon renvoie le pointeur de la valeur précédente.
	AVLData* Insert(AVLData value);

	/// @brief Supprime une valeur dans l'arbre en log(n).
	/// @return true si la valeur est supprimée, sinon false.
	bool Remove(AVLData value);
	
	/// @brief Affiche les données sous forme d'une liste.
	void PrintList(void) const;

	/// @brief Affiche les données sous forme d'un arbre.
	void PrintTree(void) const;
};

template class AVLTree<int>;
template class AVLTree<float>;
template class AVLTree<char>;
