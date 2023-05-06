// Function to get the best move for the computer opponent using minimax algorithm
int getMinimaxMove(vector<House>& houses, int player, int difficulty) {
    vector<House> &houses = (player == 1) ? player1 : player2; // Determine which player's houses to use
    int numHouses = houses.size() - 1; // Exclude player's store

    // Set search depth based on difficulty
    int depth;
    if (difficulty == 1) { //function + values need to be called from main of objects.cpp
        depth = 3; // Easy
    } else if (difficulty == 2) {
        depth = 5; // Medium
    } else if (difficulty == 3) {
        depth = 7; // Hard
    }

    // If depth limit reached or game over, return score
    if (depth == 0 || checkGameOver()) {
        return getScore(player);
    }

    int bestScore;
    if (player == 1) {
        // Maximize score for player 1
        bestScore = INT_MIN;
        for (int i = 0; i < numHouses; i++) {
            if (houses[i].stones == 0) {
                continue; // Skip empty houses
            }
            Board nextBoard = *this; // Create copy of board for simulation
            int extraTurn = nextBoard.moveStones(1, i); // Make move and check for extra turn
            int score = nextBoard.getMinimaxMove(1, difficulty, depth - 1); // Recursively evaluate score for next move
            if (score > bestScore) {
                bestScore = score;
            }
        }
    } else {
        // Minimize score for player 2
        bestScore = INT_MAX;
        for (int i = 0; i < numHouses; i++) {
            if (houses[i].stones == 0) {
                continue; // Skip empty houses
            }
            Board nextBoard = *this; // Create copy of board for simulation
            int extraTurn = nextBoard.moveStones(2, i); // Make move and check for extra turn
            int score = nextBoard.getMinimaxMove(2, difficulty, depth - 1); // Recursively evaluate score for next move
            if (score < bestScore) {
                bestScore = score;
            }
        }
    }
    return bestScore;
}


int getMinimaxMove(int player) {
    vector<House> &houses = (player == 1) ? player1 : player2; // Determine which player's houses to use
    int numHouses = houses.size() - 1; // Exclude player's store

    int bestMove = -1;
    int bestScore = (player == 1) ? INT_MIN : INT_MAX;

    for (int i = 0; i < numHouses; i++) {
        if (houses[i].stones == 0) {
            continue; // Skip empty houses
        }
        Board nextBoard = *this; // Create copy of board for simulation
        int extraTurn = nextBoard.moveStones(player, i); // Make move and check for extra turn
        int score = nextBoard.getMinimaxMove((player == 1) ? 2 : 1); // Recursively evaluate score for next move

        if (player == 1 && score > bestScore) {
            bestScore = score;
            bestMove = i;
        } else if (player == 2 && score < bestScore) {
            bestScore = score;
            bestMove = i;
        }
    }

    return bestMove;
}