#ifndef TVMPROGRAM_H
#define TVMPROGRAM_H

#include <stdio.h>
#include "tvmtype.h"

typedef struct {
	enum {
		SUCCESS = 0,
		INVALID_INSTRUCTION,
		INVALID_INTEGER,
	} type;
	uint line;
	uint column;
	char symbol;
} ploadret;

ploadret pload(program *p, FILE *file);	//load program from file
int prun(program p);						//run program
void pfree(program p);					//free program from memory

#endif
