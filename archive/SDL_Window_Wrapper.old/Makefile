CC = g++
COMPILER_FLAGS = -w 
INCLUDE_PATHS = -I../../include -I../../vendors/imgui -I../../vendors/imgui/backends -I../../vendors/
LINKER_FLAGS =  -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 
NAME = sdl_window_wrapper_impl

OBJECT_FILES = $(patsubst %.cpp,%.o,$(wildcard ../../src/*.cpp))  
OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard ../../src/io/*.cpp)) 
OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard ../../src/loader/*.cpp)) 
OBJECT_FILES += $(patsubst %.cpp,%.o,$(wildcard ../../vendors/imgui/*.cpp))
OBJECT_FILES += ../../vendors/imgui/backends/imgui_impl_opengl3.o ../../vendors/imgui/backends/imgui_impl_sdl.o
OBJECT_FILES += $(NAME).o 
%.o : %.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)
	
all: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $(NAME).exe 

