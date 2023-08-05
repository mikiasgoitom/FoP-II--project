#include "library.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include "staff_info.h"
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

// Declare and initialize structure from staff_info.h
vector <librarianInfo> staff;
librarianInfo staffInfo;

int main() {

do{	
	 system("CLS");
    system("color F0");
  int choice;
  displayMainMenu();
  cin >> choice;
  if (choice == 1) {
	    system("CLS");
    system("color 0A");
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
        cout << "\n****************************************************************************\n";
      break;
    }
  } else if (choice == 2) {
	  system("CLS");
    system("color 0C");
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
      //displayOutdatedBooks();
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
 cout << "\n****************************************************************************\n";
      break;
    }
  }
	else
{           
           cout << "\n****************************************************************************\n";
         cout << "Exiting program. Goodbye!\n";
       cout << "\n****************************************************************************\n";
       return 0;
}
system("pause");
}while(true);
	
  return 0;
}
void displayMainMenu() {
 cout << endl << endl;
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>                                   LIBRARY MANAGEMENT SYSTEM                             <>\n";
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>STUDENT   ...........................................................................[1] <>\n";
    cout << "\t\t<> STAFF    ...........................................................................[2] <>\n";
    cout << "\t\t<> EXIT     ...........................................................................[3] <>\n";
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\tEnter your choice : " ;
}
void displayStudentMenu() {
         cout << endl << endl;
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>                                   STUDENT MENU                                          <>\n";
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>SEARCH BOOKS   ......................................................................[1] <>\n";
    cout << "\t\t<> RESERVE BOOK    ....................................................................[2] <>\n";
    cout << "\t\t<> CHECK AVAILABILTY     ..............................................................[3] <>\n";
    cout << "\t\t<> RETURN TO MAIN MENU     .............................................................[4] <>\n";
    cout << "\t\t<>                                                                                          <>\n";
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\tEnter your choice : " ;
}
void displayStaffMenu() {
   cout << endl << endl;
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>                                   STAFF MENU                                            <>\n";
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<>ADD BOOKS   .........................................................................[1] <>\n";
    cout << "\t\t<> REMOVE BOOK    .....................................................................[2] <>\n";
    cout << "\t\t<> DISPLAY INVENTORY     ..............................................................[3] <>\n";
    cout << "\t\t<> DISPLAY OUTDATED BOOKS  ............................................................[4] <>\n";
    cout << "\t\t<> ANALYZ DEMAND     ..................................................................[5] <>\n";
    cout << "\t\t<> ADD STAFF     ......................................................................[6] <>\n";
    cout << "\t\t<> REMOVE STAFF     ...................................................................[7] <>\n";
    cout << "\t\t<> DISPLAY STAFF LIST     .............................................................[8] <>\n";
    cout << "\t\t<> SEARCH STAFF     ...................................................................[9] <>\n";
    cout << "\t\t<>RETURN TO MAIN MENU ................................................................[10] <>\n";
    cout << "\t\t<>                                                                                         <>\n";
    cout << "\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "\t\tEnter your choice : " ;
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
      
         
      cout << endl;
      cout << "****************************************************************************";
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
            cout << "\n****************************************************************************\n";
            cout << "No books found.\n";
            cout << "\n****************************************************************************\n";

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
                      cout << "\n****************************************************************************\n";
               cout << "Book reserved successfully.\n";
               cout << "\n****************************************************************************\n";
      } else {
        cout << "\n****************************************************************************\n";
            cout << "The book is not available for reservation.\n";
            cout << "\n****************************************************************************\n";
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
                  cout << "\n****************************************************************************\n";
               cout << "Book reserved successfully.\n";
               cout << "\n****************************************************************************\n";
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
            cout << "\n****************************************************************************\n";
          cout << "The book is available for borrowing.\n";
          cout << "\n****************************************************************************\n";
                
        } else {
                     cout << "\n****************************************************************************\n";
                        cout << "The book is not available for borrowing.\n";
                         cout << "\n****************************************************************************\n";
      
        }
      }
    }
    bookFile.close();
  } catch (const char *msg) {
    cout << msg << endl;
  }

  if (!found) {
                        cout << "\n****************************************************************************\n";
                        cout << "Book with ISBN " << ISBN << " not found.\n";
                        cout << "\n****************************************************************************\n";
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

          cout << "\n****************************************************************************\n";
           cout << "Book added successfully.\n";
          cout << "\n****************************************************************************\n";
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
         cout << "\n****************************************************************************\n";
    cout << "\nTitle: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "ISBN: " << book.ISBN << endl;
    cout << "Publisher: " << book.publisher << endl;
    cout << "Year of publication: " << book.year << endl;
    cout << "Quantity: " << book.quantity << endl;
  }
         cout << "\n****************************************************************************\n";

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
         cout << "\n****************************************************************************\n";
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Category: " << category << endl;
        cout << "Status: " << status << endl;
        cout << "Publication Date: " << publicationDate << endl;
	         cout << "\n****************************************************************************\n";
        cout << endl;
      }
    }
    file.close();
  } else {
	  cout << "\n****************************************************************************\n";
    cout << "Unable to open the file." << endl;
      cout << "\n****************************************************************************\n";

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
	          cout << "\n****************************************************************************\n";
    cout<<"1.The top 5 books that are in high demand."<<endl;
    cout<<"2.The top 10 books that are in high demand."<<endl;
    cout<<"3.The demand for all books in general."<<endl;
    cout<<"4.the top 5 books that are in low demand."<<endl;
    cout<<"please enter your choice.1,2 or 3"<<endl;
	          cout << "\n****************************************************************************\n";

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
      cout << "\n****************************************************************************\n";
    cout<<"invalid choice";

}
}
// Function to add a staff member
void addStaff() {
  int numOfEmployee;
    cout<<"Enter the number of employees to register: ";
    cin>>numOfEmployee;
    cin.ignore();

    for(int i=0;i<numOfEmployee;i++){
        cout<<"\n"<<i+1<<".Enter name: ";
        getline(cin,staffInfo.fullName);
        cout<<"Enter date of birth (DD/MM/YYYY): ";
        cin>>staffInfo.dateOfBirth.day>>staffInfo.dateOfBirth.month>>staffInfo.dateOfBirth.year;
        cin.ignore();
        cout<<"Enter email: ";
        getline(cin, staffInfo.email);
        cout<<"Enter password: ";
        getline(cin, staffInfo.password);
        cout<<"Enter education level: ";
        getline(cin, staffInfo.educationLevel);
        cout<<"Enter address: ";
        getline(cin, staffInfo.recidency);
        cout<<"Enter phone number: ";
        getline(cin, staffInfo.phoneNo);
        cout<<"Enter assigned employee ID: ";
        getline(cin, staffInfo.ID);
        cout<<"Enter assigned employee role: ";
        getline(cin, staffInfo.role);

        staff.push_back(staffInfo);
    }
        saveEmployeeData(staff, "employee_data.txt");

cout << "\nStaff members added successfully.\n";
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
     cout << "\n****************************************************************************\n";
    cout << "Staff member with email " << email << " not found.\n";
   cout << "\n****************************************************************************\n";

  } else {
    remove("staff.txt");
    rename("newStaff.txt", "staff.txt");
	            cout << "\n****************************************************************************\n";
    cout << "Staff member removed successfully.\n";
	            cout << "\n****************************************************************************\n";

  }
}
// Function to display the list of staff members
void displayStaffList() {
  readEmployeeData("employee_data.txt");
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
          cout << "\n****************************************************************************\n";
      cout << "\nName: " << staff.name << endl;
      cout << "Email: " << staff.email << endl;
          cout << "\n****************************************************************************\n";
      count++;
    }
  }

  staffFile.close();

  if (count == 0) {
     cout << "\n****************************************************************************\n";
    cout << "No staff members found.\n";
cout << "\n****************************************************************************\n";

  }
}

/************************************************************************
*                    END OF THE PROGRAM.                                *
************************************************************************/
