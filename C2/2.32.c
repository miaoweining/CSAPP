/**
* 判断两个有符号数（补码）相减是否发生溢出及提示发生何种溢出
* buggy：忽略了TMin=-TMin，造成当y为TMin时，只要x-y，x为负数就提示负溢出，其实没有溢出。
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
		printf("正溢出");
	}
	else if (-1 == tmp) {
		printf("负溢出");
	}
	else {
		printf("正常");
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