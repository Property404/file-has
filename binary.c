#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "binary.h"

static size_t get_size(int fd);
static int open_file(const char* path);


void construct_binary(Binary* self, const char* path) {
    const int fd = open_file(path);
    const size_t size = get_size(fd);
    uint8_t* map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    self->_fd = fd;
    self->map = map;
    self->size = size;
}

void destroy_binary(Binary* self) {
    close(self->_fd);
    munmap(self->map, self->size);
}

static size_t get_size(int fd) {
    struct stat st;
    if (0<fstat(fd, &st)) {
        fprintf(stderr, "Stat failed\n");
        exit(1);
    }
    return st.st_size;
}

static int open_file(const char* path) {
    const int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Could not open file '%s'\n", path);
        exit(1);
    }
    return fd;
}
