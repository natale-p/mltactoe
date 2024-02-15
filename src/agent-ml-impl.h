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

#include <mltactoe/agent-ml.h>
#include <mlpack.hpp>

class AgentMl::Impl {
 public:
  Impl();

  int selectMove(const TicTacToe::State& state);
  void reward(int selected_action,
              double reward,
              const std::vector<double>& previous_state,
              const std::vector<double>& current_state);
  void setExplorationRate(double exploration_rate);

  bool load(const std::string& filename);
  bool save(const std::string& filename) const;

 private:
  mlpack::FFN<mlpack::MeanSquaredError, mlpack::RandomInitialization> q_network_;
  double discount_factor_ = 0.4;
  double exploration_rate_ = 0.0;
  static constexpr bool verbose_ = false;
};
