#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Pages = std::set<std::pair<int, int>>;
using Updates = std::vector<std::vector<int>>;

bool contain(const std::vector<int> &vec, const std::pair<int, int> &p) {
  bool first = false, second = false;
  for (const auto &v : vec) {
    if (v == p.first)
      first = true;
    if (v == p.second)
      second = true;
  }
  return first && second;
}

bool isBefore(const std::vector<int> &vec, const std::pair<int, int> &p) {
  int i_first, i_second;
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i] == p.first)
      i_first = i;
    if (vec[i] == p.second)
      i_second = i;
  }
  return i_first < i_second;
}
int getIndex(const std::vector<int> &v, const int &n) {
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == n)
      return i;
  }
  return -1;
}
void isCorrectOrder(std::vector<int> &vec, Pages &pages, bool &check) {
  for (auto p : pages) {
    if (contain(vec, p)) {
      if (!isBefore(vec, p)) {
        vec.erase(vec.begin() + getIndex(vec, p.first));
        vec.insert(vec.begin() + getIndex(vec, p.second), p.first);
        check = true;
      }
    }
  }
}
void printVector(std::vector<int> &V) {
  for (auto v : V) {
    std::cout << v << ',';
  }
  std::cout << '\n';
}
int main() {
  std::ifstream myfile("input.txt");
  std::string l;
  int total = 0;
  Updates u;
  Pages p;
  while (std::getline(myfile, l)) {
    if (l.find('|') != std::string::npos) {
      std::istringstream ss(l);
      int n1, n2;
      char delimiter;
      ss >> n1 >> delimiter >> n2;
      p.insert({n1, n2});
    }
    if (l.find(',') != std::string::npos) {
      std::vector<int> numbers;
      std::stringstream ss(l);
      std::string temp;

      while (std::getline(ss, temp, ',')) {
        numbers.push_back(std::stoi(temp));
      }
      u.push_back(numbers);
    }
  }
  for (auto const &update : u) {
    std::vector<int> ordered = update;
    bool edit = false;
    isCorrectOrder(ordered, p, edit);
    if (edit)
      total += ordered[ordered.size() / 2];
  }
  std::cout << "Total: " << total << '\n';
  return 0;
}