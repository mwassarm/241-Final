#include <iostream>
#include <vector>

using namespace std;

// Define a struct to represent a house on the board
struct House {
    int stones; // The number of stones in the house
    bool isStore; // Whether the house is a store
    House(int s = 4, bool st = false) : stones(s), isStore(st) {} // Constructor to initialize the number of stones and whether it is a store
};

// Define a class to represent the game board
class Board {
private:
    vector<House> player1; // Houses for player 1
    vector<House> player2; // Houses for player 2
public:
    Board() {
        // Initialize the board with 4 stones in each house and set the stores
        for (int i = 0; i < 6; i++) {
            player1.push_back(House());
            player2.push_back(House());
        }
        player1.push_back(House(0, true)); // The last house for player 1 is the store
        player2.push_back(House(0, true)); // The last house for player 2 is the store
    }
    void displayBoard() {
        // Display the board
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

    void moveStones(int player, int houseIndex, bool isHumanPlayer) {
    vector<House>& houses = (player == 1) ? player1 : player2; // Determine which player's houses to use
    House& selectedHouse = houses[houseIndex];
    if (selectedHouse.stones == 0) {
        cout << "Invalid move: Selected house is empty" << endl;
        return;
    }
    selectedHouse.stones = 0; // Remove all stones from the selected house
    int numStones = selectedHouse.stones;
    int currentIndex = houseIndex + 1;
    while (numStones > 0) {
        // Loop through consecutive houses and add one stone to each
        if (currentIndex == 6 && player == 1) {
            // Skip opponent's store
            currentIndex = 0;
            continue;
        } else if (currentIndex == 13 && player == 2) {
            // Skip opponent's store
            currentIndex = 7;
            continue;
        }
        House& currentHouse = houses[currentIndex];
        currentHouse.stones++;
        numStones--;
        currentIndex++;
    }
    // Check if last stone was placed in the player's store
    if ((currentIndex == 6 && player == 1) || (currentIndex == 13 && player == 2)) {
        cout << "You get to take another turn!" << endl;
        return;
    }
    // Check if last stone was placed in an empty house on the player's side
    if (numStones == 0 && currentIndex >= 0 && currentIndex <= 5 && houses[currentIndex].stones == 1) {
        int oppositeIndex = 12 - currentIndex;
        int capturedStones = houses[oppositeIndex].stones;
        houses[oppositeIndex].stones = 0;
        houses[currentIndex].stones = 0;
        houses[player - 1].stones += capturedStones + 1; // Add captured stones to player's store
    }
    else if (!isHumanPlayer) { // If the current player is the computer player
        // Call the bot engine's getMove function to get the computer's move
        int computerMove = getMinimaxMove(houses, player);
        cout << "Computer player selects house " << computerMove + 1 << endl;
        moveStones(player, computerMove, false); // Make the computer's move recursively
    }
}

};
};


/*
Main...

Button to select how many stones in each house (4,5,6)

Button to select difficulty level for engine

*/
