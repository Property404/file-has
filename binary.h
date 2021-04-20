#pragma once
#include <cstdint>
#include <cstdlib>
#include <optional>

// Represents a binary file
class Binary {
	private:
    uint8_t* _map;
    size_t _size;
    int _fd;

	public: 
	Binary(const char* path);

	Binary(Binary&& rhs) = delete;
	Binary& operator=(Binary&& rhs) = delete;
	Binary(const Binary&) = delete;
	Binary& operator=(const Binary&) = delete;

	// Look for smaller binary in self Returns nothing if not found, otherwise
	// returns the exact location
	std::optional<size_t> find(const Binary& binary) const;

	// Getters
	size_t size() const noexcept  { return _size; }

	// Access bytes by indexing
	uint8_t operator[](size_t idx) const;

	~Binary();
};
