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
3. Insertion Sort by Student ID (binary search prerequisite)
4. Insertion Sort by Name (binary search prerequisite)
5. Insertion Sort by CGPA Ascending
6. Insertion Sort by CGPA Descending
7. Binary Search by Student ID
8. Binary Search by Name

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
   - Option 2: Display all records
   - Option 3: Add a new student
   - Option 4: Sort students by CGPA (Ascending or Descending)
   - Option 5: Binary search by Student ID or Name
   - Option 6: Delete a student by student ID
   - Option 7: Run performance test
   - Option 8: Exit program
3. Always perform Option 1: Load a dataset from .csv file before using other features.

MENU OPTIONS
------------
1. Load a dataset from .csv file   : select one of the four datasets to load into the system
2. Display all records             : print all student records currently loaded
3. Add a new student               : manually enter a new student record
4. Sort students by CGPA           : sort all records by CGPA ascending or descending (Insertion Sort)
5. Binary search by Student ID or  : search for a student by Student ID or Full Name
   Name                              (array will be sorted automatically before searching)
6. Delete a student by student ID  : remove a student record using their Student ID
7. Run performance test            : measure execution time of all operations on a selected dataset
8. Exit program                    : terminate the system

IMPORTANT NOTES
---------------
Always load a dataset (Option 1) before using any other options.
Sort (Option 4) will prompt whether to sort Ascending or Descending before sorting.
Binary Search (Option 5) will prompt whether to search by Student ID or Full Name.
  - Searching by Student ID will automatically sort the array by Student ID first.
  - Searching by Name will automatically sort the array by Name first.
Performance Test (Option 7) loads its own separate copy of the dataset and will not
  affect the records currently loaded in the system.
CGPA must be between 0.0 and 4.0.
Duplicate Student IDs are not allowed.

DATASET FILES
-------------
students_500.csv    —    500 records (~25 KB)
students_2000.csv   —  2,000 records (~100 KB)
students_8000.csv   —  8,000 records (~400 KB)
students_30000.csv  — 30,000 records (~1.5 MB)
===========================================================================================
END OF README
===========================================================================================