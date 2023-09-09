#include "Settings.h"
#include "AVL.h"

using namespace std;

int main()
{
	srand(time(NULL));

	AVLTree<int>* tree = new AVLTree<int>();

	for (int i = 0; i < 10; i++)
	{
		int* value = new int(i);
		tree->Insert(value);
	}

	tree->PrintList();
	tree->PrintTree();

	delete tree;

	return EXIT_SUCCESS;
}
