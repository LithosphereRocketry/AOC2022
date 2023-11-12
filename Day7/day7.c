#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct node {
    int dir;
    char* name;
    struct node* parent;
    union {
        struct {
            size_t n_contents;
            struct node** contents;
        } d;
        struct {
            size_t size;
        } f;
    } data;
} node;

size_t nodeSize(node* n) {
    if(n->dir) {
        size_t total = 0;
        for(int i = 0; i < n->data.d.n_contents; i++) {
            total += nodeSize(n->data.d.contents[i]);
        }
        return total;
    } else {
        return n->data.f.size;
    }
}

void addNode(node* parent, node* child) {
    node** newContents = malloc(sizeof(node*)*(parent->data.d.n_contents+1));
    if(parent->data.d.contents) {
        memcpy(newContents, parent->data.d.contents, parent->data.d.n_contents * sizeof(node*));
        free(parent->data.d.contents);
    }
    newContents[parent->data.d.n_contents] = child;
    parent->data.d.contents = newContents;
    parent->data.d.n_contents ++;
    child->parent = parent;
}

node* findChild(node* parent, char* name) {
    if(parent->dir) {
        for(int i = 0; i < parent->data.d.n_contents; i++) {
            node* newNode = parent->data.d.contents[i];
            if(strcmp(newNode->name, name) == 0) {
                return newNode;
            }
        }
    }
    return NULL;
}

size_t total_of_large(node* start) {
    if(start->dir) {
        size_t total = nodeSize(start);
        if(total > 100000) {
            total = 0;
        }
        for(int i = 0; i < start->data.d.n_contents; i++) {
            total += total_of_large(start->data.d.contents[i]);
        }
        return total;
    } else {
        return 0;
    }
}

node root;
node* current = &root;

char linebuf[512]; // this should be enough
int main() {
    root.dir = 1;
    root.name = "ROOT";
    root.data.d.n_contents = 0;
    root.data.d.contents = NULL;

    FILE* f = fopen("input.txt", "r");
    if(!f) { return -1; }
    while(!feof(f)) {
        fgets(linebuf, 512, f);
        linebuf[strlen(linebuf)-1] = '\0';
        printf("%s\n", linebuf);
        if(linebuf[0] == '$') {
            if(linebuf[2] == 'c') {
                if(linebuf[5] == '/') {
                    current = &root;
                } else if(linebuf[5] == '.') {
                    current = current->parent;
                } else {
                    current = findChild(current, linebuf+5);
                }
            }
        } else {
            if(linebuf[0] == 'd') {
                char* name = strdup(linebuf+4);
                if(!findChild(current, name)) {
                    node* newNode = malloc(sizeof(node));
                    newNode->name = name;
                    newNode->dir = 1;
                    newNode->data.d.n_contents = 0;
                    newNode->data.d.contents = NULL;
                    addNode(current, newNode);
                }
            } else {
                char namebuf[512];
                size_t size;
                sscanf(linebuf, "%lu %s", &size, namebuf);
                if(!findChild(current, namebuf)) {
                    node* newNode = malloc(sizeof(node));
                    newNode->name = strdup(namebuf);
                    newNode->dir = 0;
                    newNode->data.f.size = size;
                    addNode(current, newNode);
                }
            }
        }
    }
    printf("%lu\n", total_of_large(&root));
}