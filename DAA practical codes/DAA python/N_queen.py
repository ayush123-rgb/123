def solveNQueens(n):
    solutions = []
    board = [["."] * n for _ in range(n)]

    cols = set()
    diag1 = set()   # r - c
    diag2 = set()   # r + c

    def backtrack(r):
        if r == n:
            solutions.append(["".join(row) for row in board])
            return

        for c in range(n):
            if c in cols or (r - c) in diag1 or (r + c) in diag2:
                continue

            board[r][c] = "Q"
            cols.add(c)
            diag1.add(r - c)
            diag2.add(r + c)

            backtrack(r + 1)

            board[r][c] = "."
            cols.remove(c)
            diag1.remove(r - c)
            diag2.remove(r + c)

    backtrack(0)
    return solutions


# Run
n = int(input("Enter the value of n: "))
sol = solveNQueens(n)
for s in sol:
    print(*s, sep="\n")
    print()


'''
✅ ALGORITHM (N-Queens Backtracking — Copy-Paste Ready)
1. Create an empty chessboard of size n × n.

2. Maintain three sets:
      cols  → stores which columns already have a queen
      diag1 → stores r - c (top-left to bottom-right diagonals)
      diag2 → stores r + c (top-right to bottom-left diagonals)

3. Define a recursive function backtrack(r):
      - If r == n:
            store the current board arrangement as a valid solution
            return

      - For each column c from 0 to n-1:
            * If column c, diag1 (r - c), or diag2 (r + c) is blocked:
                  continue to next column

            * Place a queen at (r, c)
                  mark column, diag1, diag2 as used

            * Recursively call backtrack(r + 1)

            * Remove the queen (undo the move)
                  unmark column, diag1, diag2

4. Start recursion from row 0.

5. Return all stored solutions.


Worst Case Time Complexity:  O(N!)
Explanation:
- Each row tries N positions
- Backtracking heavily prunes, but mathematically it reduces to factorial behavior
- The N-Queens problem is known to have O(N!) complexity

Space Complexity:  O(N)
Reason:
- Recursion depth = N
- cols, diag1, diag2 sets store at most N entries
- Board storage for each solution is extra but not counted in auxiliary space

Output Space: O(N² × number_of_solutions)
Reason:
- Each valid board is N×N
'''