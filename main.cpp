#include "main.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream file2("db.txt");
	vector<Book> books2 = parseFile(file2);
	for (const Book &book : books2) {
		print_book(book);
	}
}
