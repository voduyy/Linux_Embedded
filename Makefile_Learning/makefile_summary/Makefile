CC := gcc
.PRECIOUS: $(OBJ_DIR)/%.o

.PHONY: clean all

EXTRA_CFLAGS := -Wall
CUR_DIR := $(shell pwd)
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
BIN_DIR := $(CUR_DIR)/bin

INC_FILES := $(foreach LIB_DIR, $(LIB_DIR),$(wildcard $(LIB_DIR)/*))
SRC_FILES := $(foreach SRC_DIR,$(SRC_DIR),$(wildcard $(SRC_DIR)/*.c))

OBJ_FILES := $(subst .c,.o, $(notdir $(SRC_FILES)))	
BIN_FILES := $(subst .o,.exe, $(OBJ_FILES))

.PRECIOUS: $(OBJ_DIR)/%.o

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.exe $(BIN_DIR)

all: $(BIN_FILES)
	@for exe_files in $(BIN_FILES); do \
		$(BIN_DIR)/$$exe_files;  done \

%.exe: $(OBJ_DIR)/%.o	
	$(CC) $< -o $(BIN_DIR)/$@
	chmod 777 $(BIN_DIR)/$@


$(OBJ_DIR)/%.o: %.c $(INC_FILES)
	$(CC) -I $(LIB_DIR) -c $< -o $@


clean:
	@if [ -n "$$(find $(OBJ_DIR) -name '*.o' -print -quit)" ]; then \
		rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*; \
		echo "Cleaned up object and executable files."; \
	else \
		echo "No object files found to clean."; \
	fi
