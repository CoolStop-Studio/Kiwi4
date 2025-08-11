# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 \
	-I "C:/Installed/SDL3/include" \
	-I "C:/Installed/SDL3_image/include" \
	-I "C:/Installed/SDL3_ttf/include" \
    -I "C:/Installed/lua/include" \
	-I. \
	-I "C:/Installed"

# Linker flags
LDFLAGS = -L "C:/Installed/SDL3/lib" -lSDL3 \
	-L "C:/Installed/SDL3_image/lib" -lSDL3_image \
	-L "C:/Installed/SDL3_ttf/lib" -lSDL3_ttf \
    -L "C:/Installed/lua/lib" -llua54

# Source and output
SRC = main.cpp src/draw.cpp src/input.cpp src/utils.cpp src/load.cpp src/globals.cpp
OUT = main.exe

# Build target
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean build files
clean:
	del /Q *.exe *.o 2>nul || true
