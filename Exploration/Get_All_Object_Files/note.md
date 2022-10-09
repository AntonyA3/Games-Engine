
$(patsubst ../vendors/imgui/%.cpp,%.o,$(wildcard ../vendors/imgui/*.cpp))

$(patsubst ../vendors/imgui/%.cpp,%.o,$(wildcard ../vendors/imgui/*.cpp)) 

imgui_impl_sdl.o  imgui_impl_opengl3.o



$(subst ee,EE,feet on the street)
produces the value ‘fEEt on the strEEt’. 




$(patsubst %.c, %.o, x.c.c bar.c)
In the string: x.c.c bar.c
Find anything matching %.c where % is any number of letters in the filename
Replace anything matching %.c with %.o

Therefore in the string "x.c.c bar.c"
I am able to find "x.c.c" based on this pattern %.c
I replace "x.c.c" with "x.c.o" based on this patter %.o

produces the value ‘x.c.o bar.o’. 

What I want to do is when I am given a cpp file, I want to create it's object file

Therefore
$(patsubst find: %.cpp, replaceWith: %.o, inText: "source_file.cpp")
$(patsubst %.cpp, %.o, "source_file.cpp")
also to get any cpp file with a wildcard
$(patsubst %.cpp,%.o,$(wildcard *.cpp)) 
