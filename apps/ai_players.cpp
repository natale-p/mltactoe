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
#include <unistd.h>
#include <cstdlib>
#include <iostream>

/**
 * @brief Prints usage information.
 * @details This function prints the usage information for the program.
 * @param programName The name of the program.
 */
static void printUsage(const char* program_name) {
  std::cout << "Usage: " << program_name << " [-n num_episodes] [-x input_file] [-o input_file] [-h]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -x <input_file>     Specify the input file path for loading the 'X' model." << std::endl;
  std::cout << "  -o <input_file>     Specify the input file path for loading the 'O' model." << std::endl;
  std::cout << "  -n <num_episodes>   Specify the number of games." << std::endl;
  std::cout << "  -h                  Print this usage message." << std::endl;
}

int main(int argc, char* argv[]) {
  constexpr int kDefaultEpisodes = 5000;  ///< Default number of training episodes.
  int num_episodes = kDefaultEpisodes;    ///< Number of training episodes.
  std::string x_model;
  std::string o_model;

  // Parse command-line arguments using getopt.
  int opt = -1;
  while ((opt = getopt(argc, argv, "n:o:x:")) != -1) {
    switch (opt) {
      case 'n':
        // User has provided the number of episodes.
        num_episodes = atoi(optarg);
        if (num_episodes <= 0) {
          std::cerr << "Invalid number of episodes." << std::endl;
          return 1;
        }
        break;
      case 'o':
        o_model = optarg;
        break;
      case 'x':
        x_model = optarg;
        break;
      case 'h':
        // Print usage information and exit.
        printUsage(argv[0]);
        return 0;
      default:
        // Invalid option or missing argument.
        printUsage(argv[0]);
        return 1;
    }
  }

  if (x_model.empty() || o_model.empty()) {
    printUsage(argv[0]);
    return 1;
  }

  // Create two instances
  AgentMl agent_x;
  agent_x.setExplorationRate(0.1);
  if (!agent_x.load(x_model)) {
    std::cerr << "Cannot load file " << x_model << std::endl;
  }

  AgentMl agent_o;
  agent_o.setExplorationRate(0.1);
  if (!agent_o.load(o_model)) {
    std::cerr << "Cannot load file " << o_model << std::endl;
  }

  int games_won_by_x = 0;
  int games_won_by_o = 0;
  int draws = 0;

  for (int episode = 0; episode < num_episodes; ++episode) {
    // Reset the game.
    TicTacToe game;

    int moves = 0;
    for (int moves = 0; !game.isGameOver(); ++moves) {
      // Determine the current player.
      const char current_player = (moves % 2 == 0) ? 'X' : 'O';
      AgentMl& current_agent = (moves % 2 == 0) ? agent_x : agent_o;

      // Get the current state (Tic-Tac-Toe board configuration).
      std::vector<double> state = game.getFlattenedBoard(current_player);

      // Select action
      const int action = current_agent.selectMove(state);

      // Perform the selected action and feed-forward the reward.
      if (!game.makeMove(action, current_player)) {
        std::cerr << "Invalid move. Aborting" << std::endl;
        return 1;
      }
    }

    if (game.checkWinner() == 'X') {
      ++games_won_by_x;
    } else if (game.checkWinner() == 'O') {
      ++games_won_by_o;
    } else {
      ++draws;
    }
  }

  std::cout << "X won " << games_won_by_x << " games. " << std::endl
            << "O won " << games_won_by_o << " games. " << std::endl
            << "Draws: " << draws << std::endl;

  return 0;
}
