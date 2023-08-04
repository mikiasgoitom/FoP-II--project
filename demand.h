#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<cstdlib>
#include<iomanip>
#define FILENAME "db.txt"

using namespace std;
enum class Status { CheckedOut, CheckedIn };
struct Book1 {
  string title;
  string author;
  string genre;
  Status status;
  int pages;
  int borrowCount;
  int publishYear;
};
vector<Book1> bookss;
/*void print_book(const Book1 &book) {
  std::cout << book.title << ",";
  std::cout << book.author << ",";
  std::cout << book.genre << ",";
  std::cout << static_cast<int>(book.status) << ",";
  std::cout << book.pages << ",";
  std::cout << book.borrowCount << ",";
  std::cout << book.publishYear << std::endl;
}*/
vector<Book1> parseFile(ifstream &file) {
  //if (!file.is_open()) {
   // throw "Unable to open file";
  //}

  vector<Book1> books2;
  string line;
  while (getline(file, line)) {
    if (line[0] == '#' || line.empty()) {
      continue;
    }
    Book1 book;
    stringstream ss(line);
    string token;
    int index = 0;
    while (!ss.eof()) {
      getline(ss, token, ',');
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
    bookss.push_back(book);
  }}
  void demandAnalysis(vector<Book1>& books2) {
    sort(books2.begin(), books2.end(), [](const Book1& a, const Book1& b) {
        return a.borrowCount > b.borrowCount;
    });
    int ch;
    cout<<"1.The top 5 books that are in high demand."<<endl;
    cout<<"2.The top 10 books that are in high demand."<<endl;
    cout<<"3.The demand for all books in general."<<endl;
    cout<<"4.the top 5 books that are in low demand."<<endl;
    cout<<"please enter your choice.1,2 or 3"<<endl;
    cin>>ch;
    system("cls");
    switch(ch)
    {
  case 1:
      cout<<"\n\nThe top 5 books that are in high demand.\n\n";
    for(int i = 0; i < 5 && i < bookss.size(); i++) {
        cout<<i+1<<".  " << books2[i].title << " by " << books2[i].author <<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  case 2:
      cout<<"\n\nThe top 10 books that are in high demand.\n\n";
    for(int i = 0; i < 10 && i < bookss.size(); i++) {
        cout <<i+1<<".  "<<books2[i].title << " by " << books2[i].author <<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  case 3:
      cout<<"\n\nThe demand for all books in general.\n\n";
    for(int i = 0;i < bookss.size(); i++) {
        cout<<i+1<<".  " << books2[i].title << " by " << books2[i].author <<"   "<<endl;
    }
    break;
  case 4:
      cout<<"\n\n the top 5 books that are in low demand.\n\n";
    for(int i = bookss.size()-1;i > bookss.size()-6; i--) {
        cout<<100-i<<".  " << books2[i].title << " by " << books2[i].author<<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  default:
    cout<<"invalid choice";

}
  }
