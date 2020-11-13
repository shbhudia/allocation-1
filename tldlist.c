//Niall Boyd
//2392483b
//Systems Programming Assessed Exercise 1
//This is my own work as defined in the Academic Ethic agreement I have signed
//I have used the folling websites to aid in my uderstanding of various asoects of this program
//1. geekforgeeks.org/avl-tree-set-1-insertion
//2. programiz.com/dsa/tree-traversal
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"
#include "tldlist.h"
#include "ctype.h"

struct tldlist{
	TLDNode *root;
	Date *begin;
	Date *end;
	long count;
	long size;
};

struct tldnode{
	char *key;
	TLDNode *left;
	TLDNode *right;
	long height;
	long count;
};

struct tlditerator{
	long next;
	long size;
	TLDNode **nodes;
};

long max(long a, long b){
	return (a > b)? a:b;
}

long height(TLDNode *node){
	if (node==NULL)
		return 0;
	return node->height;
}


TLDNode* newNode(char *key){
	TLDNode* node = (TLDNode*) malloc(sizeof(TLDNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
};

TLDNode *rightRotate(TLDNode *y){
	TLDNode *x = y->left;
	TLDNode *z = x->right;
	x->right = y;
	y->left = z;
	
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;
	
	return x;
}

TLDNode *leftRotate(TLDNode *x){
	TLDNode *y = x->right;
	TLDNode *z = y->left;

	y->left = x;
	x->right = z;

	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;	
	
	return y;
}

long getBalance(TLDNode *n){
	if (n == NULL)
		return 0;
	return height(n->left) - height(n->right);
}

TLDList *tldlist_create(Date *begin, Date *end){
	TLDList *tld = (TLDList*) malloc(sizeof(TLDList));
	if(tld==NULL)
		return NULL;
	tld->root = NULL;
	tld->begin = date_duplicate(begin);
	tld->end = date_duplicate(end);
	tld->size = 0;
	tld->count = 0;
	return tld;
}

void destroy_nodes(TLDNode *node){
	if(node==NULL)
		return;
	destroy_nodes(node->left);
	destroy_nodes(node->right);
	free(node);
}

void tldlist_destroy(TLDList *tld){
	if(tld!=NULL)
		destroy_nodes(tld->root);
	free(tld);
}

TLDNode *rebalance(TLDList *tld, TLDNode *root, TLDNode *node){
	long balance = getBalance(root);
	if(balance > 1 && strcmp(node->key, root->left->key) < 0)
		return rightRotate(root);
	if(balance < -1 && strcmp(node->key, root->right->key) > 0)
		return leftRotate(root);
	if(balance > 1 && strcmp(node->key, root->right->key) > 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance < -1 && strcmp(node->key, root->right->key) < 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

TLDNode *insert_tld(TLDList *list, TLDNode *root, TLDNode *node){
	if(root == NULL){
		++list->size;
		return node;
	}
	if(strcmp(node->key, root->key) < 0){
		root->left = insert_tld(list,root->left,node);
	}else if(strcmp(node->key, root->key)>0){
		root->right = insert_tld(list, root->right, node);
	}else{
		++root->count;
	}
	root->height = max(height(root->left), height(root->right))+1;
	root = rebalance(list, root, node);
	return root;
}

int tldlist_add(TLDList *tld, char *hostname, Date *d){
	if(date_compare(tld->begin, d) > 0 || date_compare(tld->end, d) < 0)
		return 0;	

	char *input = strrchr(hostname, '.')+1;


	//convert to lower case as tld needs to be case insensitive
	char* tldName = (char *)malloc(sizeof(hostname));
	for(int i = 0; i < strlen(input); i++){
		tldName[i] = tolower(input[i]);
	}

	
	TLDNode *node = newNode(tldName);
	insert_tld(tld, tld->root, node);
	(tld->count)++;
	return 1;
}	

long tldlist_count(TLDList *tld){
	return tld->count;
}

//inorder traversal
void traverse(TLDNode* root, TLDNode *nodes[], long *index){
	if(root == NULL)
		return;
	if(root->left != NULL)
		traverse(root->left, nodes, index);
	nodes[*index] = root;
	(*index)++;
	if(root->right != NULL)
		traverse(root->right, nodes, index);	
}

TLDIterator *tldlist_iter_create(TLDList *tld){
	TLDIterator *tlditerator = (TLDIterator *) malloc(sizeof(TLDIterator));
	TLDNode **nodes = (TLDNode **) malloc(sizeof(TLDNode *)*tld->size);

	if(tlditerator==NULL)
		return NULL;
	
	//long *i = (long *) malloc(sizeof(long));
	long *i = 0;
	traverse(tld->root, nodes, i);
	tlditerator->next = 0;
	tlditerator->size = tld->size;
	tlditerator->nodes = nodes;
	
	return tlditerator;
}

	
TLDNode *tldlist_iter_next(TLDIterator *iter){
	if(iter->next >= (iter->size)+1)
		return NULL;
	return iter->nodes[iter->next++];	
}

void tldlist_iter_destroy(TLDIterator *iter){
	free(iter->nodes);
	free(iter);
}

char *tldnode_tldname(TLDNode *node){
	return node->key;
}

long tldnode_count(TLDNode *node){
	if(node==NULL)
		return 0;
	return node->count;
}













