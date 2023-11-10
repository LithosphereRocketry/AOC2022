#include <stdio.h>
#include <string.h>

char state[] = {0, 0, 0, 0};
int count = 0;
int burndown = 4;

int max(int a, int b) { return a>b ? a : b; }

int main() {
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }
    while(!feof(f)) {
        count++;
        burndown--;
        memmove(state, state+1, 3);
        state[3] = fgetc(f);

        if(state[2] == state[3]) {
            burndown = max(burndown, 3);
        } else if(state[1] == state[3]) {
            burndown = max(burndown, 2);
        } else if(state[0] == state[3]) {
            burndown = max(burndown, 1);
        } else if(burndown <= 0) {
            printf("%i\n", count);
            return 0;
        }
    }
    printf("No pattern found\n");
}