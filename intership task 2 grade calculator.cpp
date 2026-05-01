#include <iostream>
#include <fstream>
using namespace std;

class Student {
protected:
    string name;
    int subjects;
    float marks[10];

public:
    void input() {
        cout << "Enter student name: ";
        cin >> name;

        cout << "Enter number of subjects: ";
        cin >> subjects;

        for (int i = 0; i < subjects; i++) {
            do {
                cout << "Enter marks for subject " << i + 1 << ": ";
                cin >> marks[i];

                if (marks[i] < 0 || marks[i] > 100) {
                    cout << "Invalid marks! Try again.\n";
                }

            } while (marks[i] < 0 || marks[i] > 100);
        }
    }

    virtual void calculate() {
        cout << "Base class function\n";
    }
};

class Result : public Student {
private:
    float total, average;
    char grade;

public:
    float calculateTotal() {
        total = 0;
        for (int i = 0; i < subjects; i++) {
            total += marks[i];
        }
        return total;
    }

    float calculateAverage() {
        average = total / subjects;
        return average;
    }

    char calculateGrade() {
        if (average >= 80)
            grade = 'A';
        else if (average >= 70)
            grade = 'B';
        else if (average >= 60)
            grade = 'C';
        else if (average >= 50)
            grade = 'D';
        else
            grade = 'F';

        return grade;
    }

    void calculate() {
        calculateTotal();
        calculateAverage();
        calculateGrade();
    }

    void display() {
        cout << "\n--- Result ---\n";
        cout << "Name: " << name << endl;
        cout << "Total Marks: " << total << endl;
        cout << "Average: " << average << endl;
        cout << "Grade: " << grade << endl;
    }

    void saveToFile() {
        ofstream file("result.txt", ios::app);

        file << "Name: " << name << endl;
        file << "Total: " << total << endl;
        file << "Average: " << average << endl;
        file << "Grade: " << grade << endl;
        file << "---------------------\n";

        file.close();
    }

    void readFromFile() {
        ifstream file("result.txt");

        if (!file) {
            cout << "File not found!\n";
            return;
        }

        string line;
        cout << "\n--- File Data ---\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

int main() {
    int choice;
    Result r;

    do {
        cout << "\n1. Add Student\n2. View File\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            r.input();
            r.calculate();
            r.display();
            r.saveToFile();
            break;

        case 2:
            r.readFromFile();
            break;
        }

    } while (choice != 3);

    return 0;
}
