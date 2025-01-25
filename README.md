#Finalproject:
SUDOKU GAME

#Overview:
This project implements a Sudoku Solver and Generator using C++. It utilizes data structures such as linked lists, stacks, and queues to handle various tasks, such as managing empty cells and performing backtracking to solve the puzzle. The program also features functions to generate Sudoku puzzles with a specified difficulty level and sort the rows of the puzzle.

#Features:
Sudoku Puzzle Generation: Creates a valid Sudoku puzzle with a configurable number of revealed cells (difficulty level).
Sudoku Solver: Solves the given Sudoku puzzle using a backtracking algorithm.
Linked List: Tracks custom node information for demonstration purposes.
Queue: Manages empty cells in a First-In-First-Out (FIFO) order.
Stack: Tracks backtracking states for solving the puzzle.
Row Sorting: Sort the rows of the Sudoku puzzle in ascending order.
Simple and interactive console interface.

#Usage:
Run the Program: The program will prompt you to input a difficulty level (between 1 and 81).
View the Puzzle: After generating the puzzle, the program will display the unsolved Sudoku board.
Sort the Rows: The rows of the board will be sorted and displayed.
Solve the Puzzle: The program attempts to solve the puzzle using backtracking and outputs the solution.

#Code Highlights:
Backtracking Algorithm: Solves the puzzle by filling empty cells while ensuring validity.
Empty Cell Management: Uses a queue to track all empty cells.
Backtracking State: Uses a stack to save and restore the solving state during backtracking.
Row Sorting: Implements std::sort to sort rows in ascending order.
