#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Course {
    string name;
    float grade; 
    int credit;
};

int main() {
    int numCourses;
    float totalGradePoints = 0.0;
    int totalCredits = 0;

    cout << "====== CGPA CALCULATOR ======\n";
    cout << "Enter number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);

    
	for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Course Name: ";
        cin.ignore(); 
        getline(cin, courses[i].name);

        cout << "Grade Point (e.g. A=10, B=8): ";
        cin >> courses[i].grade;

        cout << "Credit Hours: ";
        cin >> courses[i].credit;

        totalGradePoints += courses[i].grade * courses[i].credit;
        totalCredits += courses[i].credit;
    }

    
    float cgpa = totalGradePoints / totalCredits;

    
    cout << "\n=========== RESULT ===========\n";
    cout << left << setw(20) << "Course Name" 
         << setw(15) << "Grade Point" 
         << setw(15) << "Credit Hours" << endl;

    for (const auto& course : courses) {
        cout << left << setw(20) << course.name 
             << setw(15) << course.grade 
             << setw(15) << course.credit << endl;
    }

    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << fixed << setprecision(2);
    cout << "\nFinal CGPA: " << cgpa << endl;
    cout << "==============================\n";

    return 0;
}
