# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 \
    -I "C:/Program Files/SDL3/include" \
    -I "C:/Installed/lua/include" \
	-I. \
	-I "C:/Installed"

# Linker flags
LDFLAGS = -L "C:/Program Files/SDL3/lib" -lSDL3 \
          -L "C:/Installed/lua/lib" -llua54

# Source and output
SRC = main.cpp src/draw.cpp
OUT = main.exe

# Build target
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean build files
clean:
	del /Q *.exe *.o 2>nul || true
