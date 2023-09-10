#pragma once

#include "Settings.h"

/// @brief Classe représentant un noeud dans un arbre (AVL).
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

	/// @brief Détruit la valeur du noeud et le noeud.
	~AVLNode();

	/// @brief Détruit le sous-arbre du noeud (méthode récursive).
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

	/// @brief Affiche le noeud et son sous-arbre sous forme d'une liste (méthode récursive).
	void PrintListRec(void) const;

	/// @brief Affiche le noeud et son sous-arbre sous forme d'un arbre (méthode récursive).
	void PrintTreeRec(int level = 0) const;
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

	/// @brief Ré-équilibre l'arbre à partir d'un noeud jusqu'à la racine.
	void Balance(AVLNode<AVLData>* node);

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
	bool Find(AVLData* value, AVLNode<AVLData>** res) const;

	/// @brief Insère une valeur dans l'arbre en log(n).
	/// @return true si la valeur est insérée, false sinon (existe déjà).
	bool Insert(AVLData* value);

	/// @brief Vérifie si une valeur est dans l'arbre en log(n).
	/// @return true si la valeur se trouve dans l'arbre, false sinon.
	bool IsIn(AVLData* value) const;

	/// @brief Supprime une valeur dans l'arbre en log(n).
	/// @return true si la valeur est supprimée, false sinon (n'existe pas).
	bool Remove(AVLData* value);

	/// @brief Affiche les données sous forme d'une liste.
	void PrintList(void) const;

	/// @brief Affiche les données sous forme d'un arbre.
	void PrintTree(void) const;
};

template class AVLTree<int>;
