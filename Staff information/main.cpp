/*This functionality will store information about library staff,
including their contact information, work schedules, and roles.
This can help in creating shift systems and fulfilling legal requirements for employee registration.
Again we will be using file handling to store the staff information.*/
#ifndef staff_info
#define staff_info

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct birthDate{
    int day, month, year;
};

struct librarianInfo{
    string fullName;
    birthDate dateOfBirth;
    string email;
    string password;
    string educationLevel;
    string recidency;
    string phoneNo;
    string ID;
    string role;
};

struct schedule{
    string shift;
};

void saveEmployeeData(const vector<librarianInfo>& data,const string& fileName){
    ofstream file(fileName, ios::app);
    if(file.is_open()){
        for(const auto& employee: data){
            file << "Name: "<<employee.fullName<<endl;
            file << "Date of birth: " << employee.dateOfBirth.day << "/" << employee.dateOfBirth.month << "/" << employee.dateOfBirth.year << endl;
            file << "Email: "<<employee.email<<endl;
            file << "Password: "<<employee.password<<endl;
            file << "Education: "<<employee.educationLevel<<endl;
            file << "Address: "<<employee.recidency<<endl;
            file << "Phone number: "<<employee.phoneNo<<endl;
            file << "Employee ID: "<<employee.ID<<endl;
            file << "Employee role: "<<employee.role<<endl<<endl;
        }
        file.close();
        cout<<"Employee data is saved to file"<<endl;
    }
        else{
            cout<<"Unable to open file for writing"<<endl;
        }
    }


ostream& operator <<(ostream& print, const librarianInfo& info){
    print << "Name: "<<info.fullName<<endl;
    print << "Date of birth: " << info.dateOfBirth.day << "/" << info.dateOfBirth.month << "/" << info.dateOfBirth.year << endl;
    print << "Email: "<<info.email<<endl;
    print << "Password: "<<info.password<<endl;
    print << "Education: "<<info.educationLevel<<endl;
    print << "Address: "<<info.recidency<<endl;
    print << "Phone number: "<<info.phoneNo<<endl;
    print << "Employee ID: "<<info.ID<<endl;
    print << "Employee role: "<<info.role<<endl<<endl;
    return print;
}

void readEmployeeData(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        librarianInfo employee;
        string line;
        while (getline(file, line)) {
            if (line.find("Name: ") != string::npos) {
                employee.fullName = line.substr(6);
            }
            else if (line.find("Date of birth: ") != string::npos) {
                sscanf(line.c_str(), "Date of birth: %d/%d/%d", &employee.dateOfBirth.day, &employee.dateOfBirth.month, &employee.dateOfBirth.year);
            }
            else if (line.find("Email: ") != string::npos) {
                employee.email = line.substr(7);
            }
            else if (line.find("Password: ") != string::npos) {
                employee.password = line.substr(10);
            }
            else if (line.find("Education: ") != string::npos) {
                employee.educationLevel = line.substr(11);
            }
            else if (line.find("Address: ") != string::npos) {
                employee.recidency = line.substr(9);
            }
            else if (line.find("Phone number: ") != string::npos) {
                employee.phoneNo = line.substr(14);
            }
            else if (line.find("Employee ID: ") != string::npos) {
                employee.ID = line.substr(13);
            }
            else if (line.find("Employee role: ") != string::npos) {
                employee.role = line.substr(15);
                cout << employee;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file for reading" << endl;
    }
}

void readEmployeeDataForSearch(vector<librarianInfo>& hold, const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        librarianInfo employee;
        while (getline(file, line)) {
             // Move librarianInfo employee inside the loop to create a new object for each line

            if (line.find("Name: ") != string::npos) {
                employee.fullName = line.substr(6);
            }
            else if (line.find("Date of birth: ") != string::npos) {
                sscanf(line.c_str(), "Date of birth: %d/%d/%d", &employee.dateOfBirth.day, &employee.dateOfBirth.month, &employee.dateOfBirth.year);
            }
            else if (line.find("Email: ") != string::npos) {
                employee.email = line.substr(7);
            }
            else if (line.find("Password: ") != string::npos) {
                employee.password = line.substr(10);
            }
            else if (line.find("Education: ") != string::npos) {
                employee.educationLevel = line.substr(11);
            }
            else if (line.find("Address: ") != string::npos) {
                employee.recidency = line.substr(9);
            }
            else if (line.find("Phone number: ") != string::npos) {
                employee.phoneNo = line.substr(14);
            }
            else if (line.find("Employee ID: ") != string::npos) {
                employee.ID = line.substr(13);
            }
            else if (line.find("Employee role: ") != string::npos) {
                employee.role = line.substr(15);
                cout << employee;
            }

            hold.push_back(employee); // Add the employee object to the hold vector
        }

        file.close();
    }
    else {
        cout << "Unable to open file for reading" << endl;
    }
}


void searchName(const vector<librarianInfo>& data, const string& name){
    bool found = false;
    for(const auto& employee: data){
        if(employee.fullName == name){
            cout << "Name: "<<employee.fullName<<endl;
            cout << "Date of birth: " << employee.dateOfBirth.day << "/" << employee.dateOfBirth.month << "/" << employee.dateOfBirth.year << endl;
            cout << "Email: "<<employee.email<<endl;
            cout << "Password: "<<employee.password<<endl;
            cout << "Education: "<<employee.educationLevel<<endl;
            cout << "Address: "<<employee.recidency<<endl;
            cout << "Phone number: "<<employee.phoneNo<<endl;
            cout << "Employee ID: "<<employee.ID<<endl;
            cout << "Employee role: "<<employee.role<<endl<<endl;
            found = true;
        }
        if(!found){
                cout<<"That name doesn't exist";
        }
    }
}
void searchID(const vector<librarianInfo>& data, const string& ID){
    bool found = false;
    for(const auto& employee: data){
        if(employee.ID == ID){
            cout << "Name: "<<employee.fullName<<endl;
            cout << "Date of birth: " << employee.dateOfBirth.day << "/" << employee.dateOfBirth.month << "/" << employee.dateOfBirth.year << endl;
            cout << "Email: "<<employee.email<<endl;
            cout << "Password: "<<employee.password<<endl;
            cout << "Education: "<<employee.educationLevel<<endl;
            cout << "Address: "<<employee.recidency<<endl;
            cout << "Phone number: "<<employee.phoneNo<<endl;
            cout << "Employee ID: "<<employee.ID<<endl;
            cout << "Employee role: "<<employee.role<<endl<<endl;
            found = true;
        }
        if(!found){
                cout<<"That ID doesn't exist";
        }
    }
}

void removeEmployeeData(vector<librarianInfo>& data, int index){
    if(index >= 0 && index <= data.size()){
        data.erase(data.begin()+index);
        cout<<"\nSuccessfully removed employee data!\n";
    }
    else{
        cout<<"\nWrong index!\n";
    }
}

vector <librarianInfo> staff;
librarianInfo staffInfo;

#endif // staff_info


