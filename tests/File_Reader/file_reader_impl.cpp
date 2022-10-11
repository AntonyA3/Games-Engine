#include <io/file_reader.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{

    FileReader file_reader;
    file_reader.m_filename = "hello_world.txt";
    file_reader.read();

    std::cout << file_reader.m_content << std::endl;
    
    return 0;
}
