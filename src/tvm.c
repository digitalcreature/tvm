#include <stdlib.h>
#include <stdio.h>
#include "tvmtype.h"
#include "tvmprog.h"

#define usage(name) printf("usage: %s <sourcefile.tvm>\n", name); return -1

int main(int argc, char *argv[]) {
	if (argc < 2) {
		usage(argv[0]);
	}
	else {
		char *fname = argv[1];
		FILE *file = fopen(fname, "r");
		if (file == NULL) {
			printf ("invalid file: %s\n", fname);
			return -1;
		}
		program p;
		ploadret ret = pload(&p, file);
		if (ret.type == SUCCESS) {
			printf("%d instructions loaded successfully\n", p.length);
		}
		else {
			printf("error loading source: ");
			switch (ret.type) {
				case SUCCESS:
					printf("SUCCESS");
					break;
				case INVALID_INSTRUCTION:
					printf("INVALID_INSTRUCTION");
					break;
				case INVALID_INTEGER:
					printf("INVALID_INTEGER");
					break;
			}
			printf(" in %s:%d:%d: '%c'(%d)\n", fname, ret.line, ret.column, ret.symbol, ret.symbol);
		}
		fclose(file);
		printf("\nprogram output:\n\n");
		prun(p);
		return ret.type;
	}
}