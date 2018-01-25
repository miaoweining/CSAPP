#include <stdio.h>

int main() {
	
	return 0;
}

float fpwr2(int x) {
	unsigned exp, frac;
	unsigned u;
	
	if(x < -149) {
		// 太小，返回0.0 
		exp  = 0x0;
		frac = 0x0;
	} else if(x < -129) {
		// 非规格化值 
		exp = 0x0;
		frac = 1 << (x+149);
	} else if(x < 128) {
		// 规格化值 
		exp = x + 127;
		frac = 0;
	} else {
		// 太大，返回正无穷 
		exp = 255;
		frac = 0;
	}
	
	u = exp << 23 | frac;
	
	return u2f(u);
}
