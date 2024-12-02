#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
int main() {
  std::ifstream myfile("input.txt");
  std::string line;
  int total = 0;

  while (std::getline(myfile, line)) {
    std::istringstream iss(line);
    std::vector<int> nums{std::istream_iterator<int>(iss),
                          std::istream_iterator<int>()};

    bool incr = true, decr = true;
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1]) {
        incr = decr = false;
        break;
      }
      if (nums[i] < nums[i - 1]) {
        incr = false;
        decr &= (nums[i - 1] <= nums[i] + 3);
      } else {
        decr = false;
        incr &= (nums[i] <= nums[i - 1] + 3);
      }
    }

    if (incr || decr)
      ++total;
  }

  std::cout << "total: " << total << '\n';
  return 0;
}

