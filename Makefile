
CC = g++
COMPILER_FLAGS = -w 
INCLUDE_PATHS =-I. -I./include -I./vendors/libcester-0.4/include
LINKER_FLAGS =  -lSDL2main -lSDL2 -lglu32 -lopengl32 -lglew32 
OBJECT_FILES = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp)) 


./src/%.o: ./src/%.cpp
	$(CC) -c $< -o $@ $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS)


%.test.exe: $(OBJECT_FILES)
	$(CC) $*.test.cpp $(OBJECT_FILES) $(INCLUDE_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $@

