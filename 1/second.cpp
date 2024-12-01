#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ifstream myfile{"input.txt"};

  if (!myfile) {
    std::cerr << "File could not be opened";
    return 1;
  }

  std::vector<int> vec1;
  std::vector<int> vec2;
  int num1, num2;

  while (myfile >> num1 >> num2) {
    vec1.push_back(num1);
    vec2.push_back(num2);
  }

  int similarity = 0;
  for (int i = 0; i < vec1.size(); ++i) {
    similarity += vec1[i] * std::count(vec2.begin(), vec2.end(), vec1[i]);
  }

  std::cout << similarity << '\n';
  return 0;
}
