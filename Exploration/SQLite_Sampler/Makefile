CC = g++
COMPILER_FLAGS = -w 
LINKER_FLAGS =  -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 -lsqlite3
EXECUTABLE_NAME = sql_lite_sampler.exe
OBJECT_FILES = sql_lite_sampler.cpp

all :
	$(CC) $(OBJECT_FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE_NAME)
	