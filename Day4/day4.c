#include <stdio.h>


int main(int argc, char** argv) {
	FILE* f = fopen("input.txt", "r");
	if(!f) {
		printf("No file found\n");
		return 1;
	}
	int total = 0;
	
	
	while(!feof(f)) {
		unsigned int s1, s2, e1, e2;
		fscanf(f, "%u-%u,%u-%u\n", &s1, &e1, &s2, &e2);
		if((s2 >= s1 && e2 <= e1) || (s1 >= s2 && e1 <= e2)) {
			total++;
		}
	}
	printf("%i\n", total);
}