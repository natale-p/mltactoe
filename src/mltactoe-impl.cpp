/*
 * MLTacToe, a ML Tic Tac Toe
 * Copyright (C) 2024 Natale Patriciello <natale.patriciello@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mltactoe-impl.h"
#include <iostream>

TicTacToe::Impl::Impl() {
  // Initialize the game board with empty cells
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      board[i][j] = ' ';
    }
  }
}

void TicTacToe::Impl::reset() {
  // Clear the game board by setting all cells to empty
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      board[i][j] = ' ';
    }
  }
}

void TicTacToe::Impl::displayBoard() {
  // Output the current state of the game board to the console
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << board[i][j];
      if (j < 2)
        std::cout << " | ";
    }
    std::cout << std::endl;
    if (i < 2)
      std::cout << "---------" << std::endl;
  }
}

bool TicTacToe::Impl::makeMove(int row, int col, char player) {
  // Check if the move is valid
  if (!isValidMove(row, col)) {
    // std::cout << "Invalid move! Please try again." << std::endl;
    return false;
  }

  // Place the player's symbol on the specified row and column
  board[row][col] = player;
  return true;
}

char TicTacToe::Impl::checkWinner() const {
  // Check rows
  for (int i = 0; i < 3; ++i) {
    if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return board[i][0];
    }
  }

  // Check columns
  for (int j = 0; j < 3; ++j) {
    if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
      return board[0][j];
    }
  }

  // Check diagonals
  if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return board[0][0];
  }
  if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return board[0][2];
  }

  // If no winner found, return space indicating no winner yet
  return '\0';
}

bool TicTacToe::Impl::isBoardFull() const {
  // Check if any cell is empty
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == ' ') {
        return false;  // Found an empty cell, board is not full
      }
    }
  }
  return true;  // All cells are filled, board is full
}

bool TicTacToe::Impl::isValidMove(int row, int col) {
  // Check if the cell is within the bounds of the board
  if (row < 0 || row >= 3 || col < 0 || col >= 3) {
    return false;
  }

  // Check if the cell is already occupied
  if (board[row][col] != ' ') {
    return false;
  }

  // Move is valid if it passes both conditions
  return true;
}

char TicTacToe::Impl::checkSymbol(int row, int col) const {
  if (row < 0 || row >= 3 || col < 0 || col >= 3) {
    return '\0';
  }

  return board[row][col];
}

std::vector<double> TicTacToe::Impl::getFlattenedBoard(char currentPlayer) const {
  std::vector<double> flattenedBoard;
  for (size_t row = 0; row < 3; ++row) {
    for (size_t col = 0; col < 3; ++col) {
      char cell = board[row][col];
      if (cell == ' ') {
        flattenedBoard.push_back(0.0);
      } else if (cell == currentPlayer) {
        flattenedBoard.push_back(1.0);
      } else {
        flattenedBoard.push_back(-1.0);
      }
    }
  }
  return flattenedBoard;
}

std::vector<int> TicTacToe::Impl::getAvailableMoves() const {
  std::vector<int> availableMoves;

  // Iterate over each cell in the board
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      // If the cell is empty, it's available for a move
      if (board[row][col] == ' ') {
        // Convert row and column indices to an integer representing the move
        int action = row * 3 + col;
        availableMoves.push_back(action);
      }
    }
  }

  return availableMoves;
}

std::vector<int> TicTacToe::Impl::getAvailableMoves(const State& currentState) {
  std::vector<int> availableMoves;

  // Iterate over each cell in the board
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      // Convert row and column indices to an integer representing the move
      int action = row * 3 + col;
      // If the cell is empty, it's available for a move
      if (currentState[action] == 0.0) {
        availableMoves.push_back(action);
      }
    }
  }

  return availableMoves;
}
