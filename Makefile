
CC = g++
COMPILER_FLAGS = -w
INCLUDE_PATHS = -I.
INCLUDE_PATHS += -I./include
INCLUDE_PATHS += -I./vendors/libcester-0.4/include
INCLUDE_PATHS += -I./vendors
INCLUDE_PATHS += -I./vendors/imgui
INCLUDE_PATHS += -I./vendors/imgui/backends

LINKER_FLAGS = -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 

SRC_OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRC_OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard src/loader/*.cpp))
SRC_OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard ./vendors/imgui/*.cpp))
SRC_OBJECT_FILES += ./vendors/imgui/backends/imgui_impl_opengl3.o 
SRC_OBJECT_FILES += ./vendors/imgui/backends/imgui_impl_sdl.o

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)

%.test.exe: %.test.o $(SRC_OBJECT_FILES)
	$(CC) $*.test.o $(SRC_OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@ -D__BASE_FILE__=$*.test.cpp


%.impl.exe: %.impl.o $(SRC_OBJECT_FILES)
	$(CC) $*.impl.o $(SRC_OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@ -DSHADER_FILE_PATH=\"./data/shaders/\" -DTEST_DATA_DIRECTORY=\"./tests/data/\"
