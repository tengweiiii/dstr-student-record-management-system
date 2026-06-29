 // ==================================================================================================================
 // Module Code: CT077-3-2-DSTR (Data Structures)
 // System Name: Student Record Management System
 // Intake Code: APD2F2511CS(DA)
 // Lecturer Name: Dr. Masrina Akmal Binti Salleh
 // Student Name: Cheong Teng Wei
 // TP Number: TP076095
 // Hand Out Date: 11th May 2026 (Week 4)
 // Hand In Date: 3rd July 2026 (Week 10)
 // Group: 9
 //
 // Data Structure Used: Array
 // Algorithms Used: 
 // 1.  Append to End
 // 2.  Delete by Value
 // 3.  Insertion Sort by Student ID
 // 4.  Insertion Sort by Name
 // 5.  Insertion Sort by CGPA Ascending
 // 6.  Insertion Sort by CGPA Descending
 // 7.  Binary Search by Student ID
 // 8.  Binary Search by Name
 // 9.  Linear Search by Student ID
 // 10. Linear Search by Name
 // ==================================================================================================================

#define _CRT_SECURE_NO_WARNINGS // removes the warning of strcpy

// include necesssary header files
#include <iostream> // for input/output operations
#include <cstring> // for string manipulation
#include <fstream> // for file handling
#include <string> // for string class
#include <sstream> // for string stream operations
#include <chrono> // for measuring execution time
#include <iomanip> // for table formatting

using namespace std;
using namespace chrono;

// set maximum number of students that can be stored in the system
const int maxStudents = 35000;

// ===================================================================================================================
// Student struct:
// stores the details of a student
// ===================================================================================================================

struct Student {
	char studentID[20]; // set student id to 20 characters
	char fullName[50]; // set full name to 50 characters
	char programme[10]; // set programme code to 10 characters
	int yearOfStudy;
	double cgpa;
	char contactNumber[20]; // set contact number to 20 characters

};

// ===================================================================================================================
// Programme struct:
// stores the details of a programme loaded from programmes.csv
// ===================================================================================================================

struct Programme {
	char code[10];
	char name[100];
	char faculty[80];
	int durationYears;
};

// ===================================================================================================================
// ProgrammeArray struct:
// stores all available programmes
// ===================================================================================================================

const int maxProgrammes = 100;

struct ProgrammeArray {
	Programme programmes[maxProgrammes];
	int count;
};

// ===================================================================================================================
// displayStudentInfo() function:
// print the details of a student
// ===================================================================================================================

void displayStudentInfo(const Student& student) {

	// check if student ID is empty
	if (strlen(student.studentID) == 0) {
		cout << "[!] Error: Student ID is empty." << endl;
		return; // student ID is empty

	}

	// check if full name is empty
	if (strlen(student.fullName) == 0) {
		cout << "[!]Error: Full name is empty." << endl;
		return; // full name is empty

	}

	cout << "Student ID: " << student.studentID << endl;
	cout << "Full Name: " << student.fullName << endl;
	cout << "Programme: " << student.programme << endl;
	cout << "Year of Study: " << student.yearOfStudy << endl;
	cout << "CGPA: " << student.cgpa << endl;
	cout << "Contact Number: " << student.contactNumber << endl;

}

// ===================================================================================================================
// StudentArray struct:
// A simple container that contains 
// - a fixed array to store data (students)
// - a counter to track usage (count)
// ===================================================================================================================

struct StudentArray {
	Student students[maxStudents]; // act as database to store student records
	int count; // number of students currently stored in the array

};

// ===================================================================================================================
// checkStudentID() function:
// check for duplicate student ID 
// ===================================================================================================================

bool checkStudentID(const StudentArray& arr, const char* id) {
	for (int i = 0; i < arr.count; i++) {
		// compare the student id in the array with the given id
		if (strcmp(arr.students[i].studentID, id) == 0) {
			return true; // duplicate student id found

		}

	}

	return false; // no duplicate student id found

}

// ===================================================================================================================
// checkTPNumber() function:
// validates if the student ID follows the format TPXXXXXX
// must start with "TP" followed by exactly 6 digits
// valid example: TP076095
// ===================================================================================================================

bool checkTPNumber(const char* id) {
	// must be exactly 8 characters
	if (strlen(id) != 8) return false;

	// first 2 characters must be "TP"
	if (id[0] != 'T' || id[1] != 'P') return false;

	// remaining 6 characters must all be digits
	for (int i = 2; i < 8; i++) {
		if (!isdigit(id[i])) return false;
	}

	return true;
}

// ===================================================================================================================
// checkContactNumber() function:
// validates if the contact number follows Malaysian format XXX-XXXXXXXX
// prefix must be 3 digits, followed by a dash, followed by 7 or 8 digits
// valid examples: 011-12345678, 012-3456789
// ===================================================================================================================

bool checkContactNumber(const char* contact) {
	int len = strlen(contact);

	// total length must be 11 (3 + 1 + 7) or 12 (3 + 1 + 8)
	if (len < 11 || len > 12) return false;

	// first 3 characters must be digits
	for (int i = 0; i < 3; i++) {
		if (!isdigit(contact[i])) return false;
	}

	// 4th character must be a dash
	if (contact[3] != '-') return false;

	// remaining characters must all be digits
	for (int i = 4; i < len; i++) {
		if (!isdigit(contact[i])) return false;
	}

	return true;
}

// ===================================================================================================================
// checkCGPA() function:
// validates if the CGPA is between 0.0 and 4.0
// ===================================================================================================================

bool checkCGPA(double cgpa) {
	if (cgpa < 0.0 || cgpa > 4.0) {
		return false; // invalid CGPA

	}

	return true; // valid CGPA

}

// ===================================================================================================================
// Algorithm 1: Append New Student Record to End
// 
// How it works:
// 1. Check if there is enough space in the array to add a new student. 
//	  If the count of students has reached the maximum limit, display error message.
// 2. Check for duplicate student ID. If found, display error message.
// 3. Validate the CGPA of the new student. If CGPA is not between 0.0 and 4.0, display error message.
// 4. If all checks pass, add the new student to the end of the array and display success message. 
//
// Big-O Notation: O(1) constant time 
// This means that the time taken to add a new student does not increase as the number of students grows.
// This is because the new student is added directly to the end of the array without shifting other elements.
// ===================================================================================================================

bool appendToEnd(StudentArray& arr, const Student& newStudent) {
	// check if we have enough space to add a new student
	if (arr.count >= maxStudents) {
		cout << "[!] Error: Student array is full. Cannot add new student." << endl;
		return false; // failed to append

	}

	// check for duplicate student ID
	if (checkStudentID(arr, newStudent.studentID)) {
		cout << "[!] Error: Student ID " << newStudent.studentID << " already exists. " << endl;
		return false; // failed to append

	}

	// check if CGPA is valid
	if (!checkCGPA(newStudent.cgpa)) {
		cout << "[!] Error: Invalid CGPA. CGPA must be between 0.0 and 4.0." << endl;
		return false; // failed to append

	}

	// add the new student to the end of the array
	arr.students[arr.count] = newStudent;
	arr.count++; 

	// display success message
	cout << ">>> Student " << newStudent.fullName << " added successfully." << endl;

	return true; // successfully appended

}

// ===================================================================================================================
// Algorithm 2: Linear Search by Student ID
//
// How it works:
// 1. Loop through the array from the first element to the last.
// 2. Compare each student's ID with the target ID.
//    - If they match , return the index immediately.
// 3. - If the loop finishes without finding a match, return -1.
//
// Prerequisite: None. Array does not need to be sorted.
//
// Big-O Notation: O(n) linear time
// This means the time taken grows proportionally with the number of students.
// In the worst case, the target is at the last position or does not exist,
// so every record must be checked before a conclusion can be made.
// ===================================================================================================================

int linearSearchByID(const StudentArray& arr, const char* target) {
	// loop through every student in the array
	for (int i = 0; i < arr.count; i++) {
		// compare current student ID with target ID
		if (strcmp(arr.students[i].studentID, target) == 0) {
			return i; // target found

		}

	}

	return -1; // target not found

}

// ===================================================================================================================
// Algorithm 3: Linear Search by Name
//
// How it works:
// 1. Loop through the array from the first element to the last.
// 2. Compare each student's full name with the target name.
//    - If they match , return the index immediately.
// 3. If the loop finishes without finding a match, return -1.
//
// Prerequisite: None. Array does not need to be sorted.
//
// Big-O Notation: O(n) linear time
// This means the time taken grows proportionally with the number of students.
// In the worst case, the target is at the last position or does not exist,
// so every record must be checked before a conclusion can be made.
// ===================================================================================================================

int linearSearchByName(const StudentArray& arr, const char* target) {
	// loop through every student in the array
	for (int i = 0; i < arr.count; i++) {
		// compare current student's name with target name
		if (strcmp(arr.students[i].fullName, target) == 0) {
			return i; // target found

		}

	}

	return -1; // target not found

}

// ===================================================================================================================
// Algorithm 4: Insertion Sort By Student ID
// 
// How it works:
// 1. Loop through the array from the second element to the end of the array.
// 2. Store the current student as key
// 3. Compare the key's student ID with those before it.
// 4. Shift students right if their ID is lexicographically greater than the key's ID.
// 5. Place the key student in the correct position.
// 6. Display success message after sorting.
//
// Big-O Notation: O(n) best case, O(n²) worst case 
// Best case when the students are already sorted by student ID so no shifting is needed.
// Worst case when the students are sorted in reverse order so every student ID needs to be compared and shifted.
// ===================================================================================================================

void insertionSortByID(StudentArray& arr) {
	// loop the array from the second element
	for (int i = 1; i < arr.count; i++) {
		// store the current student as the key
		Student key = arr.students[i];
		int j = i - 1;

		// compare the key student with the students ID before it
		while (j >= 0 && strcmp(arr.students[j].studentID, key.studentID) > 0) {
			// shift students whose ID is greater than key's ID to the right
			arr.students[j + 1] = arr.students[j];
			j--;

		}

		// place the key student in the correct position
		arr.students[j + 1] = key;

	}

	// display success message
	cout << ">>> Students sorted by Student ID successfully." << endl;

}

// ===================================================================================================================
// Algorithm 5: Insertion Sort By Name
// 
// How it works:
// 1. Loop through the array from the second element to the end of the array.
// 2. Store the current student as key
// 3. Compare the key's full name with those before it.
// 4. Shift students right if their name is lexicographically greater than the key's name.
// 5. Place the key student in the correct position.
// 6. Display success message after sorting.
//
// Big-O Notation: O(n) best case, O(n²) worst case 
// Best case when the students are already sorted by student name so no shifting is needed.
// Worst case when the students are sorted in reverse order so every student name needs to be compared and shifted.
// ===================================================================================================================

void insertionSortByName(StudentArray& arr) {
	// loop the array from the second element
	for (int i = 1; i < arr.count; i++) {
		// store the current student as the key
		Student key = arr.students[i];
		int j = i - 1;

		// compare the key student with the students name before it
		while (j >= 0 && strcmp(arr.students[j].fullName, key.fullName) > 0) {
			// shift students whose full name is greater than key's ID to the right
			arr.students[j + 1] = arr.students[j];
			j--;

		}

		// place the key student in the correct position
		arr.students[j + 1] = key;

	}

	// display success message
	cout << ">>> Students sorted by name successfully." << endl;

}

// ===================================================================================================================
// Algorithm 6: Insertion Sort By CGPA (Ascending)
// 
// How it works:
// 1. Loop through the array from the second element to the end of the array.
// 2. Store the current student as key
// 3. Compare the key's cgpa with those before it.
// 4. Shift the students to the right if their CGPA is greater than the key student's CGPA.
// 5. Place the key student in the correct position.
// 6. Display success message after sorting.
//
// Big-O Notation: O(n) best case, O(n²) worst case 
// Best case when the students are already sorted by CGPA so no shifting is needed.
// Worst case when the students are sorted in reverse order so every student name needs to be compared and shifted.
// ===================================================================================================================

void insertionSortAscending(StudentArray& arr) {
	// loop the array from the second element
	for (int i = 1; i < arr.count; i++) {
		// store the current student as the key
		Student key = arr.students[i];
		int j = i - 1;

		// compare the key student with the students cgpa before it
		while (j >= 0 && arr.students[j].cgpa > key.cgpa) {
			// shift students whose cgpa is greater than key's ID to the right
			arr.students[j + 1] = arr.students[j];
			j--;

		}

		// place the key student in the correct position
		arr.students[j + 1] = key;

	}

	// display success message
	cout << ">>> Students sorted by CGPA (Ascending) successfully." << endl;

}



// ===================================================================================================================
// Algorithm 7: Insertion Sort By CGPA (Descending)
// 
// How it works:
// 1. Loop through the array from the second element to the end of the array.
// 2. Store the current student as key
// 3. Compare the key's cgpa with those before it.
// 4. Shift the students to the right if their CGPA is lesser than the key student's CGPA.
// 5. Place the key student in the correct position.
// 6. Display success message after sorting.
//
// Big-O Notation: O(n) best case, O(n²) worst case 
// Best case when the students are already sorted by CGPA so no shifting is needed.
// Worst case when the students are sorted in ascending order so every student name needs to be compared and shifted.
// ===================================================================================================================

void insertionSortDescending(StudentArray& arr) {
	// loop the array from the second element
	for (int i = 1; i < arr.count; i++) {
		// store the current student as the key
		Student key = arr.students[i];
		int j = i - 1;

		// compare the key student with the students cgpa before it
		while (j >= 0 && arr.students[j].cgpa < key.cgpa) {
			// shift students whose cgpa is less than key's ID to the right
			arr.students[j + 1] = arr.students[j];
			j--;

		}

		// place the key student in the correct position
		arr.students[j + 1] = key;

	}

	// display success message
	cout << ">>> Students sorted by CGPA (Descending) successfully." << endl;

}

// keep insertionSort() as an alias for ascending 
// used internally by performance test
void insertionSort(StudentArray& arr) {
	insertionSortAscending(arr);

}



// ===================================================================================================================
// Algorithm 8: Binary Search by Student ID
// 
// How it works:
// 1. Define lower and upper positions of the search range.
// 2. Loop until low index is less than or equal to high index.
// 3. Calculate the middle position of the current search range. 
// 4. Compare student ID at the middle position with the target ID.
//    - If they match (strcmp returns 0), walk left to find the first occurrence and return the index.
//    - If the middle ID is less than the target, continue searching in the right half.
//    - If the middle ID is greater than the target, continue searching in the left half.
// 
// Prerequisite: Array must be sorted by Student ID (call insertionSortByID first).
// 
// Big-O Notation: O(log n) logarithmic time
// This means that the time taken to search for a student by student ID does not increase much as the number of student grows.
// This is because binary search keeps dividing the search range in half, which reduces the number of 
// comparisons needed to find the target student ID.
// ===================================================================================================================

int binarySearchByID(const StudentArray& arr, const char* target) {
	// set low and high positions of the search 
	int low = 0;
	int high = arr.count - 1;

	// loop until low index is less than or equal to high index
	while (low <= high) {
		// calculate the middle position
		int middle = (low + high) / 2; 

		// compare the student ID at the middle position with the target ID
		int compare = strcmp(arr.students[middle].studentID, target);

		if (compare == 0) {
			// walk left to find the first occurrence
			while (middle > 0 && strcmp(arr.students[middle - 1].studentID, target) == 0) {
				middle--;

			}

			return middle; // target found

		} else if (compare < 0) {
			low = middle + 1; // search right half

		} else {
			high = middle - 1; // search left half

		}

	}

	return -1; // target not found

}



// ===================================================================================================================
// Algorithm 9: Binary Search by Name
// 
// How it works:
// 1. Define lower and upper positions of the search range.
// 2. Loop until low index is less than or equal to high index.
// 3. Calculate the middle position of the current search range. 
// 4. Compare full name at the middle position with the target ID.
//    - If they match, walk left to find the first occurrence and return the index.
//    - If the middle name is less than the target, continue searching in the right half.
//    - If the middle name is greater than the target, continue searching in the left half.
// 
// Prerequisite: Array must be sorted by name (call insertionSortByName first).
// 
// Big-O Notation: O(log n) logarithmic time
// This means that the time taken to search for a student by name does not increase much as the number of student grows.
// This is because binary search keeps dividing the search range in half, which reduces the number of 
// comparisons needed to find the target student name.
// ===================================================================================================================

int binarySearchByName(const StudentArray& arr, const char* target) {
	// set low and high positions of the search 
	int low = 0;
	int high = arr.count - 1;

	// loop until low index is less than or equal to high index
	while (low <= high) {
		// calculate the middle position
		int middle = (low + high) / 2;

		// compare the full name at the middle position with the target name
		int compare = strcmp(arr.students[middle].fullName, target);

		if (compare == 0) {
			// walk left to find the first occurrence
			while (middle > 0 && strcmp(arr.students[middle - 1].fullName, target) == 0) {
				middle--;

			}

			return middle; // target found, return the index

		} else if (compare < 0) {
			low = middle + 1; // search right half

		} else {
			high = middle - 1; // search left half

		}

	}

	return -1; // target not found

}

// ===================================================================================================================
// Algorithm 10: Delete by Student ID
// 
// How it works:
// 1. Use linear search to find the index of the target student ID in the array. 
//	  If not found, display error message.
// 2. Check if the array is empty. If empty, display error message.
// 3. Check if the target student ID is found. If not found, display error message.
// 4. Shift the elements left to fill the gap.
// 5. Display success message after deletion.
//
// Big-O Notation: O(n) linear time
// This means that the time taken to delete a student increases as the number of students increases.
// This is because the function may need to search through the array to find the target student ID before deleting it.
// ===================================================================================================================

void deleteByID(StudentArray& arr, const char* target) {
	// find the index of the target student using linear search
	int index = linearSearchByID(arr, target);

	// check if the array is empty
	if (arr.count == 0) {
		cout << "[!] Error: Student array is empty. Nothing to delete." << endl;
		return; // array is empty

	}

	// check if the target student id is found
	if (index == -1) {
		cout << "[!] Error: Student ID " << target << " not found. " << endl;
		return; // target not found

	}

	// shift the elements left to fill the gap
	for (int i = index;i < arr.count - 1; i++) {
		arr.students[i] = arr.students[i + 1];

	}

	arr.count--;

	// display success message
	cout << ">>> Student with ID " << target << " has been deleted successfully." << endl;

}

// ===================================================================================================================
// displayAllRecords() function:
// This function displays the details of all students in a table format.
// ===================================================================================================================

void displayAllRecords(const StudentArray& arr) {
	// check if there are any student records to display
	if (arr.count == 0) {
		cout << endl << ">>> No student records to display. Please select a dataset file to load. " << endl;
		return; // no records to display

	}

	cout << ">>> Total records: " << arr.count << endl;
	cout << endl << "------------------------------------------------------------------------------------" << endl;

	// print table header
	cout << left
		<< setw(8) << "No. "
		<< setw(12) << "Student ID"
		<< setw(25) << "Full Name"
		<< setw(12) << "Programme"
		<< setw(8) << "Year"
		<< setw(8) << "CGPA"
		<< setw(15) << "Contact"
		<< endl;

	cout << "------------------------------------------------------------------------------------" << endl;

	// loop through the array to display each student's details in a row
	for (int i = 0; i < arr.count; i++) {
		const Student& s = arr.students[i];

		cout << left
			<< setw(8) << i + 1
			<< setw(12) << s.studentID
			<< setw(25) << s.fullName
			<< setw(12) << s.programme
			<< setw(8) << s.yearOfStudy
			<< setw(8) << fixed << setprecision(2) << s.cgpa
			<< setw(15) << s.contactNumber
			<< endl;

	}

	cout << "------------------------------------------------------------------------------------" << endl;

}

// ===================================================================================================================
// loadFromCSV() function:
// Opens a CSV file and reads each student row one by one.
// Each row is stored into array using appendToEnd() function.
// 
// CSV file format:
// Student ID, Full Name, Programme, Year of Study, CGPA, Contact Number
// ===================================================================================================================

int loadFromCSV(StudentArray& arr, const string& filename) {
	// open the CSV file
	fstream file;
	file.open(filename, ios::in);

	// check if the file is opened
	if (!file.is_open()) {
		cout << "[!] Error: Could not open file " << filename << endl;
		return 0; // failed to load data

	}

	// read the file line by line
	string line;
	int loadedCount = 0;
	int skippedCount = 0;
	bool isFirstLine = true;

	// read the file line by line
	while (getline(file, line)) {

		// check if the line is first line 
		if (isFirstLine) {
			isFirstLine = false;
			continue; // skip header row

		}

		// check if the line is empty
		if (line.empty()) {
			continue; // skip empty line

		}

		// split the line using comma 
		stringstream ss(line);
		string studentID, fullName, programme, yearOfStudy, cgpa, contactNumber;

		getline(ss, studentID, ',');
		getline(ss, fullName, ',');
		getline(ss, programme, ',');
		getline(ss, yearOfStudy, ',');
		getline(ss, cgpa, ',');
		getline(ss, contactNumber, ',');

		// check if there is missing required fields
		if (studentID.empty() || fullName.empty() || programme.empty() || cgpa.empty()) {
			cout << "[!]Warning: Skipping line with missing fields: " << line << endl;
			skippedCount++;
			continue; // skip line 

		}

		// create a new student object
		Student student;
		strncpy(student.studentID, studentID.c_str(), sizeof(student.studentID) - 1);
		strncpy(student.fullName, fullName.c_str(), sizeof(student.fullName) - 1);
		strncpy(student.programme, programme.c_str(), sizeof(student.programme) - 1);
		student.yearOfStudy = stoi(yearOfStudy); // convert from string to integer
		student.cgpa = stof(cgpa); // convert from string to float
		strncpy(student.contactNumber, contactNumber.c_str(), sizeof(student.contactNumber) - 1);

		// add the student into array
		if (appendToEnd(arr, student)) {
			loadedCount++; // increase loaded count if student is added

		} else {
			skippedCount++; // increase skipped count if student is not added
			// display warning message if there is error
			cout << "[!] Warning: Skipping line due to validation error: " << line << endl;

		}

	}
		// close file
		file.close();

		// display summary
		cout << endl << ">>> Loaded " << loadedCount << " students from " << filename << endl;
		cout << ">>> Skipped " << skippedCount << " rows." << endl;

		return loadedCount; // return the number of students loaded

}

// ===================================================================================================================
// loadProgrammesFromCSV() function:
// reads programmes.csv and stores each row into the ProgrammeArray
// ===================================================================================================================
void loadProgrammesFromCSV(ProgrammeArray& pArr, const string& filename) {
	// open the CSV file
	fstream file;
	file.open(filename, ios::in);

	// check if the file is opened
	if (!file.is_open()) {
		cout << "[!] Warning: Could not open " << filename << ". Programme dropdown will not be available." << endl;
		return;
	}

	string line;
	bool isFirstLine = true;

	// read the file line by line
	while (getline(file, line)) {
		// skip the header row
		if (isFirstLine) {
			isFirstLine = false;
			continue;
		}

		// skip empty lines
		if (line.empty()) {
			cout << "[!] Warning: Skipping empty line in " << filename << endl;
			continue;
		}

		// split the line using comma
		stringstream ss(line);
		string code, name, faculty, duration;

		getline(ss, code, ',');
		getline(ss, name, ',');
		getline(ss, faculty, ',');
		getline(ss, duration, ',');

		// check for missing required fields
		if (code.empty() || name.empty()) {
			cout << "[!] Warning: Skipping line with missing fields: " << line << endl;
			continue;
		}

		if (pArr.count >= maxProgrammes) {
			cout << "[!] Warning: Maximum number of programmes reached." << endl;
			break;
		}

		// create a new Programme object and store the data
		Programme programme;
		strncpy(programme.code, code.c_str(), sizeof(programme.code) - 1);
		strncpy(programme.name, name.c_str(), sizeof(programme.name) - 1);
		strncpy(programme.faculty, faculty.c_str(), sizeof(programme.faculty) - 1);
		programme.durationYears = duration.empty() ? 0 : stoi(duration);

		pArr.programmes[pArr.count++] = programme;
	}

	// close the file and display summary
	file.close();
	cout << ">>> Loaded " << pArr.count << " programmes from " << filename << endl;
}

// ===================================================================================================================
// selectProgramme() function:
// shows a numbered list of programmes and returns the chosen programme code
// returns false if user cancels
// ===================================================================================================================
bool selectProgramme(const ProgrammeArray& pArr, char* outCode, int& outDuration) {
	// check if programme list is empty
	if (pArr.count == 0) {
		cout << "[!] No programme list loaded. Please enter programme code manually: ";
		cin.getline(outCode, 10);
		outDuration = 0;
		return true;
	}

	cout << endl << "  Select Programme:" << endl;

	// display the list of programmes
	for (int i = 0; i < pArr.count; i++) {
		cout << "  " << right << setw(3) << i + 1 << ". "
			<< left << setw(8) << pArr.programmes[i].code
			<< pArr.programmes[i].name << endl;
	}

	cout << "   " << pArr.count + 1 << ". Back to main menu" << endl;

	// prompt user for choice
	int choice;
	while (true) {
		cout << "  Enter choice (1-" << pArr.count + 1 << "): ";
		cin >> choice;
		cin.ignore();

		if (choice == pArr.count + 1) return false; // user cancelled

		if (choice >= 1 && choice <= pArr.count) {
			strncpy(outCode, pArr.programmes[choice - 1].code, 9);
			outDuration = pArr.programmes[choice - 1].durationYears;
			return true;
		}

		cout << "  [!] Invalid choice. Please try again." << endl;
	}
}

// ===================================================================================================================
// runEdgeCaseTest() function:
// This function make sure the program handles errors and boundaries correctly.
// ===================================================================================================================

void runEdgeCaseTest() {
	// display edge case test header
	cout << "====================================================================================" << endl;
	cout << "   Running Edge Case Test......   " << endl;
	cout << "====================================================================================" << endl;

	StudentArray* arr = new StudentArray();

	cout << endl << "---- Edge Case 1: Search on empty array ----" << endl;
	int result = binarySearchByID(*arr, "TP000001");
	if (result == -1) {
		cout << ">>> Test Passed. Binary search on empty array returned -1 as expected." << endl;
	}

	cout << endl << "---- Edge Case 2: Insert CGPA = 4.00 (maximum boundary) ----" << endl;
	Student student1 = {"TP000001", "Testing Student 1", "CT103", 1, 4.00, "010-3914368" };
	appendToEnd(*arr, student1);

	cout << endl << "---- Edge Case 3: Insert CGPA = 0.00 (minimum boundary) ----" << endl;
	Student student2 = {"TP000002", "Testing Student 2", "CT103", 1, 0.00, "011-69832913" };
	appendToEnd(*arr, student2);

	cout << endl << "---- Edge Case 4: Linear search ID for non-existent Student ID ----" << endl;
	int idLinearNotFound = linearSearchByID(*arr, "TP999999");
	if (idLinearNotFound == -1) {
		cout << ">>> Test Passed. Search for non-existent student returned -1 as expected." << endl;

	}

	cout << endl << "---- Edge Case 5: Linear search by Name for non-existent student name ----" << endl;
	int nameLinearNotFound = linearSearchByName(*arr, "Non-existent Student");
	if (nameLinearNotFound == -1) {
		cout << ">>> Test Passed. Search for non-existent student returned -1 as expected." << endl;

	}

	cout << endl << "---- Edge Case 6: Binary search ID for non-existent Student ID ----" << endl;
	insertionSort(*arr);
	int idBinaryNotFound = binarySearchByID(*arr, "TP999999");
	if (idBinaryNotFound == -1) {
		cout << ">>> Test Passed. Search for non-existent student returned -1 as expected." << endl;

	}

	cout << endl << "---- Edge Case 7: Binary search by Name for non-existent student name ----" << endl;
	insertionSort(*arr);
	int nameBinaryNotFound = binarySearchByName(*arr, "Non-existent Student");
	if (nameBinaryNotFound == -1) {
		cout << ">>> Test Passed. Search for non-existent student returned -1 as expected." << endl;

	}

	cout << endl << "---- Edge Case 8: Delete a record twice ----" << endl;
	deleteByID(*arr, "TP000002");  // first delete should succeed
	deleteByID(*arr, "TP000002");  // second delete should show error

	cout << endl << "---- Edge Case 9: Insert 1 record, delete it, then display ----" << endl;
	Student student3 = {"TP000003", "Testing Student 3", "CT101", 1, 2.50, "011-3936706" };
	appendToEnd(*arr, student3);
	deleteByID(*arr, "TP000003");
	cout << endl;
	displayAllRecords(*arr);

	delete arr;

	cout << endl << ">>> Edge Case Testing Completed " << endl;
	cout << "====================================================================================" << endl;
		
}

// ===================================================================================================================
// runPerformanceTest() function:
// This function is used to measure the execution time of the four operations:
// - Append to End 
// - Linear Search
// - Insertion Sort
// - Binary Search 
// - Delete by Value
// ===================================================================================================================

void runPerformanceTest() {

	// define the four CSV files in an array for easy access
	const char* files[] = {
		"students_500.csv",
		"students_2000.csv",
		"students_8000.csv",
		"students_30000.csv"
	};

	// run edge case test to check for any validation error
	runEdgeCaseTest();

	// display performance test header
	cout << endl << "====================================================================================" << endl;
	cout << "   Performance Test for Student Record Management System   " << endl;
	cout << "====================================================================================" << endl;

	// display dataset to users
	cout << endl << "Select a dataset to test: " << endl;
	cout << "  1. students_500.csv" << endl;
	cout << "  2. students_2000.csv" << endl;
	cout << "  3. students_8000.csv" << endl;
	cout << "  4. students_30000.csv" << endl;
	cout << "  5. Back to main menu" << endl;

	int choice;

	while (true) {
		cout << "Enter your choice (1-5): ";
		cin >> choice;
		cin.ignore();

		if (choice >= 1 && choice <= 5) {
			break;
		}

		cout << "[!] Error: Invalid choice. Please enter a number between 1 and 5." << endl;

	}

	if (choice == 5) {
		cout << "Returning to main menu..." << endl;
		return; // exit runPerformanceTest() and return to main menu
	}

	// map choice to the correct file
	int index = choice - 1;

	// ---- Load Data from CSV ----
	cout << endl << ">>> Dataset: " << files[index] << endl;

	StudentArray* arr = new StudentArray();
	loadFromCSV(*arr, files[index]);

	// display success message
	cout << endl << ">>> All data from " << files[index] << " has been loaded successfully. " << endl;

	// check if data is loaded successfully
	if (arr->count == 0) {
		cout << "[!] Error: No data loaded from " << files[index] << ". Skipping performance test for this dataset." << endl;
		delete arr; // free memory allocated for the array
		return; 

	}

	// ---- Display all Records ----
	auto start1 = high_resolution_clock::now();
	displayAllRecords(*arr);
	auto end1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(end1 - start1);
		
	// ---- Append to End ----
	// insert 10 new records
	Student newStudent[10] = {
		{"TP076095", "Cheong Teng Wei", "CT103", 4, 3.70, "011-69832913"},
		{"TP076693", "Lim Rui Yuan", "CS102", 2, 3.45, "012-3456789"},
		{"TP075952", "Chong Jia Huey", "CT106", 2, 3.50, "013-2223344"},
		{"TP076534", "Siew Sheng Yong", "BM103", 3, 3.60, "014-5556677"},
		{"TP075892", "Ng Kai Kit", "CT103", 2, 3.90, "016-8889999"},
		{"TP076274", "Lim Hong Feng", "CS101", 1, 3.5, "017-1234567"},
		{"TP076247", "Chow Chun Seng", "CT103", 4, 3.95, "018-7654321"},
		{"TP076371", "Ethan Tan Zheng Nan", "CT103", 4, 3.70, "019-1122334"},
		{"TP076118", "Leong Yuan Kang", "CT104", 4, 3.65, "010-9988776"},
		{"TP075883", "Carrie Yap Liu Qing", "CT104", 4, 3.52, "011-5566778"}
	};


	auto start2 = high_resolution_clock::now(); // start time
	for (int i = 0; i < 10; i++) {
		appendToEnd(*arr, newStudent[i]); // perform append operation

	} 
	auto end2 = high_resolution_clock::now(); // end time
	auto duration2 = duration_cast<microseconds>(end2 - start2); // calculate duration in microseconds

	// ---- Linear Search by Student ID
	int linearIDCount = arr->count; // snapshot count
	auto duration3 = duration_cast<microseconds>(microseconds(0));

	if (linearIDCount > 0) {
		// search for 3 different student IDs: first, middle and last student
		const char* linearIDTargets[3] = {
			arr->students[0].studentID,
			arr->students[linearIDCount / 2].studentID,
			arr->students[linearIDCount - 1].studentID
		};

		auto start3 = high_resolution_clock::now(); // start time

		// run each target 1000 times to get a measurable average time
		for (int i = 0; i < 3; i++) {
			for (int repeat = 0; repeat < 1000; repeat++) {
				linearSearchByID(*arr, linearIDTargets[i]);
			}
		}

		auto end3 = high_resolution_clock::now(); // end time
		duration3 = duration_cast<microseconds>(end3 - start3);

	} 

	// ---- Linear Search by Name ----
	int linearNameCount = arr->count; // snapshot count
	auto duration4 = duration_cast<microseconds>(microseconds(0));

	if (linearNameCount > 0) {
		// search for 3 different names: first, middle and last student
		const char* linearNameTargets[3] = {
			arr->students[0].fullName,
			arr->students[linearNameCount / 2].fullName,
			arr->students[linearNameCount - 1].fullName
		};

		auto start4 = high_resolution_clock::now(); // start time

		// run each target 1000 times to get a measurable average time
		for (int i = 0; i < 3; i++) {
			for (int repeat = 0; repeat < 1000; repeat++) {
				linearSearchByName(*arr, linearNameTargets[i]);
			}
		}

		auto end4 = high_resolution_clock::now(); // end time
		duration4 = duration_cast<microseconds>(end4 - start4);

	}

	// ---- Insertion Sort ----
	auto start5 = high_resolution_clock::now(); // start time
	insertionSort(*arr); // perform insertion sort operation
	auto end5 = high_resolution_clock::now(); // end time
	auto duration5 = duration_cast<microseconds>(end5 - start5); // calculate duration in microseconds
		

	// ---- Binary Search by Student ID ----
	insertionSortByID(*arr); // sort by student ID first

	int binaryIdCount = arr->count; // snapshot count after sort
	auto duration6 = duration_cast<microseconds>(microseconds(0));

	if (binaryIdCount > 0) {
		// search for 3 different student ids: first, middle and last student
		const char* binaryIdTargets[3] = {
			arr->students[0].studentID,
			arr->students[binaryIdCount / 2].studentID,
			arr->students[binaryIdCount - 1].studentID
		};

		auto start6 = high_resolution_clock::now(); // start time

		// run each target 1000 times to get a measurable average time
		for (int i = 0; i < 3; i++) {
			for (int repeat = 0; repeat < 1000; repeat++) {
				binarySearchByID(*arr, binaryIdTargets[i]);
			}
		}

		auto end6 = high_resolution_clock::now(); // end time
		duration6 = duration_cast<microseconds>(end6 - start6); // calculate duration in microseconds
	}

	// ---- Binary Search by Name ----
	insertionSortByName(*arr); // sort by name first

	int binaryNameCount = arr->count; // snapshot count after sort
	auto duration7 = duration_cast<microseconds>(microseconds(0));

	if (binaryNameCount > 0) {
		// search for 3 different names: first, middle and last student
		const char* binaryNameTargets[3] = {
			arr->students[0].fullName,
			arr->students[binaryNameCount / 2].fullName,
			arr->students[binaryNameCount - 1].fullName

		};

		auto start7 = high_resolution_clock::now(); // start time

		// run each target 1000 times to get a measurable average time
		for (int i = 0; i < 3; i++) {
			for (int repeat = 0; repeat < 1000; repeat++) {
				binarySearchByName(*arr, binaryNameTargets[i]);

			}
		}

		auto end7 = high_resolution_clock::now(); // end time
		duration7 = duration_cast<microseconds>(end7 - start7); // calculate duration in microseconds

	}

	// ---- Delete by Value ----
	// delete the 10 students interted above and calculate the time
	const char* deleteStudent[10] = {
		"TP076095",
		"TP076693",
		"TP075952",
		"TP076534",
		"TP075892",
		"TP076274",
		"TP076247",
		"TP076371",
		"TP076118",
		"TP075883"
	};

	auto start8 = high_resolution_clock::now(); // start time
	for (int i = 0; i < 10; i++) {
		deleteByID(*arr, deleteStudent[i]); // perform delete operation

	}

	auto end8 = high_resolution_clock::now(); // end time
	auto duration8 = duration_cast<microseconds>(end8 - start8); // calculate duration in microseconds

	// display summary of performance test
	cout << endl << "------------------------------------------------------------------------------------" << endl;
	cout << "   SUMMARY OF PERFORMANCE TEST (IN MICROSECONDS)  " << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "Display All Records          : " << duration1.count() << " microseconds" << endl;
	cout << "Append New Student to End    : " << duration2.count() / 10.0 << " microseconds (average of 10 inserts)" << endl;
	cout << "Linear Search by Student ID  : " << duration3.count() / 3000.0 << " microseconds (average of 3 targets x 1000 runs)" << endl;
	cout << "Linear Search by Name        : " << duration4.count() / 3000.0 << " microseconds (average of 3 targets x 1000 runs)" << endl;
	cout << "Insertion Sort by CGPA       : " << duration5.count() << " microseconds" << endl; 
	cout << "Binary Search by Student ID  : " << duration6.count() / 3000.0 << " microseconds (average of 3 targets x 1000 runs)" << endl;
	cout << "Binary Search by Name        : " << duration7.count() / 3000.0 << " microseconds (average of 3 targets x 1000 runs)" << endl;
	cout << "Delete by Student ID         : " << duration8.count() / 10.0 << " microseconds (average of 10 deletes)" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;

	delete arr; // free memory allocated for the array

	// display completion message 
	cout << endl << ">>> Performance test completed for the selected datasets." << endl;
	cout << "====================================================================================" << endl;

}

// ===================================================================================================================
// menu() function:
// This function displays the menu options to the user and prompts for input.
// ===================================================================================================================

void menu() {
	cout << endl << "====================================================================================" << endl;
	cout << "   Welcome to the Student Record Management System!   " << endl;
	cout << "====================================================================================" << endl;
	cout << "1. Load a dataset from .csv file" << endl;
	cout << "2. Display all records" << endl;
	cout << "3. Add a new student" << endl;
	cout << "4. Linear search by Student ID or Name" << endl;
	cout << "5. Sort students by CGPA" << endl;
	cout << "6. Binary search by Student ID or Name" << endl;
	cout << "7. Delete a student by Student ID" << endl;
	cout << "8. Run performance test" << endl;
	cout << "9. Exit program" << endl;
	cout << "====================================================================================" << endl;
	cout << "Please select an option (1-9): ";
}

// ===================================================================================================================
// main() function:
// This is the entry point of the program. It displays the menu and handles user input.
// ===================================================================================================================
int main() {
	// create an instance of StudentArray to store student records
	StudentArray* arr = new StudentArray();
	int choice = 0;

	// load programmes from CSV file
	ProgrammeArray pArr = {};
	loadProgrammesFromCSV(pArr, "programmes.csv");

	// loop until user chooses to exit
	while (true) {
		// display menu
		menu();

		// get user input
		cin >> choice;
		cin.ignore(); // ignore newline character after integer input

		switch (choice) {
			// ---- Load data from CSV file ----
		case 1:
		{
			// display the dataset options 
			cout << "Select a dataset to load:" << endl;
			cout << "  1. students_500.csv" << endl;
			cout << "  2. students_2000.csv" << endl;
			cout << "  3. students_8000.csv" << endl;
			cout << "  4. students_30000.csv" << endl;
			cout << "  5. Back to main menu" << endl;

			int choice;
			string filename;

			// map the choice to the corresponding dataset
			while (true) {
				cout << "Enter your choice (1-5): ";
				cin >> choice;
				cin.ignore(); // ignore newline character after integer input

				if (choice == 1) {
					filename = "students_500.csv";
					break;

				}
				else if (choice == 2) {
					filename = "students_2000.csv";
					break;

				}
				else if (choice == 3) {
					filename = "students_8000.csv";
					break;

				}
				else if (choice == 4) {
					filename = "students_30000.csv";
					break;

				} 
				else if (choice == 5) {
					break;
				}
				else {
					cout << "[!] Invalid choice. Please enter a number between 1 and 5." << endl;

				}
			}

			if (choice == 5) {
				break; // back to main menu
			}

			// load the dataset based on the choice
			loadFromCSV(*arr, filename);
			break;
		}

		// ---- Display all records ----
		case 2:
		{
			displayAllRecords(*arr);
			break;

		}

		// ---- Add a new student ----
		case 3:
		{
			Student newStudent = {};

			cout << endl;
			while (true) {
				cout << "  " << left << setw(20) << "Student ID" << " : ";
				cin.getline(newStudent.studentID, sizeof(newStudent.studentID));

				if (checkTPNumber(newStudent.studentID)) {
					break;
				}

				cout << "  [!] Invalid format. Please use TPXXXXXX (e.g. TP012345)" << endl;
			}

			cout << "  " << left << setw(20) << "Student Name" << " : ";
			cin.getline(newStudent.fullName, sizeof(newStudent.fullName));

			// dynamic programme selection
			int programmeDuration = 0;
			bool selected = selectProgramme(pArr, newStudent.programme, programmeDuration);
			if (!selected) {
				cout << ">>> Add student cancelled." << endl;
				break;
			}

			cout << "  " << left << setw(20) << "Selected Programme" << " : " << newStudent.programme << endl;

			// auto-fill year of study from programme duration
			if (programmeDuration > 0) {
				newStudent.yearOfStudy = programmeDuration;
				cout << "  " << left << setw(20) << "Year of Study" << " : " << newStudent.yearOfStudy << endl;
			}
			else {
				cout << "  " << left << setw(20) << "Year of Study" << " : ";
				cin >> newStudent.yearOfStudy;
				cin.ignore();
			}

			while (true) {
				cout << "  " << left << setw(20) << "CGPA" << " : ";

				// validate CGPA input
				if (cin >> newStudent.cgpa) {
					cin.ignore();

					// validate CGPA range
					if (checkCGPA(newStudent.cgpa)) {
						break;
					}
					cout << "  [!] Invalid CGPA. Please enter a value between 0.0 and 4.0." << endl;
				}
				else {
					cin.clear();          // clear the failed state
					cin.ignore(1000, '\n'); // flush the bad input from the buffer
					cout << "  [!] Invalid input. Please enter a number between 0.0 and 4.0." << endl;
				}
			}

			while (true) {
				cout << "  " << left << setw(20) << "Contact Number" << " : ";
				cin.getline(newStudent.contactNumber, sizeof(newStudent.contactNumber));

				// validate contact number format
				if (checkContactNumber(newStudent.contactNumber)) {
					break;
				}

				cout << "  [!] Invalid format. Please use XXX-XXXXXXXX (e.g. 011-12345678)" << endl;
			}

			cout << endl;
			appendToEnd(*arr, newStudent);
			break;
		}

		// ---- Linear search by Student ID or Name ----
		case 4:
		{
			// check if there are any student records to search
			if (arr->count == 0) {
				cout << "[!]Error: No student records to search." << endl;
				break;
			}

			// prompt user to choose search type
			cout << "Linear Search Options: " << endl;
			cout << "1. Search by Student ID" << endl;
			cout << "2. Search by Name" << endl;
			cout << "3. Back to main menu" << endl;

			int searchChoice;
			while (true) {
				cout << "Enter your choice (1-3): ";
				cin >> searchChoice;
				cin.ignore();

				if (searchChoice >= 1 && searchChoice <= 3) {
					break;

				}

				cout << "[!] Error: Invalid choice. Please enter 1, 2 or 3." << endl;
			}

			if (searchChoice == 3) {
				break; // back to main menu

			}

			if (searchChoice == 1) {
				// ---- Linear Search by Student ID ----
				char targetID[20];
				cout << "Enter Student ID to search: ";
				cin.getline(targetID, sizeof(targetID));

				int index = linearSearchByID(*arr, targetID);

				if (index != -1) {
					cout << endl << ">>> First match at index " << index << ":" << endl;
					// display all students with the same Student ID
					for (int i = index; i < arr->count; i++) {
						if (strcmp(arr->students[i].studentID, targetID) == 0) {
							cout << "------------------------------------------------------------------------------------" << endl;
							displayStudentInfo(arr->students[i]);

						}
						else {
							break; // stop when ID no longer matches

						}
					}
				}
				else {
					cout << ">>> Error: No student found with Student ID " << targetID << endl;
					cout << "------------------------------------------------------------------------------------" << endl;
				}
			}
			else {
				// ---- Linear Search by Name ----
				char targetName[50];
				cout << "Enter full name: ";
				cin.getline(targetName, sizeof(targetName));

				int index = linearSearchByName(*arr, targetName);

				if (index != -1) {
					cout << endl << ">>> First match at index " << index << ":" << endl;
					// display all students with the same name
					for (int i = index; i < arr->count; i++) {
						if (strcmp(arr->students[i].fullName, targetName) == 0) {
							cout << "------------------------------------------------------------------------------------" << endl;
							displayStudentInfo(arr->students[i]);

						}
						else {
							break; // stop when name no longer matches

						}
					}
				}
				else {
					cout << "[!] Error: No student found with name " << targetName << endl;
					cout << "------------------------------------------------------------------------------------" << endl;

				}
			}

			break;

		}

		// ---- Sort students by CGPA ----
		case 5:
		{
			// check if there are any student records to sort
			if (arr->count == 0) {
				cout << "[!] Error: No student records to sort." << endl;
				break;

			}

			// prompt user to choose for ascending and descending
			cout << "Sort Options:" << endl;
			cout << "  1. Ascending " << endl;
			cout << "  2. Descending " << endl;
			cout << "  3. Back to main menu" << endl;

			int sortChoice;
			while (true) {
				cout << "Enter your choice (1-3): ";
				cin >> sortChoice;
				cin.ignore();

				if (sortChoice >= 1 && sortChoice <= 3) {
					break;

				}

				cout << "[!] Error: Invalid choice. Please enter 1, 2 or 3." << endl;
			}

			if (sortChoice == 1) {
				insertionSortAscending(*arr);

			}
			else if (sortChoice == 2 ) {
				insertionSortDescending(*arr);

			}
			else if (sortChoice == 3) {
				break;
			}
			else {
				cout << "[!] Error: Invalid choice. Please enter 1 or 2." << endl;
			}

			cout << "Do you want to display all records? (1 = Yes, 2 = No): ";
			int displayChoice;
			cin >> displayChoice;
			cin.ignore();

			if (displayChoice == 1) {
				displayAllRecords(*arr);
			}

			break;

		}

		// ---- Binary search by Student ID or Name ----
		case 6:
		{
			// check if there are any student records to search
			if (arr->count == 0) {
				cout << "[!] Error: No student records to search." << endl;
				break;

			}

			// prompt user to choose search type
			cout << "Binary Search Options: " << endl;
			cout << "1. Search by Student ID" << endl;
			cout << "2. Search by Name" << endl;
			cout << "3. Back to main menu" << endl;

			int searchChoice;
			while (true) {
				cout << "Enter your choice (1-3): ";
				cin >> searchChoice;
				cin.ignore();

				if (searchChoice >= 1 && searchChoice <= 3) {
					break;

				}

				cout << "[!] Error: Invalid choice. Please enter 1, 2 or 3." << endl;
			} 

			if (searchChoice == 1) {
				// ---- Binary Search by Student ID ----
				char targetID[20];
				cout << ">>> Note: The array will be sorted by Student ID before performing binary search." << endl;
				insertionSortByID(*arr);

				cout << "Enter Student ID to search: ";
				cin.getline(targetID, sizeof(targetID));

				int index = binarySearchByID(*arr, targetID);

				if (index != -1) {
					cout << "First match at index " << index << ":" << endl;

					// display all students with the same Student ID
					for (int i = index; i < arr->count; i++) {
						if (strcmp(arr->students[i].studentID, targetID) == 0) {
							cout << "------------------------------------------------------------------------------------" << endl;
							displayStudentInfo(arr->students[i]);

						}
						else {
							break; // stop when ID no longer matches

						}
					}

				}
				else {
					cout << "[!] Error: No student found with Student ID " << targetID << endl;
					cout << "------------------------------------------------------------------------------------" << endl;

				}

			}
			else if (searchChoice ==2) {
				// ---- Binary Search by Name ----
				char targetName[50];
				cout << ">>> Note: The array will be sorted by Name before performing binary search." << endl;
				insertionSortByName(*arr);

				cout << "Enter full name: ";
				cin.getline(targetName, sizeof(targetName));

				int index = binarySearchByName(*arr, targetName);

				if (index != -1) {
					cout << "First match at index " << index << ":" << endl;

					// display all students with the same name
					for (int i = index; i < arr->count; i++) {
						if (strcmp(arr->students[i].fullName, targetName) == 0) {
							cout << "------------------------------------------------------------------------------------" << endl;
							displayStudentInfo(arr->students[i]);

						}
						else {
							break; // stop when name no longer matches

						}
					}

				}
				else if (searchChoice == 3) {
					break; // back to main menu

				}
				else {
					cout << "[!] Error: No student found with name " << targetName << endl;
					cout << "------------------------------------------------------------------------------------" << endl;

				}

			}



			break;

		}

		// ---- Delete a student by student ID ----
		case 7:
		{
			char target[20];
			cout << "Enter student ID to delete: ";
			cin.getline(target, sizeof(target));
			deleteByID(*arr, target);
			break;

		}

		// ---- Run performance test ----
		case 8:
		{
			runPerformanceTest();
			break;

		}

		// ---- Exit program ----
		case 9:
		{
			cout << "Thank you for using the Student Record Management System!" << endl;
			cout << "Exiting program..." << endl;
			return 0; // exit the program

		}

		// ---- Invalid option ----
		default:
		{
			cout << "[!] Error: Invalid option. Please select a number between 1 and 9." << endl;
			break;

		}

		}
	}
}