#include <iostream>
#include <thread>

using namespace std;

void functionThread();

class backgroundTask {
public:
    void operator()() const {
        cout << "I'm the operator () of backgroundTask\n";
    }
};

int main()
{
        backgroundTask task1;

        thread threadFunction(functionThread);
        thread threadClass1(task1);
        thread threadClass2((backgroundTask()));
        thread threadClass3{backgroundTask()};
        thread threadLambda1([]{ cout << "I'm a lambda\n"; });

        threadFunction.join();
        threadClass1.join();
        threadClass2.join();
        threadClass3.join();
        threadLambda1.join();
        return EXIT_SUCCESS;
}


void functionThread()
{
        cout << "This is a simple function called with a thread" << endl;
}
