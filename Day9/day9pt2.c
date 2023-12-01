#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEGMENTS 10

int minpow2(int input) {
    int count = 0;
    while(input) { input >>= 1; count++; }
    return count;
}

void chase(int hr, int hc, int* tr, int* tc) {
    if((*tr) - hr > 1) {
        (*tr) --;
        if((*tc) < hc) { (*tc)++; }
        if((*tc) > hc) { (*tc)--; }
    } else if((*tr) - hr < -1) {
        (*tr) ++;
        if((*tc) < hc) { (*tc)++; }
        if((*tc) > hc) { (*tc)--; }
    } else if((*tc) - hc > 1) {
        (*tc) --;
        if((*tr) < hr) { (*tr)++; }
        if((*tr) > hr) { (*tr)--; }
    } else if((*tc) - hc < -1) {
        (*tc) ++;
        if((*tr) < hr) { (*tr)++; }
        if((*tr) > hr) { (*tr)--; }
    }
}

int main() { 
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }

    fseek(f, 0, SEEK_END);
    int fsz = ftell(f);
    char* filebuf = malloc(fsz);
    fseek(f, 0, SEEK_SET);
    fread(filebuf, sizeof(char), fsz, f);

    int nrows = 0;
    for(int i = 0; i < fsz; i++) {
        if(filebuf[i] == '\n') {
            nrows++;
        }
    }
    free(filebuf);
    
    int bits = minpow2(nrows);
    size_t mapsz = 1ul << (bits*2 - 3);
    char* map = malloc(mapsz);
    memset(map, 0, mapsz);

    int rows[SEGMENTS];
    int cols[SEGMENTS];
    memset(rows, 0, SEGMENTS*sizeof(int));
    memset(cols, 0, SEGMENTS*sizeof(int));
    
    void mark(int r, int c) {
        r &= ((1ul<<bits) - 1);
        c &= ((1ul<<bits) - 1);
        size_t longind = ((r << bits) + c) >> 3;
        int shortind = c & 0b111;
        map[longind] |= (1 << shortind);
    }

    fseek(f, 0, SEEK_SET);
    while(!feof(f)) {
        char dir;
        int dist;
        fscanf(f, "%c %i\n", &dir, &dist);
        for(int i = 0; i < dist; i++) {
            switch(dir) {
                case 'U': rows[0]++; break;
                case 'D': rows[0]--; break;
                case 'L': cols[0]--; break;
                case 'R': cols[0]++; break;
            }
            for(int i = 1; i < SEGMENTS; i++) {
                chase(rows[i-1], cols[i-1], rows+i, cols+i);
            }
            mark(rows[SEGMENTS-1], cols[SEGMENTS-1]);
        }
    }
    size_t total = 0;
    for(size_t i = 0; i < mapsz; i++) {
        for(int j = 0; j < 8; j++) {
            total += map[i] & 1;
            map[i] >>= 1;
        }
    }
    printf("%lu\n", total);
}