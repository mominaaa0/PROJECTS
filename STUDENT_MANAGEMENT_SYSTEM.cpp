/*
 Student Management System (simple, console-based)
 Author: Momina Fatima (sample student project style)
 Compile: g++ -std=c++11 student_management.cpp -o student_mgmt
 Run: ./student_mgmt
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string branch;
};

string dataFile = "students.txt";

// -- helpers to convert Student to/from a CSV line --
string serialize(const Student &s) {
    // id,name,age,branch
    ostringstream oss;
    oss << s.id << ',' << s.name << ',' << s.age << ',' << s.branch;
    return oss.str();
}

Student deserialize(const string &line) {
    Student s;
    stringstream ss(line);
    string token;
    getline(ss, token, ','); s.id = stoi(token);
    getline(ss, s.name, ',');
    getline(ss, token, ','); s.age = stoi(token);
    getline(ss, s.branch, ',');
    return s;
}

vector<Student> loadAll() {
    vector<Student> list;
    ifstream fin(dataFile);
    string line;
    while (getline(fin, line)) {
        if (line.size() == 0) continue;
        list.push_back(deserialize(line));
    }
    fin.close();
    return list;
}

void saveAll(const vector<Student> &list) {
    ofstream fout(dataFile, ios::trunc);
    for (const auto &s : list) {
        fout << serialize(s) << '\n';
    }
    fout.close();
}

int nextId(const vector<Student> &list) {
    int maxId = 0;
    for (auto &s : list) if (s.id > maxId) maxId = s.id;
    return maxId + 1;
}

void addStudent() {
    vector<Student> list = loadAll();
    Student s;
    s.id = nextId(list);
    cout << "Enter name: ";
    getline(cin, s.name);
    cout << "Enter age: ";
    cin >> s.age; cin.ignore();
    cout << "Enter branch: ";
    getline(cin, s.branch);

    list.push_back(s);
    saveAll(list);
    cout << "Student added with ID: " << s.id << "\n";
}

void viewAll() {
    vector<Student> list = loadAll();
    if (list.empty()) { cout << "No records found.\n"; return; }
    cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age" << setw(12) << "Branch\n";
    cout << "-------------------------------------------------\n";
    for (auto &s : list) {
        cout << setw(6) << s.id << setw(20) << s.name << setw(6) << s.age << setw(12) << s.branch << '\n';
    }
}

void searchById() {
    cout << "Enter ID to search: ";
    int id; cin >> id; cin.ignore();
    vector<Student> list = loadAll();
    for (auto &s : list) {
        if (s.id == id) {
            cout << "Found:\n";
            cout << "ID: " << s.id << "\nName: " << s.name << "\nAge: " << s.age << "\nBranch: " << s.branch << "\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

void updateStudent() {
    cout << "Enter ID to update: ";
    int id; cin >> id; cin.ignore();
    vector<Student> list = loadAll();
    bool found = false;
    for (auto &s : list) {
        if (s.id == id) {
            found = true;
            cout << "Enter new name (blank to keep): ";
            string tmp; getline(cin, tmp);
            if (!tmp.empty()) s.name = tmp;
            cout << "Enter new age (0 to keep): ";
            int a; cin >> a; cin.ignore();
            if (a != 0) s.age = a;
            cout << "Enter new branch (blank to keep): ";
            getline(cin, tmp);
            if (!tmp.empty()) s.branch = tmp;
            break;
        }
    }
    if (!found) cout << "ID not found.\n";
    else {
        saveAll(list);
        cout << "Record updated.\n";
    }
}

void deleteStudent() {
    cout << "Enter ID to delete: ";
    int id; cin >> id; cin.ignore();
    vector<Student> list = loadAll();
    vector<Student> newlist;
    bool found = false;
    for (auto &s : list) {
        if (s.id == id) { found = true; continue; }
        newlist.push_back(s);
    }
    if (!found) cout << "ID not found.\n";
    else {
        saveAll(newlist);
        cout << "Record deleted.\n";
    }
}

void showMenu() {
    cout << "----- Student Management System -----\n";
    cout << "1. Add student\n2. View all\n3. Search by ID\n4. Update student\n5. Delete student\n6. Exit\n";
    cout << "Choose option: ";
}

int main() {
    // ensure data file exists
    ofstream fout(dataFile, ios::app);
    fout.close();

    while (true) {
        showMenu();
        int opt; cin >> opt; cin.ignore();
        switch (opt) {
            case 1: addStudent(); break;
            case 2: viewAll(); break;
            case 3: searchById(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Bye!\n"; return 0;
            default: cout << "Invalid option.\n";
        }
        cout << "\n";
    }
    return 0;
}
