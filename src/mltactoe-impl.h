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
#pragma once
#include <mltactoe/mltactoe.h>
#include <array>

class TicTacToe::Impl {
 public:
  Impl();

  void reset();                                  // Reset the game
  void displayBoard() const;                     // Display the game board
  bool makeMove(int row, int col, char player);  // Make a move
  char checkWinner() const;                      // Check for a winner
  bool isBoardFull() const;                      // Check if the board is full
  bool isValidMove(int row, int col);            // Check if a move is valid
  char checkSymbol(int row, int col) const;
  State getFlattenedBoard(char currentPlayer) const;
  std::vector<int> getAvailableMoves() const;

  static std::vector<int> getAvailableMoves(const State& currentState);

 private:
  static constexpr int kSize = 9;

  char& accessBoardAt(int row, int col) { return board_.at(row * 3 + col); }
  const char& accessBoardAt(int row, int col) const { return board_.at(row * 3 + col); }

  std::array<char, kSize> board_ {};  // Game board
};
