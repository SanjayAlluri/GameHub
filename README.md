# GameHub

A collection of classical games implemented using **Data Structures and Algorithms in C++**.

---

## 🧩 Sudoku Solver

The Sudoku Solver automatically solves a **9×9 Sudoku puzzle** using the **Backtracking algorithm**.
The program fills empty cells while ensuring that all Sudoku rules are satisfied.

### Features

* Solves any valid **9×9 Sudoku puzzle**
* Uses **recursive backtracking**
* Validates Sudoku constraints:

  * Row constraint
  * Column constraint
  * 3×3 subgrid constraint
* Clean **grid-based board visualization**
* **Color-coded output**

  * Green → Original puzzle numbers
  * Red → Numbers filled by the solver
* Displays the completed Sudoku board in the terminal

### Algorithm

The solver uses **Backtracking**, a recursive approach that tries possible numbers and backtracks when a conflict occurs.

Basic idea:

```
Find an empty cell
Try digits 1–9
Check if the number is valid
If valid → place the number
Recursively solve the rest of the board
If it fails → remove the number (backtrack)
```


### How to Run

Compile:

```
g++ Sudoku.cpp -o sudoku
```

Run:

```
./sudoku
```
## 🎮 Tic-Tac-Toe (4×4) – C++ Terminal Game

A simple 4×4 Tic-Tac-Toe game implemented in C++ where a human player competes against the computer in the terminal.

The player uses X, while the computer uses O. The game continues until a player wins or the board becomes full.

### 📌 Features

4×4 Tic-Tac-Toe board

Human vs Computer gameplay

Turn-based system

Input moves using numbers (0–15)

Valid move checking

Detects winning conditions

Detects draw when the board is full

Simple terminal-based board display

Computer makes random valid moves

### How to Run

Compile:

```
g++ tictactoe.cpp -o tictactoe
```

Run:

```
./tictactoe
```

## 🎮 Connect Four (5×5) – C++ Terminal Game with AI

A terminal-based Connect Four–style game implemented in C++ where a human player competes against a computer-controlled AI.

The game is played on a 5×5 grid, and the objective is to connect 4 pieces in a row (horizontally, vertically, or diagonally). The player can choose their piece color and whether to play first or second.

The computer uses a recursive game search algorithm (Minimax-style) to determine the best possible move.

### 📌 Features

5×5 Connect Four style board

Human vs Computer gameplay

Turn-based system

Pieces drop to the lowest available position in a column (gravity effect)

Player chooses Red (R) or Blue (B)

Option to start first or second

AI opponent using recursive search to choose optimal moves

Detects winning conditions:

Horizontal connection of 4

Vertical connection of 4

Diagonal connection of 4

Detects draw when the board becomes full

Color-coded terminal display using ANSI color codes

Column-based input for moves


### 🖥️ How to Compile
g++ connect4.cpp -o connect4
### ▶️ How to Run
./connect4
