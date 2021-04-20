#include "binary.h"
#include <stdlib.h>
#include <stdio.h>

ssize_t compare(const Binary* big, const Binary* small) {
    if(big->size < small->size) {
        fprintf(stderr, "Wrong size order\n");
        exit(1);
    }

    for (size_t i=0; i<big->size; i++) {
        for(size_t j=0;j<small->size;j++) {
            if (big->map[i+j] != small->map[j]) {
                break;
            }
            
            // Hooray!
            if(j == small->size - 1) {
                return i;
            }
        }
    }

    return -1;
}

int main(int argc, const char** argv) {

    if (argc<3) {
        fprintf(stderr, "Need two arguments!\n");
        return 1;
    }

    Binary big;
    Binary small;

    construct_binary(&big, argv[1]);
    construct_binary(&small, argv[2]);

    const ssize_t cmp = compare(&big, &small);

    if (cmp<0) {
        fprintf(stderr, "No match\n");
        return 1;
    } else {
        printf("Found @ 0x%lx\n", cmp);
        return 0;
    }

    destroy_binary(&big);
    destroy_binary(&small);
}
