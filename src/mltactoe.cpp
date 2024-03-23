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
#include <mltactoe/mltactoe.h>
#include "mltactoe-impl.h"

TicTacToe::TicTacToe() noexcept : impl(new Impl()) {}

TicTacToe::~TicTacToe() {
  delete impl;
}

void TicTacToe::reset() noexcept {
  impl->reset();
}

void TicTacToe::displayBoard() noexcept {
  impl->displayBoard();
}

bool TicTacToe::makeMove(int row, int col, char player) noexcept {
  return impl->makeMove(row, col, player);
}

bool TicTacToe::makeMove(int move, char player) noexcept {
  const int row = move / 3;
  const int col = move % 3;
  return impl->makeMove(row, col, player);
}

char TicTacToe::checkWinner() const noexcept {
  return impl->checkWinner();
}

bool TicTacToe::isBoardFull() const noexcept {
  return impl->isBoardFull();
}

bool TicTacToe::isValidMove(int row, int col) noexcept {
  return impl->isValidMove(row, col);
}

char TicTacToe::checkSymbol(int row, int col) const noexcept {
  return impl->checkSymbol(row, col);
}

bool TicTacToe::isGameOver() const noexcept {
  return isBoardFull() || checkWinner() != '\0';
}

std::vector<int> TicTacToe::getAvailableMoves() const noexcept {
  return impl->getAvailableMoves();
}

TicTacToe::State TicTacToe::getState(char currentPlayer) const noexcept {
  return impl->getState();
}

std::vector<int> TicTacToe::getAvailableMoves(const State& currentState) noexcept {
  return Impl::getAvailableMoves(currentState);
}
