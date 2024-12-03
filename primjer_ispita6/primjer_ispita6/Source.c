/*Napisati program koji iz datoteke „text.txt“ èita zadani tekst. Od proèitanih rijeèi se gradi binarno
stablo pretraživanja, s tim da ukoliko se pronaðe rijeè koja se veæ nalazi u stablu potrebno ju je
dodati u vezanu listu istih rijeèi za odreðeni èvor. Ispisati stablo. Za odabranu rijeè ispitat koliko se
puta ponavlja.*/

			

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define EXIT_SUCCCESS 0
//#define ERROR -1
//#define MAX_LINE 1024
//
//
//struct stablo;
//typedef struct stablo* position;
//typedef struct stablo* stabloP;
//typedef struct stablo {
//	char el[MAX_LINE];
//	stabloP left;
//	stabloP right;
//	position next;
//}Stablo;
//
//stabloP readFromFile(char*, stabloP);
//stabloP makeNode_tree(char*);
//stabloP insertInTree(stabloP, stabloP);
//int insertInList(position, position);
//int printTree(stabloP);
//
//int main() {
//	stabloP root=NULL;
//	root = (stabloP)malloc(sizeof(Stablo));
//	if (root == NULL)
//		return ERROR;
//	root->left = NULL;
//	root->right = NULL;
//	
//
//	root=readFromFile("text.txt", root);
//	printTree(root);
//
//
//	return 0;
//}
//
//stabloP readFromFile(char* filename, stabloP root) {
//	char rjj[MAX_LINE];
//	stabloP q = NULL;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL) {
//		printf("greska pri otvaranu datoteke");
//		return NULL;
//	}
//	while (!feof(fp)) {
//		fscanf(fp, "%s", rjj);
//		q = makeNode_tree(rjj);
//		root=insertInTree(root, q);
//	}
//
//	fclose(fp);
//	return root;
//}
//
//stabloP makeNode_tree(char* rijec) {
//	stabloP new = NULL;
//	new = (stabloP)malloc(sizeof(Stablo));
//	if (new == NULL) {
//		printf("greska pri alokaciji memorije");
//		return NULL;
//	}
//	strcpy(new->el, rijec);
//	new->left = NULL;
//	new->right = NULL;
//
//	return new;
//}
//
//stabloP insertInTree(stabloP root, stabloP new) {
//	
//	if (root == NULL)
//		return new;
//	else if (strcmp(root->el, new->el) < 0)
//		root->right = insertInTree(root->right, new);
//	else if (strcmp(root->el, new->el) > 0)
//		root->left = insertInTree(root->left, new);
//	else if (strcmp(root->el, new->el)==0)
//	{
//		insertInList(root->next, new);
//		/*free(new);*/
//	}
//	return root;
//}
//
//int insertInList(position head, position q) {
//	q->next = head->next;
//	head->next = q;
//	return EXIT_SUCCESS;
//}
//
//int printTree(stabloP root) {						// inorder ispis
//	if (root == NULL)
//		return EXIT_SUCCESS;
//	else {
//		printTree(root->left);
//		printf("%s", root->el);
//		printTree(root->right);
//	}
//	return EXIT_SUCCESS;
//}


/*Napisati program koji iz datoteke „text.txt“ èita zadani tekst. Od proèitanih rijeèi se gradi binarno
stablo pretraživanja, s tim da ukoliko se pronaðe rijeè koja se veæ nalazi u stablu potrebno ju je
dodati u vezanu listu istih rijeèi za odreðeni èvor. Ispisati stablo. Za odabranu rijeè ispitat koliko se
puta ponavlja.*/

			
																									// RADI

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCCESS 0
#define ERROR -1
#define MAX_LINE 1024

struct rijec;
typedef struct stablo* position;
/*typedef struct rijec {  // ne treba nam vezana lista jer mozemo samo imati position next na stablu
	char rj[MAX_LINE];
	position next;
}Rijec;*/

struct stablo;
typedef struct stablo* stabloP;
typedef struct stablo {
	char el[MAX_LINE];
	stabloP left;
	stabloP right;
	position next;
}Stablo;

stabloP readFromFile(char*, stabloP);
stabloP makeNode_tree(char*);
stabloP insertInTree(stabloP, stabloP);
int printTree(stabloP);
int inputList(position, position);
position findElement(position root, char* word); // trazi element koji nas zanima
int countOccurences(position head, char* word); // prolazi kroz vezanu listu i broji koliko elemenata ima u njoj

int main() {
	stabloP root = NULL;
	root = (stabloP)malloc(sizeof(Stablo));
	if (root == NULL)
		return ERROR;
	root->left = NULL;
	root->right = NULL;
	char rijec[128];

	position temp = NULL;

	root = readFromFile("text.txt", root);
	printTree(root);

	printf("\nUnesite rijec: ");
	scanf(" %s", rijec);
	temp = findElement(root, rijec);

	int count = 0;
	count = countOccurences(temp, rijec);
	printf("Rijec '%s' se ponavlja %d puta", rijec, count);

	return 0;
}

stabloP readFromFile(char* filename, stabloP root) {
	char rjj[MAX_LINE];
	stabloP q = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranu datoteke");
		return NULL;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", rjj);
		q = makeNode_tree(rjj);
		root = insertInTree(root, q);
	}

	fclose(fp);
	return root;
}

stabloP makeNode_tree(char* rijec) {
	stabloP new = NULL;
	new = (stabloP)malloc(sizeof(Stablo));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->el, rijec);
	new->left = NULL;
	new->right = NULL;

	return new;
}

stabloP insertInTree(stabloP root, stabloP new) {
	char ista_rj[MAX_LINE] = { 0 };
	if (root == NULL)
		return new;
	else if (strcmp(root->el, new->el) < 0)
		root->right = insertInTree(root->right, new);
	else if (strcmp(root->el, new->el) > 0)
		root->left = insertInTree(root->left, new);
	else if (strcmp(root->el, new->el) == 0)
	{
		inputList(root, new);
	}
	return root;
}


int printTree(stabloP root) {						// inorder ispis
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		printTree(root->left);
		printf("%s\t", root->el);
		printTree(root->right);
	}
	return EXIT_SUCCESS;
}

int inputList(position head, position q) {
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

position findElement(position root, char* word) {
	if (root == NULL)
		return NULL;
	else if (strcmp(root->el, word) > 0)
		root->left = findElement(root->left, word);
	else if (strcmp(root->el, word) < 0)
		root->right = findElement(root->right, word);
	else if (strcmp(root->el, word) == 0) // vraca element koji je isti kao rijec
		return root;
}

int countOccurences(position head, char* word) {
	int counter = 0;
	while (head!= NULL) {
		counter++; // broji koliko 'stvari' ima u vezanoj listi
		head = head->next;
	}
	return counter;
}