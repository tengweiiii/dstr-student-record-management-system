# CT077-3-2-DSTR (Data Structures) | Lab Work #1
## Student Record Management System

| Field          | Details                          |
|----------------|----------------------------------|
| Intake Code    | APD2F2511CS(DA)                  |
| Lecturer       | Dr. Masrina Akmal Binti Salleh   |
| Student Name   | Cheong Teng Wei                  |
| TP Number      | TP076095                         |
| Data Structure | Array                            |

---

## Algorithms Used

| #  | Algorithm                                                 |
|----|-----------------------------------------------------------|
| 1  | Append to End                                             |
| 2  | Delete by Value                                           |
| 3  | Insertion Sort by Student ID (binary search prerequisite) |
| 4  | Insertion Sort by Name (binary search prerequisite)       |
| 5  | Insertion Sort by CGPA Ascending                          |
| 6  | Insertion Sort by CGPA Descending                         |
| 7  | Binary Search by Student ID                               |
| 8  | Binary Search by Name                                     |
| 9  | Linear Search by Student ID                               |
| 10 | Linear Search by Name                                     |

---

## How to Compile

1. Open Visual Studio
2. Create a new C++ Console Application project
3. Add the source file:
      TP076095_CheongTengWei_CT077_LW1.cpp
4. Make sure all 4 dataset files are in the SAME folder as the .cpp file:
      - students_500.csv
      - students_2000.csv
      - students_8000.csv
      - students_30000.csv
5. Build and run the project using Ctrl + F5

---

## How to Run

1. Run the program
2. The system will display a menu with 9 options:

| Option | Description                                      |
|--------|--------------------------------------------------|
| 1      | Load a dataset from .csv file                    |
| 2      | Display all records                              |
| 3      | Add a new student                                |
| 4      | Linear search by Student ID or Name              |
| 5      | Sort students by CGPA (Ascending or Descending)  |
| 6      | Binary search by Student ID or Name              |
| 7      | Delete a student by Student ID                   |
| 8      | Run performance test                             |
| 9      | Exit program                                     |

3. Always perform Option 1 before using any other feature

---

## Menu Options

### Option 1 - Load a dataset from .csv file
Select one of the four datasets to load into the system.
Select Option 5 to go back to the main menu without loading.

### Option 2 - Display all records
Print all student records currently loaded in the system.

### Option 3 - Add a new student
Manually enter a new student record with the following fields:
  - Student ID (begin with TP, followed by 6 digits)
  - Full Name
  - Programme (select 1-26 from the programme list)
  - Year of Study (autofilled based on the programme chosen)
  - CGPA
  - Contact Number (follow Malaysian format XXX-XXXXXXXX e.g. 011-12345678)

### Option 4 - Linear search by Student ID or Name
Search for a student record using Linear Search. You will be prompted to choose:
  - 1  Search by Student ID
  - 2  Search by Name
  - 3  Back to main menu

No sorting is required. Linear search works on an unsorted array.

### Option 5 - Sort students by CGPA
Sort all records by CGPA using Insertion Sort. You will be prompted to choose:
  - 1  Ascending  - lowest CGPA first
  - 2  Descending - highest CGPA first
  - 3  Back to main menu

After sorting, you will be asked whether to display all records.

### Option 6 - Binary search by Student ID or Name
Search for a student record using Binary Search. You will be prompted to choose:
  - 1  Search by Student ID - array will be sorted by Student ID automatically before searching
  - 2  Search by Name       - array will be sorted by Name automatically before searching
  - 3  Back to main menu

NOTE: Binary search will re-sort the array before searching, which changes the current order of records.

### Option 7 - Delete a student by Student ID
Remove a student record from the system using their Student ID.

### Option 8 - Run performance test
Measures the execution time of all operations on a selected dataset.
Loads its own separate copy of the dataset and will NOT affect the records currently loaded in the system.
Select Option 5 to go back to the main menu without running the test.

Before running the performance test, the system will automatically run an Edge Case Test
to verify that all operations handle boundary conditions and errors correctly.
The Edge Case Test covers the following scenarios:

  - Edge Case 1: Binary search on an empty array
  - Edge Case 2: Insert a student with CGPA = 4.00 (maximum boundary)
  - Edge Case 3: Insert a student with CGPA = 0.00 (minimum boundary)
  - Edge Case 4: Binary search for a non-existent Student ID
  - Edge Case 5: Binary search for a non-existent student name
  - Edge Case 6: Linear search for a non-existent Student ID
  - Edge Case 7: Linear search for a non-existent student name
  - Edge Case 8: Delete a record twice (duplicate delete)
  - Edge Case 9: Insert 1 record, delete it, then display (empty-after-delete)

The edge case test results are displayed before the dataset selection prompt.

### Option 9 - Exit program
Terminate the system.

---

## Important Notes

WARNING: Always load a dataset (Option 1) before using any other options.

  - Linear Search (Option 4) does not require sorting - it works on the array in its current order
  - Sort (Option 5) will prompt whether to sort Ascending or Descending, and whether to display all records after sorting
  - Binary Search (Option 6) will automatically re-sort the array before searching, which will change the current record order
  - Performance Test (Option 8) loads its own separate copy of the dataset and will not affect records currently loaded
  - Performance Test (Option 8) automatically runs an Edge Case Test (9 cases) before prompting for a dataset
  - CGPA must be between 0.0 and 4.0
  - Duplicate Student IDs are not allowed

---

## Dataset Files

| File                | Records | Size     |
|---------------------|---------|----------|
| students_500.csv    |     500 | ~25 KB   |
| students_2000.csv   |   2,000 | ~100 KB  |
| students_8000.csv   |   8,000 | ~400 KB  |
| students_30000.csv  |  30,000 | ~1.5 MB  |