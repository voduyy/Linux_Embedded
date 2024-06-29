
CLIENT_FILE := client
SERVER_FILE := server
PORT := 8983
IP_ADDR := 192.168.236.129
CUR_DIR := .
LIB_DIR := $(CUR_DIR)/lib
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
TEXT_DIR := $(CUR_DIR)/text
CC := gcc
INC_FLAG := -I $(LIB_DIR)
build_object: 
	$(CC) -o $(OBJ_DIR)/client $(SRC_DIR)/socket_client.c -pthread $(INC_FLAG)
	$(CC) -o $(OBJ_DIR)/server $(SRC_DIR)/socket_server.c -pthread $(INC_FLAG)
clean:
	rm -rf $(OBJ_DIR)/*
run_client: 
	$(OBJ_DIR)/$(CLIENT_FILE) $(IP_ADDR) $(PORT)
run_server:
	$(OBJ_DIR)/$(SERVER_FILE) $(PORT)
