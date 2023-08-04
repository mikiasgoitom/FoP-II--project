#include "library.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

const string FILENAME = "text files/books.txt";

struct Book {
  string title;
  string author;
  string ISBN;
  string publisher;
  int year;
  int quantity;
  string genre;
  int pages;
  string status;
  int borrowCount;
};
struct Staff {
  string name;
  string email;
  string password;
};

void saveFile(ofstream &file, const vector<Book> &books) {
  if (!file.is_open()) {
    throw "Unable to open file";
  }

  for (const Book &book : books) {
    file << book.title << ",";
    file << book.author << ",";
    file << book.genre << ",";
    file << book.status << ",";
    file << book.pages << ",";
    file << book.borrowCount << ",";
    file << book.year << endl;
  }
}

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
        book.ISBN = token;
      } else if (index == 4) {
        book.publisher = token;
      } else if (index == 5) {
        book.year = stoi(token);
      } else if (index == 6) {
        book.quantity = stoi(token);
      } else {
        // TODO: Handle other cases
      }
      index++;
    }
    books.push_back(book);
  }

  return books;
}

string toLowercase(string str) {
  for (char &c : str) {
    c = tolower(c);
  }
  return str;
}

int main() {
  int choice;
  displayMainMenu();
  cin >> choice;
  if (choice == 1) {
    displayStudentMenu();
    int choice2;
    cin >> choice2;
    switch (choice2) {
    case 1:
      searchBooks();
      break;
    case 2:
      reserveBook();
      break;
    case 3:
      checkAvailability();
      break;
    case 4:
      cout << "Exiting program. Goodbye!\n";
      break;
    }
  } else if (choice == 2) {
    displayStaffMenu();
    int choice3;
    cin >> choice3;
    switch (choice3) {

    case 1:
      addBook();
      break;
    case 2:
      removeBook();
      break;
    case 3:
      displayInventory();
      break;
    case 4:
      displayOutdatedBooks();
      break;
    case 5:
      analyzeDemand();
      break;
    case 6:
      addStaff();
      break;
    case 7:
      removeStaff();
      break;
    case 8:
      displayStaffList();
      break;
    case 9:
      searchStaff();
      break;
    case 10:
      cout << "Exiting program. Goodbye!\n";
      break;
    }
  }

  return 0;
}
void displayMainMenu() {
  cout << "\n==== Library Management System ====\n";
  cout << "1. Student\n";
  cout << "2. Staff\n";
  cout << "3. Exit\n";
  cout << "Enter your choice: ";
}
void displayStudentMenu() {
  cout << "\n==== Student Menu ====\n";
  cout << "1. Search Books\n";
  cout << "2. Reserve Book\n";
  cout << "3. Check Availability\n";
  cout << "4. Exit\n";
  cout << "Enter your choice: ";
}
void displayStaffMenu() {
  cout << "\n==== Staff Menu ====\n";
  cout << "1. Add Book\n";
  cout << "2. Remove Book\n";
  cout << "3. Display Inventory\n";
  cout << "4. Display outdated books\n";
  cout << "5. Analyze Demand\n";
  cout << "6. Add Staff\n";
  cout << "7. Remove Staff\n";
  cout << "8. Display Staff List\n";
  cout << "9. Search Staff\n";
  cout << "10. Exit\n";
  cout << "Enter your choice: ";
}
void searchBooks() {
  string keyword;
  int count = 0;
  cin.ignore();
  cout << "Enter a keyword to search for: ";
  getline(cin, keyword);
  ifstream bookFile(FILENAME);
  try {
    vector<Book> books = parseFile(bookFile);
    bool found = false;
    for (const Book book : books) {
      if (toLowercase(book.title).find(toLowercase(keyword)) == string::npos) {
        continue;
      }

      cout << "\nTitle: " << book.title << endl;
      cout << "Author: " << book.author << endl;
      cout << "ISBN: " << book.ISBN << endl;
      cout << "Publisher: " << book.publisher << endl;
      cout << "Year of publication: " << book.year << endl;
      cout << "Quantity: " << book.quantity << endl;
      found = true;
      cout << "-----------------------------------" << endl;
    }

    if (!found) {
      cout << "No books found.\n";
    }
  } catch (const char *msg) {
    cout << msg << endl;
  }

  bookFile.close();
}
// Function to reserve a book
void reserveBook() {
  string ISBN;
  bool found = false;
  cout << "Enter ISBN of the book to reserve: ";
  cin >> ISBN;
  ifstream inputDB(FILENAME);
  ofstream outputDB(FILENAME);

  vector<Book> books = parseFile(inputDB);
  for (Book book : books) {
    if (book.ISBN == ISBN) {
      found = true;
      if (book.quantity > 0) {
        book.quantity--;
        cout << "Book reserved successfully!\n";
      } else {
        cout << "Book is not available.\n";
      }
      break;
    }
  }
  saveFile(outputDB, books);

  inputDB.close();
  outputDB.close();
  if (found == false) {
    cout << "Book with ISBN " << ISBN << " not found.\n";
  } else {
    cout << "Book reserved successfully.\n";
  }
}

// Function to check availability of a book
void checkAvailability() {
  string ISBN;
  bool found = false;
  cout << "Enter ISBN of the book to check availability: ";
  cin >> ISBN;
  ifstream bookFile("books.txt");

  try {
    vector<Book> books = parseFile(bookFile);
    for (Book book : books) {
      if (book.ISBN == ISBN) {
        found = true;
        if (book.quantity > 0) {
          cout << "The book is available for borrowing.\n";
        } else {
          cout << "The book is not available for borrowing.\n";
        }
      }
    }
    bookFile.close();
  } catch (const char *msg) {
    cout << msg << endl;
  }

  if (!found) {
    cout << "Book with ISBN " << ISBN << " not found.\n";
  }
}

// Function to add a book
void addBook() {
  Book book;
  cout << "Enter book title: ";
  getline(cin, book.title);
  cout << "Enter book author: ";
  getline(cin, book.author);
  cout << "Enter book ISBN: ";
  getline(cin, book.ISBN);
  cout << "Enter book publisher: ";
  getline(cin, book.publisher);
  cout << "Enter year of publication: ";
  cin >> book.year;
  cout << "Enter quantity: ";
  cin >> book.quantity;
  ofstream bookFile(FILENAME, ios::app);
  bookFile << book.title << "," << book.author << "," << book.ISBN << ","
           << book.publisher << "," << book.year << ";" << book.quantity
           << endl;
  bookFile.close();

  cout << "Book added successfully.\n";
}

// Function to remove a book
void removeBook() {
  string ISBN;
  bool found = false;

  cout << "Enter ISBN of the book to remove: ";
  cin >> ISBN;

  ifstream bookFile("books.txt");
  ofstream newBookFile("newBooks.txt");

  string line;
  while (getline(bookFile, line)) {
    string ISBNFromFile = line.substr(line.find_last_of(",") + 1);
    if (ISBNFromFile == ISBN) {
      found = true;
    } else {
      newBookFile << line << endl;
    }
  }

  bookFile.close();
  newBookFile.close();

  if (!found) {
    cout << "Book with ISBN " << ISBN << " not found.\n";
  } else {
    remove("books.txt");
    rename("newBooks.txt", "books.txt");
    cout << "Book removed successfully.\n";
  }
}

// Function to display the inventory of books
void displayInventory() {
  ifstream bookFile("books.txt");

  string line;
  while (getline(bookFile, line)) {
    Book book;
    size_t pos = 0;
    string delimiter = ",";
    pos = line.find(delimiter);
    book.title = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    pos = line.find(delimiter);
    book.author = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    pos = line.find(delimiter);
    book.ISBN = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    pos = line.find(delimiter);
    book.publisher = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    pos = line.find(delimiter);
    book.year = stoi(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
    book.quantity = stoi(line);

    cout << "\nTitle: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "ISBN: " << book.ISBN << endl;
    cout << "Publisher: " << book.publisher << endl;
    cout << "Year of publication: " << book.year << endl;
    cout << "Quantity: " << book.quantity << endl;
  }

  bookFile.close();
}
// function to display outdated books
void displayOutdatedBooks() {

  ifstream file("bookData.txt");

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string title, author, category, status, publicationDate;

      getline(ss, title, ',');
      getline(ss, author, ',');
      getline(ss, category, ',');
      getline(ss, status, ',');
      getline(ss, publicationDate, ',');

      if (publicationDate < "2000") {

        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Category: " << category << endl;
        cout << "Status: " << status << endl;
        cout << "Publication Date: " << publicationDate << endl;
        cout << endl;
      }
    }
    file.close();
  } else {
    cout << "Unable to open the file." << endl;
  }
}
// Function to analyze the demand for books
void analyzeDemand() {
  ifstream file2("d.txt");
	vector<Book> books = parseFile(file2);
  sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
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
    for(int i = 0; i < 5 && i < books.size(); i++) {
        cout<<i+1<<".  " << books[i].title << " by " << books[i].author <<"   "<<books[i].borrowCount<<endl;
    }
    break;
  case 2:
      cout<<"\n\nThe top 10 books that are in high demand.\n\n";
    for(int i = 0; i < 10 && i < books.size(); i++) {
        cout <<i+1<<".  "<<books[i].title << " by " << books[i].author <<"   "<<books[i].borrowCount<<endl;
    }
    break;
  case 3:
      cout<<"\n\nThe demand for all books in general.\n\n";
    for(int i = 0;i < books.size(); i++) {
        cout<<i+1<<".  " << books[i].title << " by " << books[i].author <<"   "<<endl;
    }
    break;
  case 4:
      cout<<"\n\n the top 5 books that are in low demand.\n\n";
    for(int i = books.size()-1;i > books.size()-6; i--) {
        cout<<100-i<<".  " << books[i].title << " by " << books[i].author<<"   "<<books[i].borrowCount<<endl;
    }
    break;
  default:
    cout<<"invalid choice";

}
}
// Function to add a staff member
void addStaff() {
  Staff staff;
  cout << "Enter staff name: ";
  getline(cin >> ws, staff.name);
  cout << "Enter staff email: ";
  getline(cin >> ws, staff.email);
  cout << "Enter staff password: ";
  getline(cin >> ws, staff.password);
  ofstream staffFile("staff.txt", ios::app);
  staffFile << staff.name << "," << staff.email << "," << staff.password
            << endl;
  staffFile.close();
  cout << "Staff member added successfully.\n";
}

// Function to remove a staff member
void removeStaff() {
  string email;
  bool found = false;
  cout << "Enter email of the staff member to remove: ";
  cin >> email;
  ifstream staffFile("staff.txt");
  ofstream newStaffFile("newStaff.txt");
  string line;
  while (getline(staffFile, line)) {
    string emailFromFile = line.substr(line.find_last_of(",") + 1);
    if (emailFromFile == email) {
      found = true;
    } else {
      newStaffFile << line << endl;
    }
  }

  staffFile.close();
  newStaffFile.close();

  if (!found) {
    cout << "Staff member with email " << email << " not found.\n";
  } else {
    remove("staff.txt");
    rename("newStaff.txt", "staff.txt");
    cout << "Staff member removed successfully.\n";
  }
}
// Function to display the list of staff members
void displayStaffList() {
  ifstream staffFile("staff.txt");
  string line;
  while (getline(staffFile, line)) {
    Staff staff;
    size_t pos = 0;
    string delimiter = ",";
    pos = line.find(delimiter);
    staff.name = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    pos = line.find(delimiter);
    staff.email = line.substr(0, pos);
    line.erase(0, pos + delimiter.length());
    staff.password = line;
    cout << "\nName: " << staff.name << endl;
    cout << "Email: " << staff.email << endl;
  }
  staffFile.close();
}

// Function to search for a staff member
void searchStaff() {
  string keyword;
  int count = 0;
  cout << "Enter a keyword to search for: ";
  getline(cin, keyword);
  ifstream staffFile("staff.txt");
  string line;
  while (getline(staffFile, line)) {
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    if (line.find(keyword) != string::npos) {
      Staff staff;
      size_t pos = 0;
      string delimiter = ",";
      pos = line.find(delimiter);
      staff.name = line.substr(0, pos);
      line.erase(0, pos + delimiter.length());
      pos = line.find(delimiter);
      staff.email = line.substr(0, pos);
      line.erase(0, pos + delimiter.length());
      staff.password = line;

      cout << "\nName: " << staff.name << endl;
      cout << "Email: " << staff.email << endl;

      count++;
    }
  }

  staffFile.close();

  if (count == 0) {
    cout << "No staff members found.\n";
  }
}
