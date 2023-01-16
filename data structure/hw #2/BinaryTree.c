//Author: Noam Karasso
//Score: 100
#include"BinaryTree.h"

/*=========================================================*/
node* NewNode(int value) 
/* Function that allocates a new node with the
given data and NULL left and right pointers */
{
	node* p = (node*)malloc(sizeof(node));
	p->data = value;
	p->left = NULL;
	p->right = NULL;
	return p;
}
node* Left(node* root) {
	return root->left;
}
node* Right(node* root) {
	return root->right;
}
/*============================a recursive function to help us in ex1===========================*/
node* randomInsertInto(node* root, int value) {
	if (root == NULL)//if there's no node at that spot it makes a new node
		root = NewNode(value);
	//if there is a node there, it searches for a new one randomly
	else if (rand() % 2 == 0)
		root->left = randomInsertInto(root->left, value);//proceed to the left node
	else
		root->right = randomInsertInto(root->right, value);//proceed to the right node
	return root;
}
/*============================ex1===========================*/
node* randomTree()
/* function creating random binary tree */
{
	node* root = NULL;
	int listSize = rand() % 21;//0-20 nodes in the tree
	for (int i = 0; i < listSize; i++) {
		int value = rand() % 21;//random value 0-20
		root = randomInsertInto(root, value);
	}
	return root;
}

/*============================ex2===========================*/
void deleteTree(node* root) //we'll use the postorder algorithm for this
{
	if (root != NULL) {
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}	
}

/*============================ex3===========================*/
void printNodeAtDistance(node *root , int k)
/*Given a Binary Tree and a positive integer ‘k’, write code which will 
print all the nodes which are at distance ‘k’ from the root.
For example: For Binary Tree on the right side, Following are the 
nodes which should get printed for the below values of ‘k’*/
{
	if (k > 0 && root != NULL) {
		printNodeAtDistance(root->left, k - 1);
		printNodeAtDistance(root->right, k - 1);
	}
	if (k == 0 && root != NULL)//if it reached distance k print the node
		printf("%d ", root->data);
}

/*============================ex4===========================*/
void mirrorify(node* root, node** mirror)
/*Mirrorify function takes two trees, riginal tree and a mirror tree
It recurses on both the trees,but when original tree recurses on left,
mirror tree recurses on right and vice-versa*/
{
	if (root != NULL) {
		*mirror = NewNode(root->data);//make a new node with the value of the original tree
		mirrorify(root->left, &(*mirror)->right);//send the address of the mirror's current right node
		mirrorify(root->right, &(*mirror)->left);//send the address of the mirror's current left node
	}
	
}

/*============================ex5===========================*/
void preOrderTraversal(node* root)
{
	if (root != NULL) {
		printf("%d ", root->data);
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void inOrderTraversal(node* root)
{
	if (root != NULL) {
		inOrderTraversal(root->left);
		printf("%d ", root->data);
		inOrderTraversal(root->right);
	}
}

void postOrderTraversal(node* root)
{
	if (root != NULL) {
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		printf("%d ", root->data);
	}
}

/*============================ex6===========================*/
node* insert(node* root, int data) 
// 1. If the tree is empty, return a new, single node
// 2. Otherwise, recur down the tree
// 3. return the (unchanged) node pointer
{
	if (root == NULL)//if there's no node at that spot it makes a new node
		root = NewNode(data);
	else if (root->data < data)
		root->right = insert(root->right, data);//proceed to the right node
	else if(root->data > data)
		root->left = insert(root->left, data);//proceed to the left node
	return root;
}

/*============================ex7===========================*/
bool isFull(node* root) 
// 1. If root = NULL this a full binary tree
// 2. If the element hasn't son this is a full binary tree
// 3. Browse the left and right side to see if it is a full binary tree
{	
	if (root == NULL)//if the tree is empty return true
		return TRUE;
	else if (root->left != NULL && root->right != NULL) {//keep going down the tree as long as the node has 2 sons
		return isFull(root->left) && isFull(root->right);
	}
	else if ((root->left == NULL && root->right != NULL) || (root->right == NULL && root->left != NULL))//if a node has only 1 son, return false
		return FALSE;
	else//if a node has 0 sons return true
		return TRUE;
}

/*============================ex8===========================*/
void printLeaves(node* root)
{
	if (root != NULL) {
		printLeaves(root->left);
		printLeaves(root->right);
		if (root->left == NULL && root->right == NULL)//if the node has no sons then its a leaf
			printf("%d ", root->data);
	}
}

/*============================ex9===========================*/
int depth(node *root)
{
	int leftT, rightT;
	if (root == NULL)
		return -1;
	leftT = depth(root->left);//count the left sub-tree's depth
	rightT = depth(root->right);//count the right sub-tree's depth
	if (leftT > rightT)//check which is farther from the root and take the higher value + 1
		return leftT + 1;
	else
		return rightT + 1;
}

/*============================ex10===========================*/
//int levelStatistics(node* root, int level) //recursive solution (not efficient)
//{
//	if (root != NULL) {
//		if (level < 0 || (level > depth(root) && root->left != NULL && root->right != NULL)) {//a very sofishticated code that works
//			printf("Not a valid level\n");
//			return 0;
//		}
//	}
//	else if (root == NULL)
//		return 0;
//	if (level > 0) {
//		return levelStatistics(root->left, level - 1) + levelStatistics(root->right, level - 1);
//	}
//	else if (level == 0) {
//		printf("%d ", root->data);
//		return 1;
//	}
//}
/*============================ex10===========================*/
int levelStatistics(node* root, int level) {
	if (level < 0 || level > depth(root)) {//check that the input value is within the tree's range
		printf("Not a valid level\n");
		return 0;
	}
	printNodeAtDistance(root, level);//to print the nodes in the level
	return countNodesOnLevel(root, level);//to count the nodes in the level
}
/*============================a recursive function that will help us in ex10===========================*/
int countNodesOnLevel(node* root, int level) {
	if (level > 0 && root != NULL) {
		return countNodesOnLevel(root->left, level - 1) + countNodesOnLevel(root->right, level - 1);
	}
	if (level == 0 && root != NULL)//if it reached distance k print the node
		return 1;
	return 0;
}