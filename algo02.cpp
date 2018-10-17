#include <iostream>
#include <map>
#include <list>
#include <functional>

void selection_sort(std::list<int> const&) {

}

void insertion_sort(std::list<int> const&) {

}

void merge_sort(std::list<int> const&) {

}

const std::map<std::string, std::function<void(std::list<int> const&)>> algorithms {
  {"selection", selection_sort},
  {"insertion", insertion_sort},
  {"merge", merge_sort}
};

void print_avaliable_algos() {
  std::cout << "\n  Available algorithms:" << std::endl;
  for(const auto& algo : algorithms) {
    std::cout << "  - " << algo.first << std::endl;
  }
}

void print_list(const std::list<int>& list) {
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
  
  std::list<int> inputs;
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