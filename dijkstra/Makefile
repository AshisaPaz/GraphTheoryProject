# Compiler settings
CXX := g++ # Change to your desired compiler
CXXFLAGS := -std=c++11 -Wall -Wextra

# Source file and output filenames
SRC := dijkstra.cpp
EXE := dijkstra.exe
BIN := dijkstra.bin

# Detect the operating system
ifeq ($(OS),Windows_NT)
	# Windows settings
	RM := del /Q
	EXE := dijkstra.exe
else
	# Linux settings
	RM := rm -f
	EXE := dijkstra.bin
endif

all: $(EXE) $(BIN)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(EXE) $(BIN)