#include <iostream>
#include <thread>

void functionThread();

int main()
{
        std::thread threadFunction(functionThread);
        threadFunction.join();
        return EXIT_SUCCESS;
}


void functionThread()
{
        std::cout << "This is a simple function called with a thread" << std::endl;
}
