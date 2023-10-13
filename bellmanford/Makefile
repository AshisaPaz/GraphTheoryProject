# Compiler settings
CXX := g++ # Change to your desired compiler
CXXFLAGS := -std=c++11 -Wall -Wextra

# Source file and output filenames
SRC := bellmanford.cpp
EXE := bellmanford.exe
BIN := bellmanford.bin

# Detect the operating system
ifeq ($(OS),Windows_NT)
	# Windows settings
	RM := del /Q
	EXE := bellmanford.exe
else
	# Linux settings
	RM := rm -f
	EXE := bellmanford.bin
endif

all: $(EXE) $(BIN)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(EXE) $(BIN)