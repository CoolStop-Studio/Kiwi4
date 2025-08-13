# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 \
	-I "C:/Installed/SDL3/include" \
    -I "C:/Installed/lua/include" \
	-I. \
	-I "C:/Installed"

LDFLAGS = \
    "C:/Installed/SDL3/lib/SDL3.lib" \
    "C:/Installed/SDL3/lib/SDL3_image.lib" \
    "C:/Installed/SDL3/lib/SDL3_ttf.lib" \
    "C:/Installed/lua/lib/lua54.lib" \
    -lopengl32 -lwinmm -ldsound -ldxguid -luser32 -lkernel32

# Source and output
SRC = main.cpp src/draw.cpp src/input.cpp src/utils.cpp src/load.cpp src/globals.cpp
OUT = main.exe

# Build target
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean build files
clean:
	del /Q *.exe *.o 2>nul || true
