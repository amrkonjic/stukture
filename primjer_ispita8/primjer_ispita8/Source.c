/*Napisati program kojim se
a) Sluèajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u binarno stablo
pretraživanja. Zatim ispišemo to stablo u preorder naèinu ispisa.
b) Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u proizvoljno
definiranoj datoteci.*/

											// NE RADI BAS (mozda sad radi)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 1024
#define MIN 300
#define MAX 700

struct stablo;
typedef struct stablo* position;
typedef struct stablo {
	int broj;
	position left;
	position right;
}Stablo;

int generateRandNum();
position makeNode(int);
position insertInTree(position,position);
int printTree(position);
int loadFile(char*, position);
position findElement(position,int);
position deleteElement(position, position);
position findMin(position);
position findMax(position);


int main() {
	srand(time(0));
	int br = 0;
	position q = NULL;
	position root = NULL;
	root = (position)malloc(sizeof(Stablo));
	if (root == NULL) {
		printf("greska pri stvaranju root-a");
		return ERROR;
	}
	root->broj = 0;
	root->left = NULL;
	root->right = NULL;
	for (int i = 0; i < 100; i++) {
		br=generateRandNum();
		q = makeNode(br);
		root=insertInTree(root,q);
	}
	
	printTree(root);

	loadFile("num.txt", root);
	printTree(root);

	return 0;
}

int generateRandNum() {
	int i = 0;
	i = (rand() % (MAX - MIN + 1)) + MIN;
	return i;
}

position makeNode(int br) {
	position new = NULL;
	new = (position)malloc(sizeof(Stablo));
	if (new == NULL) {
		printf("greska pri alokaciji memorije za novi cvor");
		return NULL;
	}
	new->broj = br;
	new->left = NULL;
	new->right = NULL;
	return new;
}

position insertInTree(position root, position q) {
	if (root == NULL)
		return q;
	else if (root->broj < q->broj)
		root->right = insertInTree(root->right, q);
	else if (root->broj > q->broj)
		root->left = insertInTree(root->left, q);
	else
		free(q);
	return root;
}

int printTree(position root) {
	if (root == NULL)
		return 0;
	else {
		printTree(root->left);
		printTree(root->right);
		printf("%d\n", root->broj);
	}
	return EXIT_SUCCESS;
}

int loadFile(char* filename, position root) {
	int broj = 0;
	position q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju datoteke");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d", &broj);
		q = findElement(root, broj);
		if (q != NULL)
			deleteElement(root, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

position findElement(position root,int br) {
	if (root == NULL)
		return NULL;
	else if (root->broj < br)
		root->right = findElement(root->right, br);
	else if (root->broj > br)
		root->left = findElement(root->left, br);
	else
		return root;
}

position deleteElement(position root, position q) {
	if (root == NULL)
		return NULL;
	else {
		if (q->broj < root->broj)
			root->left=deleteElement(root->left, q);
		else if (q->broj > root->broj)
			root->right=deleteElement(root->right, q);
		else {
			if (root->left != NULL) {
				position temp = findMax(root);
				root->broj = temp->broj;
				deleteElement(root->left, temp);
			}
			else if (root->right != NULL) {
				position temp = findMin(root);
				root->broj = temp->broj;
				deleteElement(root->right, temp);
			}
			else
				free(root);
		}

	}
	return root;
}

position findMin(position root) {
	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return findMin(root->left);
}

position findMax(position root) {
	if (root == NULL)
		return NULL;
	else if (root->right == NULL)
		return root;
	else
		return findMax(root->right);
}