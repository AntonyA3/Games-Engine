#include <iostream>
#include <string>
int main(int argc, char const *argv[])
{
    bool active = true;
    while (active)
    {
        std::string command;
        std::cin >> command;
        if(command == std::string("exit")){
            active = false;
        }
        //  Insert Custom Commands

    }
    return 0;
}
