#include <stdio.h>

int main() {
	
	return 0;
}

float fpwr2(int x) {
	unsigned exp, frac;
	unsigned u;
	
	if(x < -149) {
		// ̫С������0.0 
		exp  = 0x0;
		frac = 0x0;
	} else if(x < -129) {
		// �ǹ��ֵ 
		exp = 0x0;
		frac = 1 << (x+149);
	} else if(x < 128) {
		// ���ֵ 
		exp = x + 127;
		frac = 0;
	} else {
		// ̫�󣬷��������� 
		exp = 255;
		frac = 0;
	}
	
	u = exp << 23 | frac;
	
	return u2f(u);
}
