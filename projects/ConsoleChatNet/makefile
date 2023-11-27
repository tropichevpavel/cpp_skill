CC = clang++
CFLAGS = -std=c++17
TARGET = ConsoleChatNet
SRC_CLIENT = $(wildcard ./src/client/*.cpp ./src/client/core/*.cpp ./src/client/entities/*.cpp ./src/client/UI/*.cpp ./src/client/UI/Pages/*.cpp)
SRC_SERVER = $(wildcard ./src/server/*.cpp ./src/server/core/*.cpp ./src/server/SQLiteWrapper/*.cpp)
BUILD = ./build

client:
	[ -d $(BUILD) ] || mkdir $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET)_client -g $(SRC_CLIENT)
	rm -rf $(BUILD)/$(TARGET)_client.dSYM

server:
	[ -d $(BUILD) ] || mkdir $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET)_server -g $(SRC_SERVER) -lsqlite3
	rm -rf $(BUILD)/$(TARGET)_server.dSYM
