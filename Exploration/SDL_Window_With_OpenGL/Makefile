CC = g++
COMPILER_FLAGS = -w 
LINKER_FLAGS =  -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 
EXECUTABLE_NAME = sdl_window_w_opengl.exe
OBJECT_FILES = sdl_window_w_opengl.cpp $(patsubst %.cpp,%.o,$(wildcard ../../src/*.cpp)) 
INCLUDE_PATHS = -I../../include
all :
	$(CC) $(OBJECT_FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE_NAME)
	