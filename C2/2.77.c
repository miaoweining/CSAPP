#include <stdio.h>

int divide_power2(int x, int k) {
	int ans = x >> k;
    int w   = sizeof(int) << 3;
    ans    += (x >> (w-1)) && (x & ((1<<k)-1));
    return ans;
}

int main() {
	printf("%d", divide_power2(10, 1));
	
	return 0;
} 
