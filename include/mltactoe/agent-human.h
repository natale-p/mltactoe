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

#include <mltactoe/agent.h>

/**
 * @class AgentHuman
 * @brief Represents a human player agent for Tic Tac Toe game.
 * @details This class extends the Agent class and provides an implementation for
 * selecting moves by human players.
 */
class AgentHuman final : public Agent {
 public:
  /**
   * @brief Selects a move based on the current state of the game.
   * @param state The current state of the Tic Tac Toe game.
   * @return The index of the selected move.
   * @note This method is overridden from the base class Agent. In the case of
   * AgentHuman, it prompts the human player to enter their move via standard input.
   */
  int selectMove(const TicTacToe::State& state) override;
};
