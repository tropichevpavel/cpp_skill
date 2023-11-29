CC = clang++
CFLAGS = -std=c++17
TARGET = ConsoleChatNet
SRC_CLIENT = $(wildcard ./src/client/*.cpp ./src/client/core/*.cpp ./src/client/entities/*.cpp ./src/client/UI/*.cpp ./src/client/UI/Pages/*.cpp)
SRC_SERVER = $(wildcard ./src/server/*.cpp ./src/server/core/*.cpp ./src/server/SQLiteWrapper/*.cpp)
SRC_SERVER_LOGGER = $(wildcard ./src/server_logger/*.cpp ./src/server_logger/core/*.cpp ./src/server_logger/SQLiteWrapper/*.cpp)
BUILD = ./build

client:
	[ -d $(BUILD) ] || mkdir $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET)_client -g $(SRC_CLIENT)
	rm -rf $(BUILD)/$(TARGET)_client.dSYM

server:
	[ -d $(BUILD) ] || mkdir $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/server -g $(SRC_SERVER) -lsqlite3
	rm -rf $(BUILD)/server.dSYM

server_logger:
	[ -d $(BUILD) ] || mkdir $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/server_logger -g $(SRC_SERVER_LOGGER) -lsqlite3
	rm -rf $(BUILD)/server_logger.dSYM
