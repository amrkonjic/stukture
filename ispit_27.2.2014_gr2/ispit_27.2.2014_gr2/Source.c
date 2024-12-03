/* Napisati program koji iz datoteke èita podatke o broju bodova koje je jedan student dobio na ispitu 
i sprema ih u binarno stablo pretraživanja. (Napomena : 0 <
broj_bodova <= 100). Ispisati binarno stablo na „inorder“ naèin.
U tako kreiranom binarnom stablu potrebno je za svakog od studenata izraèunati i relativan broj bodova
po formuli: relativan_broj_bodova=( broj_bodova / MAX(broj_bodova) ). Ispisati binarno stablo na
„preorder“ naèin. */
																																		// radi
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 128
#define MAX_BR_BOD 100

struct student;
typedef struct student* position;
typedef struct student {
	char ime[MAX];
	char prezime[MAX];
	int br_bodova;
	float rel_br_bodova;
	position left;
	position right;
}Student;

int citajDat(char*, position);
position napraviCvor(char*, char*, int);
position unesiUStablo(position, position);
position ispisiInorder(position);
position relBr(position, int);
position upisiRel(position);
position ispisiPreorder(position);
position brisiStablo(position);

int main() {
	position root = NULL;
	root = (position)malloc(sizeof(Student));
	if (root == NULL) {
		printf("greksa pri alokaciji");
		return NULL;
	}
	root->left = NULL;
	root->right = NULL;

	citajDat("text.txt", root);
	root = ispisiInorder(root);

	root = upisiRel(root);
	root = ispisiPreorder(root);

	root = brisiStablo(root);
	return 0;
}

int citajDat(char* filename, position root) {
	char ime[MAX] = { 0 }, prezime[MAX] = { 0 };
	int br_b = 0;
	position q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", ime, prezime, &br_b);
		q = napraviCvor(ime, prezime, br_b);
		root = unesiUStablo(root, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

position napraviCvor(char* ime, char* prezime, int br) {
	position new = NULL;
	new = (position)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greksa pri alokaciji");
		return NULL;
	}
	strcpy(new->ime, ime);
	strcpy(new->prezime, prezime);
	new->br_bodova = br;
	new->left = NULL;
	new->right = NULL;

	return new;
}

position unesiUStablo(position root, position q) {
	if (root == NULL)
		return q;
	else if (strcmp(root->prezime, q->prezime) < 0)
		root->right = unesiUStablo(root->right, q);
	else if (strcmp(root->prezime, q->prezime) > 0)
		root->left = unesiUStablo(root->left, q);
	else
		free(q);
	return root;
}

position ispisiInorder(position root) {
	if (root == NULL)
		return NULL;
	else {
		root->left=ispisiInorder(root->left);
		printf("%s\t%s\t%d\n", root->ime, root->prezime, root->br_bodova);
		root->right = ispisiInorder(root->right);
	}
	return root;
}

position relBr(position p, int bod) {
	float rel = 0.0;
	rel = (float)bod / MAX_BR_BOD;
	p->rel_br_bodova = rel;
	return p;
}

position upisiRel(position root) {
	if (root == NULL)
		return NULL;
	else {
		root->left = upisiRel(root->left);
		root = relBr(root, root->br_bodova);
		root->right = upisiRel(root->right);
	}
	return root;
}

position ispisiPreorder(position root) {
	if (root == NULL)
		return NULL;
	else {
		printf("%s\t%s\t%d\t%f\n", root->ime, root->prezime, root->br_bodova,root->rel_br_bodova);
		root->left = ispisiPreorder(root->left);
		root->right = ispisiPreorder(root->right);
	}
	return root;
}

position brisiStablo(position root) {
	if (root == NULL)
		return NULL;
	else {
		root->left=brisiStablo(root->left);
		root->right=brisiStablo(root->right);
		free(root);
	}
	return NULL;
}