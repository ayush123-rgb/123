#include <iostream>
#include <vector>
#include <thread>
using namespace std;

void multiplyRow(const vector<vector<int>>& A,
                 const vector<vector<int>>& B,
                 vector<vector<int>>& C,
                 int row, int common, int colB)
{
    for (int j = 0; j < colB; j++) {
        C[row][j] = 0;
        for (int k = 0; k < common; k++)
            C[row][j] += A[row][k] * B[k][j];
    }
}

int main() {
    int r1, c1, r2, c2;

    cout << "Enter rows, cols of Matrix A: ";
    cin >> r1 >> c1;

    cout << "Enter rows, cols of Matrix B: ";
    cin >> r2 >> c2;

    if (c1 != r2) {
        cout << "Matrix multiplication not possible!\n";
        return 0;
    }

    vector<vector<int>> A(r1, vector<int>(c1));
    vector<vector<int>> B(r2, vector<int>(c2));
    vector<vector<int>> C(r1, vector<int>(c2));

    cout << "Enter Matrix A:\n";
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            cin >> A[i][j];

    cout << "Enter Matrix B:\n";
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            cin >> B[i][j];

    vector<thread> threads;

    for (int i = 0; i < r1; i++) {
        threads.push_back(thread(multiplyRow,
            cref(A), cref(B), ref(C), i, c1, c2));
    }

    for (auto &t : threads)
        t.join();

    cout << "\nResult Matrix:\n";
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    return 0;
}



/*
Enter rows and columns of Matrix A: 2 3
Enter rows and columns of Matrix B: 3 2

Enter Matrix A:
1 2 3
4 5 6

Enter Matrix B:
7 8
9 10
11 12
*/

/*Algo:
Steps:

Read matrix A of size r1 × c1
Read matrix B of size r2 × c2
If c1 != r2, multiplication is not possible.
Create result matrix C of size r1 × c2
For each row i (0 to r1-1):
Create a thread
Thread computes row i of matrix C
Wait for all threads to finish (join)
Print final matrix C.*/

/*Pseudocode:
FUNCTION MultithreadedMatrixMultiply(A, B):
    r1 = rows of A
    c1 = columns of A
    r2 = rows of B
    c2 = columns of B

    IF c1 != r2:
        PRINT "Multiplication not possible"
        EXIT

    Create matrix C of size r1 × c2

    FOR each row i from 0 to r1-1:
        Create a thread to compute RowMultiply(i)

    Wait for all threads to complete

    RETURN C


FUNCTION RowMultiply(i):
    FOR each column j from 0 to c2-1:
        C[i][j] = 0
        FOR k from 0 to c1-1:
            C[i][j] = C[i][j] + A[i][k] * B[k][j]
*/

/*TIme complexity
| Aspect                       | Result                                |
| ---------------------------- | ------------------------------------- |
| **Algorithm**                | Row-wise multithreaded multiplication |
| **Parallel Time Complexity** | `O(c1 × c2)`                          |
| **Normal Time Complexity**   | `O(r1 × c1 × c2)`                     |
| **Space Complexity**         | `O(r1c1 + r2c2 + r1c2)`               |
| **Speedup**                  | Up to `r1×` faster (ideal)            |
| **Threads used**             | `r1`                                  |
*/