/*
�ж������޷���������Ƿ������
*/
#include <stdio.h>
#include <Windows.h>

int uadd_ok(unsigned x, unsigned y);

int main() {
	unsigned x, y;
	x = 0x1;
	y = 0xffffffff;
	if (uadd_ok(x, y)) {
		printf("���");
	}

	Sleep(500000);
	return 0;
}

int uadd_ok(unsigned x, unsigned y) {
	unsigned s = x + y;
	return s < x;
};