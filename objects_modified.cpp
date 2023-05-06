// moveStones() function return a value to indicate whether the player has an extra turn, as it was suggested in the comment now
//checkGameOver() - When the function is called, you can check the returned value to know if the player has an extra turn or not.


#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct House {
  int stones;
  bool isStore;

  House(int s = 4, bool st = false) : stones(s), isStore(st) {}
};

class Board {
private:
  vector<House> player1;
  vector<House> player2;

public:
  Board() {
    for (int i = 0; i < 6; i++) {
      player1.push_back(House());
      player2.push_back(House());
    }
    player1.push_back(House(0, true)); // Player 1's store
    player2.push_back(House(0, true)); // Player 2's store
  }

  void displayBoard() {
    cout << "Player 2: Store: " << player2.back().stones << endl;
    for (int i = 5; i >= 0; i--) {
      cout << "\t" << player2[i].stones << "\t";
    }
    cout << endl << player1.back().stones << "\t";
    for (int i = 0; i < 6; i++) {
      cout << "\t" << player1[i].stones << "\t";
    }
    cout << endl << "\tPlayer 1: Store: " << player1.back().stones << endl;
  }

  int moveStones(int player, int houseIndex) {
    vector<House> &houses = (player == 1) ? player1 : player2;
    vector<House> &opponentHouses = (player == 1) ? player2 : player1;
    House &selectedHouse = houses[houseIndex];

    if (selectedHouse.stones == 0) {
      cout << "Invalid move: Selected house is empty" << endl;
      return -1;
    }

    int numStones = selectedHouse.stones;
    selectedHouse.stones = 0;
    int currentIndex = houseIndex + 1;
    bool extraTurn = false;

    while (numStones > 0) {
      if (currentIndex == 6) {
        if (player == 1) {
          houses[currentIndex].stones++; // Add to player's store
          numStones--;
          if (numStones == 0) {
            extraTurn = true;
          }
        }
        currentIndex = 0; // Switch to the opponent's houses
        swap(houses,
             opponentHouses); // Change added: Swap houses and opponentHouses
        continue;
      }

      houses[currentIndex].stones++;
      numStones--;
      currentIndex++;
    }

    //currentIndex--; // Adjust index to the last house that received a stone

    if (!extraTurn && !houses[currentIndex].isStore &&
        houses[currentIndex].stones == 1 && currentIndex >= 0 &&
        currentIndex < 6) {
      int oppositeIndex = 5 - currentIndex;
      int capturedStones = opponentHouses[oppositeIndex].stones;
      opponentHouses[oppositeIndex].stones = 0;
      houses[currentIndex].stones = 0;
      houses[6].stones += capturedStones + 1;
    }

    if (!extraTurn) {
      swap(houses,
           opponentHouses); // Change added: Swap houses and opponentHouses back
    }

    return extraTurn ? 1 : 0;
  }

  bool checkGameOver() {
    bool gameOver = true;
    for (int p = 1; p <= 2; p++) {
      vector<House> &houses = (p == 1) ? player1 : player2;
      gameOver = true;

      for (int i = 0; i < 6; i++) {
        if (houses[i].stones > 0) {
          gameOver = false;
          break;
        }
      }

      if (gameOver) {
        // Move the remaining stones to the respective player's store
        for (int i = 0; i < 6; i++) {
          vector<House> &opponentHouses = (p == 1) ? player2 : player1;
          houses[6].stones += opponentHouses[i].stones;
          opponentHouses[i].stones = 0;
        }
        break;
      }
    }
    return gameOver;
  }
};
