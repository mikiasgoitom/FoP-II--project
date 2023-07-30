#include "main.h"
#include <fstream>
#include <sstream>

void saveFile(ofstream &file, const vector<Book> &books) {
  if (!file.is_open()) {
    throw "Unable to open file";
  }

  for (const Book &book : books) {
    file << book.title << ",";
    file << book.author << ",";
    file << book.genre << ",";
    file << static_cast<int>(book.status) << ",";
    file << book.pages << ",";
    file << book.borrowCount << ",";
    file << book.publishYear << endl;
  }
}

vector<Book> parseFile(ifstream &file) {
  if (!file.is_open()) {
    throw "Unable to open file";
  }

  vector<Book> books;
  string line;
  while (getline(file, line)) {
    if (line[0] == '#' || line.empty()) {
      continue;
    }
    Book book;
    stringstream ss(line);
    string token;
    int index = 0;
    while (!ss.eof()) {
      getline(ss, token, ',');
      remove_trailing_whitespace(token);
      if (index == 0) {
        book.title = token;
      } else if (index == 1) {
        book.author = token;
      } else if (index == 2) {
        book.genre = token;
      } else if (index == 3) {
        if (token == "CheckedIn") {
          book.status = Status::CheckedIn;
        } else if (token == "CheckedOut") {
          book.status = Status::CheckedOut;
        }
      } else if (index == 4) {
        book.pages = stoi(token);
      } else if (index == 5) {
        book.borrowCount = stoi(token);
      } else if (index == 6) {
        book.publishYear = stoi(token);
      }
      index++;
    }
    books.push_back(book);
  }

  return books;
}
