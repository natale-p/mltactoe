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
#include <string>

/**
 * @class AgentMl
 * @brief Represents a machine learning-based agent for playing Tic Tac Toe.
 * @details This class extends the Agent class and provides functionality for
 * a machine learning-based agent. It utilizes a separate implementation class,
 * AgentMlImpl, to encapsulate the machine learning model and training logic.
 */
class AgentMl : public Agent {
 public:
  /**
   * @brief Default constructor.
   * @details Constructs an AgentMl object.
   */
  AgentMl();

  /**
   * @brief Destructor.
   * @details Destroys the AgentMl object and releases any allocated resources.
   */
  ~AgentMl() override;

  /**
   * @brief Copy constructor.
   * @details Deleted to prevent copying of AgentMl objects.
   */
  AgentMl(const AgentMl&) = delete;

  /**
   * @brief Move constructor.
   * @details Deleted to prevent moving of AgentMl objects.
   */
  AgentMl(AgentMl&&) = delete;

  /**
   * @brief Copy assignment operator.
   * @details Deleted to prevent copying of AgentMl objects.
   */
  AgentMl& operator=(const AgentMl&) = delete;

  /**
   * @brief Move assignment operator.
   * @details Deleted to prevent moving of AgentMl objects.
   */
  AgentMl& operator=(AgentMl&&) = delete;

  /**
   * @brief Selects a move based on the current state of the game.
   * @param state The current state of the Tic Tac Toe game.
   * @param player The player for selecting the move for.
   * @return The index of the selected move.
   * @note This method is overridden from the base class Agent and implements
   * the selection of moves using the machine learning model.
   */
  int selectMove(const TicTacToe::State& state) override;

  /**
   * @brief Set the exploration rate for the agent.
   *
   * The exploration rate determines the probability of the agent exploring a random action
   * instead of exploiting its current knowledge. A higher exploration rate encourages more
   * exploration, while a lower exploration rate favors exploitation of known strategies.
   *
   * @param exploration_rate The new exploration rate for the agent. Must be in the range [0, 1].
   */
  void setExplorationRate(double exploration_rate);

  /**
   * @brief "Rewrite" the neural network of the agent based on its action, resulting game state, and the reward
   *
   * This method updates the agent's knowledge based on the feedback received from the environment.
   * The reward is used to reinforce or discourage certain actions taken by the agent.
   *
   * @param selected_action The action selected by the agent.
   * @param reward The reward received by the agent for taking the selected action.
   * @param previous_state The state of the game before the agent's action.
   * @param current_state The state of the game after the agent's action.
   *
   * @note This method is typically called after each action taken by the agent to update its learning model.
   */
  void reward(int selected_action,
              double reward,
              const std::vector<double>& previous_state,
              const std::vector<double>& current_state);

  /**
   * @brief Loads a trained machine learning model from a file.
   * @param filename The filename of the file containing the model.
   * @return True if the model is successfully loaded, false otherwise.
   */
  bool load(const std::string& filename);

  /**
   * @brief Saves the trained machine learning model to a file.
   * @param filename The filename for saving the model.
   * @return True if the model is successfully saved, false otherwise.
   */
  bool save(const std::string& filename) const;

 private:
  /**
   * @class Impl
   * @brief Private implementation class for AgentMl.
   * @details This class encapsulates the machine learning model and training logic
   * for the AgentMl class.
   */
  class Impl;
  Impl* impl_;  ///< Pointer to the implementation object.
};
