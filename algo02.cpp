#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <utility>

void selection_sort(std::vector<int>& list) {
  for(size_t i = 0; i < list.size(); i++) {
    // find min element in range [i,size)
    size_t pos = i;
    int val = __INT_MAX__;
    for(size_t j = i; j < list.size(); j++) {
      if(list[j] < val) {
        val = list[j];
        pos = j;
      }
    }
    std::swap(list[i], list[pos]);
  }
}

void bubble_sort(std::vector<int>& list) {
  if(list.size() < 2) {
    return;
  }
  for(size_t i = 0; i < (list.size() - 1); i++) {
    for(size_t j = 0; j < (list.size() - 1); j++) {
      if(list[j] > list[j + 1]) {
        std::swap(list[j], list[j + 1]);
      }
    }
  }
}

void insertion_sort(std::vector<int>& list) {

}

void merge_sort(std::vector<int>& list) {

}

const std::map<std::string, std::function<void(std::vector<int>&)>> algorithms {
  {"selection", selection_sort},
  {"insertion", insertion_sort},
  {"merge", merge_sort},
  {"bubble", bubble_sort}
};

void print_avaliable_algos() {
  std::cout << "\n  Available algorithms:" << std::endl;
  for(const auto& algo : algorithms) {
    std::cout << "  - " << algo.first << std::endl;
  }
}

void print_list(const std::vector<int>& list) {
  for(int i : list) {
    std::cout << i << " ";
  }

  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cout << "Usage: algo02 <algorithm> [<number 1> [<number 2> [...]]]" << std::endl;
    print_avaliable_algos();
    return 2;
  }

  try {
    algorithms.at(argv[1]);
  } catch(const std::out_of_range& e) {
    std::cerr << "Algorithm \"" << argv[1] << "\" not found" << std::endl;
    print_avaliable_algos();
    return 2;
  }
  
  std::vector<int> inputs;
  for(size_t i = 2; i < argc; i++) {
    try {
      inputs.push_back(std::stoi(argv[i]));
    } catch(const std::exception& e) {
      std::cerr << "invalid argument \"" << argv[i] << "\": unable to convert to integer" << std::endl;
      return 3;
    }
  }

  algorithms.at(argv[1])(inputs);

  print_list(inputs);

  return 0;
}