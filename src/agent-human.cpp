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
#include <mltactoe/agent-human.h>
#include <iostream>

int AgentHuman::selectMove(const TicTacToe::State& state) {
  int row = 1;
  int col = 1;
  std::cin >> row >> col;

  return row * 3 + col;
}
