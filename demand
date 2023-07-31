#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include<cstdlib>
void demandAnalysis(vector<Book>& books2) {
    sort(books2.begin(), books2.end(), [](const Book& a, const Book& b) {
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
    for(int i = 0; i < 5 && i < books.size(); i++) {
        cout<<i+1<<".  " << books2[i].title << " by " << books2[i].author <<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  case 2:
    for(int i = 0; i < 10 && i < books.size(); i++) {
        cout <<i+1<<".  "<<books2[i].title << " by " << books2[i].author <<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  case 3:
    for(int i = 0;i < books.size(); i++) {
        cout<<i+1<<".  " << books2[i].title << " by " << books2[i].author <<"   "<<endl;
    }
    break;
  case 4:
    for(int i = books.size()-1;i > books.size()-6; i--) {
        cout<<100-i<<".  " << books2[i].title << " by " << books2[i].author<<"   "<<books2[i].borrowCount<<endl;
    }
    break;
  default:
    cout<<"invalid choice";

}
  }
