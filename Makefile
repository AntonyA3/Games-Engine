SHELL := powershell.exe
CC = g++
COMPILER_FLAGS = -Wall -g -MD
INCLUDE_PATHS = -I.
INCLUDE_PATHS += -I./src
INCLUDE_PATHS += -I./src/impl
INCLUDE_PATHS += -I./vendors/libcester-0.4/include
INCLUDE_PATHS += -I./vendors
INCLUDE_PATHS += -I./vendors/imgui
INCLUDE_PATHS += -I./vendors/imgui/backends
INCLUDE_PATHS += -I./vendors/libcester-0.4/include
# INCLUDE_PATHS += -I./vendors/catch2
INCLUDE_PATHS += -IC:\\msys64\\mingw64\\lib\\SDL2-2.24.1\\x86_64-w64-mingw32\\include\\SDL2
LINKER_FLAGS = -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 

IMPLEMENTATION_FILES = $(patsubst %.cpp,%.o,$(wildcard ./src/impl/*.cpp))
IMPLEMENTATION_FILES += $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
IMPLEMENTATION_FILES += ./vendors/imgui/backends/imgui_impl_opengl3.o 
IMPLEMENTATION_FILES += ./vendors/imgui/backends/imgui_impl_sdl.o

show :
	echo $(IMPLEMENTATION_FILES)

%.o: %.cpp %.hpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)
	$(CC) $(INCLUDE_PATHS) -MMD -c -o $@ $<

%.o: %.cpp %.h
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)
	$(CC) $(INCLUDE_PATHS) -MMD -c -o $@ $<

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)

%.x.exe: %.x.o $(IMPLEMENTATION_FILES)
	$(CC) $*.x.o $(IMPLEMENTATION_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@ -DSHADER_FILE_PATH=\"./data/shaders/\" -DTEST_DATA_DIRECTORY=\"./tests/data/\"

clean:
	powershell -ExecutionPolicy Bypass -File .\src\clean.ps1

.RETAIN : $(IMPLEMENTATION_FILES) $(SRC_HEADER_FILES)

