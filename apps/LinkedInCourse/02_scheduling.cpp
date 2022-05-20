#include <format>
#include <iostream>
#include <string>
#include <thread>

bool chopping{true};

void vegetableChopper(std::string_view name) {
  unsigned int vegetableCount {0};
  while (chopping) {
    vegetableCount++;
  }
  std::cout << std::format("{} chopped {} vegatables.\n", name, vegetableCount);
}

int main() {
  std::thread olivia(vegetableChopper, "Olivia");
  std::thread barron(vegetableChopper, "Barron");

  std::cout << "Barron and Olivia are chopping vegetables...\n";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  chopping = false;

  olivia.join();
  barron.join();

  return EXIT_SUCCESS;
}
