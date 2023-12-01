#include <stdio.h>

int x = 1;
int pc = 1;

int sum = 0;
void step() {
    if(pc % 40 == 20) {
        sum += pc*x;
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
    printf("%i\n", sum);
}