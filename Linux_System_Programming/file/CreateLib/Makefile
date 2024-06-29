.PHONY: obj clean
PROJECT := hello
CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib

STATIC_DIR := $(LIB_DIR)/static
SHARED_DIR := $(LIB_DIR)/shared
	 
INC_FLAG := -I $(INC_DIR)

CC := gcc
obj:
	$(CC) -c -o $(OBJ_DIR)/main.o main.c $(INC_FLAG)
	$(CC) -c -o $(OBJ_DIR)/hello.o $(SRC_DIR)/hello.c $(INC_FLAG)
	$(CC) -c -o $(OBJ_DIR)/hi.o $(SRC_DIR)/hi.c $(INC_FLAG)
clean:
	rm -rf $(OBJ_DIR)/* \
	$(STATIC_DIR)/libhello.a \
	$(BIN_DIR)/$(PROJECT)
mkstatic: obj
	ar rcs $(STATIC_DIR)/libhello.a $(OBJ_DIR)/hello.o $(OBJ_DIR)/hi.o
all: mkstatic
	$(CC) $(OBJ_DIR)/main.o -L$(STATIC_DIR) -lhello -o $(BIN_DIR)/$(PROJECT)
obj_shared:
	$(CC) -c -fPIC -o $(OBJ_DIR)/main.o main.c $(INC_FLAG)
	$(CC) -c -fPIC -o $(OBJ_DIR)/hello.o $(SRC_DIR)/hello.c $(INC_FLAG)
	$(CC) -c -fPIC -o $(OBJ_DIR)/hi.o $(SRC_DIR)/hi.c $(INC_FLAG)
mkshared: obj_shared
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/hi.o -o $(SHARED_DIR)/libhello.so
all_shared: mkshared
	$(CC) $(OBJ_DIR)/main.o -L$(SHARED_DIR) -lhello -o $(BIN_DIR)/$(PROJECT)
