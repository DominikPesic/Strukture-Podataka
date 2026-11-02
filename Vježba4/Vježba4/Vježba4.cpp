#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct polynom* position;
typedef struct polynom {

	int coef;
	int pow;
	position next;

}Pol;
int addAfter(position P, position newP) {

	newP->next = P->next;
	P->next = newP;

	return 0;
}


int insertSorted(position P,int coef,int pow) {
	
	position newP;

	while (P->next != NULL && P->next->pow < pow) {
		P = P->next;
	}

	if (P->next != NULL && P->next->pow == pow) {
		P->next->coef += coef;
		return 0;
	}

	newP = (position)malloc(sizeof(Pol));
	if (!newP) {
		return  -1;
	}
	
	newP->coef = coef;
	newP->pow = pow;
	newP->next = NULL;
	addAfter(P, newP);

	
	return 0;
}

int add(position n1, position n2, position res) {
	position q;

	for (q = n1->next; q != NULL; q = q->next) {
		insertSorted(res, q->coef, q->pow);
	}

	for (q = n2->next; q != NULL; q = q->next) {
		insertSorted(res, q->coef, q->pow);
	}

	return 0;
}
int multi(position n1,position n2,position P) {
	
	position q;
	position k;
	


	for (q = n1->next; q != NULL; q = q->next) {
		for (k = n2->next; k != NULL; k = k->next) {
			
				int c = q->coef * k->coef;
				int e = q->pow + k->pow;
				insertSorted(P, c, e);
			
		}
	}

	

	return 0;
}
int load(FILE* dat, position head) {
	int n, c, e, i;

	if (fscanf(dat, "%d", &n) != 1) {
		return -1;
	}

	for (i = 0; i < n; i++) {
		if (fscanf(dat, "%d %d", &c, &e) != 2) {
			return -1;
		}
		insertSorted(head, c, e);
	}

	return 0;
}
int ispis(position P) {
	position q;

	for (q = P->next; q != NULL; q = q->next) {
		printf("%dx^%d", q->coef, q->pow);
	}
	printf("\n");
	return 0;
}


int main() {
	Pol Head = { 0,0,NULL };
	Pol p1 = Head;
	Pol p2 = Head;
	Pol  addi= Head;
	Pol mult = Head;

	FILE* dat = fopen("t.txt", "r");
	if (!dat) {
		return -1;
	}

	load(dat, &p1);
	load(dat, &p2);
	fclose(dat);

	add(&p1, &p2, &addi);
	multi(&p1, &p2, &mult);
	printf("p1: ");
	ispis(&p1);
	printf("\np2: ");
	ispis(&p2);
	printf("\nZbroj: ");
	ispis(&addi);
	printf("\nUmnozak: ");
	ispis(&mult);

	return 0;
}