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
 * @file trainer.cpp
 * @brief Main file for training and saving a machine learning-based Tic Tac Toe agent.
 * @details This file contains the main function, which trains a machine learning-based
 * Tic Tac Toe agent for a specified number of episodes and saves the trained model to a file.
 */

/**
 * @brief Prints usage information.
 * @details This function prints the usage information for the program.
 * @param programName The name of the program.
 */
static void printUsage(const char* program_name) {
  std::cout << "Usage: " << program_name << " [-o output_file] [-n num_episodes] [-h]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -o <output_file>    Specify the output file path for saving the model (default: $HOME/tic.bin)."
            << std::endl;
  std::cout << "  -n <num_episodes>   Specify the number of training episodes (default: 5000)." << std::endl;
  std::cout << "  -v                  Be verbose." << std::endl;
  std::cout << "  -h                  Print this usage message." << std::endl;
}

/**
 * @brief Main function.
 * @details The main function creates an instance of the AgentMl class, trains it for a
 * specified number of episodes, and saves the trained model to a file.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return 0 upon successful completion of the program.
 */
int main(int argc, char* argv[]) {
  constexpr int kDefaultEpisodes = 5000;                                     ///< Default number of training episodes.
  int num_episodes = kDefaultEpisodes;                                       ///< Number of training episodes.
  const char* home_dir = getenv("HOME");                                     ///< Home directory
  std::string file_path = (home_dir != nullptr) ? std::string(home_dir) + "/tic" : "";  ///< Default file path
  bool verbose = false;

  const double final_exploration_percentage = 0.4;  // Change this to the percentage where you want exploration to stop.
  const double initial_exploration_rate = 1.0;
  const double final_exploration_rate = 0.1;

  // Parse command-line arguments using getopt.
  int opt = -1;
  while ((opt = getopt(argc, argv, "hvo:n:")) != -1) {
    switch (opt) {
      case 'o':
        // User has provided a custom file path.
        file_path = optarg;
        break;
      case 'n':
        // User has provided the number of episodes.
        num_episodes = atoi(optarg);
        if (num_episodes <= 0) {
          std::cerr << "Invalid number of episodes." << std::endl;
          return 1;
        }
        break;
      case 'h':
        // Print usage information and exit.
        printUsage(*argv);
        return 0;
      case 'v':
        verbose = true;
        break;
      default:
        // Invalid option or missing argument.
        printUsage(*argv);
        return 1;
    }
  }

  const int final_exploration_episode = static_cast<int>(num_episodes * final_exploration_percentage);

  // Create two instances
  AgentMl agent_x;
  AgentMl agent_o;

  int games_won_by_x = 0;
  int games_won_by_o = 0;

  // Training loop.
  for (int episode = 0; episode < num_episodes; ++episode) {
    if (verbose) {
      std::cout << "=============== EPISODE " << std::to_string(episode) << " ===================" << std::endl;
    }
    // Reset the game.
    TicTacToe game;

    // Calculate exploration rate for this episode.
    double exploration_rate = final_exploration_rate;
    if (episode < final_exploration_episode) {
      // Linear decay: exploration_rate = initial_exploration_rate - (episode / final_exploration_episode) *
      // (initial_exploration_rate - final_exploration_rate)
      exploration_rate = initial_exploration_rate - ((episode / static_cast<double>(final_exploration_episode)) *
                                                     (initial_exploration_rate - final_exploration_rate));
    }
    if (verbose) {
      std::cout << "Setting exploration rate to " << exploration_rate << std::endl;
    }
    agent_x.setExplorationRate(exploration_rate);
    agent_o.setExplorationRate(exploration_rate);

    std::vector<double> previous_state;
    std::vector<double> starting_state;
    std::vector<double> current_state;
    AgentMl* current_agent = &agent_x;
    AgentMl* previous_agent = &agent_o;
    char current_player = 'X';
    int action = 0;
    int previous_action = 0;

    // Forward pass and backpropagation for each step in the episode.
    for (int moves = 0; !game.isGameOver(); ++moves) {
      // Determine the current and previous player.
      current_player = (moves % 2 == 0) ? 'X' : 'O';
      current_agent = (moves % 2 == 0) ? &agent_x : &agent_o;
      previous_agent = (moves % 2 == 0) ? &agent_o : &agent_x;

      // Get the Tic-Tac-Toe board configuration before the move.
      starting_state = previous_state;
      previous_state = game.getState(current_player);

      // Select action
      previous_action = action;
      action = current_agent->selectMove(previous_state);

      // Perform the selected action and feed-forward the reward.
      if (!game.makeMove(action, current_player)) {
        std::cerr << "Invalid move. Aborting" << std::endl;
        return 1;
      }

      // Get the Tic-Tac-Toe board configuration after the move.
      current_state = game.getState(current_player);
    }

    if (game.checkWinner() != '\0') {
      constexpr double kWinningReward = 1.0;
      current_agent->reward(action, kWinningReward, previous_state, current_state);
      previous_agent->reward(previous_action, -kWinningReward, starting_state, previous_state);
    } else {
      constexpr double kDrawingReward = 0.5;
      current_agent->reward(action, kDrawingReward, previous_state, current_state);
      previous_agent->reward(previous_action, kDrawingReward, starting_state, previous_state);
    }

    if (game.checkWinner() == 'X') {
      ++games_won_by_x;
    } else if (game.checkWinner() == 'O') {
      ++games_won_by_o;
    }

    if (verbose) {
      game.displayBoard();
      std::cout << " Winner is " << game.checkWinner() << std::endl;
      std::cout << "=============== EPISODE " << std::to_string(episode) << " ===================" << std::endl
                << std::endl
                << std::endl;
    }
  }

  if (verbose) {
    std::cout << "X won " << games_won_by_x << " times. O won " << games_won_by_o << " times." << std::endl;
  }

  // Save the trained model to the specified file path.
  if (agent_x.save(file_path + "_x.bin")) {
    std::cout << "Model for 'X' saved successfully to: " << file_path + "_x.bin" << std::endl;
  } else {
    std::cerr << "Failed to save the model to: " << file_path + "_x.bin" << std::endl;
    return 1;  // Return error code if saving fails.
  }

  // Save the trained model to the specified file path.
  if (agent_o.save(file_path + "_o.bin")) {
    std::cout << "Model for 'O' saved successfully to: " << file_path + "_o.bin" << std::endl;
  } else {
    std::cerr << "Failed to save the model to: " << file_path + "_o.bin" << std::endl;
    return 1;  // Return error code if saving fails.
  }

  return 0;
}
