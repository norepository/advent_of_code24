#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::string CleanString(std::string s) {
  std::regex doo(R"(do\(\))");
  std::regex dont(R"(don't\(\))");
  bool clean = false;
  std::smatch match;
  std::string clean_s;
  while (!clean) {
    if (std::regex_search(s, match, dont)) {
      clean_s.append(match.prefix());
      std::string f = match.suffix();
      if (std::regex_search(f, match, doo)) {
        s = match.suffix();
      }
    } else {
      clean = true;
    }
  }
  return clean_s;
}
int main() {
  std::ifstream myfile("test.txt");
  std::string l;
  int total = 0;

  while (std::getline(myfile, l)) {
    std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    bool suffix = true;
    std::smatch match;
    l = CleanString(l);
    while (suffix) {
      if (std::regex_search(l, match, mul_pattern)) {
        total += std::stoi(match[1]) * std::stoi(match[2]);
        l = match.suffix();
      } else {
        suffix = false;
      }
    }
  }
  std::cout << "total: " << total << '\n';
  return 0;
}
