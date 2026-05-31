 //===================================================================================================================
 //Module Code: CT077-3-2-DSTR (Data Structures)
 //System Name: Student Record Management System
 //Intake Code: APD2F2511CS(DA)
 //Lecturer Name: Dr. Masrina Akmal Binti Salleh
 //Student Name: Cheong Teng Wei
 //TP Number: TP076095
 //Hand Out Date: 11th May 2026 (Week 4)
 //Hand In Date: 29th June 2026 (Week 9)
 //Group: 9
 //
 //Data Structure Used: Array
 //Algorithms Used: 
 //1. Append to End
 //2. Delete by Value
 //3. Update by Value
 //4. Binary Search
 //5. Insertion Sort
 //===================================================================================================================

#define _CRT_SECURE_NO_WARNINGS // removes the warning of strcpy

// include necesssary header files
#include <iostream> // for input/output operations
#include <cstring> // for string manipulation
#include <fstream> // for file handling
#include <string> // for string class
#include <sstream> // for string stream operations
#include <chrono> // for measuring execution time

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
// displayStudentInfo() function:
// print the details of a student
// ===================================================================================================================
void displayStudentInfo(const Student& student) {

	// check if student ID is empty
	if (strlen(student.studentID) == 0) {
		cout << "Error: Student ID is empty." << endl;
		return; // student ID is empty

	}

	// check if full name is empty
	if (strlen(student.fullName) == 0) {
		cout << "Error: Full name is empty." << endl;
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
// Algorithm 1: Append to End
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
		cout << "Error: Student array is full. Cannot add new student." << endl;
		return false; // failed to append

	}

	// check for duplicate student ID
	if (checkStudentID(arr, newStudent.studentID)) {
		cout << "Error: Student ID " << newStudent.studentID << " already exists. " << endl;
		return false; // failed to append

	}

	// check if CGPA is valid
	if (!checkCGPA(newStudent.cgpa)) {
		cout << "Error: Invalid CGPA. CGPA must be between 0.0 and 4.0." << endl;
		return false; // failed to append

	}

	// add the new student to the end of the array
	arr.students[arr.count] = newStudent;
	arr.count++; 

	// display success message
	cout << "Student " << newStudent.fullName << " added successfully." << endl;

	return true; // successfully appended
}



// ===================================================================================================================
// Algorithm 2: Delete by Value
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

// find the index of the target student ID 
int linearSearch(Student arr[], int n, const char* target) {
	for (int i = 0; i < n; i++) {
		// compare the student id with the target student id
		if (strcmp(arr[i].studentID, target) == 0) {
			return i; // target found

		}
	}

	return -1; // target not found
}

void deleteByValue(StudentArray& arr, const char* target) {
	// find the index of the target student using linear search
	int index = linearSearch(arr.students, arr.count, target);

	// check if the array is empty
	if (arr.count == 0) {
		cout << "Error: Student array is empty. Nothing to delete." << endl;
		return; // array is empty

	}

	// check if the target student id is found
	if (index == -1) {
		cout << "Error: Student ID " << target << " not found. " << endl;
		return; // target not found

	}

	// shift the elements left to fill the gap
	for (int i = index;i < arr.count - 1; i++) {
		arr.students[i] = arr.students[i + 1];

	}

	arr.count--;

	// display success message
	cout << "Student with ID " << target << " has been deleted successfully." << endl;

}



// ===================================================================================================================
// Algorithm 3: Binary Search
// 
// How it works:
// 1. Define lower and upper positions of the search range.
// 2. Loop until low index is less than or equal to high index.
// 3. Calculate the middle position of the current search range. 
// 4. Compare CGPA at the middle position with the target CGPA.
// 5. Calculate the difference between the middle student's CGPA and the target CGPA.
//    - If the difference is within 0.0001, the CGPA is considered a match.
//      Move left to find the first occurrence of the matching CGPA and return the index.
//	  - If the middle CGPA is smaller than the target, continue searching in the right half.
//    - If the middle CGPA is larger than the target, continue searching in the left half.
// 
// Note: Direct equality (==) is avoided for CGPA comparison because CGPA is stored as a
// double and floating point values can have tiny precision errors internally.
// To fix the floating point issue, we can check the difference between two CGPA values;
// If is smaller than 0.0001, it is close enough to be equal because CGPA only has 2 decimal places.
// 
// Big-O Notation: O(log n) logarithmic time
// This means that the time taken to search for a student by CGPA does not increase much as the number of student grows.
// This is because binary search keeps dividing the search range in half, which reduces the reduces the number of 
// comparisons needed to find the target CGPA.
// ===================================================================================================================

int binarySearch(const StudentArray& arr, double target) {
	// set low and high positions of the search 
	int low = 0;
	int high = arr.count - 1;

	// loop until low index is less than or equal to high index
	while (low <= high) {
		// calculate the middle position
		int middle = (low + high) / 2; 

		// // calculate the difference between the current student's CGPA and the target CGPA
		double difference = arr.students[middle].cgpa - target;

		// fix floating point issue: check if difference is close enough to zero
		if (difference > -0.0001 && difference < 0.0001) {
			// walk left to find the first occurence 
			while (middle > 0 && arr.students[middle - 1].cgpa - target > -0.0001
				&& arr.students[middle - 1].cgpa - target < 0.0001) {
				middle--;

			}
			return middle; // return the index of first student with target CGPA

		  // check if the middle student's CGPA is less than the target CGPA
		} else if (arr.students[middle].cgpa < target) { 
			low = middle + 1; // continue searching in the right half
		  
		  // check if the middle student's CGPA is greater than the target CGPA
		} else {
			high = middle - 1; // continue searching in the left half

		}

	}

	return -1; // target not found

}



// ===================================================================================================================
// Algorithm 4: Insertion Sort
// 
// How it works:
// 1. Loop through the array from the second element to the end of the array.
// 2. Store the current student as key
// 3. Compare the key with the students before it. 
// 4. Shift the students to the right if their CGPA is greater than the key student's CGPA.
// 5. Place the key student in the correct position.
// 6. Display success message after sorting.
//
// Big-O Notation: O(n) best case, O(n²) worst case 
// Best Case when the students are alreadt sorted by CGPA so no shifting is needed.
// Worst case when the students are sorted in reverse order so every student needs to be compared and shifted.
// ===================================================================================================================

void insertionSort(StudentArray& arr) {
	// loop the array from the second element
	for (int i=1; i<arr.count; i++) {
		// store the current student as the key
		Student key = arr.students[i];
		int j = i - 1; 

		// compare the key student with the students before it
		while (j >= 0 && arr.students[j].cgpa > key.cgpa) {
			// shift the student to right if CGPA > key student
			arr.students[j + 1] = arr.students[j];
			j--;

		}

		// place the key student in the correct position
		arr.students[j + 1] = key; 

	}

	// display success message
	cout << "Students sorted by CGPA successfully." << endl;

}


// ===================================================================================================================
// displayAllRecords() function:
// This function displays the details of all students in the array.
// ===================================================================================================================

void displayAllRecords(const StudentArray& arr) {
	// check if there are any student records to display
	if (arr.count == 0) {
		cout << "No student records to display." << endl;
		return; // no records to display

	}

	cout << "Total records: " << arr.count << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

	// loop through the array to display each student's details
	for (int i = 0; i < arr.count; i++) {
		cout << "Record #" << (i + 1) << endl;
		displayStudentInfo(arr.students[i]);
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

	}
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
		cout << "Error: Could not open file " << filename << endl;
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
			cout << "Warning: Skipping line with missing fields: " << line << endl;
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
			cout << "Warning: Skipping line due to validation error: " << line << endl;

		}

	}
		// close file
		file.close();

		// display summary
		cout << "Loaded " << loadedCount << " students from " << filename << endl;
		cout << "Skipped " << skippedCount << " rows." << endl;

		return loadedCount; // return the number of students loaded

}




// ===================================================================================================================
// runEdgeCaseTest() function:
// This function make sure the program handles errors and boundaries correctly.
// ===================================================================================================================
void runEdgeCaseTest() {
	// display edge case test header
	cout << "===================================================================================================================" << endl;
	cout << "   Running Edge Case Test......   " << endl;
	cout << "===================================================================================================================" << endl;

	StudentArray* arr = new StudentArray();

	cout << endl << "---- Edge Case 1: Search on empty array ----" << endl;
	int result = binarySearch(*arr, 3.5);
	if (result == -1)
		cout << ">>> Test Passed. Binary search on empty array returned -1 as expected." << endl;

	cout << endl << "---- Edge Case 2: Insert CGPA = 4.00 (maximum boundary) ----" << endl;
	Student student1 = { "TP000001", "Testing Student 1", "CT103", 1, 4.00, "010-3914368" };
	appendToEnd(*arr, student1);

	cout << endl << "---- Edge Case 3: Insert CGPA = 0.00 (minimum boundary) ----" << endl;
	Student student2 = { "TP000002", "Tetsing Student 2", "CT103", 1, 0.00, "011-69832913" };
	appendToEnd(*arr, student2);

	cout << endl << "---- Edge Case 4: Binary search for non-existent CGPA ----" << endl;
	insertionSort(*arr);
	int notFound = binarySearch(*arr, 6.70);
	if (notFound == -1) {
		cout << ">>> Test Passed. Search for non-existent CGPA returned -1 as expected." << endl;

	}

	cout << endl << "---- Edge Case 5: Delete a record twice ----" << endl;
	deleteByValue(*arr, "TP000002");  // first delete should succeed
	deleteByValue(*arr, "TP000002");  // second delete should show error

	cout << endl << "---- Edge Case 6: Insert 1 record, delete it, then display ----" << endl;
	Student student3 = { "TP000003", "Testing Student 3", "CT101", 1, 2.50, "011-3936706" };
	appendToEnd(*arr, student3);
	deleteByValue(*arr, "TP000003");
	cout << endl;
	displayAllRecords(*arr);

	delete arr;

	cout << endl << ">>> Edge Case Testing Completed " << endl;
	cout << "===================================================================================================================" << endl;
		
}



// ===================================================================================================================
// runPerformanceTest() function:
// This function is used to measure the execution time of the four operations:
// - Append to End 
// - Delete by Value
// - Binary Search 
// - Insertion Sort
// ===================================================================================================================

void runPerformanceTest() {

	// define the four CSV files in an array for easy access
	const char* files[] = {
		"students_500.csv",
		"students_2000.csv",
		"students_8000.csv",
		"students_30000.csv"
	};

	// display performance test header
	cout << "===================================================================================================================" << endl;
	cout << "   Performance Test for Student Record Management System   " << endl;
	cout << "===================================================================================================================" << endl;

	// run edge case test to check for any validation error
	runEdgeCaseTest();

	// display dataset to users
	cout << endl << "Select a dataset to test: " << endl;
	cout << "  1. students_500.csv" << endl;
	cout << "  2. students_2000.csv" << endl;
	cout << "  3. students_8000.csv" << endl;
	cout << "  4. students_30000.csv" << endl;

	int choice;

	while (true) {
		cout << "Enter your choice (1-4): ";
		cin >> choice;
		cin.ignore();

		if (choice >= 1 && choice <= 4) {
			break;
		}

		cout << "Error: Invalid choice. Please enter a number between 1 and 4." << endl;

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
		cout << "Error: No data loaded from " << files[index] << ". Skipping performane test for this dataset." << endl;
		delete arr; // free memory allocated for the array
		return; 

	}

	// ---- Display all Records ----
	auto start = high_resolution_clock::now();

	for (int i = 0; i < arr->count; i++) {
		// traverse the array without printing
		volatile char* id = (volatile char*)arr->students[i].studentID;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	//cout << "Display All: " << duration.count() << " microseconds" << endl;
		
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


	auto start1 = high_resolution_clock::now(); // start time
	for (int i = 0; i < 10; i++) {
		appendToEnd(*arr, newStudent[i]); // perform append operation

	} 
	auto end1 = high_resolution_clock::now(); // end time
	auto duration1 = duration_cast<microseconds>(end1 - start1); // calculate duration in microseconds
	
	// divide by 10 to get average time per insert
	//cout << "Append to End  : " 
	//	<< duration1.count() / 10.0
	//	<< " microseconds (average of 10 inserts)" << endl;

	// ---- Insertion Sort ----
	auto start2 = high_resolution_clock::now(); // start time
	insertionSort(*arr); // perform insertion sort operation
	auto end2 = high_resolution_clock::now(); // end time
	auto duration2 = duration_cast<microseconds>(end2 - start2); // calculate duration in microseconds
		
	//cout << "Insertion Sort: " 
	//	<< duration2.count() 
	//	<< " microseconds" << endl; // display execution time

	// ---- Binary Search ----
	// array is already sorted from the step above

	// search for 3 different CGPAs: first, middle and last student
	double targets[3] = {
		arr->students[0].cgpa,                  
		arr->students[arr->count / 2].cgpa,     
		arr->students[arr->count - 1].cgpa 

	};

	auto start3 = high_resolution_clock::now(); // start time

	// run each target 1000 times to get a measurable average time
	for (int i = 0; i < 3; i++) {
		for (int repeat = 0; repeat < 1000; repeat++) {
			binarySearch(*arr, targets[i]);

		}
	}

	auto end3 = high_resolution_clock::now(); // end time
	auto duration3 = duration_cast<microseconds>(end3 - start3); // calculate duration in microseconds
		
	// divide by 3000 to get average time per search (
	// Note: 3 targets x 1000 runs each
	//cout << "Binary Search  : " 
	//	<< duration3.count() / 3000.0
	//	<< " microseconds (average of 3 targets x 1000 runs)" << endl;

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

	auto start4 = high_resolution_clock::now(); // start time
	for (int i = 0; i < 10; i++) {
		deleteByValue(*arr, deleteStudent[i]); // perform delete operation

	}

	auto end4 = high_resolution_clock::now(); // end time
	auto duration4 = duration_cast<microseconds>(end4 - start4); // calculate duration in microseconds

	// divide by 10 to get average time per delete
	//cout << "Delete by Value: "
	//	<< duration4.count() / 10.0
	//	<< " microseconds (average of 10 deletes)" << endl;

	// display summary of performance test
	cout << endl << "-------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "   SUMMARY OF PERFORMANCE TEST (IN MICROSECONDS)  " << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Display All Records: " << duration.count() << " microseconds" << endl;
	cout << "Append to End  : " << duration1.count() / 10.0 << " microseconds (average of 10 inserts)" << endl;
	cout << "Insertion Sort: " << duration2.count() << " microseconds" << endl; 
	cout << "Binary Search  : " << duration3.count() / 3000.0 << " microseconds (average of 3 targets x 1000 runs)" << endl;
	cout << "Delete by Value: " << duration4.count() / 10.0 << " microseconds (average of 10 deletes)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

	delete arr; // free memory allocated for the array

	// display completion message 
	cout << endl << ">>> Performance test completed for the selected datasets." << endl;
	cout << "===================================================================================================================" << endl;

}



// ===================================================================================================================
// menu() function:
// This function displays the menu options to the user and prompts for input.
// ===================================================================================================================

void menu() {
	cout << endl << "===================================================================================================================" << endl;
	cout << "   Welcome to the Student Record Management System!   " << endl;
	cout << "===================================================================================================================" << endl;
	cout << "1. Load a dataset from .csv file" << endl;
	cout << "2. Display all records" << endl;
	cout << "3. Add a new student" << endl;
	cout << "4. Sort students by CGPA" << endl;
	cout << "5. Binary search by CGPA" << endl;
	cout << "6. Delete a student by student ID" << endl;
	cout << "7. Run performance test" << endl;
	cout << "8. Exit program" << endl;
	cout << "===================================================================================================================" << endl;
	cout << "Please select an option (1-8): ";
}

// ===================================================================================================================
// main() function:
// This is the entry point of the program. It displays the menu and handles user input.
// ===================================================================================================================
int main() {
	// create an instance of StudentArray to store student records
	StudentArray* arr = new StudentArray(); 
	int choice = 0;

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

				int choice;
				string filename;
				
				// map the choice to the corresponding dataset
				while (true) {
					cout << "Enter your choice (1-4): ";
					cin >> choice;
					cin.ignore(); // ignore newline character after integer input

					if (choice == 1) {
						filename = "students_500.csv";
						break;

					} else if (choice == 2) {
						filename = "students_2000.csv";
						break;

					} else if (choice == 3) {
						filename = "students_8000.csv";
						break;

					} else if (choice == 4) {
						filename = "students_30000.csv";
						break;

					} else {
						cout << "Invalid choice. Please enter a number between 1 and 4." << endl;

					}
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
				// prompt user to enter student details
				Student newStudent;
				cout << "  Student ID    : "; 
				cin.getline(newStudent.studentID, sizeof(newStudent.studentID));

				cout << "  Student Name  : "; 
				cin.getline(newStudent.fullName, sizeof(newStudent.fullName));

				cout << "  Programme     : "; 
				cin.getline(newStudent.programme, sizeof(newStudent.programme));

				cout << "  Year of Study : "; 
				cin >> newStudent.yearOfStudy;

				cout << "  CGPA          : "; 
				cin >> newStudent.cgpa;
				
				cin.ignore(); // clear newline from input buffer

				cout << "  Contact Number: "; 
				cin.getline(newStudent.contactNumber, sizeof(newStudent.contactNumber));
				
				appendToEnd(*arr, newStudent);
				break;

			}

			// ---- Sort students by CGPA ----
			case 4:
			{
				// check if there are any student records to sort
				if (arr->count == 0) {
					cout << "Error: No student records to sort." << endl;
					break; 

				}

				insertionSort(*arr);
				break;

			}

			// ---- Binary search by CGPA ----
			case 5:
			{
				double target;

				// check if there are any student records to search
				if (arr->count == 0) {
					cout << "Error: No student records to search." << endl;
					break; 

				}

				// make sure the array is sorted before performing binary search
				cout << "Note: The array will be sorted by CGPA before performing binary search." << endl;
				insertionSort(*arr);

				// prompt user to enter target CGPA
				cout << "Enter CGPA to search: ";
				cin >> target;
				cin.ignore(); // ignore newline character after double input

				// perform binary search 
				int index = binarySearch(*arr, target);

				// check if binary search successfully found a matching CGPA
				if (index != -1) {
					cout << "First match at index " << index << ":" << endl;

					// check for other students with the same CGPA by moving right
					for (int i = index; i < arr->count; i++) {
						// calculate the difference between the current student's CGPA and the target CGPA
						double difference = arr->students[i].cgpa - target;

						// check if the difference is within 0.0001 to handle floating point precision issues
						if (difference > -0.0001 && difference < 0.0001) {
							cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
							displayStudentInfo(arr->students[i]); // display student details

						} else {
							break; // stop when CGPA no longer matches the target

						}
					}

				} else {
					cout << "Error: No student found with CGPA " << target << endl;
					cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

				}

				break;

			}

			// ---- Delete a student by student ID ----
			case 6:
			{
				char target[20];
				cout << "Enter student ID to delete: ";
				cin.getline(target, sizeof(target));
				deleteByValue(*arr, target);
				break;

			}
				
			// ---- Run performance test ----
			case 7:
			{
				runPerformanceTest();
				break;

			}

			// ---- Exit program ----
			case 8:
			{
				cout << "Thank you for using the Student Record Management System!" << endl;
				cout << "Exiting program..." << endl;
				return 0; // exit the program

			}

			// ---- Invalid option ----
			default:
			{
				cout << "Error: Invalid option. Please select a number between 1 and 8." << endl;
				break;

			}
				
		}
	}
}