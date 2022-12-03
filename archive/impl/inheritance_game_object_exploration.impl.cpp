#include <iostream>


struct ServiceClass{

    void printHello(){
        std::cout << "print hello world" << std::endl;
    }
};  


// Common object functions must be implemented
class ICommonObject
{
// A protected constructor will make it act like an abstract class
protected:
    ICommonObject(){}
    template<typename TService>
    // Don't write an implementation for this function to make sure all
    // sub-types have an implementation
    void useService(TService& service){}
    // There is no need to have a not yet implemented default function
    
    // void useService(TService& service){
    //     // service.printHello();
    //     std::cout << "Not implemented" << std::endl;
    //     exit(1);
        
    // }


    void update(float dt){}

};

struct CoolObject : ICommonObject{
    void normalExecution(){
        std::cout << "normal execution" << std::endl;
    }
    // Syntax error if userService has not been implemented regardless of inheritance
    template<typename TService>
    void useService(TService& service){
       
        std::cout << "Service has beenm implemented" << std::endl;
        exit(1);
        
    }
    void update(float dt);
};


void CoolObject::update(float dt){
    std::cout << "update cool obkect" << dt << std::endl;
}


int main(int argc, char const *argv[])
{
    ServiceClass service;
    CoolObject co;
    co.normalExecution();
    co.update(10.0f);
    co.useService<ServiceClass>(service);


    return 0;
}
