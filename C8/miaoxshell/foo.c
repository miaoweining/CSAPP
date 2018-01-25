#include <stdio.h>

int main(int argc, char **argv, char **envp) {
	
	if(argc!=2) {
		puts("foo <seconds>");
	} else {
		sleep(atoi(argv[1]));
	}
	
	return 0;
}
