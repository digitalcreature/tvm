#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "tvmtype.h"
#include "tvmprog.h"

#define STARTCAP 16
#define EXPANDFACTOR 1.5f

#define chkpntr(p) if (p == NULL) fprintf(stderr, "Could not allocate memory.\n")

void paddi(program *p, instr i, uint *cap) {
	if (p->length == *cap) {
		*cap *= EXPANDFACTOR;
		p->instrs = realloc(p->instrs, *cap * sizeof(instr));
		chkpntr(p->instrs);
	}
	p->instrs[p->length++] = i;
}

char nextc(FILE *file, char *c, uint *column) {
	*c = fgetc(file);
	(*column) ++;
	return *c;
}

int fgeti(FILE *file, char *c, int *i, uint *column) {
	int sign = 1;
		#define nextc() nextc(file, c, column)
	if (*c == '-') {
		sign = -1;
		nextc();
	}
	else if (*c == '+') {
		nextc();
	}
	if (isdigit(*c)) {
		*i = *c - '0';
		while (isdigit(nextc())) {
			*i *= 10;
			*i += *c - '0';
		}
		*i *= sign;
		return 0;
	}
	else {
		return -1;
	}
		#undef nextc
}

ploadret pload(program *_p, FILE *file) {
	program p = {NULL, 0};
	uint cap = STARTCAP;
	p.instrs = malloc(cap * sizeof(instr));
	chkpntr(p.instrs);
	uint line = 1;
	uint column = 0;
	char c;
		#define nextc() nextc(file, &c, &column)
		#define skipspaces() if (isspace(c)) while (isspace(nextc())) if (c == '\n') line = (column = 0 , line + 1)
		#define ploadret(type) ((ploadret) {type, line, column, c})
		#define paddi(i) paddi(&p, i, &cap)
		#define fgeti(i) if (fgeti(file, &c, i, &column) < 0) return (pfree(p), ploadret(INVALID_INTEGER))
	instr i;
	nextc();
	while (c != EOF) {
		skipspaces();
		i.name = (instrname) c;
		switch (i.name) {
			//these take an argument
			case PUSHC:
				skipspaces();
				i.arg = nextc();
				nextc();
				break;
			case PUSHI:
				nextc();
				skipspaces();
				fgeti(&i.arg);
				break;
			//these take no argument
			case POP:
			case PCHAR:
				nextc();
				skipspaces();
				i.arg = 0;
				break;
			default:
				pfree(p);
				return ploadret(INVALID_INSTRUCTION);
		}
		printf("%c '%c' (%d)\n", i.name, i.arg, i.arg);
		paddi(i);
	}
	*_p = p;
	return ploadret(SUCCESS);
		#undef nextc
		#undef skipspaces
		#undef paddi
		#undef fgeti
}


int prun(program p) {
		#define STACK_SIZE 2048
	int stack[STACK_SIZE];
	int stackp = 0;
		#define push(i) if (stackp < STACK_SIZE) stack[stackp ++] = i; else return (fprintf(stderr, "STACK OVERFLOW\n"), -1)
		#define pop(i) if (stackp >= 0) i = stack[stackp --]; else return (fprintf(stderr, "STACK UNDERFLOW\n"), -1)
		#define peek(i) (i = stack[stackp - 1])
	instr *pp = p.instrs;
	int i;
	while (pp - p.instrs < p.length) {
		switch (pp->name) {
			case PUSHI:
				push(0);
				break;
			case PUSHC:
				break;
			case POP:
				pop(i);
				break;
			case PCHAR:
				peek(i);
				break;
		}
		pp ++;
	}
	return 0;
}

void pfree(program p) {
	free(p.instrs);
	p.length = 0;
}
