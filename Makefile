# Compiler and flags
CC = g++
CFLAGS = -std=c++17 -Wall -IC:/raylib/raylib/src
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

# Paths
SRC = src
BUILD = build

# Files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCES))
EXECUTABLE = viney.exe

# Rules
all: $(BUILD) $(EXECUTABLE)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(BUILD) $(EXECUTABLE)
