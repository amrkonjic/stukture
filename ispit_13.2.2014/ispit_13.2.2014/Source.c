/* Napisati program koji èita iz datoteke dio teksta, te kreira binarno stablo pretraživanja. Binarno stablo se
kreira na naèin da se u njega upisuju sve razlièite rijeèi iz teksta koji je zapisan u datoteci s pripadajuæim
duljinama unesene rijeèi.
Potrebno je izraèunati prosjeènu duljinu svake rijeèi zapisane u binarnom stablu.
Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one rijeèi koje su dulje
od prosjeène duljine svih rijeèi, te ispisati tu vezanu listu. */
																							//ne radi

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256
#define MAX 50
#define EXIT_SUCCESS 0
#define ERROR -1

struct cvor;
typedef struct cvor* stabloP;
struct cvor { 
	char rijec[MAX];
	int length; 
	stabloP left; 
	stabloP right; 
}Cvor;

int citajDat(char*, stabloP);
stabloP makeNode(char*);
stabloP insertInTree(stabloP, stabloP);
int printTree(stabloP);
float racunajProsjek(stabloP);

int main() {
	stabloP root = NULL;
	root = (stabloP)malloc(sizeof(Cvor));
	if (root == NULL) {
		printf("greska pri alokaciji");
		return ERROR;
	}
	root->left = NULL;
	root->right = NULL;

	float avg = 0.0;

	citajDat("text.txt", root);
	printTree(root);
	avg = racunajProsjek(root);
	printf("\nprosjecna duljina rjeci je: \t%f\n", avg);


	return 0;
}

int citajDat(char* filename, stabloP root) {
	stabloP q = NULL;
	char rj[MAX] = { 0 };
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", rj);
		q = makeNode(rj);
		root = insertInTree(root, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

stabloP makeNode(char* rj) {
	stabloP new = NULL;
	new = (stabloP)malloc(sizeof(Cvor));
	if (new == NULL) {
		printf("greska pri alokaciji mem");
		return NULL;
	}
	strcpy(new->rijec, rj);
	new->length = strlen(rj);
	new->left = NULL;
	new->right = NULL;

	return new;
}

stabloP insertInTree(stabloP root, stabloP q) {
	if (root == NULL)
		return q;
	else if (strcmp(root->rijec, q->rijec) < 0)
		root->left = insertInTree(root->left, q);
	else if (strcmp(root->rijec, q->rijec) > 0)
		root->right = insertInTree(root->right, q);
	else
		free(q);
	return root;
}

int printTree(stabloP root) {
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		printTree(root->left);
		printf("%s\t", root->rijec);
		printTree(root->right);
	}
	return EXIT_SUCCESS;
}

float racunajProsjek(stabloP root) {
	int br = 0;
	float rez = 0.0;
	if (root == NULL)
		return 0.0;
	else {
		rez = rez+racunajProsjek(root->left);
		br++;
		rez = rez + root->length;
		br++;
		rez = rez + racunajProsjek(root->right);
		br++;

	}
	rez = (float)rez / br;
	return rez;
}