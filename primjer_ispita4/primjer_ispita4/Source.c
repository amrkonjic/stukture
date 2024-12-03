/*Nap program koji generira 30 slucajnih brojeva u opsegu od 0 do 100 i od tog br gradi vezanu listu. Ispisat listu.
Izbrisat iz liste br djeljive s 3 ili one koji sadrze znamenku 3 i rezultatnu listu upisat u dat sortiranu od najmanjeg od najveæeg
//(sama lista se ne smije sortirat prije upisa u dat)*/
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//#define EXIT_SUCCESS 0
//#define ERROR -1
//#define MAX 100
//#define MIN 0
//
//struct lista;
//typedef struct lista* position;
//typedef struct lista {
//	int el;
//	position next;
//}Lista;
//
//position makeNode(int);
//int insert_in_list(position, position);
//int print_list(position);
//int new_list(position);
//int trazi_br(position);
//
//int main() {
//	Lista head = {
//		.el = 0,
//		.next = NULL
//	};
//	srand(time(0));
//	int i = 0,br=0;
//	for (i = 0; i < 30; i++)
//	{
//		br = (rand() % MAX - MIN + 1) + MIN;
//		position q = makeNode(br);
//		insert_in_list(&head, q);
//	}
//	print_list(&head);
//	new_list(&head);
//	print_list(&head);
//
//	return 0;
//}
//position makeNode(int br) {
//	position q = NULL;
//	q = (position)malloc(sizeof(Lista));
//	if (q == NULL)
//	{
//		printf("greska pri aloksciji mem");
//		return NULL;
//	}
//	q->el = br;
//	return q;
//}
//
//int insert_in_list(position head, position q) {
//	q->next = head->next;
//	head->next = q;
//}
//
//int print_list(position head)
//{
//	while (head->next != NULL)
//	{
//		printf("%d\t", head->next->el);
//		head = head->next;
//	}
//	return EXIT_SUCCESS;
//}
//
//int trazi_br(position p)
//{
//	int br = 0;
//	while (p->next != NULL)
//	{
//		br = p->next->el / 10;
//		if (br == 3)
//			return 1;
//		else if (p->next->el % 10 == 3)
//			return 1;
//		else
//			return 0;
//		p = p->next;
//	}
//}
//
//int new_list(position head)
//{
//	position prev = NULL, temp = NULL;
//	prev = head;
//	int br = 0;
//	br = tarzi_br(head);
//
//	while (head->next != NULL)
//	{
//		if ((head->next->el % 3 == 0) || (br == 1))
//		{
//			temp = head->next;
//			prev->next = temp->next;
//			free(temp);
//		}
//		else
//			head = head->next;
//	}
//}
																									// FALI UPIS U DAT

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define USPJESNO_IZAVRSEN_PROGRAM 1
#define USPJESNO_IZAVRSENO 2
#define ERROR -1
#define UPPER 100
#define LOWER 0

typedef struct list* position;
typedef struct list {
	int el;
	position next;
}list;

int rnd();
int Unos(position);
int PrintList(position);
int SetPointers(position, position);
int CheckFor3(int);
int ChangeList(position);
int UpisUDat(position);
position NadiMin(position);

int main(void) {

	list head;
	head.next = NULL;

	Unos(&head);

	PrintList(head.next);
	printf("\n\n");

	ChangeList(&head);
	PrintList(head.next);

	UpisUDat(&head);

	return USPJESNO_IZAVRSEN_PROGRAM;
}

int UpisUDat(position p) {
	FILE* fp = NULL;
	char filename[20] = { 0 };

	printf("\nkoje je ime dat: ");
	scanf(" %s", filename);
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("neuspjesno otv dat");
		return ERROR;
	}

	position q = NULL;
	position head = NULL;
	head = p;
	while (head->next != NULL) {
		q = NadiMin(head);
		printf("%d, ", q->el);
		fprintf(fp, "%d, ", q->el);
		//p->next = q->next; //krivo
		free(q);
	}

	fclose(fp);

	return USPJESNO_IZAVRSENO;
}

position NadiMin(position p) {
	int min = 100;
	position minP = NULL;

	while (p->next != NULL) {
		if (p->next->el < min) {
			minP = p->next;
			p->next = minP->next;
		}
		p = p->next;
	}

	return minP;
}

/*int NadiMin(position p){
	int min = 100;
	position temp = NULL;
	while (p->next != NULL) {
		if (p->next->el < min) {
			min = p->next->el;
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		else
			p = p->next;
	}

	return min;
}*/

int Unos(position p) {
	int br = 0;
	srand(time(0));

	for (int i = 0; i < 30; i++) {
		position q = NULL;
		q = (position)malloc(sizeof(list));
		if (q == NULL) {
			printf("neuspjesno aloc mem!!!!");
			return ERROR;
		}
		br = rnd();
		q->el = br;
		q->next == NULL;
		SetPointers(p, q);
	}

	return USPJESNO_IZAVRSENO;
}

int ChangeList(position p) {
	position temp;

	while (p->next != NULL) {
		if ((p->next->el % 3 == 0) || CheckFor3(p->next->el) == 1) {
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		else
			p = p->next;
	}

	return USPJESNO_IZAVRSENO;
}

int SetPointers(position p, position q) {
	q->next = p->next;
	p->next = q;

	return USPJESNO_IZAVRSENO;
}

int CheckFor3(int br) {
	if (br / 10 == 3)
		return 1;
	else if (br % 10 == 3)
		return 1;
	else
		return 0;
}

int rnd() {
	int br = 0;
	br = (rand() % (UPPER + 1) - LOWER) + LOWER;

	return br;
}

int PrintList(position p) {
	while (p->next != NULL) {
		printf("%d, ", p->el);
		p = p->next;
	}

	return USPJESNO_IZAVRSENO; 
}