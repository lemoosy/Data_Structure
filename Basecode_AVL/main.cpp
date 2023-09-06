#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	AVLTree tree;

	for (int i = 0; i < 100; i++)
	{
		tree.Insert(rand() % 100);
	}

	tree.Print();
}
