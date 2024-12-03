///* Napisati program koji èita iz datoteke dio teksta, te kreira binarno stablo pretraživanja. Binarno stablo se
//kreira na naèin da se u njega upisuju sve razlièite rijeèi iz teksta koji je zapisan u datoteci s pripadajuæim
//duljinama unesene rijeèi.
//Potrebno je izraèunati prosjeènu duljinu svake rijeèi zapisane u binarnom stablu.
//Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one rijeèi koje su dulje
//od prosjeène duljine svih rijeèi, te ispisati tu vezanu listu. */
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define EXIT_SUCCESS 0
//#define ERROR -1
//#define MAX 25
//
//struct lista;
//typedef struct lista* position;
//typedef struct lista {
//	char rijec[MAX];
//	int vel;
//	position next;
//}Lista;
//
//struct stablo;
//typedef struct stablo* stabloP;
//typedef struct stablo {
//	int lenght;
//	char rijec[MAX];
//	stabloP left;
//	stabloP right;
//}Stablo;
//
//float citajDat(stabloP, char*);								// fja cita rijeci iz dat i sprema ih u bin staablo pretrazivanja ali ujedno i racuna prosjecnu duljinu rj
//stabloP napraviCvor(char*, int);
//stabloP unesiUStablo(stabloP, stabloP);
//stabloP ispisiStablo(stabloP);
//stabloP brisiStablo(stabloP);
//
//int unesiUListu(stabloP, position, float);
//position napraviCvorListe(char*, int);
//int dodaj(position, position);
//int ispisiListu(position);
//int brisiListu(position);
//
//int main() {
//	stabloP root = NULL;
//	root = (stabloP)malloc(sizeof(Stablo));
//	if (root == NULL)
//	{
//		printf("greska pri alokaciji memorije za root");
//		return ERROR;
//	}
//	root->left = NULL;
//	root->right = NULL;
//
//	Lista head = {
//		.rijec = {0},
//		.vel=0,
//		.next=NULL
//	};
//
//	float avg = 0.0;
//	avg = citajDat(root, "text.txt");
//	printf("duljina:\trijec:\n");
//	root = ispisiStablo(root);
//	printf("prosjecna duljina rijeci: %f\n", avg);
//
//	unesiUListu(root, &head, avg);
//	ispisiListu(&head);
//
//	root = brisiStablo(root);
//	brisiListu(&head);
//	return 0;
//}
//
//float citajDat(stabloP root, char* filename) {
//	char rj[MAX] = { 0 };
//	int suma = 0, br = 0, velicina = 0;
//	stabloP q = NULL;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL) {
//		printf("greska pri otvaranju dat");
//		return ERROR;
//	}
//	while (!feof(fp)) {
//		fscanf(fp, "%s", rj);
//		br++;
//		velicina = strlen(rj);
//		suma = suma + velicina;
//		q = napraviCvor(rj, velicina);
//		root = unesiUStablo(root, q);
//	}
//
//	float prosjek = 0.0;
//	prosjek = (float)suma / br;
//
//	fclose(fp);
//	return prosjek;
//}
//
//stabloP napraviCvor(char* rj, int vel) {
//	stabloP new = NULL;
//	new = (stabloP)malloc(sizeof(Stablo));
//	if (new == NULL) {
//		printf("greska pri alokaciji mem");
//		return NULL;
//	}
//	strcpy(new->rijec, rj);
//	new->lenght = vel;
//	new->left = NULL;
//	new->right = NULL;
//
//	return new;
//}
//
//stabloP unesiUStablo(stabloP root, stabloP q) {
//	if (root == NULL)
//		return q;
//	else if (strcmp(root->rijec, q->rijec) < 0)
//		root->right = unesiUStablo(root->right, q);
//	else if (strcmp(root->rijec, q->rijec) > 0)
//		root->left = unesiUStablo(root->left, q);
//	else
//		free(q);
//	return root;
//}
//
//stabloP ispisiStablo(stabloP root){
//	if (root == NULL)
//		return NULL;
//	else
//	{
//		root->left = ispisiStablo(root->left);
//		printf("%d\t\t%s\n",root->lenght,root->rijec);
//		root->right= ispisiStablo(root->right);
//	}
//	return root;
//}
//
//stabloP brisiStablo(stabloP root) {
//	if (root == NULL)
//		return NULL;
//	else {
//		root->left = brisiStablo(root->left);
//		root->right = brisiStablo(root->right);
//		
//		free(root);
//	}
//	return NULL;
//}
//
//int unesiUListu(stabloP root, position head, float avg) {
//	position q = NULL;
//	if (root == NULL) {
//		//printf("greska: stablo je prazno");									// !!!rekurziija pa se ne radi ono sto u klasicnoj if else
//		return EXIT_SUCCESS;
//	}
//	else {
//		if (root->lenght > avg) {
//			q = napraviCvorListe(root->rijec, root->lenght);
//			dodaj(head, q);
//		}
//		unesiUListu(root->left, head, avg);
//		unesiUListu(root->right, head, avg);
//	}
//	return EXIT_SUCCESS;
//}
//
//position napraviCvorListe(char* rj, int vel) {
//	position new = NULL;
//	new = (position)malloc(sizeof(Lista));
//	if (new == NULL) {
//		printf("greska pri alokaciji memorije");
//		return NULL;
//	}
//	strcpy(new->rijec, rj);
//	new->vel = vel;
//	new->next = NULL;
//
//	return new;
//}
//
//int dodaj(position head, position q) {
//	q->next = head->next;
//	head->next = q;
//
//	return EXIT_SUCCESS;
//}
//
//int ispisiListu(position head) {
//	if (head->next == NULL)
//		printf("lista je prazna");
//	while (head->next != NULL)
//	{
//		printf("%s\t%d\n", head->next->rijec, head->next->vel);
//		head = head->next;
//	}
//	return EXIT_SUCCESS;
//}
//
//int brisiListu(position head) {
//	position temp = NULL;
//	while (head->next != NULL) {
//		temp = head->next;
//		head->next = temp->next;
//		free(temp);
//	}
//	return EXIT_SUCCESS;
//}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 25

struct list;
typedef struct list* position;
typedef struct list {
    char word[MAX];
    int length;
    position next;
} List;

struct tree;
typedef struct tree* treeP;
typedef struct tree {
    int length;
    char word[MAX];
    treeP left;
    treeP right;
} Tree;

float readFile(treeP, char*);                               // Function reads words from file and stores them in binary search tree while calculating average word length
treeP createNode(char*, int);
treeP insertIntoTree(treeP, treeP);
treeP printTree(treeP);
treeP deleteTree(treeP);

int insertIntoList(treeP, position, float);
position createNodeList(char*, int);
int add(position, position);
int printList(position);
int deleteList(position);

int main() {
    treeP root = NULL;
    root = (treeP)malloc(sizeof(Tree));
    if (root == NULL) {
        printf("Memory allocation error for root");
        return ERROR;
    }
    root->left = NULL;
    root->right = NULL;

    List head = {
        .word = {0},
        .length = 0,
        .next = NULL
    };

    float avg = 0.0;
    avg = readFile(root, "text.txt");
    printf("length:\tword:\n");
    root = printTree(root);
    printf("average word length: %f\n", avg);

    insertIntoList(root, &head, avg);
    printList(&head);

    root = deleteTree(root);
    deleteList(&head);
    return 0;
}

float readFile(treeP root, char* filename) {
    char word[MAX] = { 0 };
    int sum = 0, count = 0, size = 0;
    treeP newNode = NULL;
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return ERROR;
    }

    while (!feof(fp)) {
        fscanf(fp, "%s", word);
        count++;
        size = strlen(word);
        sum += size;
        newNode = createNode(word, size);
        root = insertIntoTree(root, newNode);
    }

    float average = 0.0;
    average = (float)sum / count;

    fclose(fp);
    return average;
}

treeP createNode(char* word, int length) {
    treeP newNode = NULL;
    newNode = (treeP)malloc(sizeof(Tree));

    if (newNode == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    strcpy(newNode->word, word);
    newNode->length = length;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

treeP insertIntoTree(treeP root, treeP newNode) {
    if (root == NULL)
        return newNode;

    else if (strcmp(root->word, newNode->word) < 0)
        root->right = insertIntoTree(root->right, newNode);

    else if (strcmp(root->word, newNode->word) > 0)
        root->left = insertIntoTree(root->left, newNode);

    else
        free(newNode); // Duplicate word; free the node

    return root;
}

treeP printTree(treeP root) {
    if (root == NULL)
        return NULL;

    else {
        root->left = printTree(root->left);
        printf("%d\t\t%s\n", root->length, root->word);
        root->right = printTree(root->right);
    }

    return root;
}

treeP deleteTree(treeP root) {
    if (root == NULL)
        return NULL;

    else {
        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);

        free(root);
    }

    return NULL;
}

int insertIntoList(treeP root, position head, float avg) {
    position newNodeList = NULL;

    if (root == NULL) {
        //printf("Error: Tree is empty"); // Recursion does not work as in classic if-else
        return EXIT_SUCCESS;

    }
    else {
        if (root->length > avg) {
            newNodeList = createNodeList(root->word, root->length);
            add(head, newNodeList);
        }

        insertIntoList(root->left, head, avg);
        insertIntoList(root->right, head, avg);

    }

    return EXIT_SUCCESS;
}

position createNodeList(char* word, int length) {
    position newNodeList = NULL;

    newNodeList = (position)malloc(sizeof(List));
    if (newNodeList == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    strcpy(newNodeList->word, word);
    newNodeList->length = length;
    newNodeList->next = NULL;

    return newNodeList;
}

int add(position head, position newNode) {
    newNode->next = head->next;
    head->next = newNode;

    return EXIT_SUCCESS;
}

int printList(position head) {
    if (head->next == NULL)
        printf("The list is empty\n");

    while (head->next != NULL) {
        printf("%s\t%d\n", head->next->word, head->next->length);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int deleteList(position head) {
    position temp = NULL;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}