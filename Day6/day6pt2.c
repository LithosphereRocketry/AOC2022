#include <stdio.h>
#include <string.h>

#define DEPTH 14

char state[DEPTH];
int count = 0;
int burndown = DEPTH;

int max(int a, int b) { return a>b ? a : b; }

int main() {
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }
    while(!feof(f)) {
        count++;
        burndown--;
        memmove(state, state+1, DEPTH-1);
        state[DEPTH-1] = fgetc(f);

        for(int i = DEPTH-2; i >= 0; i--) {
            if(state[i] == state[DEPTH-1]) {
                burndown = max(burndown, i+1);
                break;
            }
        }

        if(burndown <= 0) {
            printf("%i\n", count);
            return 0;
        }
    }
    printf("No pattern found\n");
}