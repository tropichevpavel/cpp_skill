CC = clang++
CFLAGS = -std=c++17
TARGET = ConsoleChatFile
SRC = $(wildcard ./src/*.cpp ./src/core/*.cpp ./src/entities/*.cpp ./src/UI/*.cpp ./src/UI/Pages/*.cpp)
BUILD = ./build

chat:
	[ -d $(BUILD) ] || mkdir $(BUILD)

	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET) -g $(SRC)
	cp ./src/templs/users.txt $(BUILD)
	cp ./src/templs/messages.txt $(BUILD)
	cp ./src/templs/start.sh $(BUILD)
	chmod +x $(BUILD)/start.sh

	rm -rf $(BUILD)/$(TARGET).dSYM
