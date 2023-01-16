//Author: Noam Karasso
//Score: 100
#include "BinaryTree.h"

int main() {
	time_t t;
	srand(time(&t));
	node* root = randomTree();
	node* mirror = NULL;
	mirrorify(root, &mirror);
	inOrderTraversal(root);
	printf("\n");
	root = insert(root, 10);
	inOrderTraversal(root);
	printf("\n");
	inOrderTraversal(mirror);
	printf("\n");
	printf("depth: %d\n", depth(root));
	printLeaves(root);
	printf("Full: %d\n", isFull(root));
	deleteTree(mirror);
	printf("LevelStatistics 2:\n%d\n", levelStatistics(root, 2));
	printf("LevelStatistics 3:\n%d\n", levelStatistics(root, 3));
	printf("LevelStatistics 4:\n%d\n", levelStatistics(root, 4));
	printf("LevelStatistics 5:\n%d\n", levelStatistics(root, 5));
	deleteTree(root);
	
	return 0;
}