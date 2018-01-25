#include <stdio.h> 
#include <Windows.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
	int i;
	for (i = 0; i<len; i++) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void show_int(int x) {
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_poniter(void *x) {
	show_bytes((byte_pointer)&x, sizeof(void *));
}


int main() {
	int ival   = 12345;
	float fval = 12345.0;
	int *pval  = &ival;

	show_int(ival);
	show_float(fval);
	show_poniter(pval);

	Sleep(50000);
	return 0;
}
