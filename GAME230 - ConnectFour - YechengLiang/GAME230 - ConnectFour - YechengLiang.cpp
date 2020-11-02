//Author Yecheng Liang
#include <iostream>
#include <time.h>

using namespace std;

const int DIRECTION[8][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
bool WarpAroundMode = false;
bool pullMode = false;
bool PvPMode = false;
int winLenght = 4;

//Ask user for a number
//Repeat until a vaild number greater than 0
int InputNumber(int min, int max) {
    int result = min -1;
    while (result < min || result > max) {
        cin >> result;
        if (cin.fail() || result < min || result > max) {
            cout << "Please enter a valid number!" << endl;
            result = min - 1;
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
    }
    return result;
}

//Gu
void AIMove(int** board, int row, int column) {
    while (true) {
        int t = rand() % column;
        if (board[0][t] == 0) {
            for (int i = row - 1; i >= 0; i--)
                if (board[i][t] == 0) {
                    board[i][t] = 2;
                    return;
                }
        }
    }
}

//Check wether we have a winner
bool CheckWin(int** board, int row, int column, int x, int y, int d, int step) {
    if (step >= winLenght) return true;
    int dx = x + DIRECTION[d][0];
    int dy = y + DIRECTION[d][1];
    if (WarpAroundMode) {
        if (dy < 0) dy = column - 1;
        if (dy >= column) dy = 0;
    }
    if (dx >= 0 && dx < row && dy >= 0 && dy < column && board[dx][dy] == board[x][y])
        return CheckWin(board, row, column, dx, dy, d, step + 1);
    return false;
}

bool CheckWin(int** board, int row, int column, int player) {
    for (int i = 0; i < row; i ++)
        for (int j = 0; j < column; j++) {
            if (board[i][j] == player) {
                for (int k = 0; k < 8; k++) {
                    if (CheckWin(board, row, column, i, j, k, 1))
                        return (board[i][j] == player);
                }
            }
        }
    return 0;
}

bool CheckWin(int** board, int row, int column) {
    bool p1 = CheckWin(board, row, column, 1);
    bool p2 = CheckWin(board, row, column, 2);

    if (p1 && p2) {
        cout << "Draw!" << endl;
        return true;
    } else if (p1 || p2) {
        if (PvPMode)
            cout << "Player 2 Won" << endl;
        else
            cout << "AI Player Won" << endl;

        return true;
    }
    return false;
}

//number of digit
//Useful when there are more than 10 column
int NumberOfDigits(int number) {
    int i = 0;
    if (number == 0) return 1;
    while (number > 0) {
        number /= 10;
        i++;
    }
    return i;
}

char Sign(int t) {
    if (t == 0) return '.';
    else if (t == 1) return 'O';
    else return 'X';
}

void PrintBoard(int** board, int row, int column) {
    cout << endl;

    int length = 0;
    for (int i = 0; i < column; i++) {
        cout << i;
        length++;
        for (int k = 0; k < (NumberOfDigits(column) - NumberOfDigits(i) + 1); k++) {
            length++;
            cout << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << Sign(board[i][j]);
            for (int k = 0; k < (NumberOfDigits(column)); k++)
                cout << " ";
        }
        cout << endl;
    }

    cout << endl;
}

bool PullFrom(int** board, int row, int y) {
    if (board[row - 1][y] == 0)
        return false;
    else {
        for (int i = row - 1; i > 0; i--)
            board[i][y] = board[i - 1][y];
        board[0][y] = 0;
        return true;
    }
}

void ResetBoard(int** board, int row, int column) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            board[i][j] = 0;
}

bool Confirmation(string text) {
    while (true) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        cout << text << endl;
        char input = ' ';
        cin >> input;
        if (input == 'y' || input == 'Y')
            return true;
        else if (input == 'n' || input == 'N') {
            return false;
        }
    }
}

//wait and check for player input
void playerMove(int** board, int row, int column, int player) {
    cout << "Player" << player << "s Turn:" << endl;
    bool pull = false;

    while (true) {
        if (pullMode)
            pull = Confirmation("Pull or Add Piece? Y for Pull / N for Add");
        int input = InputNumber(0, column - 1);

        if (pull) {
            if (PullFrom(board, row, input))
                return;
        } else {
            for (int i = row - 1; i >= 0; i--) {
                if (board[i][input] == 0) {
                    board[i][input] = player;
                    cout << "Setting:" << input << "," << i << endl;
                    return;
                }
            }
        }

        cout << "Please enter a valid Move!" << endl;
        cout << endl;
    }
}

int main(){

    srand(time(NULL));
    cout << "Push Four!" << endl;

    cout << "Please enter the number of Row:" << endl;
    int row = InputNumber(4, 20);

    cout << "Please enter the number of column:" << endl;
    int column = InputNumber(4, 20);

    cout << "Please enter length required to Win" << endl;
    winLenght = InputNumber(3, 20);

    PvPMode = Confirmation("Player vs Player Mode? Y / N");
    pullMode = Confirmation("Pull mode? Y / N");
    WarpAroundMode = Confirmation("Warp Around Mode? Y / N");


    int** board;
    board = new int*[row];
    for (int i = 0; i < row; i++)
        board[i] = new int[column];

    ResetBoard(board, row, column);

    bool gameOver = false;
    int winner = false;
    

    //Game loop
    while (!gameOver) {

        PrintBoard(board, row, column);
        playerMove(board, row, column, 1);
        gameOver = CheckWin(board, row, column);

        if (!gameOver) {
            if (PvPMode) {
                PrintBoard(board, row, column);
                playerMove(board, row, column, 2);
            } else
                AIMove(board, row, column);

            gameOver = CheckWin(board, row, column);
        }


        //Check for draw
        bool full = true;
        for (int i = 0; i < column; i++)
            if (board[0][i] == 0) full = false;
        if (full) {
            gameOver = true;
            cout << "Draw!" << endl;
        }

        if (gameOver) {
            PrintBoard(board, row, column);
            bool result = Confirmation("Play Again? Y/N");
            if (result) {
                ResetBoard(board, row, column);
                gameOver = false;
            }
        }
    }

    for (int i = 0; i < row; i++) {
        delete[] board[i];
        board[i] = NULL;
    }
    delete[] board;
    board = NULL;

    return 0;
}
