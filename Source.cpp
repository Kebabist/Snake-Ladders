#include <iostream> // for input/output
#include <vector> // for vector
#include <cstdlib> // for rand and srand
#include <ctime> // for time
using namespace std;
// A class to represent a cell on the board
class Cell {
public:
    // The cell number
    int number;
    // The type of the cell: 'N' for normal, 'S' for snake head, 'L' for ladder start
    char type;
    // The destination of the cell if it is a snake head or a ladder start
    int destination;
    // The constructor
    Cell(int number, char type = 'N', int destination = -1) {
        this->number = number;
        this->type = type;
        this->destination = destination;
    }
};

// A class to represent a player
class Player {
public:
    // The player number
    int number;
    // The current position of the player on the board
    int position;
    // The constructor
    Player(int number) {
        this->number = number;
        this->position = 1; // All players start from cell 1
    }
};

// A class to represent the game
class Game {
public:
    // The number of players
    int k;
    // The number of rows of the board
    int m;
    // The number of columns of the board
    int n;
    // The number of snakes on the board
    int s;
    // The number of ladders on the board
    int l;
    // The vector of cells on the board
    vector<Cell> board;
    // The vector of players in the game
    vector<Player> players;
    // The constructor
    Game() {
        // Read the input from the user
        cin >> k >> m >> n >> s;
        // Create the board with normal cells
        for (int i = 1; i <= m * n; i++) {
            board.push_back(Cell(i));
        }
        // Add the snakes to the board
        for (int i = 0; i < s; i++) {
            int head, tail;
            cin >> head >> tail;
            board[head - 1].type = 'S';
            board[head - 1].destination = tail;
        }
        // Add the ladders to the board
        cin >> l;
        for (int i = 0; i < l; i++) {
            int start, end;
            cin >> start >> end;
            board[start - 1].type = 'L';
            board[start - 1].destination = end;
        }
        // Create the players
        for (int i = 1; i <= k; i++) {
            players.push_back(Player(i));
        }
    }

    // A method to roll a dice and return a random number between 1 and 6
    int rollDice() {
        return rand() % 6 + 1;
    }

    // A method to move a player according to the dice number and the board rules
    void movePlayer(Player& player, int dice) {
        // Store the previous position of the player
        int prev = player.position;
        // Update the current position of the player by adding the dice number
        player.position += dice;
        // Check if the player reached or exceeded the last cell
        if (player.position >= m * n) {
            player.position = m * n; // Set the position to the last cell
            cout << "player " << player.number << " won the game.\n"; // Announce the winner
            return; // No need to move further
        }
        // Check if the current cell is a snake head or a ladder start
        char type = board[player.position - 1].type;
        if (type == 'S' || type == 'L') {
            // Update the current position of the player by moving to the destination cell
            player.position = board[player.position - 1].destination;
        }
        // Print the move information of the player
        cout << "player " << player.number << " played with dice number " << dice
            << ", previous position: " << prev << ", current position: " << player.position << "\n";

        // Check if any other player is knocked out by this move
        for (Player& other : players) {
            if (other.number != player.number && other.position == player.position) {
                other.position = 1; // Move the other player back to cell 1
                cout << "player " << other.number << " is knocked out with player " << player.number << "\n";
            }
        }
    }
    // A method to print the board in a grid format
    void printBoard() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Get the cell number and type at the current position
                int cell = board[i * n + j].number;
                char type = board[i * n + j].type;
                // Print the cell number with a space or a symbol depending on the type
                if (type == 'N') {
                    cout << cell << " ";
                }
                else if (type == 'S') {
                    cout << "🐍 ";
                }
                else if (type == 'L') {
                    cout << "🪜 ";
                }
            }
            cout << "\n"; // Print a new line after each row
        }
    }
    // A method to print the positions of all the players
    void printPositions() {
        for (Player& player : players) {
            cout << "player " << player.number << " is at cell " << player.position << "\n";
        }
    }

    // A method to check if the game is over
    bool isGameOver() {
        // The game is over if any player reaches the last cell
        for (Player& player : players) {
            if (player.position == m * n) {
                return true;
            }
        }
        return false;
    }

    // A method to start the game and play until it is over
    void playGame() {
        // Print the initial board and positions
        printBoard();
        printPositions();
        // Loop until the game is over
        while (!isGameOver()) {
            // Loop through all the players in order
            for (Player& player : players) {
                // Roll a dice for the current player and move him/her accordingly
                int dice = rollDice();
                movePlayer(player, dice);
                // Check if the game is over after this move
                if (isGameOver()) {
                    break;
                }
            }
        }
    }
};

// The main function
int main() {
    // Initialize the random seed
    srand(time(NULL));
    // Create a game object with user input
    Game game;
    // Play the game until it is over
    game.playGame();
    return 0;
}

//Example Input
//4
//10
//10
//5
//10 2
//19 3
//25 4
//45 6
//75 8
//2
//11 80
//12 95