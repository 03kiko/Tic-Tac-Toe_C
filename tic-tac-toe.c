#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


char board[3][3];
const char PLAYER ='X';
const char COMPUTER = 'O';


// Functions we're going to use
void resetBoard();
void printBoard();
int checkFreeSpaces(); 
void playerMove();
void computerMove();
char checkWinner();
void annouceWinner(char);


int main(){
    char winner = ' ';
    char response = ' ';
    do {
        winner = ' ';
        response = ' ';

        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0){
            printBoard();
        
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0){
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0){
                break;
            }

        }

        printBoard();
        annouceWinner(winner);

        printf("\n Would you like to play again? (Y/N):");
        scanf("%c"); // clearing buffer
        scanf("%c", &response);
        response = toupper(response); // Also accept 'y' as response
    } while(response == 'Y');

    printf("Thanks for playing!");
    
    return 0;
}

// Empties the board
void resetBoard(){ 
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            board[r][c] = ' ';
        }
    }
}

// Prints the board.
void printBoard(){
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Used to check if the game is over. No free spaces means the game is over. (Assuming no winner)
int checkFreeSpaces(){ 
    int freeSpaces = 9;

    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (board[r][c] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces; 
}

// Asks the player for a move
void playerMove(){
    int row;
    int column;

    do {
        printf("Enter a row number (1 to 3): ");
        scanf("%i", &row); // Address it to the row variable
        printf("Enter a column number (1 to 3): ");
        scanf("%i", &column);

        row--;
        column--; // Decrement the values since the arrays start with 0...
        
        // Check if the position is already ocupied
        if (board[row][column] != ' '){
            printf("Invalid move!\n");
        } else{
            board[row][column]= PLAYER;
            break;
        }
    } while (board[row][column] != ' ');

}

void computerMove(){
    srand(time(0));
    int row;
    int column;

    if (checkFreeSpaces() > 0) {
        do {
            row = rand() % 3; 
            column = rand() % 3; // number between 0 and 2
        } while(board[row][column] != ' ');

        board[row][column] = COMPUTER;
    } else {
        annouceWinner(' ');
    }
}

char checkWinner() {
    // Check rows
    for (int row = 0; row < 3; row++){
        if (board[row][0] == board[row][1] && board[row][0]==board[row][2]){
            return board[row][0]; // Returns the character (X or O)
        }
    }

    // Check columns
    for (int column = 0; column < 3; column++){
        if (board[0][column] == board[1][column] && board[0][column]==board[2][column]){
            return board[0][column]; // Returns the character (X or O)
        }
    }

    // Check diags
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        return board[1][1];
    }

    // No winner
    return ' ';
}

void annouceWinner(char winner){
    if(winner == PLAYER) {
        printf("YOU WIN!");
    } else if (winner == COMPUTER){
        printf("YOU LOSE!");
    }else{
        printf("IT'S A TIE!");
    }
}