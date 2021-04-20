SHELL = /bin/sh

SRC_DIR = .
OBJ_DIR = ./build

INSTALL_DIR = ~/.local/bin
INSTALL_COMMAND = install
EXECUTABLE_NAME = file-has

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20 -fmax-errors=4
OBJECTS = $(addprefix $(OBJ_DIR)/,binary.o main.o )

# Build recipe
$(EXECUTABLE_NAME): $(OBJ_DIR) $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CXXFLAGS)
$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CXX) -c -o $@ $^ $(CXXFLAGS)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
install: $(EXECUTABLE_NAME)
	$(INSTALL_COMMAND) $(EXECUTABLE_NAME) $(INSTALL_DIR)
uninstall:
	rm $(INSTALL_DIR)/$(EXECUTABLE_NAME)
clean: $(OBJ_DIR)
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
	rmdir $(OBJ_DIR)
