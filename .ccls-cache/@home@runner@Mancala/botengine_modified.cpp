//The function should return the best move for the computer opponent, but it currently returns the best score
//The function now includes an optional parameter currentDepth to keep track of the current depth in the recursion. The function returns the best move (house index) for the computer opponent at the top level (currentDepth == 0) and the best score during recursion (currentDepth > 0).


int getMinimaxMove(int player, int difficulty, int currentDepth = 0) {
  vector<House> &houses = (player == 1) ? player1 : player2;
  int numHouses = houses.size() - 1;

  int depth;
  if (difficulty == 1) {
    depth = 3;
  } else if (difficulty == 2) {
    depth = 5;
  } else if (difficulty == 3) {
    depth = 7;
  }

  if (currentDepth == depth || checkGameOver()) {
    return getScore(player);
  }

  int bestScore;
  int bestMove = -1;
  if (player == 1) {
    bestScore = INT_MIN;
    for (int i = 0; i < numHouses; i++) {
      if (houses[i].stones == 0) {
        continue;
      }
      Board nextBoard = *this;
      int extraTurn = nextBoard.moveStones(1, i);
      int nextPlayer = (extraTurn == 1) ? 1 : 2;
      int score =
          nextBoard.getMinimaxMove(nextPlayer, difficulty, currentDepth + 1);
      if (score > bestScore || bestMove == -1) {
        bestScore = score;
        bestMove = i;
      }
    }
  } else {
    bestScore = INT_MAX;
    for (int i = 0; i < numHouses; i++) {
      if (houses[i].stones == 0) {
        continue;
      }
      Board nextBoard = *this;
      int extraTurn = nextBoard.moveStones(2, i);
      int nextPlayer = (extraTurn == 1) ? 2 : 1;
      int score =
          nextBoard.getMinimaxMove(nextPlayer, difficulty, currentDepth + 1);
      if (score < bestScore || bestMove == -1) {
        bestScore = score;
        bestMove = i;
      }
    }
  }

  if (currentDepth == 0) {
    return bestMove; // Return the best move at the top level
  } else {
    return bestScore; // Return the best score during recursion
  }
}
