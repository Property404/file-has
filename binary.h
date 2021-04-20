#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int _fd;
    uint8_t* map;
    size_t size;
} Binary;

void construct_binary(Binary* self, const char* path);
void destroy_binary(Binary* self);
