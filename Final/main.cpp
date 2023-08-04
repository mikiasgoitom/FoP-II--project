#include"library.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;
struct Book {
    string title;
    string author;
    string ISBN;
    string publisher;
    int year;
    int quantity;
};
struct Staff {
    string name;
    string email;
    string password;
};
int main() {
int choice;
 displayMainMenu();
 cin >> choice;
 if (choice==1){
    displayStudentMenu();
    int choice2;
    cin>>choice2;
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
}
else if(choice==2){
    displayStaffMenu();
    int choice3;
    cin>>choice3;
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
            analyzeDemand();
            break;
        case 5:
            addStaff();
            break;
        case 6:
            removeStaff();
            break;
        case 7:
            displayStaffList();
            break;
        case 8:
            searchStaff();
            break;
        case 9:
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
    cout << "4. Analyze Demand\n";
    cout << "5. Add Staff\n";
    cout << "6. Remove Staff\n";
    cout << "7. Display Staff List\n";
    cout << "8. Search Staff\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}
void searchBooks() {
    string keyword;
    int count = 0;
    cin.ignore();
    cout << "Enter a keyword to search for: ";
    getline(cin, keyword);
    ifstream bookFile("books.txt");
    string line;
    while (getline(bookFile, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        if (line.find(keyword) != string::npos) {
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
            count++;
        }
    }
    bookFile.close();
    if (count == 0) {
        cout << "No books found.\n";
    }
}
//Function to reserve a book
void reserveBook() {
    string ISBN;
    bool found = false;
    cout << "Enter ISBN of the book to reserve: ";
    cin >> ISBN;
    ifstream bookFile("books.txt");
    ofstream newBookFile("newBooks.txt");
    string line;
    while (getline(bookFile, line)) {
        string ISBNFromFile = line.substr(line.find_last_of(",") + 1);
        if (ISBNFromFile == ISBN) {
            found = true;
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
            book.publisher = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            pos = line.find(delimiter);
            book.year = stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
            book.quantity = stoi(line);

            if (book.quantity > 0) {
                book.quantity--;
            } else {
                cout << "The book is not available for reservation.\n";
                newBookFile << line << endl;
            }
            newBookFile << book.title << "," << book.author << "," << ISBN << "," << book.publisher << "," << book.year << "," << book.quantity << endl;
        } else {
            newBookFile << line << endl;
        }
    }
    bookFile.close();
    newBookFile.close();
    if (found==false) {
        cout << "Book with ISBN " << ISBN << " not found.\n";
    } else {
        remove("books.txt");
        rename("newBooks.txt", "books.txt");
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
    string line;
    while (getline(bookFile, line)) {
        string ISBNFromFile = line.substr(line.find_last_of(",") + 1);
        if (ISBNFromFile == ISBN) {
            found = true;
            Book book;
            size_t pos = 0;
            string delimiter = ";";
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

            if (book.quantity > 0) {
                cout << "The book is available for borrowing.\n";
            } else {
                cout << "The book is not available for borrowing.\n";
            }
        }
    }

    bookFile.close();

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
    ofstream bookFile("books.txt", ios::app);
    bookFile << book.title << "," << book.author << "," << book.ISBN << "," << book.publisher << "," << book.year << ";" << book.quantity << endl;
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

// Function to analyze the demand for books
void analyzeDemand() {
// TODO: Implement this function
cout << "This function is not yet implemented.\n";
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
staffFile << staff.name << "," << staff.email << "," << staff.password << endl;
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
getline(cin , keyword);
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
