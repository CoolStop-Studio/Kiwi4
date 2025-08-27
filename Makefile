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
SRC = main.cpp src/draw.cpp src/input.cpp src/utils.cpp src/load.cpp src/globals.cpp src/color.cpp src/files.cpp
RES = resources.res
OUT = main.exe

# Build target
$(OUT): $(SRC) $(RES)
	$(CXX) $(CXXFLAGS) $(SRC) $(RES) -o $(OUT) $(LDFLAGS)

# Compile resources
$(RES): resources.rc
	windres resources.rc -O coff -o $(RES)

# Clean build files
clean:
	del /Q *.exe *.o *.res 2>nul || true
