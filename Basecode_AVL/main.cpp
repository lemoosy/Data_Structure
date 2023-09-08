#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	srand(time(NULL));

	AVLTree<int> tree;

	for (int i = 0; i < 30; i++)
	{
		int* value = new int(i);
		tree.Insert(value);
	}

	for (int i = 0; i < 30; i++)
	{
		int* value = new int(i);
		tree.Remove(value);
		delete value;
	}

	tree.PrintList();

	return EXIT_SUCCESS;
}
