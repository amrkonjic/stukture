///* Napisati program koji generira 15 sluèajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu
//listu, po redoslijedu generiranja, a ne sortirano. U listi ne smije biti duplih vrijednosti.
//a) Potrebno je pronaæi minimalnu i maksimalnu vrijednost, te iz njih izraèunati srednju vrijednost
//((min+max)/2) i nakon toga sve vrijednosti koje su veæe od srednje prebaciti na kraj liste. Ispisati
//minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu*/
//																					// RADI
//#define CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//#define EXIT_SUCCESS 0
//#define ERROR -1
//
//struct lista;
//typedef struct lista* position;
//typedef struct lista {
//	int el;
//	position next;
//}Lista;
//
//int generateRand(int, int);
//position makeNode(int);
//int insertInList(position, position);
//int unosK(position, position);
//int unosP(position, position);
//int printList(position);
//position findMin(position);
//position findMax(position);
//int changeList(position,position, int, int);
//int brisiSve(position);
//
//int main() {
//	srand(time(0));
//	int n = 0;
//	position q = NULL,min=NULL, max = NULL;
//	Lista head = {
//		.el=0,
//		.next=NULL
//	};
//	Lista head_new = {
//		.el = 0,
//		.next = NULL
//	};
//	int brojac = 0;
//	while(brojac<15)
//	{
//		n = generateRand(100, 120);
//		q = makeNode(n);
//		brojac=brojac+insertInList(&head, q);
//	}
//	
//	printList(&head);
//	min = findMin(head.next);
//	printf("min el: %d\n", min->el);
//	max = findMax(head.next);
//	printf("max el: %d\n", max->el);
//	changeList(&head,&head_new, min->el, max->el);
//	printList(&head_new);
//
//	brisiSve(&head);
//	brisiSve(&head_new);
//	
//
//	return 0;
//}
//
//int generateRand(int min, int max) {
//	int rez = 0;
//	rez = (rand() % (max - min + 1)) + min;
//	return rez;
//}
//
//position makeNode(int br) {
//	position new = NULL;
//	new = (position)malloc(sizeof(Lista));
//	if (new == NULL)
//	{
//		printf("greska pri alokaciji memorije");
//		return NULL;
//	}
//	new->el = br;
//	new->next = NULL;
//	return new;
//}
//
//int insertInList(position head, position q) {
//	int br = 0;
//	position p = NULL;
//	p = head;
//	while (head->next != NULL && head->next->el != q->el)
//		head = head->next;	
//	if (head->next == NULL) {
//		unosK(p, q);
//		br++;
//	}	
//	else
//		free(q);
//	
//	return br;
//}
//
//int unosK(position head, position q) {
//	while (head->next != NULL)
//		head = head->next;
//	q->next = head->next;
//	head->next = q;
//	return EXIT_SUCCESS;
//}
//
//int unosP(position head, position q) {
//	q->next = head->next;
//	head->next = q;
//
//	return EXIT_SUCCESS;
//}
//
//int printList(position head) {
//	if (head->next == NULL)
//		printf("lista je prazna");
//	while (head->next != NULL)
//	{
//		printf("%d\n", head->next->el);
//		head = head->next;
//	}
//	return EXIT_SUCCESS;
//}
//
//position findMin(position p) {
//	position min=NULL;
//	min = p;
//	while (p->next!=NULL) {														// pazit jel ide p ili p->next !!!   ( while(p!=NULL) je krivo )
//		if (p->next->el < min->el) {
//			min = p->next;
//			p = p->next;
//		}
//		else
//			p = p->next;
//	}
//	return min;
//}
//
//position findMax(position p) {
//	position max = NULL;
//	max = p;
//	while (p->next != NULL) {
//		if (p->next->el > max->el) {
//			max = p->next;
//			p = p->next;
//		}
//		else
//			p = p->next;
//	}
//	return max;
//}
//
//int changeList(position head,position new, int min, int max) {
//	position p =NULL;
//	float avg = 0.0;
//	avg = (float)((min + max) / 2);
//	printf("srednja vrj: %f\n", avg);
//	while (head->next != NULL) {
//		if (head->next->el > avg) {
//			p = makeNode(head->next->el);
//			unosK(new, p);
//		}
//		else {
//			p = makeNode(head->next->el);
//			unosP(new, p);
//		}
//		head = head->next;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//int brisiSve(position head) {
//	position temp = NULL;
//	while (head->next != NULL) {
//		temp = head->next;
//		head->next = temp->next;
//		free(temp);
//
//	}
//	return EXIT_SUCCESS;
//}

#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define ERROR -1

struct list;
typedef struct list* position;
typedef struct list {
    int element;
    position next;
} List;

int generateRand(int, int);
position createNode(int);
int insertInList(position, position);
int insertAtEnd(position, position);
int insertAtBeginning(position, position);
int printList(position);
position findMin(position);
position findMax(position);
int rearrangeList(position, position, int, int);
int deleteAll(position);

int main() {
    srand(time(0));
    int randomNumber = 0;
    position newNode = NULL, minNode = NULL, maxNode = NULL;
    List head = {
        .element = 0,
        .next = NULL
    };
    List newHead = {
        .element = 0,
        .next = NULL
    };
    int counter = 0;

    while (counter < 15) {
        randomNumber = generateRand(100, 120);
        newNode = createNode(randomNumber);
        counter += insertInList(&head, newNode);
    }

    printList(&head);
    minNode = findMin(head.next);
    printf("Minimum element: %d\n", minNode->element);
    maxNode = findMax(head.next);
    printf("Maximum element: %d\n", maxNode->element);

    rearrangeList(&head, &newHead, minNode->element, maxNode->element);
    printList(&newHead);

    deleteAll(&head);
    deleteAll(&newHead);

    return 0;
}

int generateRand(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

position createNode(int number) {
    position newNode = (position)malloc(sizeof(List));

    if (newNode == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    newNode->element = number;
    newNode->next = NULL;

    return newNode;
}

int insertInList(position head, position newNode) {
    int count = 0;
    position p = head;

    while (head->next != NULL && head->next->element != newNode->element)
        head = head->next;

    if (head->next == NULL) {
        insertAtEnd(p, newNode);
        count++;
    }
    else {
        free(newNode); // Duplicate value; free the node
    }

    return count;
}

int insertAtEnd(position head, position newNode) {
    while (head->next != NULL)
        head = head->next;

    newNode->next = head->next;
    head->next = newNode;

    return EXIT_SUCCESS;
}

int insertAtBeginning(position head, position newNode) {
    newNode->next = head->next;
    head->next = newNode;

    return EXIT_SUCCESS;
}

int printList(position head) {
    if (head->next == NULL) {
        printf("The list is empty\n");
        return EXIT_SUCCESS;
    }

    while (head->next != NULL) {
        printf("%d\n", head->next->element);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

position findMin(position p) {
    position minNode = p;

    while (p->next != NULL) {
        if (p->next->element < minNode->element) {
            minNode = p->next;
        }
        p = p->next;
    }

    return minNode;
}

position findMax(position p) {
    position maxNode = p;

    while (p->next != NULL) {
        if (p->next->element > maxNode->element) {
            maxNode = p->next;
        }
        p = p->next;
    }

    return maxNode;
}

int rearrangeList(position head, position newHead, int min, int max) {
    position tempNode = NULL;
    float avg = (float)((min + max) / 2);

    printf("Average value: %f\n", avg);

    while (head->next != NULL) {
        if (head->next->element > avg) {
            tempNode = createNode(head->next->element);
            insertAtEnd(newHead, tempNode); // Insert at the end for values greater than average
        }
        else {
            tempNode = createNode(head->next->element);
            insertAtBeginning(newHead, tempNode); // Insert at the beginning for values less than or equal to average
        }

        head = head->next;
    }

    return EXIT_SUCCESS;
}

int deleteAll(position head) {
    position temp = NULL;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}