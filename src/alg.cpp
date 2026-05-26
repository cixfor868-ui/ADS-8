// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>
#include <string>
#include <filesystem>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(const BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> pairs = tree.getAllSortedByKey();

  std::sort(pairs.begin(), pairs.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second != b.second) {
        return a.second > b.second;
      }
      return a.first < b.first;
    });

  for (const auto& p : pairs) {
    std::cout << p.first << " : " << p.second << "\n";
  }

  std::filesystem::create_directories("result");

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
    return;
  }

  for (const auto& p : pairs) {
    out << p.first << " : " << p.second << "\n";
  }

  out.close();
}
