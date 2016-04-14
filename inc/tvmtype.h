#ifndef TVMTYPE_H
#define TVMTYPE_H

typedef unsigned int uint;

typedef enum {
	PUSHI = '#',			//push integer to stack
	PUSHC = '@',			//push character to stack
	POP = '~',			//pop and discard integer from stack
	PCHAR = '>',			//print character at top of stack
} instrname;

typedef struct _instr {
	instrname name;
	int arg;
} instr;

typedef struct _program {
	instr *instrs;
	uint length;
} program;

#endif
