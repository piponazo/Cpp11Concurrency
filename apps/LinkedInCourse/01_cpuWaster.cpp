#include <format>
#include <iostream>
#include <thread>

#include <Windows.h>

void cpuWaster() {
  std::cout << std::format("CPU Waster process ID: {}", GetCurrentProcessId()) << std::endl;
  std::cout << "CPU Waster thread ID: " << std::this_thread::get_id() << std::endl;
  while (true)
    continue;
}

int main() {
  std::cout << std::format("Main process ID: {}", GetCurrentProcessId()) << std::endl;
  std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
  std::thread thread1(cpuWaster);
  std::thread thread2(cpuWaster);

  while(true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return EXIT_SUCCESS;
}
