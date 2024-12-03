/* Kreirati dvije datoteke i u njih upisati 10 sluèajno generiranih brojeva iz opsega od 20-35. Svaku od
datoteka proèitati i spremiti u vezanu listu (kreiraju se dvije vezane liste, npr. L1 i L2). Ispisati ih.
Iz ove dvije vezane liste se kreiraju dvije nove vezane liste koje sadrže:
a) presjek parnih èlanova listi L1 i L2;
b) uniju neparnih èlanova listi L1 i L2.
Kod kreiranja listi pod a) i b) se ne smije koristiti malloc, veæ uzeti postojeæe elemente iz listi L1 i
L2 i preusmjeriti pokazivaèe. Ispisati sve èetiri liste.
U listama pod a) i b) ne smije biti duplih vrijednosti i vrijednosti moraju bit složene uzlaznim
redoslijedom. */
																									// NEZ STA 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 256

struct lista;
typedef struct lista* position;
typedef struct lista {
	int el;
	position next;
}Lista;

int upisiDat(char*,position);
int randomBr(int, int);
int citajDat(char*, position);
position makeNode(int);
int insertInList(position, position);
int unosK(position, position);
int printList(position);

int main() {
	srand(time(0));
	Lista head = {
		.el=0,
		.next=NULL
	};
	int n = 0;
	//upisiDat("prva.txt",&head);
	//printList(&head);

	return 0;
}

int upisiDat(char* filename,position head) {
	int n = 0,brojac=0;
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while(brojac<15)
	{
		n = randomBr(20, 35);
		fprintf(fp, "%d ", n);
	}
	brojac = brojac + citajDat(filename, head);
	fclose(fp);
	return EXIT_SUCCESS;
}

int randomBr(int min, int max) {
	int rez = 0;
	rez = (rand() % (max - min + 1)) + min;
	return rez;
}

int citajDat(char* filename, position head) {
	int br = 0,n=0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d", &br);
		position q = NULL;
		q = makeNode(br);
		n=insertInList(head,q);
	}
	fclose(fp);
	return n;
}

position makeNode(int br) {
	position new = NULL;
	new = (position)malloc(sizeof(Lista));
	if (new == NULL)
	{
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	new->el = br;
	new->next = NULL;
	return new;
}

int insertInList(position head, position q) {
	int br = 0;
	position p = NULL;
	p = head;
	while (head->next != NULL && head->next->el != q->el)
		head = head->next;
	if (head->next == NULL) {
		unosK(p, q);
		br++;
	}
	else
		free(q);

	return br;
}

int unosK(position head, position q) {
	while (head->next != NULL && head->next->el < q->el)
		head = head->next;
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int printList(position head) {
	if (head->next == NULL)
		printf("lista je prazna");
	while (head->next != NULL)
	{
		printf("%d\n", head->next->el);
		head = head->next;
	}
	return EXIT_SUCCESS;
}