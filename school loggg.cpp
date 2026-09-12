#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

// Enum representing the available designations
enum Designation {
    TEACHER = 1,
    COOK,
    WATCHMAN,
    LIBRARIAN,
    BURSAR,
    PRINCIPAL
};

// Data structure to store Employee details
struct Employee {
    string id;
    string name;
    string password;
    Designation designation;
};

// Helper function to convert Designation Enum to String for display
string getDesignationName(Designation desig) {
    switch (desig) {
        case TEACHER:    return "Teacher";
        case COOK:       return "Cook";
        case WATCHMAN:   return "Watchman";
        case LIBRARIAN:  return "Librarian";
        case BURSAR:     return "Bursar";
        case PRINCIPAL:  return "Principal";
        default:         return "Unknown";
    }
}

// Global mock database of registered school staff
map<string, Employee> employeeDB = {
    {"T101", {"T101", "Cheruiyot", "pass123", TEACHER}},
    {"C101", {"C101", "Mary Wambui", "cook123", COOK}},
    {"W101", {"W101", "John Kiprop", "watch123", WATCHMAN}},
    {"L101", {"L101", "Amina Otieno", "lib123", LIBRARIAN}},
    {"B101", {"B101", "David Ndung'u", "bursar123", BURSAR}},
    {"P101", {"P101", "Dr. Mutua", "admin123", PRINCIPAL}}
};

// Exam marks storage structure
struct StudentMark {
    string studentId;
    string studentName;
    string subject;
    double mark;
};

vector<StudentMark> examMarksList;

// Module for handling Exam Marks Entry
void examMarksEntryModule(const Employee& loggedInUser) {
    cout << "\n=========================================\n";
    cout << "         EXAM MARKS ENTRY MODULE         \n";
    cout << "=========================================\n";
    cout << "Logged in as: " << loggedInUser.name << " (" << getDesignationName(loggedInUser.designation) << ")\n\n";

    int choice;
    do {
        cout << "1. Add New Student Marks\n";
        cout << "2. View All Recorded Marks\n";
        cout << "3. Return to Dashboard\n";
        cout << "Select Option (1-3): ";
        cin >> choice;

        if (choice == 1) {
            StudentMark entry;
            cout << "\nEnter Student ID: ";
            cin >> entry.studentId;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, entry.studentName);
            cout << "Enter Subject: ";
            getline(cin, entry.subject);
            cout << "Enter Marks (0-100): ";
            cin >> entry.mark;

            examMarksList.push_back(entry);
            cout << "\n[✓] Exam mark successfully saved!\n\n";

        } else if (choice == 2) {
            cout << "\n------------------------------------------------------------\n";
            cout << left << setw(12) << "Student ID" 
                 << setw(20) << "Name" 
                 << setw(15) << "Subject" 
                 << setw(10) << "Mark" << "\n";
            cout << "------------------------------------------------------------\n";
            
            if (examMarksList.empty()) {
                cout << "No exam records found.\n";
            } else {
                for (const auto& record : examMarksList) {
                    cout << left << setw(12) << record.studentId 
                         << setw(20) << record.studentName 
                         << setw(15) << record.subject 
                         << setw(10) << record.mark << "\n";
                }
            }
            cout << "------------------------------------------------------------\n\n";
        }
    } while (choice != 3);
}

// Designation-specific Dashboard
void displayDashboard(const Employee& user) {
    cout << "\n=========================================\n";
    cout << "  WELCOME, " << user.name << "\n";
    cout << "  Designation: " << getDesignationName(user.designation) << "\n";
    cout << "=========================================\n";

    int choice;
    while (true) {
        cout << "\n--- Main Actions ---\n";
        cout << "1. View Profile Details\n";

        // Access restriction: Only Teachers and Principal can enter marks
        if (user.designation == TEACHER || user.designation == PRINCIPAL) {
            cout << "2. Exam Marks Entry\n";
        } else {
            cout << "2. View Operational Tasks\n";
        }
        cout << "3. Logout\n";
        cout << "Select Choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Profile Info ---\n";
            cout << "ID: " << user.id << "\n";
            cout << "Name: " << user.name << "\n";
            cout << "Role: " << getDesignationName(user.designation) << "\n";
        } else if (choice == 2) {
            if (user.designation == TEACHER || user.designation == PRINCIPAL) {
                examMarksEntryModule(user);
            } else {
                cout << "\n[Task Board] Logged in successfully as " 
                     << getDesignationName(user.designation) 
                     << ". System operational.\n";
            }
        } else if (choice == 3) {
            cout << "\nLogging out successfully. Goodbye!\n";
            break;
        } else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }
}

int main() {
    while (true) {
        cout << "\n=========================================\n";
        cout << "      SCHOOL EMPLOYEE LOGIN SYSTEM       \n";
        cout << "=========================================\n";
        cout << "1. Teacher Login\n";
        cout << "2. Cook Login\n";
        cout << "3. Watchman Login\n";
        cout << "4. Librarian Login\n";
        cout << "5. Bursar Login\n";
        cout << "6. Principal Login\n";
        cout << "7. Exit Application\n";
        cout << "Select your Designation Role (1-7): ";

        int roleChoice;
        cin >> roleChoice;

        if (roleChoice == 7) {
            cout << "Shutting down system...\n";
            break;
        }

        if (roleChoice < 1 || roleChoice > 6) {
            cout << "\n[!] Invalid designation choice.\n";
            continue;
        }

        string empID, empPassword;
        cout << "\nEnter Employee ID: ";
        cin >> empID;
        cout << "Enter Password: ";
        cin >> empPassword;

        // Authentication logic
        if (employeeDB.find(empID) != employeeDB.end()) {
            Employee user = employeeDB[empID];
            
            // Verify Password and Designation Match
            if (user.password == empPassword && user.designation == static_cast<Designation>(roleChoice)) {
                cout << "\n[✓] Authentication successful!";
                displayDashboard(user);
            } else if (user.designation != static_cast<Designation>(roleChoice)) {
                cout << "\n[!] Access Denied: Selected designation does not match account credentials.\n";
            } else {
                cout << "\n[!] Incorrect Password.\n";
            }
        } else {
            cout << "\n[!] Employee ID not found.\n";
        }
    }

    return 0;
}
