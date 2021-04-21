#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

#include "binary.h"

static size_t get_size(int fd);
static int open_file(const char* path);


Binary::Binary(const char* path) {
    const int fd = open_file(path);
    const size_t size = get_size(fd);
    uint8_t* map = static_cast<uint8_t*>(mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0));

    this->_fd = fd;
    this->_map = map;
    this->_size = size;
}

Binary::~Binary() {
	if(this->_fd)
		close(this->_fd);

	if(this->_map)
		munmap(this->_map, this->_size);
}

uint8_t Binary::operator[] (size_t idx)const {
	if (idx >= this->_size)
		throw std::runtime_error("Index out of bounds");

	return this->_map[idx];
}


std::optional<size_t> Binary::find(const Binary& small) const {
    if(this->size() < small.size()) {
		throw std::runtime_error("Needle is bigger than haystack");
    }

    for (size_t i=0; i<this->size(); i++) {
        for(size_t j=0;j<small.size();j++) {
            if (this->_map[i+j] != small[j]) {
                break;
            }
            
            // Hooray!
            if(j == small.size() - 1) {
                return i;
            }
        }
    }

    return {};
}

static size_t get_size(int fd) {
    struct stat st;
    if (fstat(fd, &st)) {
		throw std::runtime_error("Stat failed");
    }
    return st.st_size;
}

static int open_file(const char* path) {
    const int fd = open(path, O_RDONLY);
    if (fd < 0) {
		throw std::runtime_error(std::string("Could not open file")+path);
    }
    return fd;
}
