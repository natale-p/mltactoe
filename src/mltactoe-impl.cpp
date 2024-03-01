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
  reset();
}

void TicTacToe::Impl::reset() {
  // Clear the game board by setting all cells to empty
  board_.fill(' ');
}

void TicTacToe::Impl::displayBoard() const {
  // Output the current state of the game board to the console
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      std::cout << accessBoardAt(row, col);
      if (col < 2) {
        std::cout << " | ";
      }
    }
    std::cout << std::endl;
    if (row < 2) {
      std::cout << "---------" << std::endl;
    }
  }
}

bool TicTacToe::Impl::makeMove(int row, int col, char player) {
  // Check if the move is valid
  if (!isValidMove(row, col)) {
    // std::cout << "Invalid move! Please try again." << std::endl;
    return false;
  }

  // Place the player's symbol on the specified row and column
  accessBoardAt(row, col) = player;
  return true;
}

char TicTacToe::Impl::checkWinner() const {
  // Check rows
  for (int row = 0; row < 3; ++row) {
    if (accessBoardAt(row, 0) != ' ' && accessBoardAt(row, 0) == accessBoardAt(row, 1) &&
        accessBoardAt(row, 1) == accessBoardAt(row, 2)) {
      return accessBoardAt(row, 0);
    }
  }

  // Check columns
  for (int col = 0; col < 3; ++col) {
    if (accessBoardAt(0, col) != ' ' && accessBoardAt(0, col) == accessBoardAt(1, col) &&
        accessBoardAt(1, col) == accessBoardAt(2, col)) {
      return accessBoardAt(0, col);
    }
  }

  // Check diagonals
  if (accessBoardAt(0, 0) != ' ' && accessBoardAt(0, 0) == accessBoardAt(1, 1) &&
      accessBoardAt(1, 1) == accessBoardAt(2, 2)) {
    return accessBoardAt(0, 0);
  }
  if (accessBoardAt(0, 2) != ' ' && accessBoardAt(0, 2) == accessBoardAt(1, 1) &&
      accessBoardAt(1, 1) == accessBoardAt(2, 0)) {
    return accessBoardAt(0, 2);
  }

  // If no winner found, return space indicating no winner yet
  return '\0';
}

bool TicTacToe::Impl::isBoardFull() const {
  // Check if any cell is empty
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (accessBoardAt(row, col) == ' ') {
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
  if (accessBoardAt(row, col) != ' ') {
    return false;
  }

  // Move is valid if it passes both conditions
  return true;
}

char TicTacToe::Impl::checkSymbol(int row, int col) const {
  if (row < 0 || row >= 3 || col < 0 || col >= 3) {
    return '\0';
  }

  return accessBoardAt(row, col);
}

std::vector<double> TicTacToe::Impl::getFlattenedBoard(char currentPlayer) const {
  std::vector<double> flattenedBoard;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      const char cell = accessBoardAt(row, col);
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
      if (accessBoardAt(row, col) == ' ') {
        // Convert row and column indices to an integer representing the move
        availableMoves.push_back(row * 3 + col);
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
      const int action = row * 3 + col;
      // If the cell is empty, it's available for a move
      if (currentState[action] == 0.0) {
        availableMoves.push_back(action);
      }
    }
  }

  return availableMoves;
}
