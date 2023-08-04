#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Book {
    std::string title;
    std::string author;
    std::string category;
    std::string status;
    std::string publicationDate;
};
// accept new book details 
void acceptNewBook(Book& book){
   std::cout << "**********************************************" << std::endl;
   std::cout << "Book title : ";
     std:: cin >> book.title ;
   std::cout << "Author of the book : ";
     std:: cin >> book.author ;
   std::cout << "catagory : ";
     std:: cin >> book.category ;
   std::cout << "status : ";
     std:: cin >> book.status ;
   std::cout << "publicationDate : ";
     std:: cin >> book.publicationDate ;

}
// add book details  to file "bookData.txt"
void addBookToFile(const Book& book) {
    std::ofstream file("bookData.txt", std::ios::app);

    if (file.is_open()) {
        file << book.title << ",";
        file << book.author << ",";
        file << book.category << ",";
        file << book.status << ",";
        file << book.publicationDate << "\n";

        file.close();
        std::cout << "Book details added successfully!" << std::endl;
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
}

// display outdated books from file
void displayBooksFromFile() {
    std::cout <<std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;


    std::ifstream file("bookData.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string title, author, category, status , publicationDate;

            std::getline(ss, title, ',');
            std::getline(ss, author, ',');
            std::getline(ss, category, ',');
            std::getline(ss, status, ',');
            std::getline(ss, publicationDate, ',');

                 if(publicationDate < "2000"){

            std::cout << "Title: " << title << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Category: " << category << std::endl;
            std::cout << "Status: " << status << std::endl;
            std::cout << "Publication Date: " << publicationDate << std::endl;
            std::cout << std::endl;
        }
    }
        file.close();
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
}

// main function
int main() {
   
      std:: cout << "************************ outdatedBook identifer ************************\n" ;
         
    do{
                               
      std::cout << std::endl;
      std::cout << "ADD books to the program .................... [1]\n" ;
      std::cout << "list all outdated books ..........  ......... [2]\n" ;
      std::cout << "Exit............ ....... .....................[3]\n";
      std::cout << "choice : ";
      int choice;
      std::cin >> choice;
      if(choice == 1){
              Book newBook;
          acceptNewBook(newBook);
          addBookToFile(newBook);

      }
      
       else if(choice == 2)
      displayBooksFromFile();
      else if (choice == 3)  
       return 0;
    
      }  while (true);
      
}

