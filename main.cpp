#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Cấu trúc để lưu thông tin sinh viên
struct Student {
    int id;
    string name;
    float grade;
};

struct User {
    string username;
    string password;
};

// Hàm để đọc dữ liệu từ tệp CSV
vector<Student> readStudentsFromCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;

    // Bỏ qua dòng tiêu đề
    getline(file, line);

    while (getline(file, line)) {
        Student student;
        stringstream ss(line);
        string temp;

        // Đọc ID
        getline(ss, temp, ',');
        student.id = stoi(temp);

        // Đọc tên
        getline(ss, student.name, ',');

        // Đọc điểm
        getline(ss, temp, ',');
        student.grade = stof(temp);

        students.push_back(student);
    }

    return students;
}

// Hàm để ghi dữ liệu vào tệp CSV
void writeStudentsToCSV(const string& filename, const vector<Student>& students) {
    ofstream file(filename);

    // Ghi tiêu đề
    file << "ID,Name,Grade" << endl;

    // Ghi dữ liệu sinh viên
    for (const auto& student : students) {
        file << student.id << "," << student.name << "," << student.grade << endl;
    }
}

vector<User> readUsersFromCSV(const string& filename) {
    vector<User> users;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        User user;
        stringstream ss(line);
        getline(ss, user.username, ',');
        getline(ss, user.password);
        users.push_back(user);
    }

    return users;
}

// Hàm để ghi dữ liệu người dùng vào tệp CSV
void writeUsersToCSV(const string& filename, const vector<User>& users) {
    ofstream file(filename);
    for (const auto& user : users) {
        file << user.username << "," << user.password << endl;
    }
}

// Hàm đăng ký người dùng mới
bool signup(vector<User>& users, const string& username, const string& password) {
    // Kiểm tra xem username đã tồn tại chưa
    auto it = find_if(users.begin(), users.end(),
                      [&username](const User& user) { return user.username == username; });
    if (it != users.end()) {
        cout << "Username already exists. Please choose another one." << endl;
        return false;
    }

    // Thêm người dùng mới
    users.push_back({username, password});
    writeUsersToCSV("users.csv", users);
    cout << "Signup successful!" << endl;
    return true;
}

// Hàm đăng nhập
bool login(const vector<User>& users, const string& username, const string& password) {
    auto it = find_if(users.begin(), users.end(),
                      [&](const User& user) { return user.username == username && user.password == password; });
    if (it != users.end()) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid username or password." << endl;
    return false;
}


int main() {
    const string student_filename = "students.csv";
    const string user_filename = "users.csv";

    vector<Student> students = readStudentsFromCSV(student_filename);
    vector<User> users = readUsersFromCSV(user_filename);

    string choice;
    while (true) {
        cout << "1. Signup\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == "1") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            signup(users, username, password);
        } else if (choice == "2") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (login(users, username, password)) {
                // Hiển thị thông tin sinh viên sau khi đăng nhập thành công
                cout << "Student information:" << endl;
                for (const auto& student : students) {
                    cout << "ID: " << student.id << ", Name: " << student.name << ", Grade: " << student.grade << endl;
                }
            }
        } else if (choice == "3") {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}