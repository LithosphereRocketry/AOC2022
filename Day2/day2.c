#include <stdio.h>

// much less awful code this time bc it wasn't 4am

int main(size_t argc, char** argv) {
	FILE* f = fopen("input.txt", "r");
	int total = 0;
		
	while(!feof(f)) {
		char self;
		char other;
		fscanf(f, "%c %c\n", &other, &self);
		int selfVal = self - 'X';
		int otherVal = other - 'A';
		int score = (selfVal + 1) + ((selfVal - otherVal + 4) % 3) * 3;
		total += score;
	}
	printf("%i\n", total);
}