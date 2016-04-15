#ifndef TVMPROGRAM_H
#define TVMPROGRAM_H

#include <stdio.h>
#include "tvmtype.h"

typedef struct _instr {
	enum {
		PUSHI = '#',			//push integer to stack
		PUSHC = '@',			//push character to stack
		POP = '~',				//pop and discard integer from stack
		PCHAR = '>',			//print character at top of stack
		PINT = '}',				//print integer at top of stack
		IADD =  '+',
		ISUB =  '-',
		IMUL =  '*',
		IDIV =  '/',
		IMOD =  '%',
	} name;
	int arg;
} instr;

typedef struct _program {
	instr *instrs;
	uint length;
} program;

#define STACK_SIZE 2048

typedef struct _progstate {
	int stack[STACK_SIZE];
	int stackp;
} progstate;

typedef struct {
	enum {
		SUCCESS = 0,
		INVALID_INSTRUCTION,
		INVALID_INTEGER,
		INVALID_ESCAPE,
	} type;
	uint line;
	uint column;
	char symbol;
} ploadret;

ploadret pload(program *p, FILE *file);	//load program from file
int prun(progstate *state, program p);		//run program
void pfree(program p);							//free program from memory

#define progstatenew() (progstate) {{}, 0}

int ppush(progstate *state, int i);
int ppop(progstate *state, int *i);
int ppeek(progstate *state, int *i);

#endif
