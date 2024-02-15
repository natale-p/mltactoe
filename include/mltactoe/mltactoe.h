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

#include <vector>

/**
 * @brief The TicTacToe class
 *
 * To complete
 */
class TicTacToe final {
 public:
  using State = std::vector<double>;

  TicTacToe() noexcept;
  ~TicTacToe();

  TicTacToe(const TicTacToe&) = delete;
  TicTacToe(TicTacToe&&) = delete;
  TicTacToe& operator=(const TicTacToe&) = delete;
  TicTacToe& operator=(TicTacToe&&) = delete;

  /**
   * @brief Resets the game.
   * @details This function resets the game state, clearing the board and preparing for a new game.
   * @note This function does not throw exceptions.
   */
  void reset() noexcept;

  /**
   * @brief Displays the game board.
   * @details This function prints the current state of the game board to the console.
   * @note This function does not throw exceptions.
   */
  void displayBoard() noexcept;

  /**
   * @brief Makes a move on the game board.
   * @details This function allows a player to make a move on the game board at the specified row and column.
   * @param row The row index of the move.
   * @param col The column index of the move.
   * @param player The symbol representing the player making the move ('X' or 'O').
   * @return True if the move is valid and successfully made, false otherwise.
   * @note This function does not throw exceptions.
   */
  bool makeMove(int row, int col, char player) noexcept;

  /**
   * @brief Makes a move on a 3x3 representation of the game board.
   * @details This function allows a player to make a move on a 3x3 representation of the game board.
   * @param move The index of the move in the flattened 3x3 board.
   * @param player The symbol representing the player making the move ('X' or 'O').
   * @return True if the move is valid and successfully made, false otherwise.
   * @note This function does not throw exceptions.
   */
  bool makeMove(int move, char player) noexcept;

  /**
   * @brief Checks for a winner.
   * @details This function checks if there is a winner in the current game state.
   * @return The symbol of the winning player ('X' or 'O'), or '\0' if there is no winner yet.
   * @note This function does not throw exceptions.
   */
  char checkWinner() const noexcept;

  /**
   * @brief Checks if the game board is full.
   * @details This function checks if the game board is fully occupied by player moves.
   * @return True if the board is full, false otherwise.
   * @note This function does not throw exceptions.
   */
  bool isBoardFull() const noexcept;

  /**
   * @brief Checks if a move is valid.
   * @details This function checks if a move at the specified row and column is valid.
   * @param row The row index of the move.
   * @param col The column index of the move.
   * @return True if the move is valid, false otherwise.
   * @note This function does not throw exceptions.
   */
  bool isValidMove(int row, int col) noexcept;

  /**
   * @brief Checks the symbol at the specified position on the game board.
   * @details This function returns the symbol at the specified row and column on the game board.
   * @param row The row index of the position.
   * @param col The column index of the position.
   * @return The symbol at the specified position ('X', 'O', or '\0' if empty).
   * @note This function does not throw exceptions.
   */
  char checkSymbol(int row, int col) const noexcept;

  /**
   * @brief Checks if the game is over.
   * @details This function checks if the game is over, either due to a winner or a draw.
   * @return True if the game is over, false otherwise.
   * @note This function does not throw exceptions.
   */
  bool isGameOver() const noexcept;

  /**
   * @brief Returns available moves.
   * @details This function returns a vector containing the indices of available moves on the game board.
   * @return A vector of integers representing available moves.
   * @note This function does not throw exceptions.
   */
  std::vector<int> getAvailableMoves() const noexcept;

  /**
   * @brief Gets the flattened representation of the game board.
   * @details This function returns the flattened representation of the game board given the current player.
   * @param currentPlayer The symbol representing the current player ('X' or 'O').
   * @return The flattened state of the game board.
   * @note This function does not throw exceptions.
   */
  State getFlattenedBoard(char currentPlayer) const noexcept;

  /**
   * @brief Returns available moves.
   * @details This function returns a vector containing the indices of available moves on the game board.
   * @return A vector of integers representing available moves.
   * @note This function does not throw exceptions.
   */
  static std::vector<int> getAvailableMoves(const State& currentState) noexcept;

 private:
  class Impl;  // Forward declaration of the implementation class
  Impl* impl;  // Pointer to the implementation
};

/**
 * @mainpage Tic Tac Toe Game
 *
 * @section intro_sec Introduction
 *
 * Welcome to the documentation for the Tic Tac Toe game implementation. This program
 * provides a simple command-line interface for playing Tic Tac Toe against an AI opponent.
 *
 * @section features_sec Features
 *
 * - Allows playing Tic Tac Toe against an AI opponent.
 * - Implements Q-learning algorithm for AI decision-making.
 * - Supports both 3x3 and flattened board representations.
 * - Provides methods for resetting the game, making moves, checking for winners, and more.
 *
 * @section usage_sec Usage
 *
 * To use this program, simply include the necessary header files and link against the
 * provided source files. Then, you can interact with the Tic Tac Toe game using the
 * provided functions and classes.
 *
 * Example usage:
 * @code
 * // Create a Tic Tac Toe game instance
 * TicTacToe game;
 *
 * // Make moves and interact with the game
 * game.displayBoard();
 * game.makeMove(0, 0, 'X');
 * game.makeMove(1, 1, 'O');
 * // Continue making moves...
 *
 * // Check for a winner
 * char winner = game.checkWinner();
 * if (winner != '\0') {
 *     std::cout << "The winner is: " << winner << std::endl;
 * } else {
 *     std::cout << "It's a draw!" << std::endl;
 * }
 * @endcode
 *
 * @section reference_sec Reference
 *
 * For detailed documentation on classes, functions, and data types, please see the
 * documentation generated from the source code.
 *
 */
