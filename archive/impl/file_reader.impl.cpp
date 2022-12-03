#include <loader/file_reader.hpp>

int main(int argc, char const *argv[])
{
    FileReader file_reader;

    
    std::string filename;
    std::cout << "Enter a filename\n";
    std::cin >> filename;

    file_reader.read(filename);

    if(file_reader.failed()){
        std::cout << "OOPS: This file failed to be read \n";
    }else if(file_reader.success()){
        std::cout << file_reader.getContent() << "\n";
        std::cout << "Successful file read <<<<<<\n\n";

    }else{
        std::cout << "Something When Wrong\n";
    }
    std::cout << "END" << std::endl;
    return 0;
}
