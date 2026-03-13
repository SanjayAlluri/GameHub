#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

enum Player { EMPTY = 0, RED, BLUE };

constexpr int ROW = 5;
constexpr int COLUMN = 5;
constexpr int WIN = 4;

const string ANSI_COLOR_RED = "\x1b[31;1m";
const string ANSI_COLOR_BLUE = "\x1b[1;34m";
const string ANSI_COLOR_GREEN = "\x1b[32;1m";
const string ANSI_COLOR_RESET = "\x1b[0m";

using Board = vector<vector<char>>;

void init_board(Board &board) {
  for (int row = 0; row < ROW; ++row) {
    for (int col = 0; col < COLUMN; ++col) {
      board[row][col] = '.';
    }
  }
}

void print_board(const Board &board) {
  for (int row = 0; row < ROW; ++row) {
    for (int col = 0; col < COLUMN; ++col) {
      if (board[row][col] == 'R') {
        cout << ANSI_COLOR_RED << 'R' << ANSI_COLOR_RESET << ' ';
      } else if (board[row][col] == 'B') {
        cout << ANSI_COLOR_BLUE << 'B' << ANSI_COLOR_RESET << ' ';
      } else {
        cout << ANSI_COLOR_GREEN << '.'<< ANSI_COLOR_RESET << ' ' ;
      }
    }
    cout << '\n';
  }
}

void print_keys() {
  for (int i = 0; i < COLUMN; ++i) {
    cout << i + 1 << ' ';
  }
  cout << '\n';
}

bool is_full(const Board &board) {
  for (int row = 0; row < ROW; ++row) {
    for (int col = 0; col < COLUMN; ++col) {
      if (board[row][col] == '.') {
        return false;
      }
    }
  }
  return true;
}

struct PlayerCount {
  char to_check;
  int score;
};

struct PlaceXO {
  int row;
  int col;
};

struct Move {
  int row;
  int col;
  int score;
};

int place_move(Board &board, char player, PlaceXO place_object) {
  for (int row = ROW - 1; row >= 0; --row) {
    if (board[row][place_object.col] == '.') {
      board[row][place_object.col] = player;
      return row;
    }
  }
  return -1;
}

bool has_won(const Board &board, char player) {
  PlayerCount count{player, 0};

  // Check rows
  for (int row = 0; row < ROW; ++row) {
    for (int col = 0; col < COLUMN; ++col) {
      count.score = (board[row][col] == count.to_check) ? count.score + 1 : 0;
      if (count.score >= WIN) {
        return true;
      }
    }
    count.score = 0;
  }

  // Check columns
  for (int col = 0; col < COLUMN; ++col) {
    for (int row = 0; row < ROW; ++row) {
      count.score = (board[row][col] == count.to_check) ? count.score + 1 : 0;
      if (count.score >= WIN) {
        return true;
      }
    }
    count.score = 0;
  }

  // Check diagonals
  for (int start_row = 0; start_row <= ROW - WIN; ++start_row) {
    for (int start_col = 0; start_col <= COLUMN - WIN; ++start_col) {
      int cd1 = 0, cd2 = 0;
      for (int i = 0; i < WIN; ++i) {
        if (board[start_row + i][start_col + i] == player) {
          cd1++;
          if (cd1 == WIN) {
            return true;
          }
        } else {
          cd1 = 0;
        }

        if (board[start_row + i][start_col + WIN - 1 - i] == player) {
          cd2++;
          if (cd2 == WIN) {
            return true;
          }
        } else {
          cd2 = 0;
        }
      }
    }
  }
  return false;
}

char other_player(char player) {
  switch (player) {
  case 'R':
    return 'B';
  case 'B':
    return 'R';
  default:
    assert(false);
  }
}

Move best_move(Board &board, char player, int depth) {
  Move response, candidate;
  bool no_candidate = true;

  assert(!is_full(board));
  assert(!has_won(board, player));
  assert(!has_won(board, other_player(player)));

  for (int col = 0; col < COLUMN; ++col) {
    PlaceXO move{ROW - 1, col};
    move.row = place_move(board, player, move);
    if (move.row == -1)
      continue;

    if (has_won(board, player)) {
      board[move.row][move.col] = '.';
      return {move.row, move.col, 1};
    }
    board[move.row][move.col] = '.';
  }

  for (int col = 0; col < COLUMN; ++col) {
    int row = ROW - 1;
    while (row >= 0 && board[row][col] != '.') {
      row--;
    }
    if (row >= 0) {
      board[row][col] = player;
      if (is_full(board)) {
        board[row][col] = '.';
        return {row, col, 0};
      }
      response = best_move(board, other_player(player), depth + 1);
      board[row][col] = '.';
      if (depth > 13) {
        return {row, col, 1};
      }
      if (response.score == -1) {
        return {row, col, 1};
      } else if (response.score == 0) {
        candidate = {row, col, 0};
        no_candidate = false;
      } else {
        if (no_candidate) {
          candidate = {row, col, -1};
          no_candidate = false;
        }
      }
    }
  }
  return candidate;
}

int main() {
  int move, row;
  Board board(ROW, vector<char>(COLUMN, '.'));
  Move response;
  char current = 'X';
  char player = 'O';
  int car, start;

  cout << "Please enter 5 or 7 to choose your character! 5 for B; 7 for R: ";
  cin >> car;
  player = (car == 5) ? 'B' : 'R';
  current = player;

  init_board(board);

  cout << "Please enter 1 or 2 to start first or second respectively: ";
  cin >> start;
  current = (start == 1) ? player : other_player(player);

  while (true) {
    if (current == player) {
      print_board(board);
      cout << "\n";
      print_keys();
      cout << "Enter your move: ";
      cin >> move;

      PlaceXO place_object{ROW - 1, move - 1};
      row = place_move(board, current, place_object);
      if (row == -1) {
        cout << "Invalid move please enter a valid move\n";
        continue;
      }
    } else {
      response = best_move(board, current, 0);
      PlaceXO place_object{response.row, response.col};
      place_move(board, current, place_object);
    }
    if (has_won(board, current)) {
      print_board(board);
      cout << "Player " << current << " has won!\n";
      break;
    } else if (is_full(board)) {
      print_board(board);
      cout << "Draw.\n";
      break;
    }
    current = other_player(current);
  }

  return 0;
}