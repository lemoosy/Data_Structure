#pragma once

#include "Settings.h"

/// @brief Type valeur d'un noeud dans un arbre (AVL).
typedef int AVLData;

/// @brief Classe représentant un noeud dans un arbre (AVL).
class AVLNode
{
public:
	
	/// @brief Valeur du noeud.
	AVLData m_value;

	/// @brief Pointeur vers le parent.
	AVLNode* m_parent;

	/// @brief Pointeur vers l'enfant de gauche.
	AVLNode* m_left;

	/// @brief Pointeur vers l'enfant de droite.
	AVLNode* m_right;

	/// @brief Hauteur du noeud.
	int m_height;

	AVLNode(AVLData value);

	~AVLNode();

	/// @brief Lie un noeud à gauche du noeud.
	void SetLeft(AVLNode* node);

	/// @brief Lie un noeud à droite du noeud.
	void SetRight(AVLNode* node);

	/// @brief Met à jour la hauteur du noeud [max(L, R) + 1].
	void UpdateHeight(void);

	/// @brief Renvoie la différence de hauteur entre
	/// l'enfant de gauche et l'enfant de droite.
	int GetBalance(void) const;

	/// @brief Affiche le noeud et son sous-arbre (méthode récursive).
	void PrintRec(void) const;
};

/// @brief Classe représentant un arbre (AVL).
class AVLTree
{
private:

	/// @brief Nombre de noeuds dans l'arbre.
	int m_size;

	/// @brief Racine de l'arbre.
	AVLNode* m_root;
	
	/// @brief Remplace 'oldChild' par 'newChild',
	/// 'parent' est le parent de 'oldChild'.
	void Replace(AVLNode* parent, AVLNode* oldChild, AVLNode* newChild);

	/// @brief Fait une rotation à gauche (ce noeud et son enfant de droite).
	void RotateLeft(AVLNode* node);

	/// @brief Fait une rotation à droite (ce noeud et son enfant de gauche).
	void RotateRight(AVLNode* node);

	/// @brief Ré-équilibre l'arbre.
	void Balance(AVLNode* node);

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
	bool Find(AVLData value, AVLNode** res) const;

	/// @brief Insère une valeur dans l'arbre en log(n).
	/// @return NULL si la valeur est ajoutée,
	/// sinon renvoie le pointeur de la valeur précédente.
	AVLData* Insert(AVLData value);
	
	/// @brief Affiche l'arbre.
	void Print(void);
};
