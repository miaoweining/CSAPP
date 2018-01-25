/**
 * 判断两个有符号数（补码）相加是否发生溢出及提示发生何种溢出
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
		printf("正溢出");
	} else if (-1 == tmp) {
		printf("负溢出");
	} else {
		printf("正常");
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