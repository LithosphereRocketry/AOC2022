#include <stdio.h>
#include <stdlib.h>

#define TURNS 20

struct ilist {
    int val;
    struct ilist* tail;
};

struct ilist* il_append(struct ilist* list, int val) {
    if(!list) {
        list = malloc(sizeof(struct ilist));
        list->val = val;
        list->tail = NULL;
        return list;
    } else {
        list->tail = il_append(list->tail, val);
        return list;
    }
}
struct ilist* il_pop(struct ilist* list, int* val) {
    if(list) {
        struct ilist* newlist = list->tail;
        *val = list->val;
        free(list);
        return newlist;
    } else {
        return NULL;
    }
}
void il_print(struct ilist* list) {
    if(list) {
        printf("%i", list->val);
        if(list->tail) {
            printf(", ");
            il_print(list->tail);
        }
    }
}
void il_destroy(struct ilist* list) {
    if(list) {
        il_destroy(list->tail);
        free(list);
    }
}

struct monkey {
    struct ilist* items;
    char op;
    int val;
    int test;
    int ifyes;
    int ifno;
    int count;
};

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }

    int nmonkeys = 1; // last entry doesn't have a double newline
    int nitems = 0;
    char lastc = -1;
    while(!feof(f)) {
        char c = getc(f);
        if(c == '\n' && lastc == '\n') { nmonkeys++; }
        lastc = c;
    }
    fseek(f, 0, SEEK_SET);
    struct monkey* monkeys = malloc(nmonkeys*sizeof(struct monkey));

    for(int i = 0; !feof(f); i++) {
        fscanf(f, "Monkey %*i:\n");
        int v;
        monkeys[i].items = NULL;
        fscanf(f, "  Starting items: %i", &v);
        monkeys[i].items = il_append(monkeys[i].items, v);
        while(fscanf(f, ", %i", &v)) {
            monkeys[i].items = il_append(monkeys[i].items, v);
        }
        char firstchar;
        fscanf(f, "\n  Operation: new = old %c %c", &monkeys[i].op, &firstchar);
        if(firstchar == 'o') {
            monkeys[i].op = '^';
            monkeys[i].val = 2;
            fscanf(f, "ld\n");
        } else {
            ungetc(firstchar, f);
            fscanf(f, "%i\n", &monkeys[i].val);
        }
        fscanf(f, "  Test: divisible by %i\n", &monkeys[i].test);
        fscanf(f, "    If true: throw to monkey %i\n", &monkeys[i].ifyes);
        fscanf(f, "    If false: throw to monkey %i\n", &monkeys[i].ifno);
        fscanf(f, "\n");
        monkeys[i].count = 0;
    }
    for(int i = 0; i < TURNS; i++) {
        for(int j = 0; j < nmonkeys; j++) {
            printf("Monkey %i: ", j);
            il_print(monkeys[j].items);
            printf("\n");
            while(monkeys[j].items) {
                int item;
                monkeys[j].items = il_pop(monkeys[j].items, &item);
                printf("\tInspect %i -> %c %i", item, monkeys[j].op, monkeys[j].val);
                switch(monkeys[j].op) {
                    case '+': item += monkeys[j].val; break;
                    case '*': item *= monkeys[j].val; break;
                    case '^': item *= item; break;
                    default: printf("Unrecognized op %c\n", monkeys[i].op);
                }
                printf(" = %i\n", item);
                item /= 3;
                printf("\t\tDecay to %i\n", item);
                int throwto = (item % monkeys[j].test == 0) ?
                    monkeys[j].ifyes : monkeys[j].ifno;
                printf("\t\tThrow to %i\n", throwto);
                monkeys[throwto].items = il_append(monkeys[throwto].items, item);
                monkeys[j].count++;
                printf("\t\tCount = %i\n", monkeys[j].count);

            }
        }
    }
    int most = 0;
    int secondmost = 0;
    for(int i = 0; i < nmonkeys; i++) {
        int val = monkeys[i].count;
        if(val > most) {
            secondmost = most;
            most = val;
        } else if(val > secondmost) {
            secondmost = val;
        }
        il_destroy(monkeys[i].items);
    }
    printf("%i\n", most*secondmost);
}