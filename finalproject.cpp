#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

const int SIZE = 9;

// ===================== Linked List Node =====================
struct Node
{
    int row, col;
    Node *next;
};

// Function to add a node to the linked list
void addNode(Node *&head, int row, int col)
{
    Node *newNode = new Node();
    newNode->row = row;
    newNode->col = col;
    newNode->next = head;
    head = newNode;
}

// Function to print the linked list
void printLinkedList(Node *head)
{
    while (head)
    {
        cout << "(" << head->row << ", " << head->col << ") -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// ===================== Stack Structure =====================
struct StackState
{
    int row, col, num;
};

// ===================== Queue for Empty Cells =====================
struct QueueNode
{
    int row, col;
};

// ===================== Function Prototypes =====================
void printBoard(int board[SIZE][SIZE]);
bool isValid(int board[SIZE][SIZE], int row, int col, int num);
bool solveSudoku(int board[SIZE][SIZE], queue<QueueNode> &emptyCells);
void generateSudoku(int board[SIZE][SIZE], int difficulty);
void sortBoardRows(int board[SIZE][SIZE]);

// ===================== Main Function =====================
int main()
{
    int board[SIZE][SIZE] = {0}; // Initialize Sudoku board with zeros

    // Choose the difficulty level (number of initially revealed cells)
    int difficulty;
    cout << "Enter difficulty level (1-81): ";
    cin >> difficulty;

    if (difficulty < 1 || difficulty > 81)
    {
        cout << "Invalid difficulty level. Exiting.\n";
        return 1;
    }

    generateSudoku(board, difficulty);

    cout << "Sudoku Puzzle:\n";
    printBoard(board);

    cout << "\nSorted Rows of Puzzle:\n";
    sortBoardRows(board);
    printBoard(board);

    cout << "\nSolving Sudoku...\n";
    queue<QueueNode> emptyCells;

    // Collect empty cells into the queue (FIFO)
    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            if (board[row][col] == 0)
            {
                emptyCells.push({row, col});
            }
        }
    }

    cout << "Empty Cells (Queue): ";
    while (!emptyCells.empty())
    {
        QueueNode cell = emptyCells.front();
        cout << "(" << cell.row << ", " << cell.col << ") -> ";
        emptyCells.pop();
    }
    cout << "NULL\n";

    // Solve the Sudoku
    if (solveSudoku(board, emptyCells))
    {
        cout << "Sudoku Solution:\n";
        printBoard(board);
    }
    else
    {
        cout << "No solution exists.\n";
    }

    return 0;
}

// ===================== Print Board =====================
void printBoard(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// ===================== Check Validity =====================
bool isValid(int board[SIZE][SIZE], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < SIZE; ++i)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < SIZE; ++i)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }

    // Check 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[startRow + i][startCol + j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// ===================== Solve Sudoku =====================
bool solveSudoku(int board[SIZE][SIZE], queue<QueueNode> &emptyCells)
{
    stack<StackState> s;

    while (!emptyCells.empty())
    {
        QueueNode current = emptyCells.front();
        emptyCells.pop();
        bool placed = false;

        // Try to place a number in the empty cell
        for (int num = 1; num <= 9; ++num)
        {
            if (isValid(board, current.row, current.col, num))
            {
                board[current.row][current.col] = num;
                s.push({current.row, current.col, num});
                placed = true;
                break;
            }
        }

        // If no number is placed, backtrack
        if (!placed)
        {
            if (s.empty())
                return false;

            StackState last = s.top();
            s.pop();
            board[last.row][last.col] = 0;
            emptyCells.push({last.row, last.col});
        }
    }

    return true;
}

// ===================== Generate Sudoku =====================
void generateSudoku(int board[SIZE][SIZE], int difficulty)
{
    srand(time(0));

    // Fill the diagonal 3x3 grids
    for (int i = 0; i < SIZE; i += 3)
    {
        for (int row = i; row < i + 3; ++row)
        {
            for (int col = i; col < i + 3; ++col)
            {
                int num;
                do
                {
                    num = rand() % 9 + 1;
                } while (!isValid(board, row, col, num));
                board[row][col] = num;
            }
        }
    }

    // Solve the board to complete it
    queue<QueueNode> dummyQueue;
    solveSudoku(board, dummyQueue);

    // Remove numbers to create the puzzle
    int cellsToRemove = SIZE * SIZE - difficulty;
    while (cellsToRemove > 0)
    {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (board[row][col] != 0)
        {
            board[row][col] = 0;
            cellsToRemove--;
        }
    }
}

// ===================== Sort Board Rows =====================
void sortBoardRows(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        sort(board[i], board[i] + SIZE);
    }
}
