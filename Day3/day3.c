#include <stdio.h>
#include <string.h>

int priority(char item) {
	return (item > 'Z') ? (item-'a'+1) : (item-'A'+27);
}

char match(char* line) {
	int nitems = strlen(line);
	char* back = line + nitems/2;
	for(int i = 0; i < nitems/2; i++) {
		for(int j = 0; j < nitems/2; j++) {
			if(back[i] == line[j]) {
				return back[i];
			}
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	FILE* f = fopen("input.txt", "r");
	int total = 0;
		
	while(!feof(f)) {
		char line[512];
		fscanf(f, "%s\n", line);
		total += priority(match(line));
	}
	printf("%i\n", total);
}