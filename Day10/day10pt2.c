#include <stdio.h>
#include <stdlib.h>

int x = 1;
int pc = 0;

void step() {
    int hpos = pc % 40;
    if(abs(hpos-x) <= 1) {
        printf("#");
    } else {
        printf(".");
    }
    if(hpos == 39) {
        printf("\n");
    }
    pc++;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }

    while(!feof(f)) {
        char instr[4];
        fread(instr, 1, 4, f);
        if(instr[0] == 'n') {
            fscanf(f, "\n");
            step();
        } else {
            int offs;
            fscanf(f, " %i\n", &offs);
            step();
            step();
            x += offs;
        }
    }
}