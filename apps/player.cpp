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
#include <mltactoe/agent-ml.h>
#include <mltactoe/mltactoe.h>
#include <unistd.h>
#include <iostream>
#include <thread>

/**
 * @file player.cpp
 * @brief Main file for playing against a machine learning-based Tic Tac Toe agent.
 */

/**
 * @brief Prints usage information.
 * @param programName The name of the program.
 */
static void printUsage(const char* program_name) {
  std::cout << "Usage: " << program_name << " -f <model_file_path> [-h]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -f <model_file_path>    Specify the file path of the model." << std::endl;
  std::cout << "  -h                      Print this usage message." << std::endl;
}

/**
 * @brief clear the shell
 */
static void clearShell() {
  std::cout << "\x1B[2J\x1B[H" << std::endl;
}

/**
 * @brief Main function.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return 0 upon successful completion of the program.
 */
int main(int argc, char* argv[]) {
  const char* home_dir = getenv("HOME");
  AgentMl agent;
  TicTacToe game;
  AgentHuman human;
  std::string model_file_path = (home_dir != nullptr) ? std::string(home_dir) + "tic.bin" : "";

  // Parse command-line arguments using getopt.
  int opt = -1;
  while ((opt = getopt(argc, argv, "hf:")) != -1) {
    switch (opt) {
      case 'f':
        // User has provided the model file path.
        model_file_path = optarg;
        break;
      case 'h':
        // Print usage information and exit.
        printUsage(*argv);
        return 0;
      default:
        // Invalid option or missing argument.
        printUsage(*argv);
        return 1;
    }
  }

  // Check if the model file path is provided.
  if (model_file_path.empty()) {
    std::cerr << "Error: Model file path is not provided." << std::endl;
    printUsage(*argv);
    return 1;
  }

  agent.load(model_file_path);

  // Main game loop
  while (!game.isGameOver()) {
    clearShell();
    game.displayBoard();
    std::cout << "You are X. Select your row and column " << std::endl;
    // Human player makes a move as 'X'
    bool valid_move = false;
    while (!valid_move) {
      const int move = human.selectMove(game.getState('X'));
      valid_move = game.makeMove(move, 'X');
      if (!valid_move) {
        std::cout << " Not valid. Try again." << std::endl;
      }
    };

    // Check if game is over after human player's move
    if (game.isGameOver()) {
      break;  // Game over
    }

    clearShell();
    game.displayBoard();
    std::cout << "The AI is playing..." << std::endl;
    const std::chrono::milliseconds duration(500);
    std::this_thread::sleep_for(duration);

    valid_move = false;
    int tries = 0;
    while (!valid_move) {
      // Model selects the next move
      const int modelAction = agent.selectMove(game.getState('O'));
      valid_move = game.makeMove(modelAction, 'O');
      tries++;
      if (tries > 2) {
        std::cerr << "Infinite model loop while selecting invalid move " << modelAction << std::endl;
        return 1;
      }
    };
  }

  const char gameWinner = game.checkWinner();
  clearShell();
  game.displayBoard();

  if (gameWinner == '\0') {
    std::cout << "The game ends in a draw" << std::endl;
  } else {
    std::cout << " Game is Over. Winner is " << game.checkWinner() << std::endl;
  }

  return 0;
}
