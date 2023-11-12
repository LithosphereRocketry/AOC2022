#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { 
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }

    fseek(f, 0, SEEK_END);
    size_t fsz = ftell(f);
    char* filebuf = malloc(fsz);
    fseek(f, 0, SEEK_SET);
    fread(filebuf, sizeof(char), fsz, f);

    size_t rows = 0;
    size_t cols = 0;
    int colsDone = 0;
    for(int i = 0; i < fsz; i++) {
        if(filebuf[i] == '\n') {
            rows++;
            colsDone = 1;
        } else if(!colsDone) {
            cols++;
        }
    }
    char index(size_t r, size_t c) { return filebuf[r*(cols+1) + c] - '0'; }
    
    size_t sweep(size_t r, size_t c, int dr, int dc) {
        char height = index(r, c);
        size_t count = 0;
        size_t ir = r+dr, ic = c+dc;
        int stop = 0;

        while(1) {
            if(ir < 0 || ic < 0 || ir >= rows || ic >= cols) break;
            count++;
            if(index(ir, ic) >= height) break;
            ir += dr;
            ic += dc;
        }
        return count;
    }

    size_t bestScore = 0;
    for(size_t r = 0; r < rows; r++) {
        for(size_t c = 0; c < cols; c++) {
            size_t score = sweep(r, c, 0, 1) * sweep(r, c, 0, -1)
                         * sweep(r, c, 1, 0) * sweep(r, c, -1, 0);
            if(score > bestScore) { bestScore = score; }
        }
    }

    free(filebuf);
    printf("%lu\n", bestScore);

}