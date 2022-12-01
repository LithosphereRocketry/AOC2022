#include <stdio.h>

// this is hella ugly but I'm tired

int main(size_t argc, char** argv) {
	FILE* f = fopen("testinput.txt", "r");
	int running = 0;
	int best = 0;
	while(!feof(f)) {
		int calorie = 0;
		char in = getc(f); 
		while(!feof(f) && in != '\n' && in != '\r') {
			calorie *= 10;
			calorie += (in - '0');
			in = getc(f);
		}
		if(!feof(f)) {
			in = getc(f);
			if(in != '\n' && in != '\r') {
				ungetc(in, f);
			}
		}
		running += calorie;
		printf("%i\t:\t%i\n", calorie, running);
		if(calorie == 0 || feof(f)) {
			if(best < running) {
				best = running;
			}
			printf(" ==== \n");
			running = 0;
		}
	}
	printf("%i\n", best);
}