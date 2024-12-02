#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

bool isValidSequence(const std::vector<int> &nums) {
  bool incr = true, decr = true;
  for (size_t i = 1; i < nums.size(); ++i) {
    if (nums[i] == nums[i - 1]) {
      incr = decr = false;
      break;
    }
    if (nums[i] < nums[i - 1]) {
      incr = false;
      if (nums[i - 1] > nums[i] + 3)
        return false;
    } else {
      decr = false;
      if (nums[i] > nums[i - 1] + 3)
        return false;
    }
  }
  return incr || decr;
}

int main() {
  std::ifstream myfile("input.txt");
  std::string line;
  int total = 0;
  while (std::getline(myfile, line)) {
    std::istringstream iss(line);
    std::vector<int> nums{std::istream_iterator<int>(iss),
                          std::istream_iterator<int>()};

    if (isValidSequence(nums)) {
      ++total;
      continue;
    }

    for (size_t j = 0; j < nums.size(); ++j) {
      std::vector<int> modifiedNums = nums;
      modifiedNums.erase(modifiedNums.begin() + j);

      if (isValidSequence(modifiedNums)) {
        ++total;
        break;
      }
    }
  }
  std::cout << "total: " << total << '\n';
  return 0;
}
