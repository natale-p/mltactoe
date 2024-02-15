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

/**
 * @class Agent
 * @brief Abstract base class for representing an agent in a Tic Tac Toe game.
 * @details This class defines an interface for agents that can select moves in a Tic Tac Toe game.
 *
 * Agents implementing this interface should provide an implementation for the selectMove() method,
 * which selects a move based on the current state of the game.
 */
class Agent {
 public:
  /**
   * @brief Constructor.
   * @details Default constructor.
   */
  Agent() = default;

  /**
   * @brief Destructor.
   * @details A virtual destructor to ensure proper cleanup of derived classes.
   */
  virtual ~Agent() = default;

  /**
   * @brief Copy constructor.
   * @details Deleted to prevent copying of Agent objects.
   */
  Agent(const Agent&) = delete;

  /**
   * @brief Move constructor.
   * @details Deleted to prevent moving of Agent objects.
   */
  Agent(Agent&&) = delete;

  /**
   * @brief Copy assignment operator.
   * @details Deleted to prevent copying of Agent objects.
   */
  Agent& operator=(const Agent&) = delete;

  /**
   * @brief Move assignment operator.
   * @details Deleted to prevent moving of Agent objects.
   */
  Agent& operator=(Agent&&) = delete;

  /**
   * @brief Selects a move based on the current state of the game.
   * @param state The current state of the Tic Tac Toe game.
   * @return The index of the selected move.
   * @note This method must be implemented by derived classes.
   */
  virtual int selectMove(const TicTacToe::State& state) = 0;
};
