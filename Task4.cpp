#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

struct Student {
    int id;
    std::string name;
    int age;
    double average_score;
    std::string country;
};

class StudentRecordSystem {
private:
    std::vector<Student> students;
    std::unordered_map<int, Student> studentMap;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
        studentMap[student.id] = student;
    }

    void displayStudents() {
        for (const auto& student : students) {
            std::cout << "ID: " << student.id << ", Name: " << student.name
                      << ", Age: " << student.age << ", Average Score: " << student.average_score
                      << ", Country: " << student.country << "\n";
        }
    }

    void linearSearchByName(const std::string& name) {
        for (const auto& student : students) {
            if (student.name == name) {
                std::cout << "Found: " << student.name << " with ID " << student.id << "\n";
                return;
            }
        }
        std::cout << "Student not found.\n";
    }

    void binarySearchByID(int id) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.id < b.id;
        });

        int left = 0, right = students.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (students[mid].id == id) {
                std::cout << "Found: " << students[mid].name << " with ID " << students[mid].id << "\n";
                return;
            }
            if (students[mid].id < id)
                left = mid + 1;
            else
                right = mid - 1;
        }
        std::cout << "Student not found.\n";
    }

    void bubbleSortByName() {
        for (size_t i = 0; i < students.size() - 1; i++) {
            for (size_t j = 0; j < students.size() - i - 1; j++) {
                if (students[j].name > students[j + 1].name) {
                    std::swap(students[j], students[j + 1]);
                }
            }
        }
    }

    void quickSortByScore(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSortByScore(low, pi - 1);
            quickSortByScore(pi + 1, high);
        }
    }

    int partition(int low, int high) {
        double pivot = students[high].average_score;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (students[j].average_score < pivot) {
                i++;
                std::swap(students[i], students[j]);
            }
        }
        std::swap(students[i + 1], students[high]);
        return (i + 1);
    }

    int getStudentCount() const {
        return students.size();
    }
};

void displayMenu() {
    std::cout << "1. Add student\n";
    std::cout << "2. Display students\n";
    std::cout << "3. Search student by name (Linear )\n";
    std::cout << "4. Search student by ID (Binary )\n";
    std::cout << "5. Sort students by name (Bubble )\n";
    std::cout << "6. Sort students by average Score (Quick )\n";
    std::cout << "7. Exit\n";
}

int main() {
    StudentRecordSystem srs;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 7) break;

        switch (choice) {
        case 1: {
            Student student;
            std::cout << "Enter ID: ";
            std::cin >> student.id;
            std::cin.ignore();
            std::cout << "Enter Name: ";
            std::getline(std::cin, student.name);
            std::cout << "Enter Age: ";
            std::cin >> student.age;
            std::cout << "Enter Average Score: ";
            std::cin >> student.average_score;
            std::cin.ignore();
            std::cout << "Enter Country: ";
            std::getline(std::cin, student.country);
            srs.addStudent(student);
            break;
        }
        case 2:
            srs.displayStudents();
            break;
        case 3: {
            std::string name;
            std::cout << "Enter Name to Search: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            srs.linearSearchByName(name);
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter ID to Search: ";
            std::cin >> id;
            srs.binarySearchByID(id);
            break;
        }
        case 5:
            srs.bubbleSortByName();
            std::cout << "Students sorted by name.\n";
            break;
        case 6:
            srs.quickSortByScore(0, srs.getStudentCount() - 1);
            std::cout << "Students sorted by average score.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
