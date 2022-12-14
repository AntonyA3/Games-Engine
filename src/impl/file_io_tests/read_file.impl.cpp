#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <breakout_engine.hpp>

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
