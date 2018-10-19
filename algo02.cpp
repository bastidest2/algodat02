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
  if(list.size() < 2) {
    return;
  }
  for(size_t i = 1; i < list.size(); i++) {
    for(size_t j = i; j > 0 && list[j] < list[j - 1]; j--) {
      std::swap(list[j], list[j + 1]);
    }
  }
}

std::vector<int> merge(const std::vector<int>& first, const std::vector<int>& second) {
  if(first.size() == 0) {
    return second;
  }
  if(second.size() == 0) {
    return first;
  }
  if(first[0] < second[0]) {
    std::vector<int> ret = merge(std::vector<int>{next(first.begin()), first.end()}, second);
    ret.insert(ret.begin(), first[0]);
    return ret;
  } else {
    std::vector<int> ret = merge(first, std::vector<int>{next(second.begin()), second.end()});
    ret.insert(ret.begin(), second[0]);
    return ret;
  }
}

const std::vector<int> merge_sort_impl(const std::vector<int>& list) {
  if(list.size() <= 1) {
    return list;
  } else {
    size_t splitPos = list.size() / 2;
    std::vector<int> first {list.begin(), list.begin() + splitPos};
    std::vector<int> second {list.begin() + splitPos, list.end()};
    return merge(merge_sort_impl(first), merge_sort_impl(second));
  }
}

void merge_sort(std::vector<int>& list) {
  list = std::move(merge_sort_impl(list));
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

bool is_list_sorted(const std::vector<int>& list) {
  if(list.size() < 2) {
    return true;
  }

  int last = list[0];

  for(int i : list) {
    if(last > i) {
      return false;
    }
    last = i;
  }

  return true;
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cout << "Usage: algo02 (test | <algorithm> [<number 1> [<number 2> [...]]])" << std::endl;
    print_avaliable_algos();
    return 2;
  }

  if(std::string{argv[1]} == std::string{"test"}) {
    std::vector<std::vector<int>> testCases {
      #include "./test_cases.raw"
    };
    for(const auto& algo : algorithms) {
      std::cout << "Testing sorting algorithm \"" << algo.first << "\"" << std::endl;
      for(size_t i = 0; i < testCases.size(); i++) {
        std::printf("  TC%02d\t", static_cast<int>(i));
        algo.second(testCases[i]);
        if(is_list_sorted(testCases[i])) {
          std::cout << "OK" << std::endl;
        } else {
          std::cout << "ERR" << std::endl;
        }
      }
    }
    return 0;
  }

  try {
    algorithms.at(argv[1]);
  } catch(const std::out_of_range& e) {
    std::cerr << "Algorithm \"" << argv[1] << "\" not found" << std::endl;
    print_avaliable_algos();
    return 2;
  }
  
  std::vector<int> inputs;
  for(size_t i = 2; i < static_cast<size_t>(argc); i++) {
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