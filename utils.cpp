#include <algorithm>
#include <iostream>
#include "main.h"

using namespace std;

void remove_trailing_whitespace(string &str) {

  // Remove leading whitespace
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(),
                         [](unsigned char ch) { return !std::isspace(ch); }));

  // Remove trailing whitespace
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            str.end());
}

void print_book(const Book &book) {
  std::cout << book.title << ",";
  std::cout << book.author << ",";
  std::cout << book.genre << ",";
  std::cout << static_cast<int>(book.status) << ",";
  std::cout << book.pages << ",";
  std::cout << book.borrowCount << ",";
  std::cout << book.publishYear << std::endl;
}
