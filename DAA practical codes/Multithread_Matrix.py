import threading
import time

# Function to take matrix input
def input_matrix(name):
    rows = int(input(f"Enter number of rows for Matrix {name}: "))
    cols = int(input(f"Enter number of columns for Matrix {name}: "))
    print(f"Enter elements of Matrix {name} row-wise:")
    matrix = []
    for i in range(rows):
        row = list(map(int, input(f"Row {i+1}: ").split()))
        matrix.append(row)
    return matrix

# Input matrices
print("Enter Matrix A:")
A = input_matrix("A")

print("\nEnter Matrix B:")
B = input_matrix("B")

# Check if matrices can be multiplied
if len(A[0]) != len(B):
    print("\nMatrix multiplication not possible! Columns of A must equal rows of B.")
    exit()

# Initialize result matrix with zeros
C = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]

# Function for each thread to compute one cell
def compute_cell(i, j):
    total = 0
    for k in range(len(A[0])):
        total += A[i][k] * B[k][j]
    C[i][j] = total

# Measure start time
start_time = time.time()

# Create and start threads
threads = []
for i in range(len(A)):
    for j in range(len(B[0])):
        t = threading.Thread(target=compute_cell, args=(i, j))
        threads.append(t)
        t.start()

# Wait for all threads to complete
for t in threads:
    t.join()

# Measure end time
end_time = time.time()

# Display result
print("\nResultant Matrix C (A x B):")
for row in C:
    print(row)

print("\nExecution Time (Multithreaded):", round(end_time - start_time, 5), "seconds")

# Compare with single-threaded multiplication
start = time.time()
C_single = [[sum(A[i][k] * B[k][j] for k in range(len(A[0]))) for j in range(len(B[0]))] for i in range(len(A))]
end = time.time()

print("\nResult (Single-threaded):")
for row in C_single:
    print(row)

print("\nExecution Time (Single-threaded):", round(end - start, 5), "seconds")
