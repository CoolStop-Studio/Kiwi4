# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 \
    -I "C:/Program Files/SDL3/include"

# Linker flags
LDFLAGS = -L "C:/Program Files/SDL3/lib" -lSDL3

# Source and output
SRC = main.cpp
OUT = main.exe

# Build target
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean build files
clean:
	del /Q *.exe *.o 2>nul || true