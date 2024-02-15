#include <gtest/gtest.h>
#include <mltactoe/mltactoe.h>

TEST(TicTacToeTest, ConstructorTest) {
  TicTacToe game;
  // Make some moves
  game.makeMove(0, 0, 'X');
  game.makeMove(1, 1, 'O');
  game.makeMove(2, 2, 'X');
  // Reset the game
  game.reset();
  // Check that the game board is reset to its initial state
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(game.checkSymbol(i, j), ' ');
    }
  }
}

// Test case for the makeMove method
TEST(TicTacToeTest, MakeMoveTest) {
  TicTacToe game;
  // Make a valid move
  EXPECT_TRUE(game.makeMove(0, 0, 'X'));
  EXPECT_FALSE(game.isGameOver());
  // Make an invalid move (same position)
  EXPECT_FALSE(game.makeMove(0, 0, 'O'));
  EXPECT_FALSE(game.isGameOver());
  // Make an invalid move (out of bounds)
  EXPECT_FALSE(game.makeMove(3, 3, 'X'));
  EXPECT_FALSE(game.isGameOver());
}

// Test case for the checkWinner method
TEST(TicTacToeTest, CheckWinnerTest) {
  TicTacToe game;
  // Test horizontal win
  game.makeMove(0, 0, 'X');
  game.makeMove(0, 1, 'X');
  game.makeMove(0, 2, 'X');
  EXPECT_EQ(game.checkWinner(), 'X');
  EXPECT_TRUE(game.isGameOver());

  // Test vertical win
  game.reset();
  game.makeMove(0, 0, 'O');
  game.makeMove(1, 0, 'O');
  game.makeMove(2, 0, 'O');
  EXPECT_EQ(game.checkWinner(), 'O');
  EXPECT_TRUE(game.isGameOver());

  // Test diagonal win
  game.reset();
  game.makeMove(0, 0, 'X');
  game.makeMove(1, 1, 'X');
  game.makeMove(2, 2, 'X');
  EXPECT_EQ(game.checkWinner(), 'X');
  EXPECT_TRUE(game.isGameOver());
}

// Test case for the isBoardFull method
TEST(TicTacToeTest, IsBoardFullTest) {
  TicTacToe game;
  // Fill the board without a winner
  game.makeMove(0, 0, 'X');
  game.makeMove(0, 1, 'O');
  game.makeMove(0, 2, 'X');
  game.makeMove(1, 0, 'X');
  game.makeMove(1, 1, 'O');
  game.makeMove(1, 2, 'O');
  game.makeMove(2, 0, 'O');
  game.makeMove(2, 1, 'X');
  game.makeMove(2, 2, 'O');
  EXPECT_TRUE(game.isBoardFull());

  // Reset the game and fill only part of the board
  game.reset();
  game.makeMove(0, 0, 'X');
  game.makeMove(0, 1, 'O');
  game.makeMove(0, 2, 'X');
  EXPECT_FALSE(game.isBoardFull());
}

// Test case for the isValidMove method
TEST(TicTacToeTest, IsValidMoveTest) {
  TicTacToe game;
  // Make a valid move
  EXPECT_TRUE(game.isValidMove(0, 0));
  // Make an invalid move (same position)
  game.makeMove(0, 0, 'X');
  EXPECT_FALSE(game.isValidMove(0, 0));
  // Make an invalid move (out of bounds)
  EXPECT_FALSE(game.isValidMove(3, 3));
}

// Test case for a full game scenario
TEST(TicTacToeTest, FullGameTest) {
  TicTacToe game;
  // Play a full game
  game.makeMove(0, 0, 'X');
  game.makeMove(0, 1, 'O');
  game.makeMove(1, 1, 'X');
  game.makeMove(1, 0, 'O');
  game.makeMove(2, 2, 'X');
  game.makeMove(2, 0, 'O');
  game.makeMove(0, 2, 'X');
  game.makeMove(1, 2, 'O');
  game.makeMove(2, 1, 'X');
  // Check for a winner
  EXPECT_EQ(game.checkWinner(), 'X');
  // Check that the board is full
  EXPECT_TRUE(game.isBoardFull());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
