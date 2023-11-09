#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int ind;
    char* data;
} charstk;

void push(charstk* stk, char item) {
    stk->data[stk->ind] = item;
    stk->ind++;
}
char pop(charstk* stk) {
    stk->ind--;
    return stk->data[stk->ind];
    // This is a little bit hacky but who cares this isn't threaded
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }
    
    size_t section = -1;
    char lastC = 0;
    while(!feof(f)) {
        char newC = fgetc(f);
        if(newC == '\n' && lastC == '\n') {
            section = ftell(f)-2;
            break;
        } else {
            lastC = newC;
        }
    }

    char* hdrbuf = malloc(section+1);
    fseek(f, 0, SEEK_SET);
    fread(hdrbuf, sizeof(char), section, f);
    hdrbuf[section] = '\0';

    char* axisText;
    for(char* p = hdrbuf; *p != 0; p++) {
        if(*p == '\n') {
            axisText = p;
        }
    }
    *axisText = '\0';
    axisText++;

    int cols = (hdrbuf + section - axisText)/4 + 1;
    int rows = (strlen(hdrbuf)+1)/4 / cols;
    char* stkbuf = malloc(rows*cols*cols);
    // allow everything to be stacked in one corner

    charstk* stacks = malloc(cols*sizeof(charstk));
    for(int i = 0; i < cols; i++) {
        stacks[i].ind = 0;
        stacks[i].data = stkbuf + rows*cols*i;
    }
    for(int r = rows-1; r >= 0; r--) {
        for(int c = 0; c < cols; c++) {
            char item = hdrbuf[(r*cols + c)*4 + 1];
            if(item != ' ') {
                push(stacks+c, item);
            }
        }
    }
    free(hdrbuf);

    fseek(f, section+2, SEEK_SET);
    while(!feof(f)) {
        int qty, src, dst;
        fscanf(f, "move %i from %i to %i\n", &qty, &src, &dst);
        for(int i = 0; i < qty; i++) {
            push(stacks+dst-1, pop(stacks+src-1));
        }
    }

    for(int i = 0; i < cols; i++) {
        printf("%c", pop(stacks+i));
    }
    printf("\n");

    free(stacks);
    free(stkbuf);
}