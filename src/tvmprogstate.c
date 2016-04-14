#include <stdlib.h>

#include "tvmprog.h"

int ppush(progstate *state, int i) {
	if (state->stackp < STACK_SIZE) {
		state->stack[state->stackp ++] = i;
		return 0;
	}
	else {
		return -1;
	}
}

int ppop(progstate *state, int *i) {
	if (state->stackp > 0) {
		if (i != NULL) {
			*i = state->stack[state->stackp - 1];
		}
		state->stackp --;
		return 0;
	}
	else {
		return -1;
	}
}

int ppeek(progstate *state, int *i) {
	if (state->stackp > 0) {
		*i = state->stack[state->stackp - 1];
		return 0;
	}
	else {
		return -1;
	}
}
