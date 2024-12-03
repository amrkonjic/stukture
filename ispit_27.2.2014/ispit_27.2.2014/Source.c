/* Napisati program koji iz datoteke èita dio teksta, rijeè po rijeè i unosi u binarno stablo pretraživanja
(maksimalna duljina rijeèi 1024 znaka). Ispisati binarno stablo na „inorder“ naèin.
Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve rijeèi koje poèinju samoglasnikom, a u
drugoj sve rijeèi koje poèinju suglasnikom. Rijeèi zapisane u datotekama moraju biti sortirane po abecedi. */
																												//radi
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 1024

struct lista;
typedef struct lista* position;
typedef struct lista {
	char rijec[MAX];
	int vel;
	position next;
}Lista;

struct stablo;
typedef struct stablo* stabloP;
typedef struct stablo {
	char rijec[MAX];
	stabloP left;
	stabloP right;
}Stablo;

int citajDat(stabloP, char*);
stabloP napraviCvor(char*);
stabloP unesiUStablo(stabloP, stabloP);
stabloP ispisiStablo(stabloP);
stabloP brisiStablo(stabloP);

//int upisiUDat(stabloP);
int upisiUListu(stabloP,position,position);
position napraviCvorListe(char*);
int dodaj(position, position);
int dat1(position);
int dat2(position);
int brisiListu(position);

int main() {
	stabloP root = NULL;
	root = (stabloP)malloc(sizeof(Stablo));
	if (root == NULL)
	{
		printf("greska pri alokaciji memorije za root");
		return ERROR;
	}
	root->left = NULL;
	root->right = NULL;

	Lista head1 = {
		.rijec = {0},
		.vel = 0,
		.next = NULL
	};
	Lista head2 = {
		.rijec = {0},
		.vel = 0,
		.next = NULL
	};


	citajDat(root, "text.txt");
	root = ispisiStablo(root);

	//upisiUDat(root);
	upisiUListu(root,&head1,&head2);
	dat1(&head1);
	dat2(&head2);
	

	root = brisiStablo(root);
	brisiListu(&head1);
	brisiListu(&head2);
	return 0;
}

int citajDat(stabloP root, char* filename) {
	char rj[MAX] = { 0 };
	stabloP q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", rj);
		q = napraviCvor(rj);
		root = unesiUStablo(root, q);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

stabloP napraviCvor(char* rj) {
	stabloP new = NULL;
	new = (stabloP)malloc(sizeof(Stablo));
	if (new == NULL) {
		printf("greska pri alokaciji mem");
		return NULL;
	}
	strcpy(new->rijec, rj);
	new->left = NULL;
	new->right = NULL;

	return new;
}

stabloP unesiUStablo(stabloP root, stabloP q) {
	if (root == NULL)
		return q;
	else if (strcmp(root->rijec, q->rijec) < 0)
		root->right = unesiUStablo(root->right, q);
	else if (strcmp(root->rijec, q->rijec) > 0)
		root->left = unesiUStablo(root->left, q);
	else
		free(q);
	return root;
}

stabloP ispisiStablo(stabloP root) {
	if (root == NULL)
		return NULL;
	else
	{
		root->left = ispisiStablo(root->left);
		printf("%s\n", root->rijec);
		root->right = ispisiStablo(root->right);
	}
	return root;
}

stabloP brisiStablo(stabloP root) {
	if (root == NULL)
		return NULL;
	else {
		root->left = brisiStablo(root->left);
		root->right = brisiStablo(root->right);

		free(root);
	}
	return NULL;
}

//int upisiUDat(stabloP root) {
//	if (root == NULL)
//		return EXIT_SUCCESS;
//	else {
//		if (root->rijec[0] == 'a' || root->rijec[0] == 'e' || root->rijec[0] == 'i' || root->rijec[0] == 'o' || root->rijec[0] == 'u')
//		{
//			//dat1(root->rijec);
//
//		}
//		else {
//			dat2(root->rijec);
//		}
//		upisiUDat(root->left);
//		upisiUDat(root->right);
//	}
//	return EXIT_SUCCESS;
//}

int dat1(position head) {
	FILE* fp = NULL;
	fp = fopen("sam.txt", "w");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (head->next != NULL) {
		fprintf(fp, "%s\n", head->next->rijec);
		head = head->next;
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int dat2(position head) {
	FILE* fp = NULL;
	fp = fopen("sug.txt", "w");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (head->next != NULL) {
		fprintf(fp, "%s\n", head->next->rijec);
		head = head->next;
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int upisiUListu(stabloP root,position head1,position head2) {
	position q = NULL;
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		if (root->rijec[0] == 'a' || root->rijec[0] == 'e' || root->rijec[0] == 'i' || root->rijec[0] == 'o' || root->rijec[0] == 'u') {
			q = napraviCvorListe(root->rijec);
			dodaj(head1, q);
		}
		else
		{
			q = napraviCvorListe(root->rijec);
			dodaj(head2, q);
		}
		upisiUListu(root->left,head1,head2);
		upisiUListu(root->right,head1,head2);
	}
	return EXIT_SUCCESS;
}

position napraviCvorListe(char* rj) {
	position new = NULL;
	new = (position)malloc(sizeof(Lista));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->rijec, rj);
	new->next = NULL;

	return new;
}

int dodaj(position head, position q) {
	while (head->next != NULL && strcmp(head->next->rijec, q->rijec) < 0)
		head = head->next;
	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int brisiListu(position head) {
	position temp = NULL;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}