#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct Element* position;
typedef struct Element {

	double num;
	position next;
}Element;

int Push(position Head,double N) {
	position q = (position)malloc(sizeof(Element));
	if (q == NULL) {
		return -1;
	}

	q->num = N;
	q->next = Head->next;
	Head->next = q;
	return 0;
}
int Pop(position Head, double* out) {
	position q = Head->next;
	if (q == NULL) {
		return -1;
	}
	*out = q->num;
	Head->next = q->next;
	free(q);

	return 0;
}


int Postfix(const char* namedat,position Head, double* rez){
	FILE* dat = fopen(namedat, "r");
	if (!dat) {
		return -1;
	}
	double broj,a, b;
	char op;

	while (!feof(dat)) {

		if (fscanf(dat, "%lf", &broj) == 1) {
			Push(Head, broj);
		}
		else if (fscanf(dat, " %c", &op) == 1) {
			if (Pop(Head, &b) != 0 || Pop(Head, &a) != 0 ) {
				printf("Neispravno");
				fclose(dat);
				return -1;
			}

			if (op == '+') {
				Push(Head, a + b);
			}
			if (op == '-') {
				Push(Head, a - b);
			}
			if (op == '*') {
				Push(Head, a *b);
			}
			if (op == '/') {
				Push(Head, a / b);
			}
		}
	}

	fclose(dat);
	return Pop(Head, rez);


}



int main() {
	Element Head = {0,NULL};
	double rez;

	if (Postfix("postfix.txt", &Head, &rez) == 0) {
		printf("Rezultat je %f\n", rez);
	}
	else {
		printf("Greska\n");
	}
	return 0;
}