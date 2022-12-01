#include <stdio.h>

void placein3(int* arr, int val) {
	int temp;
	if(val > arr[0]) {
		temp = val;
		val = arr[0];
		arr[0] = temp;
	}
	if(val > arr[1]) {
		temp = val;
		val = arr[1];
		arr[1] = temp;
	}
	if(val > arr[2]) {
		arr[2] = val;
	}
}

int main(size_t argc, char** argv) {
	FILE* f = fopen("testinput.txt", "r");
	int running = 0;
	int best[3];
	best[0] = 0;
	best[1] = 0;
	best[2] = 0;
	
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
			placein3(best, running);
			printf(" ==== \n");
			running = 0;
		}
	}
	printf("%i, %i, %i : %i\n", best[0], best[1], best[2], best[0]+best[1]+best[2]);
}