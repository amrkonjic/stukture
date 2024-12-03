/*
Napisati program koji:
a) Iz datoteke „drzave.txt“ èita popis država i njihov ID od proèitanih država izgraditi vezanu listu
država na sortirani naèin od poèetka prema kraju abecede (treba raditi sortirani unos, a ne
naknadno sortirati). Uz pokazivaè na sljedeæu državu struktura od koje se gradi vezana lista
mora sadržavati i pokazivaè na stablo gradova koji su u toj državi (trenutno NULL) - za 2
b) Iz datoteke „gradovi.txt“ proèitati ime grada i ID države u kojoj se nalazi. Pronaæi odgovarajuæu
državu u gornjoj listi, te dodati proèitani grad u stablo gradova te države. Za zadanu državu
ispisati sve njene gradove po abecedi. – za 5
*/	


// RADI AL NISAN SIG JESU LI GOSPODA OVO IZVOLJEVLA ZA DVA

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX_LINE 1024

struct gradovi;
typedef struct gradovi* gradP;
typedef struct gradovi {
	char ime_grada[MAX_LINE];
	gradP left;
	gradP right;
}Gradovi;

struct drzave;
typedef struct drzave* position;
typedef struct drzave {
	char ime_drzave[MAX_LINE];
	int id;
	position next;
	gradP root;
}Drzave;

int readFromFile(char*,position);
position makeNode(position,int,char*);
int insert(position,position);
int printList(position);
int deleteList(position);

int main()
{
	Drzave head = {
	.ime_drzave = {0},
	.id=0,
	.next=NULL,
	.root=NULL
	};

	readFromFile("drzave.txt", &head);
	printList(&head);

	deleteList(&head);
	printList(&head);


	return 0;
}

int readFromFile(char* filename, position head) {
	char ime[MAX_LINE] = { 0 };
	int id=0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", ime, &id);
		position q = NULL;
		q = makeNode(head, id, ime);
		insert(head, q);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

position makeNode(position head, int id, char* ime) {
	position new = NULL;
	new = (position)malloc(sizeof(Drzave));
	if (new == NULL) {
		printf("greska pri alokacij memorije");
		return NULL;
	}
	strcpy(new->ime_drzave, ime);
	new->id = id;
	new->next = NULL;
	new->root = NULL;

	return new;
}

int insert(position head,position q) {
	while (head->next != NULL && strcmp(head->next->ime_drzave, q->ime_drzave) < 0) {
		head = head->next;
	}
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int printList(position head) {
	position p = head->next;
	if (p == NULL) {
		printf("lista je prazna\n");
	}
	while (p != NULL)
	{
		printf("%s\t%d\n", p->ime_drzave, p->id);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int deleteList(position head)
{
	position temp = NULL;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}