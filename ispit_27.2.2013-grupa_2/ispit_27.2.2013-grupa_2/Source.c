/* Napisati program kojim se
a) Iz datoteke èitaju rijeèi i spremaju u vezanu listu na naèin da se rijeèi slažu po abecednom redu
obrnutom od abecednog reda. Zatim ispisati tu vezanu listu.
b) Iz generirane liste ispisati samo one rijeèi koje se nalaze zapisane u drugoj proizvoljnoj datoteci.*/
																												// radi
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 256

struct lista;
typedef struct lista* position;
typedef struct lista {
	char rijec[MAX];
	position next;
}Lista;

int loadFile(position, char*);
position makeNode(char*);
int insertInList(position, position);
int printList(position);
int printWords(position, position);
int deleteAll(position);

int main() {
	Lista head1 = {
		.rijec = {0},
		.next = NULL
	};
	Lista head2 = {
		.rijec = {0},
		.next = NULL
	};

	loadFile(&head1, "text.txt");
	printf("prva dat:\n");
	printList(&head1);

	loadFile(&head2, "druga.txt");
	printf("druga dat:\n");
	printList(&head2);

	printf("rijeci koje se pojavljuju u drugoj dat:\n");
	printWords(&head1, &head2);
	
	deleteAll(&head1);
	deleteAll(&head2);
	return 0;
}

int loadFile(position head, char* filename) {
	char rj[MAX] = { 0 };
	position q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", rj);
		q = makeNode(rj);
		insertInList(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

position makeNode(char* rj) {
	position new = NULL;
	new = (position)malloc(sizeof(Lista));
	if (new == NULL)
	{
		printf("greska pri alokaciji mem");
		return NULL;
	}
	strcpy(new->rijec, rj);
	new->next = NULL;

	return new;
}

int insertInList(position head, position q) {
	while (head->next != NULL && strcmp(head->next->rijec, q->rijec) > 0)
		head = head->next;
	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int printList(position head) {
	if (head->next == NULL)
		printf("lista je prazna\n");
	while (head->next != NULL) {
		printf("%s\n", head->next->rijec);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int printWords(position head1, position head2) {
	position p = NULL;
	p = head2;
	while (head1->next != NULL) {
		head2 = p;
		while (head2->next != NULL)
		{
			if (strcmp(head1->next->rijec, head2->next->rijec) == 0) {
				printf("%s\t", head1->next->rijec);
				head2 = head2->next;
			}
			else
				head2 = head2->next;
		}
		head1 = head1->next;
	}
	return EXIT_SUCCESS;
}

int deleteAll(position head) {
	position temp = NULL;
	while(head->next!=NULL)
	{ 
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}