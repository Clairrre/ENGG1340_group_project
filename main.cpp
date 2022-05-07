#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

const int N = 15;       //15*15 Chessboard
const char ChessBoard = ' ';  //Chessboard Sign
const char flag1 = 'o';    //Player 1 or computer logo
const char flag2 = 'x';    //Player 2 logo

typedef struct Position{    //Coordinate
    int row;        //Row
    int col;        //Column
}Position;

class GoBang{     //Backgammon
private:
    char _ChessBoard[N + 1][N + 1];    //Chessboard
public:
    GoBang(){
        InitChessBoard();      //Initialize the board
    }
    void Play(){      //Play chess
        Position Play1;   //Player 1 or Computer
        Position Play2;   //Player 2
        while (1){
            int mode = ChoiceMode();
            while (1){
                if (mode == 1){       //Computer vs Player
                    ComputerChess(Play1, flag1);            //Computer plays chess
                    if (GetVictory(Play1, 0, flag1)){       //0 for the computer, true for the computer to win
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //Player 2 plays chess
                    if (GetVictory(Play2, 2, flag2)){       //2 for player 2
                        break;
                    }
                }
                else{               //Player 1 vs Player 2
                    PlayChess(Play1, 1, flag1);         //Player 1 plays chess
                    if (GetVictory(Play1, 1, flag1)){       //Player 1 wins
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //Player 2 plays chess
                    if (GetVictory(Play2, 2, flag2)){       //Player 2 wins
                        break;
                    }
                }
            }
            cout << "======One More Round=======" << endl;
            cout << "yes or no :";
            char s[] = "yes";
            save();
            cin >> s;
            if (strcmp(s, "no") == 0){
                break;
            }
        }
    }

protected:
    void InitChessBoard(){          //Initialize the board
        for (int i = 0; i < N + 1; ++i){
            for (int j = 0; j < N + 1; ++j){
                _ChessBoard[i][j] = ChessBoard;
            }
        }
    }

    int ChoiceMode(){           //Mode Selection
        system("cls");
        //system call, clear screen
        InitChessBoard();       //Reinitialize the board
        cout << "*************************************************" << endl;
        cout << "******************0、Quit************************" << endl;
        cout << "******************1、Computer vs Player******************" << endl;
        cout << "******************2、Player vs Player******************" << endl;
        cout << "*************************************************" << endl;
        while (1){
            int i = 0;
            cout << "Please select a mode: ";
            cin >> i;
            if (i == 0){       //Quit
                exit(1);
            }
            if (i == 1 || i == 2){
                return i;
            }
            else{
                cout << "Illegal input, please re-enter!" << endl;
            }
        }
    }

    void PrintChessBoard(){        //print checkerboard
        printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
        printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        for (int i = 1; i < N + 1; ++i)
        {
            printf("%2d ", i);
            printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", _ChessBoard[i][1], _ChessBoard[i][2], _ChessBoard[i][3], _ChessBoard[i][4], _ChessBoard[i][5], _ChessBoard[i][6], _ChessBoard[i][7], _ChessBoard[i][8], _ChessBoard[i][9], _ChessBoard[i][10], _ChessBoard[i][11], _ChessBoard[i][12], _ChessBoard[i][13], _ChessBoard[i][14], _ChessBoard[i][15]);
            printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        }
        cout << endl;
    }

    void ComputerChess(Position& pos, char flag){     //Computer Chess
        //PrintChessBoard();      //Print Chessboard
        int x = 0;
        int y = 0;
        while (1){                    //Loop to find empty locations
            x = (rand() % N) + 1;      //Generate random numbers from 1 to N
            srand((unsigned int)time(NULL));
            y = (rand() % N) + 1;      //Generate random numbers from 1 to N
            srand((unsigned int)time(NULL));
            if (_ChessBoard[x][y] == ChessBoard){       //If this position is empty (no pawn), break out of the loop and play chess
                break;
            }
        }
        pos.row = x;
        pos.col = y;
        _ChessBoard[pos.row][pos.col] = flag;
    }

    void PlayChess(Position& pos, int player, char flag){
        PrintChessBoard();      //Print Chessboard
        while (1){
            printf("Please Player %d enter the coordinate：", player);
            cin >> pos.row >> pos.col;
            if (JudgeValue(pos) == 1){        //Determine whether the coordinates are legal
                break;
            }
            cout << "The coordinates are invalid, please re-enter:" << endl;
        }
        _ChessBoard[pos.row][pos.col] = flag;
    }

    int JudgeValue(const Position& pos){       //Judging the legitimacy of coordinates
        //1.On the Chessboard
        if (pos.row > 0 && pos.row <= N && pos.col > 0 && pos.col <= N){
            //2.The position is empty (no pawns）
            if (_ChessBoard[pos.row][pos.col] == ChessBoard){
                return 1;      //legitimate
            }
        }
        return 0;       //illegal
    }

    int JudgeVictory(Position pos, char flag){     //Judging whether a player wins (bottom judgment)
        int begin = 0;
        int end = 0;

        //1.Determine if a row satisfies a condition
        (pos.col - 4) > 0 ? begin = (pos.col - 4) : begin = 1;
        (pos.col + 4) > N ? end = N : end = (pos.col + 4);
        for (int i = pos.row, j = begin; j + 4 <= end; ++j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i][j + 1] == flag &&
            _ChessBoard[i][j + 2] == flag && _ChessBoard[i][j + 3] == flag &&
            _ChessBoard[i][j + 4] == flag)
                return 1;
        }
        //2.Check if a column satisfies a condition
        (pos.row - 4) > 0 ? begin = (pos.row - 4) : begin = 1;
        (pos.row + 4) > N ? end = N : end = (pos.row + 4);
        for (int j = pos.col, i = begin ; i + 4 <= end; ++i){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j] == flag &&
            _ChessBoard[i + 2][j] == flag && _ChessBoard[i + 3][j] == flag &&
            _ChessBoard[i + 4][j] == flag)
                return 1;
        }
        //3.Determine whether the main diagonal meets the condition
        int len = 0;    //relative length
        int start = 0;
        int finish = 0;
        pos.row > pos.col ? len = pos.col - 1 : len = pos.row - 1;
        if (len > 4){
            len = 4;
        }
        begin = pos.row - len;       //abscissa start position
        start = pos.col - len;       //The starting position of the ordinate

        pos.row > pos.col ? len = N - pos.row : len = N - pos.col;
        if (len > 4){
            len = 4;
        }
        end = pos.row + len;         //abscissa end position
        finish = pos.col + len;      //The end position of the ordinate

        for (int i = begin, j = start; (i + 4 <= end) && (j + 4 <= finish); ++i, ++j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j + 1] == flag &&
            _ChessBoard[i + 2][j + 2] == flag && _ChessBoard[i + 3][j + 3] == flag &&
            _ChessBoard[i + 4][j + 4] == flag)
                return 1;
        }
        //4.Determine whether the subdiagonal meets the condition
        (pos.row - 1) > (N - pos.col) ? len = N - pos.col : len = pos.row - 1;
        if (len > 4){
            len = 4;
        }
        begin = pos.row - len;       //abscissa start position
        start = pos.col + len;       //The starting position of the ordinate

        (N - pos.row) > (pos.col - 1) ? len = pos.col - 1 : len = N - pos.row;
        if (len > 4){
            len = 4;
        }
        end = pos.row + len;         //abscissa end position
        finish = pos.col - len;      //The end position of the ordinate
        for (int i = begin, j = start; (i + 4 <= end) && (j - 4 >= finish); ++i, --j){
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j - 1] == flag &&
            _ChessBoard[i + 2][j - 2] == flag && _ChessBoard[i + 3][j - 3] == flag &&
            _ChessBoard[i + 4][j - 4] == flag)
                return 1;
        }
        //The position is not playing chess
        for (int x = 1; x < N + 1; ++x){
            for (int y = 1; y < N + 1; ++y){
                if (_ChessBoard[x][y] == ChessBoard){
                    return 0;       //Not playing chess
                }
            }
        }
        return -1;      //Tie
    }

    bool GetVictory(Position& pos, int player, char flag){       //Determine which player wins
        if (JudgeVictory(pos, flag) != 0){    //Judging if there is a winner
            if (JudgeVictory(pos, flag) == 1){     //Determine whether someone wins, 1 means winning
                PrintChessBoard();     //Print Chessboard
                if (player == 0){
                    cout << "Computer Wins！" << endl;
                }
                else{
                    printf("Congratulations to Player %d for winning！\n", player);
                }
            }
            else{
                printf("Tie！\n");
            }
            return true;      //Someone Wins
        }
        return false;         //No One Wins
    }

public:
    void save(){
        ofstream fout;
        fout.open("/Users/ericli/CLionProjects/game/data.txt");

        if ( fout.fail() ) {
            cout << "Error in file opening!"     << endl;
            exit(1);
        }
        for (int i = 0; i < N+1; i++) {
            for (int j = 0; j < N+1; j++) {
                fout << _ChessBoard[i][j] << " " ;
            }
            fout<<endl;
        }
        fout.close();

}

};

int main(){
    GoBang g;
    g.Play();
    g.save();

    system("pause");
    return 0;
}