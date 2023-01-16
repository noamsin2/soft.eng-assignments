//Author: Noam Karasso
#include "postfix.h"

node* Left(node* root) 
// get left node
{
	return root->left;
}

node* Right(node* root)
// get right node
{
	return root->right;
}

node* NewNode(char* value)  
// creating a new node 
{ 
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void deleteTree(node* root) 
/* Deleting tree using postorder transversal.
 Before deleting the parent node, 
 function delete child nodes first.*/
{
	if (NULL==root)
		return;
	deleteTree(Left(root));
	deleteTree(Right(root));
    free(root->data);//added to avoid memory leak because in my code i used memory allocation for each node's data
	free(root);
}

void push(node* new_data)
// push Node data to stack
{
    stack* new_node = (stack*)malloc(sizeof(stack));
    new_node->data = new_data;
    new_node->next = top;
    top = new_node;
}
node* pop()
// delete head of stack and Return the last element
{
    if (top == NULL) {
        printf("Error, can't pop\n");
        return NULL;
    }
    node* data = top->data;
    stack* temp = top;
    top = top->next;
    free(temp);
    return data;
}

node* create_expr_tree_postfix(char* postfix)
// a function that receives a string in the form of a postfix and creates a tree accordingly
// 1. separete first symbols until space
// 2. check if a token is an operand
// 3. check if a token is an operator
// 4. saparate next symbols
// 5. returning the expression tree
{
    for (int i = 0; postfix[i] != '\0'; i++) {
        int digitCount = 0;
        int j;
        if (isdigit(postfix[i])) {//if its a digit we check if there are more digits after it
            for (j = i; isdigit(postfix[j]); j++)
                digitCount++;
            char* digits = (char*)malloc((digitCount+1) * sizeof(char));//make a char pointer to hold the number
            int index = 0;
            for (i; i < j; i++) {//use the i parameter to increase so we dont repeat the same digit twice
                digits[index] = postfix[i];
                index++;
            }
            digits[index] = '\0';//to avoid weird characters
            node* new_node = NewNode(digits);//make a new node
            push(new_node);//push the node to the stack
        }
        else if (isspace(postfix[i]))
            continue;
        else//if its not a digit or a space then its an operator because we assume its a valid expression
        {
            //make a new operator node with the digits as his children(first right and then left to maintain order)
            char* operator = (char*)malloc(1 + sizeof(char));
            operator[0] = postfix[i];
            operator[1] = '\0';//to avoid weird characters
            node* new_node = NewNode(operator);
            new_node->right = pop();
            new_node->left = pop();
            //then push the operator node
            push(new_node);
        }
    }
    return pop();//return root
}

void inOrder(node* treeNode)
// a function that prints the expression in the infix form
{
    if (treeNode != NULL) {
        //char data = *treeNode->data;
        if (ispunct(*treeNode->data))//if its an operator
            printf("( ");
        inOrder(treeNode->left);
        printf("%s ", treeNode->data);
        inOrder(treeNode->right);
        if (ispunct(*treeNode->data))//if its an operator)
            printf(") ");
    }
}

void preOrder(node* treeNode) 
// a function that prints the expression in the prefix form
{ 
    if (treeNode != NULL) {
        printf("%s ", treeNode->data);
        preOrder(treeNode->left);
        preOrder(treeNode->right);
    }
}

void postOrder(node* treeNode)
// a function that prints the expression in the postfix form
{
    if (treeNode != NULL) {
        postOrder(treeNode->left);
        postOrder(treeNode->right);
        printf("%s ", treeNode->data);
    }
}

int evaluateExpression(node* root)
// a function that evaluates the expression tree
{
        //char data = *treeNode->data;

        if (ispunct(*root->data)) {//if its an operator
            int operand1 = evaluateExpression(root->left);
            int operand2 = evaluateExpression(root->right);
            if (*root->data == '+')
                return operand1 + operand2;
            else if (*root->data == '*')
                return operand1 * operand2;
            else if (*root->data == '/')
                return operand1 / operand2;
            else if (*root->data == '^')
                return pow(operand1, operand2);
            else if (*root->data == '-')
                return operand1 - operand2;
        }
        else //if the root is an integer
            return atoi(root->data);//converts string to int
}
//optional main
//int main() {
//    char postfix[] = "12 32 + 3 + 4 +";
//    node* root = create_expr_tree_postfix(postfix);
//    preOrder(root);
//    printf("\n");
//    postOrder(root);
//    printf("\n");
//    inOrder(root);
//    printf("\n");
//    printf("%d",evaluateExpression(root));
//    deleteTree(root);
//	return 0;
//}