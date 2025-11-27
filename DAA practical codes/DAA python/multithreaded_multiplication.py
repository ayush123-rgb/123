import threading

# Thread function to compute one row of C
def multiply_row(A, B, C, row):
    cols_B = len(B[0])
    common = len(B)

    for j in range(cols_B):
        C[row][j] = sum(A[row][k] * B[k][j] for k in range(common))


# Read matrix from user
def read_matrix(name):
    rows, cols = map(int, input(f"Enter rows and cols of {name}: ").split())
    print(f"Enter elements of {name}:")
    matrix = [list(map(int, input().split())) for _ in range(rows)]
    return matrix, rows, cols


def multithreaded_matrix_multiply(A, B):
    r1, c1 = len(A), len(A[0])
    r2, c2 = len(B), len(B[0])

    # Prepare empty result matrix C
    C = [[0] * c2 for _ in range(r1)]

    threads = []

    # One thread per row
    for row in range(r1):
        t = threading.Thread(target=multiply_row, args=(A, B, C, row))
        threads.append(t)
        t.start()

    # Wait for all threads
    for t in threads:
        t.join()

    return C


# ---------------- MAIN ----------------
A, r1, c1 = read_matrix("Matrix A")
B, r2, c2 = read_matrix("Matrix B")

# Check if multiplication is possible
if c1 != r2:
    print("Matrix multiplication NOT possible!")
else:
    result = multithreaded_matrix_multiply(A, B)

    print("\nResult Matrix:")
    for row in result:
        print(*row)


'''
Algorithm: Multithreaded Matrix Multiplication

1. Read matrix A of size r1 × c1
2. Read matrix B of size r2 × c2
3. If c1 != r2:
       Print "Matrix multiplication not possible" and stop
4. Create result matrix C of size r1 × c2, initialized to 0
5. For each row i from 0 to r1 - 1:
       Create a thread to compute row i of matrix C
6. Wait for all threads to finish using join()
7. Print or return the final matrix C
-------------------------
pseudocode:
FUNCTION MultithreadedMatrixMultiply(A, B):
    r1 = number of rows in A
    c1 = number of columns in A
    r2 = number of rows in B
    c2 = number of columns in B

    IF c1 != r2:
        PRINT "Multiplication not possible"
        EXIT

    Create C as a matrix of size r1 × c2

    FOR i from 0 to r1 - 1:
        Create a thread to run RowMultiply(i)

    Wait for all threads to finish

    RETURN C


FUNCTION RowMultiply(i):
    FOR j from 0 to c2 - 1:
        C[i][j] = 0
        FOR k from 0 to c1 - 1:
            C[i][j] = C[i][j] + A[i][k] * B[k][j]
---------------------------------
Time and space complexity
| Aspect                       | Result                                |
| ---------------------------- | ------------------------------------- |
| Algorithm                    | Row-wise multithreaded multiplication |
| Parallel Time Complexity     | O(c1 × c2)                            |
| Normal Time Complexity       | O(r1 × c1 × c2)                       |
| Space Complexity             | O(r1c1 + r2c2 + r1c2)                 |
| Speedup                      | Up to r1× faster (ideal case)         |
| Threads Used                 | r1                                    |

'''

