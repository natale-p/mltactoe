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
#include "agent-ml-impl.h"

AgentMl::Impl::Impl() : q_network_(mlpack::MeanSquaredError(), mlpack::RandomInitialization()) {
  // Define the architecture of the Q-network.
  constexpr int kInputLayers = 27;
  constexpr int kHiddenLayers = 256;
  constexpr int kOutputLayers = 9;
  q_network_.Add<mlpack::Linear>(kInputLayers);  // Input layer (27 cells) -> Hidden layer with 256 units.
  q_network_.Add<mlpack::ReLU>();       // ReLU activation function for the hidden layer.
  q_network_.Add<mlpack::Linear>(kHiddenLayers);  // Hidden layer with 256 units.
  q_network_.Add<mlpack::ReLU>();       // ReLU activation function for the hidden layer.
  q_network_.Add<mlpack::Linear>(kOutputLayers);  // Output layer (Q-values for 9 possible actions).
}

int AgentMl::Impl::selectMove(const TicTacToe::State& state) {
  std::vector<int> avail_actions = TicTacToe::getAvailableMoves(state);
  assert(avail_actions.size() > 0);

  if (mlpack::Random() < exploration_rate_) {
    // Explore the possible move randomly
    const int idx = mlpack::RandInt(static_cast<int>(avail_actions.size()));
    return avail_actions.at(idx);
  }

  // Select action based on epsilon-greedy policy.
  arma::mat prediction;
  q_network_.Predict(state, prediction);

  arma::uvec indices(avail_actions.size());
  for (size_t i = 0; i < avail_actions.size(); ++i) {
    indices(i) = avail_actions[i];
  }

  arma::mat avail_q_values = prediction.elem(indices);
  return avail_actions[avail_q_values.index_max()];
}

void AgentMl::Impl::reward(int selected_action,
                           double reward,
                           const std::vector<double>& previous_state,
                           const std::vector<double>& current_state) {
  arma::mat previous_q;
  q_network_.Predict(previous_state, previous_q);

  previous_q(selected_action) = reward;

  /*
  arma::mat current_q;
  q_network_.Predict(current_state, current_q);
  // Update the Q-value for the selected action using the Q-learning update rule.
  const double target = reward + discount_factor_ * avail_actions[avail_q_values.index_max()];
  const double delta = target - previous_q(selected_action);  // Temporal difference error
  previous_q(selected_action) += 0.5 * delta;                 // Update Q-value
  */

  ens::Adam optimizer;

  // Train the neural network using the updated Q-values.
  q_network_.Train(previous_state, previous_q, optimizer);
}

void AgentMl::Impl::setExplorationRate(double exploration_rate) {
  if (exploration_rate <= 1.0) {
    exploration_rate_ = exploration_rate;
  } else {
    std::cerr << "Exploration rate of " << exploration_rate << " not valid." << std::endl;
  }
}

bool AgentMl::Impl::load(const std::string& filename) {
  return q_network_.Parameters().load(filename);
}

bool AgentMl::Impl::save(const std::string& filename) const {
  return q_network_.Parameters().save(filename, arma::arma_binary);
}
