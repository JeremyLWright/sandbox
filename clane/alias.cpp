#include <iostream>


using myDouble = double;

auto fn(myDouble) -> void
{
    std::cout << "myDouble" << std::endl;
}

auto fn(double) -> void
{
    std::cout << "double" << std::endl; 
}


int main(int argc, const char *argv[])
{
    fn(2.4l);
    myDouble d = 3.4;
    fn(d);
    return 0;
}
