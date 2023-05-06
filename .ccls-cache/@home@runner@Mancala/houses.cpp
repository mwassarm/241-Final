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
    // Add functions to manipulate the board, such as moveStones and checkWinCondition