/**
 * �ж������з����������룩����Ƿ����������ʾ�����������
 */
#include <stdio.h>
#include <Windows.h>

int tadd_ok(int x, int y);

int main() {
	int x, y, tmp;
	x = 0x7FFFFFFF;
	y = 0x0;
	tmp = tadd_ok(x, y);

	printf("%d\n", tmp);
	if (1 == tmp) {
		printf("�����");
	} else if (-1 == tmp) {
		printf("�����");
	} else {
		printf("����");
	}	

	Sleep(500000);
	return 0;
}

int tadd_ok(int x, int y) {
	int s = x + y;
	printf("s=%d\n", s);

	if (x>=0 && y>=0 && s<0) {
		return 1;
	}
	else if (x < 0 && y < 0 && s>=0) {
		return -1;
	}
	else {
		return 0;
	}

};