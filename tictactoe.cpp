#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 4;

class TicTacToe {
private:
  char board[BOARD_SIZE][BOARD_SIZE]; // 'X', 'O', or '.'
  char currentPlayer;

public:
  TicTacToe() { initBoard(); }

  void initBoard() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
      for (int col = 0; col < BOARD_SIZE; ++col) {
        board[row][col] = '.';
      }
    }
    currentPlayer = 'X'; // 'X' starts the game
  }

  void printBoard() const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
      for (int col = 0; col < BOARD_SIZE; ++col) {
        cout << " " << board[row][col] << " ";
        if (col < BOARD_SIZE - 1)
          cout << "|";
      }
      cout << endl;
      if (row < BOARD_SIZE - 1) {
        cout << "---+---+---+---" << endl;
      }
    }
    cout << endl;
  }

  bool isFull() const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
      for (int col = 0; col < BOARD_SIZE; ++col) {
        if (board[row][col] == '.') {
          return false;
        }
      }
    }
    return true;
  }

  bool hasWon(char player) const {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
      if (board[i][0] == player && board[i][1] == player &&
          board[i][2] == player && board[i][3] == player) {
        return true;
      }
      if (board[0][i] == player && board[1][i] == player &&
          board[2][i] == player && board[3][i] == player) {
        return true;
      }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player &&
         board[2][2] == player && board[3][3] == player) ||
        (board[0][3] == player && board[1][2] == player &&
         board[2][1] == player && board[3][0] == player)) {
      return true;
    }
    return false;
  }

  bool isValidMove(int row, int col) const {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE &&
            board[row][col] == '.');
  }

  void makeMove(int row, int col) {
    assert(isValidMove(row, col));
    board[row][col] = currentPlayer;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Toggle player
  }

  char getCurrentPlayer() const { return currentPlayer; }
};

int main() {
  TicTacToe game;
  int move;

  while (true) {
    game.printBoard();
    cout << "Current player: " << game.getCurrentPlayer() << endl;

    if (game.getCurrentPlayer() == 'X') {
      cout << "Enter your move (0-15): ";
      cin >> move;
      int row = move / BOARD_SIZE;
      int col = move % BOARD_SIZE;
      if (!game.isValidMove(row, col)) {
        cout << "Invalid move. Try again." << endl;
        continue;
      }
      game.makeMove(row, col);
    } else {
      // Implement computer move (best move logic)
      // For simplicity, assume the computer makes a random move.
      // Implementing the best move logic similar to the C version is possible
      // but more complex. Here's a simple random move:
      do {
        move = rand() % (BOARD_SIZE * BOARD_SIZE);
        int row = move / BOARD_SIZE;
        int col = move % BOARD_SIZE;
        if (game.isValidMove(row, col)) {
          game.makeMove(row, col);
          break;
        }
      } while (true);
    }

    if (game.hasWon('X')) {
      game.printBoard();
      cout << "Player X wins!" << endl;
      break;
    } else if (game.hasWon('O')) {
      game.printBoard();
      cout << "Player O wins!" << endl;
      break;
    } else if (game.isFull()) {
      game.printBoard();
      cout << "It's a draw!" << endl;
      break;
    }
  }

  return 0;
}