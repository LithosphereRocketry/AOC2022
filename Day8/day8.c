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

    size_t rows = 1;
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
    char index(size_t r, size_t c) { return filebuf[r*(cols+1) + c]; }
    char* visible = malloc(rows*cols);
    memset(visible, 0, rows*cols);
    void setvis(size_t r, size_t c) { visible[r*cols + c] |= 1; }

    for(int r = 0; r < rows; r++) {
        setvis(r, 0);
        char height = index(r, 0);
        for(int c = 1; c < cols; c++) {
            char newitem = index(r, c);
            if(newitem > height) {
                setvis(r, c);
                height = newitem;
            }
        }

        setvis(r, cols-1);
        height = index(r, cols-1);
        for(int c = cols-2; c >= 0; c--) {
            char newitem = index(r, c);
            if(newitem > height) {
                setvis(r, c);
                height = newitem;
            }
        }
    }

    for(int c = 0; c < cols; c++) {
        setvis(0, c);
        char height = index(0, c);
        for(int r = 1; r < rows; r++) {
            char newitem = index(r, c);
            if(newitem > height) {
                setvis(r, c);
                height = newitem;
            }
        }

        setvis(rows-1, c);
        height = index(rows-1, c);
        for(int r = rows-2; r >= 0; r--) {
            char newitem = index(r, c);
            if(newitem > height) {
                setvis(r, c);
                height = newitem;
            }
        }
    }
    free(filebuf);

    size_t count = 0;
    for(int i = 0; i < rows*cols; i++) {
        if(visible[i]) {
            count++;
        }
    }
    free(visible);

    printf("%lu\n", count);

}