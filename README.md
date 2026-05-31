# student-record-management-system
===========================================================================================

CT077-3-2-DSTR (Data Structures) | Lab Work #1
Student Record Management System
Intake Code: APD2F2511CS(DA)
Lecturer Name: Dr. Masrina Akmal Binti Salleh
Student Name: Cheong Teng Wei
TP Number: TP076095

Data Structure Used: Array
Algorithms Used: 
1. Append to End
2. Delete by Value
3. Update by Value
4. Binary Search
5. Insertion Sort

===========================================================================================

HOW TO COMPILE
--------------
1. Open Visual Studio
2. Create a new C++ Console Application project
3. Add the source file:
   TP076095_CheongTengWei_CT077_LW1.cpp
4. Make sure all 4 dataset files are in the SAME folder as the .cpp file:
   - students_500.csv
   - students_2000.csv
   - students_8000.csv
   - students_30000.csv
5. Build the project and run using:
   Ctrl + F5

HOW TO RUN
----------
1. Run the program. 
2. The system will display a menu with 8 options.
   - Option 1: Load a dataset from .csv file
   - Option 2: Add a new student
   - Option 3: Delete a student by ID
   - Option 4: Sort students by CGPA
   - Option 5: Binary search by CGPA
   - Option 6: Display all records
   - Option 7: Run performance test  	
   - Option 8: Exit program
2. Always perform Option 1: Load a dataset from .csv file before using other features.

MENU OPTIONS
------------
1. Load a dataset from .csv file: select one of the four datasets to load into the system
2. Add a new student: manually enter a new student record
3. Delete a student by ID: remove a student record using their Student ID
4. Sort students by CGPA: sort all records by CGPA in ascending order (Insertion Sort)
5. Binary search by CGPA: search for students by CGPA (array will be sorted first using insertion sort)
6. Display all records: print all the student records currently loaded
7. Run performance test: measure execution time of all operations on a selected dataset
8. Exit program: terminate the system

IMPORTANT NOTES
--------------- 
1. Always load a dataset (Option 1: Load a dataset from .csv file) before using any other options.
2. Binary Search (Option 5: Binary search by CGPA) will automatically sort the array before searching.
3. Performance Test (Option 7: Run performance test) loads its own separate copy of the dataset so it will not affect the records currently loaded in the system
4. CGPA must be between 0.0 and 4.0
5. Duplicate Student IDs are not allowed

DATASET FILES
-------------
students_500.csv    —  500 records  (~25 KB)
students_2000.csv   — 2000 records  (~100 KB)
students_8000.csv   — 8000 records  (~400 KB)
students_30000.csv  — 30000 records (~1.5 MB)

===========================================================================================

END OF README

===========================================================================================
