#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::ifstream myfile("input.txt");
  std::string l;
  int total = 0;

  while (std::getline(myfile, l)) {
    std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    bool suffix = true;
    std::smatch match;
    while (suffix) {
      if (std::regex_search(l, match, mul_pattern)) {
        total += std::stoi(match[1]) * std::stoi(match[2]);
        // total += std::stoi(match[1]) * std::stoi(match[2]);
        l = match.suffix();
      } else {
        suffix = false;
      }
    }
  }
  std::cout << "total: " << total << '\n';
  return 0;
}
