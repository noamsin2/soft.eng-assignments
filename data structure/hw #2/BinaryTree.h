//Author: Noam Karasso
//Score: 100
#ifndef _BINARY_TREE
#define _BINARY_TREE
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include <math.h>

#define TRUE (1==1)
#define FALSE (!TRUE)
typedef struct Node node;
struct Node {
	int data;
	node* left;
	node* right;
};
node* NewNode(int value);
node* Left(node* root);
node* Right(node* root);
node* randomInsertInto(node* root, int value) ;
node* randomTree();
void deleteTree(node* root) ;
void printNodeAtDistance(node *root , int k);
void mirrorify(node* root, node** mirror);
void preOrderTraversal(node* root);
void inOrderTraversal(node* root);
void postOrderTraversal(node* root);
node* insert(node* root, int data);
bool isFull(node* root);
void printLeaves(node* root);
int depth(node *root);
int height(node* root);
int isEmpty(node* root) ;
void printGivenLevel(node* root, int level);
int countNodesOnLevel(node* root, int level);
int levelStatistics(node* root, int level);
#endif