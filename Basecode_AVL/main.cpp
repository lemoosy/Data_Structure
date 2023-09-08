#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	srand(time(NULL));

	AVLTree<int> tree;

	for (int i = 0; i < 30; i++)
	{
		tree.Insert(i);
	}

	for (int i = 0; i < 30; i++)
	{
		tree.Remove(i);
	}

	tree.PrintList();

	return EXIT_SUCCESS;
}
