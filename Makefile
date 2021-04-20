SHELL = /bin/sh

SRC_DIR = .
OBJ_DIR = ./build

INSTALL_DIR = ~/.local/bin
INSTALL_COMMAND = install
EXECUTABLE_NAME = fiha

# Compiler flags
CFLAGS = -Wall -Wextra
OBJECTS = $(addprefix $(OBJ_DIR)/,binary.o main.o )

# Build recipe
$(EXECUTABLE_NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	cc -c -o $@ $^ $(CFLAGS)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
install: $(EXECUTABLE_NAME)
	$(INSTALL_COMMAND) $(EXECUTABLE_NAME) $(INSTALL_DIR)
uninstall:
	rm $(INSTALL_DIR)/$(EXECUTABLE_NAME)
clean: $(OBJ_DIR)
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
	rmdir $(OBJ_DIR)
