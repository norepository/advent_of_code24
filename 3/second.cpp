#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::string CleanString(std::string &s) {
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
      } else {
        clean = true;
        clean_s.append(f);
      }
    } else {
      clean = true;
      clean_s.append(s);
    }
  }
  return clean_s;
}

std::string takeInput() {
  std::ifstream file("input.txt");
  std::istream_iterator<char> input(file);
  std::istream_iterator<char> input_end;
  std::string text;
  auto inserter = std::back_inserter(text);
  std::copy(input, input_end, inserter);
  return text;
}

int main() {
  std::string input = takeInput();
  input = CleanString(input);
  int total = 0;
  std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  bool suffix = true;
  std::smatch match;
  while (suffix) {
    if (std::regex_search(input, match, mul_pattern)) {
      total += std::stoi(match[1]) * std::stoi(match[2]);
      input = match.suffix();
    } else {
      suffix = false;
    }
  }
  std::cout << "total: " << total << '\n';
  return 0;
}
