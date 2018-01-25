#include <stdio.h>

int mul5div8(int x) {
	int b0 = x&1, b2 = (x>>2)&1;
    int ans = (x>>3) + (x>>1);
    int w = sizeof(int)<<3;
    ans += (b0&b2);
    ans += ((x>>(w-1)) && (x&7));
    return ans;
}

int main() {
	
	return 0;
} 
