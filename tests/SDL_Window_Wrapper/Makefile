CC = g++
COMPILER_FLAGS = -w 
INCLUDE_PATHS = -I../../include
LINKER_FLAGS =  -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 
NAME = sdl_window_wrapper_impl

OBJECT_FILES = $(patsubst %.cpp,%.o,$(wildcard ../../src/*.cpp)) $(NAME).o

%.o : %.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)
	
all: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $(NAME).exe 
	