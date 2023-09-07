#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	AVLTree<int> tree;

	for (int i = 0; i < 100; i++)
	{
		tree.Insert(rand() % 100);
	}

	tree.Print();

	AVLTree<char> tree2;

	for (int i = 0; i < 100; i++)
	{
		tree2.Insert(rand() % 256);
	}

	tree2.Print();

	return EXIT_SUCCESS;
}
