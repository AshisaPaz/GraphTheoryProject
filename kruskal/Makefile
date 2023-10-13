# Compiler settings
CXX := g++ # Change to your desired compiler
CXXFLAGS := -std=c++11 -Wall -Wextra

# Source file and output filenames
SRC := kruskal.cpp
EXE := kruskal.exe
BIN := kruskal.bin

# Detect the operating system
ifeq ($(OS),Windows_NT)
	# Windows settings
	RM := del /Q
	EXE := kruskal.exe
else
	# Linux settings
	RM := rm -f
	EXE := kruskal.bin
endif

all: $(EXE) $(BIN)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(EXE) $(BIN)