/**
* �ж������з����������룩����Ƿ����������ʾ�����������
* buggy��������TMin=-TMin����ɵ�yΪTMinʱ��ֻҪx-y��xΪ��������ʾ���������ʵû�������
*/
#include <stdio.h>
#include <Windows.h>

int tsub_ok(int x, int y);
int tadd_ok(int x, int y);

int main() {
	int x, y, tmp;
	x = 0x82000000;
	y = MININT32;
	tmp = tsub_ok(x, y);

	printf("TMin=%d, -TMin=%d\n", MININT32);
	if (1 == tmp) {
		printf("�����");
	}
	else if (-1 == tmp) {
		printf("�����");
	}
	else {
		printf("����");
	}

	Sleep(500000);
	return 0;
}

int tsub_ok(int x, int y) {
	return tadd_ok(x,  -y);
}

int tadd_ok(int x, int y) {
	int s = x + y;
	printf("s=%d\n", s);

	if (x >= 0 && y >= 0 && s<0) {
		return 1;
	}
	else if (x < 0 && y < 0 && s >= 0) {
		return -1;
	}
	else {
		return 0;
	}

};