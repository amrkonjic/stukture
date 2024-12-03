/* Nap program koji iz dat "hoteli.txt" cita popis hotela te kreira vezanu listu sortiranu po datumu izgradnje hotela.
za 2: ispisat sortiranu vezanu listu. Izracunat srednju vrijednost godisnjih prihoda svih hotela pa modificirat listu u tkd 
hoteli s prihodom manjim od iracunate srednje vrjednosti budu na kraju liste. */

											// RADI 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 32

struct _date;
typedef struct _date* dateP;
typedef struct _date
{
	int year;
	int month;
	int day;
}Date;

struct _hotel;
typedef struct _hotel* hotelP;
typedef struct _hotel
{
	char name[MAX];
	dateP date;
	int income;
	hotelP next;
}Hotel;

int citajDat(char* ,hotelP);
hotelP stvoriCvor(char*, int, int, int,int);
int stvoriListu(hotelP,hotelP);
int dateCompare(hotelP,hotelP);
int ispisiListu(hotelP);
float srednjaVrijednostPrihoda(hotelP);
int promjeniListu(hotelP,hotelP,float);
int unosK(hotelP,hotelP);
int unosP(hotelP, hotelP);
int brisiSve(hotelP);

int main() {
	Hotel head;
	head.next = NULL;
	Hotel head_newList;
	head_newList.next = NULL;
	float f=0.0;

	citajDat("hoteli.txt", &head);
	ispisiListu(&head);
	f = srednjaVrijednostPrihoda(head.next);
	printf("srednja vrijednost prihoda je: %f\n", f);
	promjeniListu(&head, &head_newList,f);
	ispisiListu(&head_newList);

	
	brisiSve(&head);
	brisiSve(&head_newList);

	return 0;
}

int citajDat(char* filename, hotelP head) {
	int dan = 0, mjesec = 0, godina = 0, prihod = 0;
	char ime[MAX] = { 0 };
	char hotel[MAX] = { 0 };
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju datoteke");
		return ERROR;
	}
	while (!feof(fp)) {
		hotelP q = NULL;
		fscanf(fp, "%s %s %d-%d-%d %d", hotel, ime, &godina, &mjesec, &dan, &prihod);
		//printf("%s %d %d %d %d\n", ime, godina, mjesec, dan, prihod);
		q=stvoriCvor(ime, dan, mjesec, godina, prihod);
		stvoriListu(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

hotelP stvoriCvor(char* ime, int dan, int mj, int god,int prihod) {
	hotelP q = NULL;
	q = (hotelP)malloc(sizeof(Hotel));
	if (q == NULL)
	{
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(q->name, ime);
	q->income = prihod;
	q->next = NULL;

	q->date = NULL;
	q->date = (dateP)malloc(sizeof(Date));
	if (q->date == NULL)
	{
		printf("greska pri alociranju memorije");
		return NULL;
	}
	q->date->day = dan;
	q->date->month = mj;
	q->date->year = god;
	

	//printf("%s %d-%d-%d %d\n", q->name, q->date->day, q->date->month, q->date->year, q->income);

	return q;
}

int dateCompare(hotelP p,hotelP q) {
	int rez = 0;
	rez = p->date->year - q->date->year;
	if (rez == 0) {
		rez= p->date->month - q->date->month;
		if (rez == 0)
			rez = p->date->day - q->date->day;
	}
	return rez;
}

int stvoriListu(hotelP head, hotelP q) {
	while (head->next != NULL && dateCompare(head->next, q) < 0)
		head = head->next;
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int ispisiListu(hotelP head) {
	if (head->next == NULL)
		printf("lista je prazna\n");
	while (head->next != NULL) {
		printf("hotel %s %d-%d-%d %d\n", head->next->name, head->next->date->day, head->next->date->month, head->next->date->year, head->next->income);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

float srednjaVrijednostPrihoda(hotelP p) {
	int br_hotela = 0, suma = 0;
	float prosjek = 0.0;
	while (p != NULL) {
		br_hotela++;
		suma = suma + p->income;
		p = p->next;
	}
	prosjek = (float)suma / br_hotela;
	return prosjek;
}

int unosK(hotelP head,hotelP q) {
	while (head->next != NULL)
		head = head->next;
	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int unosP(hotelP head, hotelP q) {
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int promjeniListu(hotelP head,hotelP new_head,float min) {
	hotelP p = NULL, q = NULL, temp=NULL;
	p = head;
	while (head->next != NULL)
	{
		if (head->next->income < min) {
			q = stvoriCvor(head->next->name, head->next->date->day, head->next->date->month, head->next->date->year, head->next->income);
			unosK(new_head, q);
			//printf("%s %d-%d-%d %d\n", q->name, q->date->day, q->date->month, q->date->year, q->income);
		}	
		else
		{
			q = stvoriCvor(head->next->name, head->next->date->day, head->next->date->month, head->next->date->year, head->next->income);
			unosP(new_head, q);
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}
	
int brisiSve(hotelP head) {
	hotelP temp = NULL;
	while (head->next != NULL) {
		free(head->next->date);
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}


