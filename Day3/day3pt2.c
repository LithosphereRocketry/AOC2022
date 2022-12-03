#include <stdio.h>
#include <string.h>

int priority(char item) {
	return (item > 'Z') ? (item-'a'+1) : (item-'A'+27);
}

char match(char lines[3][512]) {
	for(char* pos = lines[0]; *pos != 0; pos++) {
		for(char* pos2 = lines[1]; *pos2 != 0; pos2++) {
			if(*pos == *pos2) {
				for(char* pos3 = lines[2]; *pos3 != 0; pos3++) {
					if(*pos == *pos3) {
						return *pos;
					}
				}
				break;
			}
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	FILE* f = fopen("input.txt", "r");
	int total = 0;
		
	while(!feof(f)) {
		char line[3][512];
		fscanf(f, "%s\n", line[0]);
		fscanf(f, "%s\n", line[1]);
		fscanf(f, "%s\n", line[2]);
		total += priority(match(line));
	}
	printf("%i\n", total);
}