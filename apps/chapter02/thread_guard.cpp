#include <iostream>
#include <thread>

using namespace std;

class ThreadGuard {
 public:
  explicit ThreadGuard(thread& t) : _t(t) {
  }
  ~ThreadGuard() {
    if (_t.joinable()) {
      _t.join();
    }
  }

  ThreadGuard(const ThreadGuard&) = delete;
  ThreadGuard& operator=(const ThreadGuard&) = delete;

 private:
  thread& _t;
};

void functionThread(int& localVar) {
  cout << "Value of variable: " << localVar << endl;
}

int main() {
  int someLocalVar = 4;
  thread t{functionThread, std::ref(someLocalVar)};
  ThreadGuard g(t);
  return EXIT_SUCCESS;
}
