#ifndef _LINKEDLIST
#define _LINKEDLIST
//Author: Noam Karasso
//Score: 100
typedef struct Node node;
struct Node {
	int data;
	node* next;
};
node* BuildList();
void PrintList(node*);
node* BuildNode(int);
node* SortList(node*);
node* addToSortList(node*, node*);
int SumOddIndex(node*);
int MinNode(node*);
void ReverseList(node**);
int MiddleList(node*);
int MultHeadTail(node*);
void ifSorted(node*);
node* FreeList(node*);
#endif

