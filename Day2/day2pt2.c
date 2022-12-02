#include <stdio.h>

int main(size_t argc, char** argv) {
	FILE* f = fopen("input.txt", "r");
	int total = 0;
		
	while(!feof(f)) {
		char result;
		char other;
		fscanf(f, "%c %c\n", &other, &result);
		int resultVal = result - 'X';
		int otherVal = other - 'A';
		int selfVal = (otherVal + resultVal + 2) % 3;
		int score = (selfVal + 1) + resultVal*3;
		total += score;
	}
	printf("%i\n", total);
}