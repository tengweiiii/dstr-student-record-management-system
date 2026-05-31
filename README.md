# CT077-3-2-DSTR (Data Structures) | Lab Work #1
## Student Record Management System

| Field | Details |
|---|---|
| Intake Code | APD2F2511CS(DA) |
| Lecturer | Dr. Masrina Akmal Binti Salleh |
| Student Name | Cheong Teng Wei |
| TP Number | TP076095 |
| Data Structure | Array |

---

## Algorithms Used

| # | Algorithm |
|---|---|
| 1 | Append to End |
| 2 | Delete by Value |
| 3 | Insertion Sort by Student ID (binary search prerequisite) |
| 4 | Insertion Sort by Name (binary search prerequisite) |
| 5 | Insertion Sort by CGPA Ascending |
| 6 | Insertion Sort by CGPA Descending |
| 7 | Binary Search by Student ID |
| 8 | Binary Search by Name |

---

## How to Compile

1. Open **Visual Studio**
2. Create a new **C++ Console Application** project
3. Add the source file:
   ```
   TP076095_CheongTengWei_CT077_LW1.cpp
   ```
4. Make sure all 4 dataset files are in the **same folder** as the `.cpp` file:
   - `students_500.csv`
   - `students_2000.csv`
   - `students_8000.csv`
   - `students_30000.csv`
5. Build and run the project using `Ctrl + F5`

---

## How to Run

1. Run the program
2. The system will display a menu with 8 options:

| Option | Description |
|---|---|
| 1 | Load a dataset from `.csv` file |
| 2 | Display all records |
| 3 | Add a new student |
| 4 | Sort students by CGPA (Ascending or Descending) |
| 5 | Binary search by Student ID or Name |
| 6 | Delete a student by Student ID |
| 7 | Run performance test |
| 8 | Exit program |

3. Always perform **Option 1** before using any other feature

---

## Menu Options

### Option 1 — Load a dataset from `.csv` file
Select one of the four datasets to load into the system.

### Option 2 — Display all records
Print all student records currently loaded in the system.

### Option 3 — Add a new student
Manually enter a new student record with the following fields:
- Student ID
- Full Name
- Programme
- Year of Study
- CGPA
- Contact Number

### Option 4 — Sort students by CGPA
Sort all records by CGPA using Insertion Sort. You will be prompted to choose:
- `1` Ascending — lowest CGPA first
- `2` Descending — highest CGPA first

### Option 5 — Binary search by Student ID or Name
Search for a student record using Binary Search. You will be prompted to choose:
- `1` Search by Student ID — array will be sorted by Student ID automatically before searching
- `2` Search by Name — array will be sorted by Name automatically before searching

### Option 6 — Delete a student by Student ID
Remove a student record from the system using their Student ID.

### Option 7 — Run performance test
Measures the execution time of all operations on a selected dataset. Loads its own separate copy of the dataset and will **not** affect the records currently loaded in the system.

### Option 8 — Exit program
Terminate the system.

---

## Important Notes

> ⚠️ Always load a dataset **(Option 1)** before using any other options.

- **Sort (Option 4)** will prompt whether to sort Ascending or Descending before sorting
- **Binary Search (Option 5)** will prompt whether to search by Student ID or Full Name
  - Searching by Student ID will automatically sort the array by Student ID first
  - Searching by Name will automatically sort the array by Name first
- **Performance Test (Option 7)** loads its own separate copy of the dataset and will not affect the records currently loaded in the system
- CGPA must be between **0.0 and 4.0**
- Duplicate Student IDs are **not allowed**

---

## Dataset Files

| File | Records | Size |
|---|---|---|
| `students_500.csv` | 500 | ~25 KB |
| `students_2000.csv` | 2,000 | ~100 KB |
| `students_8000.csv` | 8,000 | ~400 KB |
| `students_30000.csv` | 30,000 | ~1.5 MB |
