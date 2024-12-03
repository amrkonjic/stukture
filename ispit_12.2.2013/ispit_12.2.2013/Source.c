/* Napisati program koji
a) Iz datoteke èita stringove (mogu biti imena i mora ih biti min. 10) i stvara vezanu listu elemenata
sortiranih po abecedi.
b) Elemente iz datoteke ubaciti u binarno stablo i ispisati ga na inorder naèin. */
																									// RADI
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 128

struct lista;
typedef struct lista* position;
typedef struct lista {
	char rijec[MAX];
	position next;
}Lista;

struct stablo;
typedef struct stablo* stabloP;
typedef struct stablo {
	char rijec[MAX];
	stabloP left;
	stabloP right;
}Stablo;

int loadFile(char*, position);
position makeNode(char*);
int insertInList(position, position);
int printList(position);
int deleteAll(position);

stabloP makeTree(position, stabloP);
stabloP makeNodeTree(char*);
stabloP insertInTree(stabloP, stabloP);
stabloP printTree(stabloP);
stabloP deleteTree(stabloP);

int main() {
	Lista head = {
		.rijec = {0},
		.next=NULL
	};

	stabloP root=NULL;
	root = (stabloP)malloc(sizeof(Stablo));
	if (root == NULL)
		return ERROR;
	root->left = NULL;
	root->right = NULL;

	loadFile("text.txt", &head);
	printf("el liste:\n");
	printList(&head);
	
	printf("el stabla:\n");
	root = makeTree(&head, root);
	root = printTree(root);
	
	
	deleteAll(&head);
	root = deleteTree(root);
	return 0;
}

int loadFile(char* filename, position head) {
	char name[MAX] = { 0 };
	position q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", name);
		q = makeNode(name);
		insertInList(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

position makeNode(char* name) {
	position new = NULL;
	new = (position)malloc(sizeof(Lista));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->rijec, name);
	new->next = NULL;
	return new;
}

int insertInList(position head, position q) {
	while (head->next != NULL && strcmp(head->next->rijec, q->rijec) < 0)
		head = head->next;
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int printList(position head) {
	if (head->next == NULL)
		printf("lista je prazna\n");
	while (head->next != NULL)
	{
		printf("%s\n", head->next->rijec);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int deleteAll(position head) {
	position temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

stabloP makeNodeTree(char* name) {
	stabloP new = NULL;
	new = (stabloP)malloc(sizeof(Stablo));
	if (new == NULL) {
		printf("greska pri alokaciji");
		return NULL;
	}
	strcpy(new->rijec, name);
	new->left = NULL;
	new->right = NULL;

	return new;
}

stabloP insertInTree(stabloP root, stabloP q) {
	if (root == NULL)
		return q;
	else if (strcmp(root->rijec, q->rijec) < 0)
		root->right = insertInTree(root->right, q);
	else if (strcmp(root->rijec, q->rijec) > 0)
		root->left = insertInTree(root->left, q);
	else
		free(q);
	return root;
}

stabloP makeTree(position head, stabloP root) {
	stabloP q = NULL;
	while (head->next != NULL)
	{
		q = makeNodeTree(head->next->rijec);
		root = insertInTree(root, q);

		head = head->next;
	}
	return root;
}

stabloP printTree(stabloP root) {
	if (root == NULL) {
		//printf("stablo je prazno");
		return NULL;
	}
	else {
		root->left = printTree(root->left);
		printf("%s\n", root->rijec);
		root->right = printTree(root->right);

		return root;
	}
}

stabloP deleteTree(stabloP root) {
	if (root == NULL)
		return NULL;
	else {
		root->left = deleteTree(root->left);
		root->right= deleteTree(root->right);
		free(root);
	}
	return root;
}