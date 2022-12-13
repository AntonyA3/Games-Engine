#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
std::string readFile(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    bool open = my_read_file.is_open();
    assert(open);
    if(open){
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer;
            if(!my_read_file.eof()){
                ss << "\n";
            }
        }  
        my_read_file.close();
    }
    return ss.str();
} 

int main(int argc, char const *argv[])
{
    std::string command;
    std::string file_content;
    while(true){

        std::cout << "============" << std::endl;
        std::cout << "type \"exit\" to quit" << std::endl; 
        std::cout << "type filename to read" << std::endl; 
        std::cout << "============" << std::endl;

        std::cin >> command;
        if(command == "exit"){
            break;
        }
        file_content = readFile(command);

        // Otherwise print the file content
        std::cout << "============" << std::endl;
        std::cout << "file Content" << std::endl;
        std::cout << "============" << std::endl;
        std::cout << file_content << std::endl;
        
        std::cout << "============" << std::endl;




    }
    return 0;
}
