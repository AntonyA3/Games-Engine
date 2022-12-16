SHELL := powershell.exe
CC = g++
COMPILER_FLAGS = -Wall -g -MD
INCLUDE_PATHS = -I.
INCLUDE_PATHS += -I./src
INCLUDE_PATHS += -I./vendors/libcester-0.4/include
INCLUDE_PATHS += -I./vendors
INCLUDE_PATHS += -I./vendors/imgui
INCLUDE_PATHS += -I./vendors/imgui/backends
INCLUDE_PATHS += -I./vendors/libcester-0.4/include
INCLUDE_PATHS += -I./vendors/catch2
INCLUDE_PATHS += -IC:\\msys64\\mingw64\\lib\\SDL2-2.24.1\\x86_64-w64-mingw32\\include\\SDL2
LINKER_FLAGS = -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 

SRC_OBJECT_FILES = ./src/breakout_engine.o

SRC_OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
SRC_OBJECT_FILES += ./vendors/imgui/backends/imgui_impl_opengl3.o 
SRC_OBJECT_FILES += ./vendors/imgui/backends/imgui_impl_sdl.o

SRC_HEADER_FILES = $(patsubst %.hpp,%.hpp,$(wildcard src/*.hpp))
SRC_HEADER_FILES += $(patsubst %.hpp,%.hpp,$(wildcard ./vendors/imgui/*.hpp))


%.o: %.cpp %.hpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)
	$(CC) $(INCLUDE_PATHS) -MMD -c -o $@ $<

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)


%.test.exe: %.test.o $(SRC_OBJECT_FILES)
	$(CC) $*.test.o $(TEST_OBJECT_FILES) $(SRC_OBJECT_FILES)  $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@ -D__BASE_FILE__=$*.test.cpp


%.impl.exe: %.impl.o $(SRC_OBJECT_FILES)
	$(CC) $*.impl.o $(SRC_OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@ -DSHADER_FILE_PATH=\"./data/shaders/\" -DTEST_DATA_DIRECTORY=\"./tests/data/\"

clean:
	powershell -ExecutionPolicy Bypass -File .\src\clean.ps1

.RETAIN : $(SRC_OBJECT_FILES) $(TEST_OBJECT_FILES) $(SRC_HEADER_FILES)

