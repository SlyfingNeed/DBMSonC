#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

void resetBoard(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(){

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}

int checkFreeSpaces(){
    int freeSpaces = 9;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove(){
    int x;
    int y;

    do{
        printf("Masukkan baris (1-3): ");
        scanf("%d", &x);
        x--;
        printf("Masukkan kolom (1-3): ");
        scanf("%d", &y);
        y--;
        printf("\n");
        if(board[x][y] !=' '){
            printf("Pilihan tidak valid\n");
            printf("\n");
        }    
        else{
            board[x][y] = PLAYER;
            break;
        }
    } while(board[x][y] != ' ');
}

void computerMove() {
    srand(time(NULL));
    int x, y;

    // Cek apakah komputer bisa blok posisi pemain
    for (int i = 0; i < 3; i++) {
        // Cek baris dan kolom
        for (int j = 0; j < 3; j++) {
            // Cek baris i
            if ((board[i][(j+1)%3] == board[i][(j+2)%3] && board[i][(j+1)%3] == COMPUTER && board[i][j] == ' ') || 
                (board[i][(j+1)%3] == board[i][(j+2)%3] && board[i][(j+1)%3] == PLAYER && board[i][j] == ' ')) {
                x = i;
                y = j;
                board[x][y] = COMPUTER;
                return;
            }

            // Cek kolom j
            if ((board[(i+1)%3][j] == board[(i+2)%3][j] && board[(i+1)%3][j] == COMPUTER && board[i][j] == ' ') ||
                (board[(i+1)%3][j] == board[(i+2)%3][j] && board[(i+1)%3][j] == PLAYER && board[i][j] == ' ')) {
                x = i;
                y = j;
                board[x][y] = COMPUTER;
                return;
            }
        }
    }

    // Cek Diagonal
    if ((board[0][0] == board[1][1] && board[0][0] == COMPUTER && board[2][2] == ' ') || 
        (board[0][2] == board[1][1] && board[0][2] == COMPUTER && board[2][0] == ' ')) {
        x = 2;
        y = 2;
        board[x][y] = COMPUTER;
        return;
    }
    if ((board[0][2] == board[1][1] && board[0][2] == PLAYER && board[2][0] == ' ') ||
        (board[2][0] == board[1][1] && board[2][0] == PLAYER && board[0][2] == ' ')) {
        x = 0;
        y = 2;
        board[x][y] = COMPUTER;
        return;
    }

    // If no strategic move is found, choose a random empty space
    do {
        x = rand() % 3;
        y = rand() % 3;
        
    } while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
}


char checkWinner(){
    // Cek baris
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }

    // Cek kolom
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    //check diagonal
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }
    return ' ';
}

int playerWin = 0;
int computerWin = 0;
int tie = 0;
void matchRecord(char winner) {
    if(winner == PLAYER){
        playerWin++;
    }
    else if(winner == COMPUTER){
        computerWin++;
    }
    else{
        tie++;
    }
}

void printWinner(char winner) {
    matchRecord(winner);
    FILE *file;
    file = fopen("record.txt", "a");
    if (file == NULL){
        printf("Eror saat membuka record.txt\n");
        exit(1);
    }
    if(winner == PLAYER){
        printf("\n\t --- Game Over --- \n");
        printf("  *** Selamat anda menang! ***\n");
        printf(":: Terimakasih sudah bermain :: \n");
    }
    else if(winner == COMPUTER){
        printf("\n\t --- Game Over --- \n");
        printf("  *** Maaf, anda kalah ***\n");
        printf(":: Terimakasih sudah bermain :: \n");
    }
    else{
        printf("\n\t --- Game Over --- \n");
        printf("  *** Game berakhir imbang ***\n");
        printf(":: Terimakasih sudah bermain :: \n");
    }
    printf("Riwayat pertandingan\nPlayer: %d, Komputer: %d, Seri: %d", playerWin, computerWin, tie);
    fprintf(file, "Player: %d, Komputer: %d, Seri: %d\n", playerWin, computerWin, tie);
    fclose(file);
}

int main(){
    char playAgain = 'y';
    while(playAgain == 'y'){

        printf("\n\n");
        printf("****************************************************\n");
        printf("         Program TicTacToe di C                     \n");
        printf("****************************************************\n");
        printf("\n* Instruksi \n\n");
        printf("\tSimbol Pemain 1 = X\n");
        printf("\tSimbol Pemain 2 = O\n\n");
        char winner = ' ';

        resetBoard();
        while(winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }

            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
        }

        printBoard();
        printWinner(winner);

        printf("\nApakah Anda ingin bermain lagi? (y/n): ");
        scanf(" %c", &playAgain);
        }

    printf("\nTerimakasih sudah bermain!");
    return 0;
    }
