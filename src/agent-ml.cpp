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
#include <mltactoe/agent-ml.h>
#include "agent-ml-impl.h"

AgentMl::AgentMl() : impl_(new Impl()) {}

AgentMl::~AgentMl() {
  delete impl_;
}

int AgentMl::selectMove(const TicTacToe::State& state) {
  return impl_->selectMove(state);
}

void AgentMl::setExplorationRate(double exploration_rate) {
  impl_->setExplorationRate(exploration_rate);
}

void AgentMl::reward(int selected_action,
                     double reward,
                     const std::vector<double>& previous_state,
                     const std::vector<double>& current_state) {
  impl_->reward(selected_action, reward, previous_state, current_state);
}

bool AgentMl::load(const std::string& filename) {
  return impl_->load(filename);
}

bool AgentMl::save(const std::string& filename) const {
  return impl_->save(filename);
}
