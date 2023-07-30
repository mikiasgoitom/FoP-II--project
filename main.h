#include <string>
#include <vector>
using namespace std;

#define FILENAME "db.txt"

enum class Status { CheckedOut, CheckedIn };

struct Book {
  string title;
  string author;
  string genre;
  Status status;
  int pages;
  int borrowCount;
  int publishYear;
};

// database ops
void saveFile(ofstream &file, const vector<Book> &books);
vector<Book> parseFile(ifstream &file);

// utils
void remove_trailing_whitespace(string &str);
void print_book(const Book &book);
